#ifndef _CLIENT_CREATION_STRATEGY_H_
#define _CLIENT_CREATION_STRATEGY_H_ 

namespace raytracer {

	class ClientMeshCreationStrategy
	{
	public:
		typedef ClientMesh mesh_type;
		typedef mesh_type* meshptr_type;
		typedef ClientSubMesh submesh_type;
		typedef submesh_type* submeshptr_type;

		meshptr_type createMesh();

		void setMaterialName(Entity *e, Material *m);
	};

} /* raytracer */

#endif /* _CLIENT_CREATION_STRATEGY_H_ */
