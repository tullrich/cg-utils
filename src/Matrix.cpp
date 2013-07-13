#include "Matrix.h"

namespace raytracer {
	
	void Matrix4setTranslation(Matrix4 &mat, const Vector3 &translation)
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

} /* namespace raytarcer */
