#include "mesh.h"

namespace raytracer {

	void HardwareMesh::addSubMesh(HardwareSubMesh *submesh)
	{
		mSubMeshes.push_back(submesh);
	}
	

	Mesh::SubMeshIterator HardwareMesh::getSubMeshIterator()
	{
		return SubMeshIterator(mSubMeshes.begin(), mSubMeshes.end());
	}

} /* namespace raytracer */
