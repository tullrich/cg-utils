#include "import/hardwarecreationstrategy.h"
#include <cstring>

namespace raytracer {
	
	HardwareMeshCreationStrategy::meshptr_type HardwareMeshCreationStrategy::createMeshImpl(const std::string &name)
	{
		return new HardwareMesh(name);
	}

	void HardwareMeshCreationStrategy::setTransformImpl(meshptr_type mesh, glm::vec3 pos, glm::quat rot, glm::vec3 scale)
	{

	}

	void HardwareMeshCreationStrategy::addSubMeshImpl(meshptr_type mesh, submeshptr_type submesh)
	{
		mesh->addSubMesh(submesh);
	}

	HardwareMeshCreationStrategy::submeshptr_type HardwareMeshCreationStrategy::createSubMeshImpl(const std::string &name)
	{
		return new HardwareSubMesh(name);
	}

	void HardwareMeshCreationStrategy::setSubMeshGeometryImpl(submeshptr_type submesh, Vertex *verts, int numVertices, Face *faces, int numFaces)
	{
		HardwareBufferManager *hwm = HardwareBufferManager::getManager();

		HardwareBuffer *vertexBuffer = hwm->createBuffer(sizeof(Vertex), numVertices);
		void* vertData = vertexBuffer->lock();
		memcpy(vertData, verts, sizeof(Vertex) * numVertices);
		vertexBuffer->unlock();
		
		HardwareBuffer *faceBuffer = hwm->createBuffer(sizeof(Face), numFaces);
		void* faceData = faceBuffer->lock();
		memcpy(faceData, faces, sizeof(Face) * numFaces);
		faceBuffer->unlock();

		submesh->setGeoBuffers(vertexBuffer, faceBuffer);
	}

	void HardwareMeshCreationStrategy::setSubMeshMaterialImpl(submeshptr_type mesh, Material *m)
	{
		mesh->setMaterial(m);
	}

	void HardwareMeshCreationStrategy::setSubMeshUVsImpl(submeshptr_type submesh, TexCoord *coords, int numTXCoords)
	{
		HardwareBufferManager *hwm = HardwareBufferManager::getManager();

		HardwareBuffer *txBuffer = hwm->createBuffer(sizeof(TexCoord), numTXCoords);
		void* txData = txBuffer->lock();
		memcpy(txData, coords, sizeof(TexCoord) * numTXCoords);
/*
		for (int i = 0; i < numTXCoords; ++i)
		{
			TexCoord* cur = &((TexCoord*)txData)[i];
			std::cout << "txc " << cur->x << " " << cur->y << std::endl;
		}*/
		txBuffer->unlock();

		submesh->setUVBuffer(txBuffer);
	}
	
	void HardwareMeshCreationStrategy::setSubMeshNormalsImpl(submeshptr_type submesh, Vertex *normals, int numNormals)
	{
		HardwareBufferManager *hwm = HardwareBufferManager::getManager();

		HardwareBuffer *normBuffer = hwm->createBuffer(sizeof(Vertex), numNormals);
		void* normData = normBuffer->lock();
		memcpy(normData, normals, sizeof(Vertex) * numNormals);
		normBuffer->unlock();
		submesh->setNormalBuffer(normBuffer);
	}

	HardwareMeshCreationStrategy::textureptr_type HardwareMeshCreationStrategy::createTextureImpl(const std::string &name)
	{
		return new CompiledTexture(name);
	}

} /* namespace raytracer */
