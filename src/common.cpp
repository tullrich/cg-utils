#include "common.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <sys/time.h>

using namespace raytracer;
using namespace std;

namespace raytracer
{

    std::ostream& operator<<(std::ostream& o, const glm::vec3& b)
    {
        return  o << "<" << b.x << ", " << b.y << ", " << b.z << ">";
    }

    std::ostream& operator<<(std::ostream& o, const glm::vec4& b)
    {
        return  o << "<" << b.x << ", " << b.y << ", " << b.z << ", " << b.w << ">";
    }

    std::ostream& operator<<(std::ostream& o, const glm::quat& b)
    {
        return  o << "(" << b.w  << ", " << b.x << ", " << b.y << ", " << b.z << ")";
    }

    std::ostream& operator<<(std::ostream& o, const glm::mat4& b)
    {
        o << "\t[" << b[0][0] << ", " << b[1][0] << ", " << b[2][0] << ", " << b[3][0] << std::endl;
        o << "\t " << b[0][1] << ", " << b[1][1] << ", " << b[2][1] << ", " << b[3][1] << std::endl;
        o << "\t " << b[0][2] << ", " << b[1][2] << ", " << b[2][2] << ", " << b[3][2] << std::endl;
        o << "\t " << b[0][3] << ", " << b[1][3] << ", " << b[2][3] << ", " << b[3][3] << "]";

        return o;
    }

    std::ostream& operator<<(std::ostream& o, const Triangle& b)
    {
        return  o << "Triangle {" << b.A << ", " << b.B << ", " << b.C << " }";
    }

    glm::vec3 Triangle::intersectionToPoint(const glm::vec4 &intersection) const
    {
        return intersection.x * A + intersection.y * B + intersection.z * C;
    }

    TexCoord UVTriangle::interpolateUV(const glm::vec4 &intersection) const
    {
        return intersection.x * A + intersection.y * B + intersection.z * C;
    }

    glm::vec3 Triangle::normal() const
    {
        return glm::normalize(glm::cross(B - A, C - A));
    }


    glm::vec3 adjustFloatingPointToward(const glm::vec3 point, const glm::vec3 &n)
    {
        //glm::vec3 n = towards - point;

        return point + .00001f * n;
    }

    glm::vec3 uniformDirectionOnHemisphere(const glm::vec3 normal)
    {
        // sample 3-axis in uniform direction
        glm::vec3 rand_direction(randf() - 0.5f, randf() - 0.5f, randf() - 0.5f);

        if(glm::dot(rand_direction, normal) < 0)
        {
            rand_direction = -rand_direction;
        }

        return glm::normalize(rand_direction);
    }

    std::string parentPath(const std::string filename)
    {
        std::string filename_noext;
        filename_noext = boost::filesystem::path(filename).parent_path().string();

        return filename_noext;
    }

    std::string appendFilename(const std::string parent_path, const std::string filename)
    {
        boost::filesystem::path full_path(parent_path);
        full_path /= filename; // appends filename to full_path with the preferred separator

        return full_path.make_preferred().string();
    }

    Quaternion rotationBetweenVectors(const Vector3 &start, const Vector3 &end)
    {
        Vector3 startN = glm::normalize(start);
        Vector3 endN = glm::normalize(end);

        float cosAngle = glm::dot(startN, endN);
        Vector3 rotationAxis;

        // ensure we they are not parallel
        if(cosAngle < (-1.0f + .001f))
        { 
            rotationAxis = glm::cross(Vector3(0.0f, 0.0f, 1.0f), startN);
            if(glm::length(rotationAxis) < 0.01f)
            {
                rotationAxis = glm::cross(Vector3(1.0f, 0.0f, 0.0f), startN);
            }

            return glm::normalize(Quaternion(180.0f, rotationAxis));
        }

        rotationAxis = glm::cross(startN, endN);
        float scalar = sqrt((1.0f + cosAngle) * 2.0f);
        float inv_scalar = 1.0f / scalar;
        return Quaternion(scalar * 0.5f, rotationAxis.x * inv_scalar, rotationAxis.y * inv_scalar, rotationAxis.z * inv_scalar);
    }

    Matrix4 toTranslationMatrix(const Vector3 &translation)
    {
        Matrix4 translationMatrix;
        translationMatrix[3][0] = translation.x;
        translationMatrix[3][1] = translation.y;
        translationMatrix[3][2] = translation.z;

        return translationMatrix;
    }

    Matrix4 toTranslationMatrix(const Vector4 &translation)
    {
        return toTranslationMatrix(Vector3(translation));
    }

    void translate(Matrix4 &mat, const Vector4 &translation)
    {
        mat[3][0] += translation.x;
        mat[3][1] += translation.y;
        mat[3][2] += translation.z;
    }

    Matrix4 toScaleMatrix(const Vector3 &scale)
    {
        Matrix4 scaleMatrix;
        scaleMatrix[0][0] = scale.x;
        scaleMatrix[1][1] = scale.y;
        scaleMatrix[2][2] = scale.z;

        return scaleMatrix;
    }

    Matrix4 toScaleMatrix(const Vector4 &scale)
    {
        return toScaleMatrix(Vector3(scale));
    }

    inline unsigned long timeValToLong(const struct timeval &now)
    {
        return (((unsigned long)now.tv_sec) * 1000000) + ((unsigned long)now.tv_usec);
    }


    unsigned long getNow()
    {
        struct timeval now;
        gettimeofday(&now, NULL);
        return timeValToLong(now);
    }

} /* namespace raytracer */
