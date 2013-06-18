#include "mesh.h"
#include "aabb.h"
#include "material.h"

namespace raytracer {

mesh_data::~mesh_data()
{
	if(verts)
	{
		delete[] verts;
	}

	if(faces)
	{
		delete[] faces;
	}
}

void mesh_data::AABBContainMesh(AABB &aabb) const
{

	AABBContainVertices(aabb, numVertices, verts);
}

void mesh_data::setVertices(int count, const glm::vec3 *ptr)
{
	numVertices = count;
	verts       = ptr;
}

void mesh_data::setFaces(int count, const prim_tri *ptr)
{
	numFaces = count;
	faces    = ptr;
}



void textured_mesh_data::setUVs(const glm::vec2 *ptr)
{
	uvs = ptr;
}


std::ostream& operator<<(std::ostream& o, const mesh_data& b)
{
	return o << "Mesh '" << b.name << "' {\n" \
		<< "\tnumVertices: " << b.numVertices << "\n" \
		<< "\tnumFaces:" << b.numFaces << "\n" \
		<< "\tmaterial:" << *b.mat << "\n" \
		<< "}";
}

}; /* namespace raytracer */