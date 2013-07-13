#include "mesh.h"

namespace raytracer {

	void HardwareSubMesh::setGeoBuffers(HardwareBuffer *verts, HardwareBuffer *faces)
	{
		mVertHWBuffer = verts;
		mFaceHWBuffer = faces;
	}
	
	void HardwareSubMesh::setUVBuffer(HardwareBuffer *uvs)
	{
		mUVHWBuffer = uvs;
	}
	
	void HardwareSubMesh::setNormalBuffer(HardwareBuffer *normals)
	{
		mNormalBuffer = normals;
	}

} /* namespace raytracer */
