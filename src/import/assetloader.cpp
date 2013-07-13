#include "import/assetloader.h"
#include <memory>
#include <regex>

using namespace std;

namespace raytracer {

	std::unique_ptr<AssetLoader> AssetLoaderFactory::getReaderForFilename(const string &filename)
	{

		if (std::regex_match (filename, std::regex(".*\\.obj") ) ||
			std::regex_match (filename, std::regex(".*\\.3ds") ) ||
			std::regex_match (filename, std::regex(".*\\.dae") ) ||
			std::regex_match (filename, std::regex(".*\\.blend") ) ||
			std::regex_match (filename, std::regex(".*\\.mesh.xml") ))
		{
			return unique_ptr<AssimpAssetLoader>(new AssimpAssetLoader());
		}
		else
		{
			return NULL;
		}
	}

} /* namespace raytracer */
