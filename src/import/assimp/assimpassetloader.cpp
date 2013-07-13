#include "import/assimp/assimpassetloader.h"
#include "import/assimp/assimphelpers.h"

namespace raytracer {

	AssimpAssetLoader::~AssimpAssetLoader()
	{
		mBones.clear();
		if (mScene)
		{
			mScene = NULL;
			mImporter.FreeScene();
		}
	}

	AssetLoader::meshptr_type AssimpAssetLoader::buildMesh(const aiNode &node)
	{
		mCurrentMesh = createMeshImpl(node.mName.C_Str());

		aiVector3D pos, scl;
 		aiQuaternion rot;
 		aiMatrix4x4 worldSpace;
		worldSpace.Decompose(scl, rot, pos);
		glm::vec3 position(pos.x, pos.y, pos.z);
		glm::quat rotation(rot.w, rot.x, rot.y, rot.z);
		glm::vec3 scale(scl.x, scl.y, scl.z);
		setTransformImpl(mCurrentMesh, position, rotation, scale);
		//logNodes(node, 0);

		//mCurrentSkeleton = createSkeleton(node);

		recursiveBuild(&node, worldSpace);

		return mCurrentMesh;
	}

	Skeleton* AssimpAssetLoader::createSkeleton(const aiNode &node)
	{
		Skeleton *skel = NULL;

		mBones.clear();
		aggregateBones(node);
		if(mBones.size() !=  0)
		{
			aiNode *skeletonRootNode = findSkeletonRoot(node);
			skel = new Skeleton(AssimpHelpers::aiNodeToBone(skeletonRootNode));

			buildSkeletonFromSubTree(skel->getRoot(), skeletonRootNode);
			std::cout << "found " << mBones.size() << " bones" << std::endl; 
			std::cout << "Skeleton Root Node: " << skeletonRootNode->mName.C_Str()  << std::endl;

			skel->getRoot()->debugPrintTree();
		}

		return skel;
	}

	void AssimpAssetLoader::buildSkeletonFromSubTree(Bone *bone, const aiNode *node)
	{
		for(int c = 0; c < node->mNumChildren; c++)
		{
			Bone *childBone = AssimpHelpers::aiNodeToBone(node->mChildren[c]);
			bone->attachChild(childBone);
			buildSkeletonFromSubTree(childBone, node->mChildren[c]);
		}
	}

	aiNode* AssimpAssetLoader::findSkeletonRoot(const aiNode &meshRoot)
	{
		aiNode *bestFound = NULL;
		int bestDegree = 0;
		const aiNode *possibleRoot = (meshRoot.mParent) ? meshRoot.mParent : &meshRoot;

		AssimpBoneList::iterator i = mBones.begin();
		for(; i != mBones.end(); i++)
		{
			aiNode *node = mScene->mRootNode->FindNode((*i).mBone->mName);

			if(node)
			{
				int degree = AssimpHelpers::nodeDegreeFromRoot(possibleRoot, node);
				if(!bestFound || degree < bestDegree)
				{
					bestFound = node;
					bestDegree = degree;
				}
			}
			else
			{
				std::cout << "error bad bone name " << (*i).mBone->mName.C_Str() << std::endl; 
			}
		}

		return bestFound;
	}

	void AssimpAssetLoader::logNodes(const aiNode &node, int degree)
	{
		for(int i = 0; i < degree; i++)
			std::cout << "\t";

		std::cout << "'" << node.mName.C_Str() 
			<< "' { numMeshes: " << node.mNumMeshes << " }" << std::endl; 

		for(int c = 0; c < node.mNumChildren; c++)
		{
			logNodes(*node.mChildren[c], degree + 1);
		}
	}

	void AssimpAssetLoader::aggregateBones(const aiNode &node)
	{
		for(int m = 0; m < node.mNumMeshes; m++)
		{
			aiMesh *mesh = mScene->mMeshes[node.mMeshes[m]];

			if(!mesh)
			{
				std::cout << "Bad mesh index from node" << std::endl; 
				continue;
			}

			if(mesh->HasBones())
			{
				std::cout << "got a skeleton" << std::endl;
				for (int i = 0; i < mesh->mNumBones; ++i)
				{
					aiBone *bone = mesh->mBones[i];
					std::cout << "\tBone: " << bone->mName.C_Str() 
						<< " mNumWeights: " << bone->mNumWeights << std::endl;

					aiNode *boneNode = mScene->mRootNode->FindNode(bone->mName);
					if(boneNode)
					{
						std::cout << "\tboneNode" <<  boneNode->mName.C_Str() << std::endl;
						mBones.push_back(AssimpBone(bone));
					}
					else
					{
						std::cout << "Error could not find Node in heirarchy for bone " 
							<< bone->mName.C_Str() << std::endl; 
					}
				}
			}
		}

		for(int c = 0; c < node.mNumChildren; c++)
		{
			aggregateBones(*node.mChildren[c]);
		}
	}

