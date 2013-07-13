#ifndef _ASSIMP_HELPERS_H_
#define _ASSIMP_HELPERS_H_ 

#include "common.h"
#include "Skeleton.h"
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

namespace raytracer {

	namespace AssimpHelpers {
		float matPropertyToFloat(const aiMaterial &ai_mat, const char* pKey, unsigned int type, unsigned int idx);
		RGB matPropertyToRGB(const aiMaterial &ai_mat, const char* pKey, unsigned int type, unsigned int idx);
		bool matUsesTextures(const aiMaterial &ai_mat);
		void copyAiVector3DToGLM(Vertex *buf, int numVertices, aiVector3D *verts);
		void copyAiFaceToGLM(Face *buf, int numFaces, aiFace *faces);
		void copyAiTexCoordToGLM(TexCoord *buf, int numTexCoords, aiVector3D *txcoords);
		int nodeDegreeFromRoot(const aiNode *root, const aiNode *node);
		Vector3 aiVector3DToGLM(const aiVector3D &vect);
		Quaternion aiQuaternionToGLM(const aiQuaternion &quat);
		Bone* aiNodeToBone(const aiNode *node);
		void debugPrintSceneAnimationInfo(const aiScene *scene);
	}

} /* raytracer */

#endif /* _ASSIMP_HELPERS_H_ */
