#include "import.h"

namespace cgutils
{


AssimpAssetImporter::AssimpAssetImporter() : scene(NULL)
{

}

bool AssimpAssetImporter::ImportFromFile(const std::string& path)
{

	scene = importer.ReadFile( path, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

	if(scene == NULL)
	{
		// Assimp couldnt read the file
		return false;
	}


	return true;
}

} /* namespace cgutils */