#include "import/assimp/assimphelpers.h"


namespace raytracer {
namespace AssimpHelpers {

	float matPropertyToFloat(const aiMaterial &ai_mat, const char* pKey, unsigned int type, unsigned int idx)
	{
		float temp = 0;
		ai_mat.Get(pKey, type, idx, temp);
		return temp;
	}

	RGB matPropertyToRGB(const aiMaterial &ai_mat, const char* pKey, unsigned int type, unsigned int idx)
	{
		aiColor3D color (0.f,0.f,0.f); 
		ai_mat.Get(pKey, type, idx, color);
		return RGB(color.r, color.g, color.b);
	}

	bool matUsesTextures(const aiMaterial &ai_mat)
	{
		return ai_mat.GetTextureCount(aiTextureType_DIFFUSE) + 
			ai_mat.GetTextureCount(aiTextureType_SPECULAR) + 
			ai_mat.GetTextureCount(aiTextureType_EMISSIVE) + 
			ai_mat.GetTextureCount(aiTextureType_NORMALS);
	}

	void copyAiVector3DToGLM(Vertex *buf, int numVertices, aiVector3D *verts)
	{
		for (int i = 0; i < numVertices; i++)
		{
			buf[i] = Vertex(verts[i].x, verts[i].y, verts[i].z);
		}
	}

	void copyAiFaceToGLM(Face *buf, int numFaces, aiFace *faces)
	{
		for (int i = 0; i < numFaces; i++)
		{
			aiFace *face = &faces[i];
			if (face->mNumIndices == 3)
			{
				memcpy(&buf[i], face->mIndices, sizeof(Face)); 
			}
			else
			{
				std::cout << "Warning: non triangulated surface" << std::endl; 
			}
		}
	}
	
	void copyAiTexCoordToGLM(TexCoord *buf, int numTexCoords, aiVector3D *txcoords)
	{
		for (int i = 0; i < numTexCoords; i++)
		{
			buf[i] = TexCoord(txcoords[i].x, txcoords[i].y);
		}
	}


	int nodeDegreeFromRoot(const aiNode *root, const aiNode *node)
	{
		if(root == node)
			return 0;

		// this must have a parent
		CGUTILS_ASSERT(node->mParent)

		return 1 + nodeDegreeFromRoot(root, node->mParent);
	}

	Vector3 aiVector3DToGLM(const aiVector3D &vect)
	{
		return Vector3(vect.x, vect.y, vect.z);
	}

	Quaternion aiQuaternionToGLM(const aiQuaternion &quat)
	{
		return Quaternion(quat.w, quat.x, quat.y, quat.z);
	}

	Bone* aiNodeToBone(const aiNode *node)
	{
		aiVector3D scale, translation;
		aiQuaternion orientation;
		node->mTransformation.Decompose(scale, orientation, translation);

		return new Bone(node->mName.C_Str(), aiVector3DToGLM(translation)
			, aiVector3DToGLM(scale), aiQuaternionToGLM(orientation));
	}

	void debugPrintSceneAnimationInfo(const aiScene *scene)
	{
		for(int a = 0; a < scene->mNumAnimations; a++)
		{
			aiAnimation *animation = scene->mAnimations[a];
			std::cout << "Found animation '" << animation->mName.C_Str() 
				<< "'\n\tduration: " << animation->mDuration 
				<< "\n\tticks per second: " << animation->mTicksPerSecond 
				<< "\n\tnumChannels: " << animation->mNumChannels
				<< "\n\tnumMeshChannels: " << animation->mNumMeshChannels << std::endl;

			for(int na = 0; na < animation->mNumChannels; na++)
			{
				aiNodeAnim *nodeAnimation = animation->mChannels[na];
				std::cout << "\t\tNode: '" << nodeAnimation->mNodeName.C_Str() 
				<< "'\n\t\t\tmNumPositionKeys: " << nodeAnimation->mNumPositionKeys 
				<< "\n\t\t\tmNumRotationKeys: " << nodeAnimation->mNumRotationKeys 
				<< "\n\t\t\tmNumScalingKeys: " << nodeAnimation->mNumScalingKeys << std::endl;

				for(int posKey = 0; posKey < nodeAnimation->mNumPositionKeys; posKey++)
				{
					/*std::cout << "Position Key " << posKey << ": (" 
						<< nodeAnimation->mPositionKeys[posKey].mTime 
						<< ", " << AssimpHelpers::aiVector3DToGLM(nodeAnimation->mPositionKeys[posKey].mValue) << ")" << std::endl; */
				}
			}
		}
	}

} /* namespace AssimpHelpers */
} /* namespace raytracer */
