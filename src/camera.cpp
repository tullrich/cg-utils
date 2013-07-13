#include "camera.h"
#include <cmath>
#include "common.h"

namespace raytracer {

	Camera::Camera(const Vector3 &position, const Vector3 &lookAtPoint
		, float nearPlane, float farPlane
		, float FOV, float aspect)
		: mPosition(position, 1.0f), mNearPlane(nearPlane), mFarPlane(farPlane)
		, mAspect(aspect), mFrustumChanged(true), mLocationChanged(true)
		, mWindow(NULL)
	{
		mFOV = FOV * M_PI / 180 ; // in radians

		//this->up = glm::normalize(upPoint); // up; // 
	}

	void Camera::updateFrustum()
	{
		float e =  1.0f / tan(mFOV / 2.0f);		mProjectionMatrix = Matrix4(); //identity
		//mProjectionMatrix[0][0] = e;
		//mProjectionMatrix[1][1] = e / 1.0f;
		//
		float aspect = mWindow->getHeight() / mWindow->getWidth();
		float something = tan(mFOV / 2.0f ) * mNearPlane;

		mProjectionMatrix[0][0] = mNearPlane / something;
		mProjectionMatrix[1][1] = mNearPlane / (something * aspect);
		mProjectionMatrix[2][2] = -(mFarPlane + mNearPlane) / (mFarPlane - mNearPlane);
		mProjectionMatrix[2][3] = -1.0f;
		mProjectionMatrix[3][2] = (-2.0f * mFarPlane * mNearPlane) / (mFarPlane - mNearPlane);
		mProjectionMatrix[3][3] = 0.0f;
		//mProjectionMatrix[0][0] = 
		mFrustumChanged = false;
	}

	void Camera::lookAt(const Vector3 &point, const Vector3 &up)
	{
		setDirection(point - Vector3(mPosition), up);
	}

	void Camera::move(const Vector3 &point)
	{
		setPosition(Vector3(mPosition) + point);
	}

	void Camera::rotate(const Quaternion &rotation)
	{
		mOrientation = -rotation * mOrientation;
		mLocationChanged = true;
	}

	void Camera::setPosition(const Vector3 &point)
	{
		mPosition = Vector4(point, 1.0f);
		mLocationChanged = true;
	}

	void Camera::setDirection(const Vector3 &direction, const Vector3 &up)
	{
		Vector3 reverseDirection = -direction;
		Vector3 forward;
		Matrix4 rot = glm::toMat4(mOrientation);
   		forward.x = rot[2][0];
        forward.y = rot[2][1];
        forward.z = rot[2][2];
        Quaternion rotQuat = rotationBetweenVectors(forward, reverseDirection);
		mOrientation = -rotQuat * mOrientation;

		Vector3 right = cross(direction, up);
		Vector3 perpUp = cross(right, direction);
		vec3 currentUp = mOrientation * vec3(0.0f, 1.0f, 0.0f);
		quat correction = rotationBetweenVectors(currentUp, perpUp);
		mOrientation = correction * mOrientation;
		
		mLocationChanged = true;
	}


	void Camera::setOrientation(const Quaternion &orientation)
	{
		mOrientation = orientation; 
		mLocationChanged = true;
	}

	const Matrix4& Camera::getProjectionMatrix()
	{
		if(mFrustumChanged)
		{
			updateFrustum();
		}

		return mProjectionMatrix;
	}

	void Camera::updateView()
	{
		mViewMatrix = glm::toMat4(mOrientation);
		translate(mViewMatrix, mPosition);
		mViewMatrix = glm::inverse(mViewMatrix);
		mLocationChanged = false;
	}

	const Matrix4& Camera::getViewMatrix()
	{
		if(mLocationChanged)
		{
			updateView();
		}

		return mViewMatrix;
	}

	Vector3 Camera::getWorldPixelCenter(int i, int j, float variance_i, float variance_j)
	{
		CGUTILS_ASSERT(mWindow);

		int maxHeight = mWindow->getHeight();
		int maxWidth = mWindow->getWidth();

		float normalizedViewX = i / (maxWidth - 1.0f);
		float normalizedViewY = 1.0f - (j / (maxHeight - 1.0f));


		float aspect = mWindow->getHeight() / mWindow->getWidth();
		float umax = tan(mFOV / 2.0f ) * mNearPlane;
		float umin = -umax;
		float rmax = aspect * umax;
		float rmin = -rmax;

		Matrix4 mat = glm::inverse(getViewMatrix());

		//return Vector3(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		return Vector3(mat * Vector4((1.0f - normalizedViewX) * rmin + normalizedViewX * rmax
			, (1.0f - normalizedViewY) * umin + normalizedViewY * umax, -mNearPlane, 1.0f));
	}

	Ray Camera::genPickRay(int i, int j)
	{
		return Ray(Vector3(mPosition), getWorldPixelCenter(i, j, 0, 0));
	}

	std::ostream& operator<<(std::ostream& o, const Camera& b)
	{
		return o << "Camera {\n"
			<< "\n\tnearPlane : " << b.mNearPlane
			<< "\n\tfarPlane : " << b.mFarPlane
			<< "\n\tFOV : " << b.mFOV
			<< "\n\taspect: " << b.mAspect
			<< "\n\tcameraToWorld: \n" << b.cameraToWorld
			<< "\n}";
	}


} /* namespace raytracer */