#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "common.h"
#include "aabb.h"
#include "ray.h"
#include "rendersystem/HardwareBuffer.h"

namespace raytracer {

	using namespace cgutils;

	class Material; //forward declaration

	typedef union {
		unsigned int indices[3];
		struct {
			unsigned int x;
			unsigned int y;
			unsigned int z;
		};
	} prim_tri;

	/**
	 * Holds reference to and owns all data needed for rendering a mesh
	 */
	class mesh_data
	{

	public:
		typedef std::shared_ptr<mesh_data> mesh_ptr;
		//typedef std::shared_ptr<const mesh_data> mesh_ptr;

		mesh_data() : numVertices(0), verts(NULL), numFaces(0), faces(NULL), mat(NULL), uvs(NULL){};
		~mesh_data();


		void setName(const string &name) { this->name = name; };
		void setVertices(int count, const glm::vec3 *ptr);
		void setFaces(int count, const prim_tri *ptr);
		void setMaterial(const Material *mat) { this->mat = mat; };
		void setUVs(const TexCoord *ptr);

		/**
		 * Updates the given aabb so that it fully contains this mesh 
		 * @param aabb the bounding box to update
		 */
		void AABBContainMesh(AABB &aabb) const;


		int getUVCount() const;

		std::string name;
		
		int TangentsAndBitangents;

		int numVertices;
		const glm::vec3 *verts;

		int numFaces;
		const prim_tri *faces;

		const Material *mat;	

		/**
		 * Array of UV coordinates for each vertex. The size of this array is
		 * numVertices
		 */
		const TexCoord *uvs;

	private:
		/**
		 * access to private members
		 */
		friend std::ostream& operator<<(std::ostream& o, const mesh_data& b);
	};


	class SubMesh
	{
	public:
		SubMesh(const string& name) : mName(name) {};
		const string& getName() const { return mName; };
		
		void setMaterial(Material *mat) { mMaterial = mat; }
		Material* getMaterial() { return mMaterial; }

		virtual AABB buildBounds() = 0;
	private:
		string mName;
		Material* mMaterial;
	};

	/**
	 * Abstract mesh
	 */
	class Mesh
	{
	public:
		Mesh(const string& name);
		const string& getName() const { return mName; };

		typedef std::list<SubMesh*> SubMeshList;
		typedef IteratorContainer<SubMeshList> SubMeshIterator;
		virtual SubMeshIterator getSubMeshIterator() = 0;

		const AABB& getLocalBounds();
	protected:
		SubMeshList mSubMeshes;

	private:
		bool mComputedBounds;
		AABB mLocalBounds;
		string mName;
	};

	/**
	 * Client memory backed mesh
	 */
	class ClientMesh : public Mesh
	{
	public:
		ClientMesh(const string& name) : Mesh(name) {};
	};

	class ClientSubMesh : public SubMesh
	{
	public:
		ClientSubMesh(const string& name) : SubMesh(name) {};
	};


	class HardwareSubMesh; // forward declaration

	/**
	 * Hardware memory backed Mesh implementation
	 */
	class HardwareMesh : public Mesh
	{
	public:
		HardwareMesh(const string& name) : Mesh(name) {};

		void addSubMesh(HardwareSubMesh *submesh);
		virtual SubMeshIterator getSubMeshIterator();
	private:
	};

	class HardwareSubMesh : public SubMesh
	{
	public:
		HardwareSubMesh(const string& name) : SubMesh(name), mUVHWBuffer(NULL), mVertHWBuffer(NULL), mFaceHWBuffer(NULL), mNormalBuffer(NULL) {};
		void setGeoBuffers(HardwareBuffer *verts, HardwareBuffer *faces);
		void setNormalBuffer(HardwareBuffer *normals);
		void setUVBuffer(HardwareBuffer *uvs);

		HardwareBuffer* getVertexData() { return mVertHWBuffer; }
		HardwareBuffer* getIndexData() { return mFaceHWBuffer; }
		HardwareBuffer* getUVData() { return mUVHWBuffer; }
		HardwareBuffer* getNormalData() { return mNormalBuffer; }
	protected:
		virtual AABB buildBounds();

	private:
		HardwareBuffer *mVertHWBuffer;
		HardwareBuffer *mFaceHWBuffer;
		HardwareBuffer *mUVHWBuffer;
		HardwareBuffer *mNormalBuffer;
	};

	/**
	 * Insert stream operator for mesh_data
	 */
	std::ostream& operator<<(std::ostream& o, const mesh_data& b);

	class  MeshManager : public ResourceManager<std::string, mesh_data::mesh_ptr> {};

}; /* namespace raytracer */

#endif /* _MESH_H_ */
