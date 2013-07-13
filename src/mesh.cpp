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



	void mesh_data::setUVs(const glm::vec2 *ptr)
	{
		uvs = ptr;
	}

	int mesh_data::getUVCount() const
	{
		return (uvs) ? 0 : 1; // temp
	}


	Mesh::Mesh(const string& name) : mName(name), mComputedBounds(false)
	{
	}

	const AABB& Mesh::getLocalBounds()
	{
		if(!mComputedBounds)
		{
			SubMeshList::iterator i = mSubMeshes.begin();
			mLocalBounds = AABB();
			for(; i != mSubMeshes.end(); i++)
			{
				AABBContainAABB(mLocalBounds, (*i)->buildBounds());
			}
		}
		return mLocalBounds;
	}

	AABB HardwareSubMesh::buildBounds()
	{
		AABB bounds;
		if(mVertHWBuffer)
		{
			// TODO: dont use GPU memory for this;
			void* vertData = mVertHWBuffer->lock();
			for(int i = 0; i < mVertHWBuffer->getNumElements();  i++)
			{
				AABBContainVertex(bounds, ((Vector3*)vertData)[i]);
			}
			mVertHWBuffer->unlock();
		
		}
		return bounds;
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
