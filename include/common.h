#ifndef _COMMON_H_
#define _COMMON_H_ 

#include <iostream>
#include <memory>
#include <string>
#include "buildsettings.h"
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "cgutils.hpp"

using namespace cgutils;

namespace raytracer {

/* Default input values */
#define DEFAULT_IMG_WIDTH 100	// default output image height value
#define DEFAULT_IMG_HEIGHT 100	// default output image height value
#define DEFAULT_OUT_PATH "traceimage.png"	// default output image filepath


#define CONFIG_FILEPATH "raytracer.cfg" // input configuration filepath

#define OPTION_WIDTH "w"
#define OPTION_HEIGHT "h"
#define OPTION_OUTPATH "o"
#define OPTION_ASSETPATH "asset-filepath"

#define FLOAT_ERROR 0.0001f

typedef glm::vec3 RGB;
typedef glm::vec4 RGBA;
typedef glm::vec3 Vertex;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::mat3 Matrix3;
typedef glm::mat4 Matrix4;
typedef glm::vec2 TexCoord;
typedef glm::quat Quaternion;

#include "Matrix.h"

class Triangle 
{
public:
	Triangle() : A(0), B(0), C(0) {};
	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) : A(a), B(b), C(c) {}; 
	
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 C;

	/**
	 * converts a vec3 containing barycentric coordinates relative to this triangle
	 * into a point
	 * @param  intersection barycentric coordinates, |intersection| = 1.0
	 * @return              intersection point on the surface of this triangle
	 */
	glm::vec3 intersectionToPoint(const glm::vec4 &intersection) const;

	glm::vec3 normal()  const;
};

/**
 * Holds UVS for a triangle
 */
class UVTriangle
{
public:
	UVTriangle() : A(0), B(0), C(0) {};
	UVTriangle(TexCoord a, TexCoord b, TexCoord c) : A(a), B(b), C(c) {}; 
	
	TexCoord A;
	TexCoord B;
	TexCoord C;

	/**
	 * converts a vec2 containing barycentric coordinates relative to this triangle
	 * into the UVs at that point
	 * @param  intersection barycentric coordinates, |intersection| = 1.0
	 * @return              intersection point on the surface of this triangle
	 */
	TexCoord interpolateUV(const glm::vec4 &intersection) const;
};

/**
 * Index values of a triangle
 */
class Face
{
public:
	union 
	{
		unsigned int indices[3];
		struct {
			unsigned int x;
			unsigned int y;
			unsigned int z;
		};
	};
};


/**
 * A plane representing all points X s.t. dot(X, n) = d
 */
struct Plane
{
	Plane() : n(0), d(0) {};

	float d;
	glm::vec3 n;
};

glm::vec3 adjustFloatingPointToward(const glm::vec3 point, const glm::vec3 &towards);

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

/**
 * random float between 0 and 1 inclusive
 * @return random float
 */
inline float randf()
{
	return (float)rand()/(float)RAND_MAX;
}

/**
 * generate a uniformally random direction vector on a hemisphere around
 * the input normal
 * @param  normal normal vector around which the direction vector will be
 * @return        random direction vector
 */
glm::vec3 uniformDirectionOnHemisphere(const glm::vec3 normal);

std::string parentPath(const std::string path);
std::string appendFilename(const std::string path, const std::string filename);

Quaternion rotationBetweenVectors(const Vector3 &start, const Vector3 &end);
Matrix4 toTranslationMatrix(const Vector3 &translation);
Matrix4 toTranslationMatrix(const Vector4 &translation);
void translate(Matrix4 &mat, const Vector4 &translation);
Matrix4 toScaleMatrix(const Vector3 &scale);
Matrix4 toScaleMatrix(const Vector4 &scale);

unsigned long getNow();

std::ostream& operator<<(std::ostream& o, const glm::vec3& b);
std::ostream& operator<<(std::ostream& o, const glm::vec4& b);
std::ostream& operator<<(std::ostream& o, const glm::mat4& b);
std::ostream& operator<<(std::ostream& o, const glm::quat& b);
std::ostream& operator<<(std::ostream& o, const Triangle& b);

} /* raytracer */

#endif /* _COMMON_H_ */