	void AssimpAssetLoader::recursiveBuild(const aiNode *node, aiMatrix4x4 worldSpace)
	{
		if(node == NULL)
			return;

		processNode(node, worldSpace);

		// iterate child nodes
		aiMatrix4x4 worldNodeTransform = worldSpace * node->mTransformation;
		for (int i = 0; i < node->mNumChildren; i++)
		{
			aiNode *child = node->mChildren[i];
			recursiveBuild(child, worldNodeTransform);
		}
	}

	void AssimpAssetLoader::processNode(const aiNode *node, aiMatrix4x4 worldSpace)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			submeshptr_type subMesh = buildSubMesh(node, i, worldSpace);
			addSubMeshImpl(mCurrentMesh, subMesh);
		}
	}

	std::string AssimpAssetLoader::createMaterialName(unsigned int materialIndex)
	{
		return "AssimpMaterial_" + mOpenFile + "_" + std::to_string(materialIndex);
	}

	Texture* AssimpAssetLoader::getTexture(aiTextureType type, const aiMaterial &ai_mat)
	{
		Texture *t = NULL;

		if (ai_mat.GetTextureCount(type) > 0)
		{
			aiString tex_name;
			ai_mat.GetTexture(type, 0, &tex_name, NULL, NULL, NULL, NULL, NULL);
			std::cout << tex_name.C_Str() << std::endl; 
			if (tex_name.length)
			{
				std::string filename = appendFilename(mParentPath, tex_name.C_Str());

				t = TextureManager::getInstance().get(filename);
				if(!t)
				{
					t = createTextureImpl(filename);
					TextureManager::getInstance().add(filename, *t);
				}
			}
		}

		return t;
	}

	Material* AssimpAssetLoader::getMaterial(unsigned int materialIndex)
	{
		string materialName = createMaterialName(materialIndex);
		Material *m = MaterialManager::getInstance().get(materialName);

		// have we prepared this material already
		if (m == NULL)
		{
			const aiMaterial &ai_mat = *(mScene->mMaterials[materialIndex]);

			aiString name;
			ai_mat.Get(AI_MATKEY_NAME, name);

			m = new Material(name.C_Str());
			if (AssimpHelpers::matUsesTextures(ai_mat))
			{
				// this material has some textures, set them up
				// but defer load() till later
				m->setDiffuseTexture(getTexture(aiTextureType_DIFFUSE, ai_mat));
				m->setSpecularTexture(getTexture(aiTextureType_SPECULAR, ai_mat));
				m->setEmissiveTexture(getTexture(aiTextureType_EMISSIVE, ai_mat));
				m->setEmissiveTexture(getTexture(aiTextureType_AMBIENT, ai_mat));
				m->setNormalTexture(getTexture(aiTextureType_NORMALS, ai_mat));
			}

			// copy all the properties we want
			m->setDiffuse(AssimpHelpers::matPropertyToRGB(ai_mat, AI_MATKEY_COLOR_DIFFUSE));
			m->setAmbient(AssimpHelpers::matPropertyToRGB(ai_mat, AI_MATKEY_COLOR_AMBIENT));
			m->setSpecular(AssimpHelpers::matPropertyToRGB(ai_mat, AI_MATKEY_COLOR_SPECULAR));
			m->setEmissive(AssimpHelpers::matPropertyToRGB(ai_mat, AI_MATKEY_COLOR_EMISSIVE));
			std::cout << "ai_mat.GetTextureCount(aiTextureType_EMISSIVE) " << ai_mat.GetTextureCount(aiTextureType_EMISSIVE)  << std::endl; 
			std::cout << "SHIIINE " << AssimpHelpers::matPropertyToFloat(ai_mat, AI_MATKEY_SHININESS)  / 4.0f << std::endl; 
			// see http://comments.gmane.org/gmane.comp.lib.assimp.general/238
			m->setShininess(AssimpHelpers::matPropertyToFloat(ai_mat, AI_MATKEY_SHININESS) / 4.0f); // 

			MaterialManager::getInstance().add(materialName, *m);
		}

		return m;
	}

	AssetLoader::submeshptr_type AssimpAssetLoader::buildSubMesh(const aiNode *node, int mMeshes_index, aiMatrix4x4 &worldSpace)
	{
		unsigned int mesh_index = node->mMeshes[mMeshes_index];
		aiMesh *ai_mesh = mScene->mMeshes[mesh_index];
		
		// create the submesh
		submeshptr_type submesh = createSubMeshImpl(node->mName.C_Str());

		// copy the verts to memory managed by us
		std::vector<Vertex> verts(ai_mesh->mNumVertices);
		AssimpHelpers::copyAiVector3DToGLM(verts.data(), ai_mesh->mNumVertices, ai_mesh->mVertices);

		// copy the face indices to memory managed by us
		Face faces[ai_mesh->mNumFaces];
		AssimpHelpers::copyAiFaceToGLM(faces, ai_mesh->mNumFaces, ai_mesh->mFaces);

		// create the material
		Material *mat = getMaterial(ai_mesh->mMaterialIndex);
		setSubMeshMaterialImpl(submesh, mat);

		setSubMeshGeometryImpl(submesh, verts.data(), ai_mesh->mNumVertices, faces, ai_mesh->mNumFaces);
		if(ai_mesh->GetNumUVChannels() > 0 && ai_mesh->mNumUVComponents[0] == 2) 
		{
			// we only support 2 component texture lookups on texture 0
			// copy the verts to memory managed by us
			std::vector<TexCoord> uvs(ai_mesh->mNumVertices);
			AssimpHelpers::copyAiTexCoordToGLM(uvs.data(), ai_mesh->mNumVertices, ai_mesh->mTextureCoords[0]);
			setSubMeshUVsImpl(submesh, uvs.data(), ai_mesh->mNumVertices);
		}

		// if we have normals, grab them too
		if(ai_mesh->HasNormals())
		{
			std::vector<Vertex> normals(ai_mesh->mNumVertices);
			AssimpHelpers::copyAiVector3DToGLM(normals.data(), ai_mesh->mNumVertices, ai_mesh->mNormals);
			setSubMeshNormalsImpl(submesh, normals.data(), ai_mesh->mNumVertices);
		}

/*		// process any skeleton
		if(ai_mesh->HasBones())
		{
			std::cout << "got a skeleton" << std::endl;
			for (int i = 0; i < ai_mesh->mNumBones; ++i)
			{
				aiBone *bone = ai_mesh->mBones[i];
				std::cout << "\tBone: " << bone->mName.C_Str() 
					<< " mNumWeights: " << bone->mNumWeights << std::endl;

				aiNode *boneNode = mScene->mRootNode->FindNode(bone->mName);
				if(boneNode)
				{
					std::cout << "\tboneNode" <<  boneNode->mName.C_Str() << std::endl; 
				}
				else
				{
					std::cout << "Error could not find Node in heirarchy for bone " 
						<< bone->mName.C_Str() << std::endl; 
				}
			}
		}*/

		return submesh;
	}

	bool AssimpAssetLoader::open(const std::string& path)
	{

		mScene = mImporter.ReadFile( path, 
			aiProcess_CalcTangentSpace       | 
			aiProcess_Triangulate            |
			aiProcess_JoinIdenticalVertices  |
			aiProcess_SortByPType 			 |
			aiProcess_GenNormals);

		if(mScene == NULL)
		{
			// Assimp couldnt read the file
			std::cout << "Error AssimpAssetLoader Could not open file " << mImporter.GetErrorString() << std::endl; 
			std::cout << "supported extension " << mImporter.IsExtensionSupported(".mesh.xml") << std::endl; 
			return false;
		}

		mOpenFile = path;
		mParentPath = parentPath(mOpenFile);
		return true;
	}

	AssetLoader::meshptr_type AssimpAssetLoader::loadMeshByName(const std::string name)
	{
		AssertAssetOpen();
		
		aiNode *n;
		if(name == "")
			n = mScene->mRootNode;
		else
			n = mScene->mRootNode->FindNode(aiString(name));

		meshptr_type mesh = NULL;
		if(n != NULL)
		{
			std::cout << "found " << name << std::endl;
			mesh = buildMesh(*mScene->mRootNode);
		}
		else
		{
			std::cout << "did not find " << name << std::endl;
		}
		return mesh;
	}

} /* namespace raytracer */
