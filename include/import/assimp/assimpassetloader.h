#ifndef _ASSIMP_ASSET_LOADER_
#define _ASSIMP_ASSET_LOADER_ 

#include "common.h"
#include "import/assetloader.h"
#include "material.h"
#include "Skeleton.h"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

namespace raytracer {

	struct AssimpBone
	{
		aiBone *mBone;

		AssimpBone(aiBone *bone) : mBone(bone) {};
	};

	class AssimpAssetLoader: public AssetLoader
	{

	protected:
		meshptr_type buildMesh(const aiNode &node);
		void recursiveBuild(const aiNode *node, aiMatrix4x4 worldSpace);
		void processNode(const aiNode *node, aiMatrix4x4 worldSpace);
		submeshptr_type buildSubMesh(const aiNode *node, int mMeshes_index, aiMatrix4x4 &worldSpace);
		std::string createMaterialName(unsigned int materialIndex);
		Material* getMaterial(unsigned int materialIndex);
		Texture* getTexture(aiTextureType type, const aiMaterial &ai_mat);

		inline void AssertAssetOpen()
		{
			CGUTILS_ASSERT(mScene != NULL)
		}


		Skeleton* createSkeleton(const aiNode &node);
		void aggregateBones(const aiNode &node);
		void logNodes(const aiNode &node, int degree);
		aiNode* findSkeletonRoot(const aiNode &meshRoot);
		void buildSkeletonFromSubTree(Bone *bone, const aiNode *node);

	public:

		AssimpAssetLoader() : mScene(NULL), mOpenFile("") {}
		virtual ~AssimpAssetLoader();

		virtual bool open(const std::string& path);
		virtual meshptr_type loadMeshByName(const std::string name);

	private:
		Assimp::Importer mImporter;
		const aiScene* mScene;
		std::string mOpenFile;
		std::string mParentPath;

		meshptr_type mCurrentMesh;
		Skeleton *mCurrentSkeleton;

		typedef std::list<AssimpBone> AssimpBoneList;
		AssimpBoneList mBones;
	};

} /* raytracer */
	
#endif /* _ASSIMP_ASSET_LOADER_ */
