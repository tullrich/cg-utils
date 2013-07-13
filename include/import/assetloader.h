#ifndef _ASSET_LOADER_H_
#define _ASSET_LOADER_H_ 

#include "common.h"
#include "entity.h"

#ifdef MESH_ALLOCATION_STRATEGY_HARDWARE
#include "import/hardwarecreationstrategy.h"
#else
#include "import/clientcreationstrategy.h"
#endif

namespace raytracer {

	template <class AssetCreationStrategy>
	class AssetLoaderBase : public AssetCreationStrategy
	{
	public:
		typedef typename AssetCreationStrategy::mesh_type mesh_type;
		typedef typename AssetCreationStrategy::meshptr_type meshptr_type;

		virtual bool open(const std::string& path) = 0;
		virtual meshptr_type loadMeshByName(const std::string name = "") = 0;
	};

#ifdef MESH_ALLOCATION_STRATEGY_HARDWARE
	typedef HardwareMeshCreationStrategy CompiledCreationStrategy;
#else
	typedef ClientMeshCreationStrategy CompiledCreationStrategy;
#endif
	typedef	AssetLoaderBase<CompiledCreationStrategy> AssetLoader;

	class AssetLoaderFactory
	{
	public:
		static std::unique_ptr<AssetLoader> getReaderForFilename(const string &filename);
	};

} /* namespace raytracer */


#ifdef ASSIMP_ENABLED
	#include "import/assimp/assimpassetloader.h"
#endif
#ifdef FBXSDK_ENABLED
	#include "import/fbxsdk/fbxsdkassetloader.h"
#endif

#endif /* _ASSET_LOADER_H_ */
