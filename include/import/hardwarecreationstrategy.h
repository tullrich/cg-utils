#ifndef _HARDWARE_CREATION_STRATEGY_H_
#define _HARDWARE_CREATION_STRATEGY_H_ 

#include "common.h"
#include "mesh.h"
#include "rendersystem/rendersystem.h"

namespace raytracer {

	class HardwareMeshCreationStrategy
	{
	public:
		typedef HardwareMesh mesh_type;
		typedef mesh_type* meshptr_type;
		typedef HardwareSubMesh submesh_type;
		typedef submesh_type* submeshptr_type;
		typedef HardwareTexture texture_type;
		typedef texture_type* textureptr_type;

		meshptr_type createMeshImpl(const std::string &name);
		void setTransformImpl(meshptr_type mesh, glm::vec3 pos, glm::quat rot, glm::vec3 scale);
		void addSubMeshImpl(meshptr_type mesh, submeshptr_type submesh);

		submeshptr_type createSubMeshImpl(const std::string &name);
		void setSubMeshGeometryImpl(submeshptr_type submesh, Vertex *verts, int numVertices, Face *faces, int numFaces);
		void setSubMeshMaterialImpl(submeshptr_type mesh, Material *m);
		void setSubMeshUVsImpl(submeshptr_type submesh, TexCoord *verts, int numTXCoords);
		void setSubMeshNormalsImpl(submeshptr_type submesh, Vertex *normals, int numNormals);

		textureptr_type createTextureImpl(const std::string &name);
	};

} /* raytracer */

#endif /* _HARDWARE_CREATION_STRATEGY_H_ */

