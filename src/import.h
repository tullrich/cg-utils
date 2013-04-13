#ifndef _IMPORT_H
#define _IMPORT_H

#include "cgutils.hpp"

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

namespace cgutils
{

class AssimpAssetImporter 
{
public:
	AssimpAssetImporter();

	/**
	 * Read a file on disk into memory. Memory will be cleaned
	 * up when AssimpAssetImporter is destructed.
	 * 
	 * @param  path Path to the file ond disk
	 * @return      True if file was found and read correctly. 
	 */
	bool ImportFromFile(const std::string& path);

protected:
	Assimp::Importer importer;
	const aiScene* scene;
};

} /* namespace cgutils*/
#endif /* _IMPORT_H */