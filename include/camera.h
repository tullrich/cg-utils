#ifndef _CAMERA_H_
#define _CAMERA_H_ 

#include "common.h"
#include "ray.h"
#include "Movable.h"
#include "Window.h"

namespace raytracer {

	class Window; // forward declaration

	/**
	 * Represents the eye during rendering
	 */
	class Camera
	{
		friend std::ostream& operator<<(std::ostream& o, const Camera& b);
	public:
		Camera(int x_res, int y_res);
		Camera(const Vector3 &position = Vector3()
			, const Vector3 &up = Vector3(0.0f, 1.0f, 0.0f)
			, float nearPlane = 0.1f, float farPlane = 100.0f
			, float FOV = 45.0f, float aspect = 1.0f);

		glm::mat4 cameraToWorld;

		void lookAt(const Vector3 &point, const Vector3 &up = Vector3(0.0f, 1.0f, 0.0f));
		void move(const Vector3 &point);
		void rotate(const Quaternion &rotation);
		void setPosition(const Vector3 &point);
		void updateFrustum();
		void updateView();
		void setDirection(const Vector3 &direction, const Vector3 &up);
		const Matrix4& getProjectionMatrix();
		const Matrix4& getViewMatrix();
		Vector3 getPosition() const { return Vector3(mPosition); };
		void setOrientation(const Quaternion &orientation);
		Quaternion getOrientation() const { return mOrientation; };

		/**
		 * Compute the worldspace vector cooresponding to the center of pixel i, j using
		 * the orientation of this camera.	
		 * @param i      horizontal pixel number
		 * @param j      vertical pixel number
		 */
		Vector3 getWorldPixelCenter(int i, int j, float variance_i, float variance_j);

		/**
		 * generate a random viewing ray for the near plane project pixel (i, j)
		 * @param i width pixel value
		 * @param j height pixel value
		 * @param r resultant {@link Ray}
		 */
		void genViewingRay(int i, int j, Ray &r);

		Ray genPickRay(int i, int j);

		float pixelXDimension() const;
		float pixelYDimension() const;

		void setWindow(const Window *window) { mWindow = window; }

	protected:
		Quaternion mOrientation;
		Vector4 mPosition;

		Matrix4 mProjectionMatrix, mViewMatrix;
		bool mFrustumChanged, mLocationChanged;

		float mNearPlane, mFarPlane;
		float mFOV, mAspect;

		const Window *mWindow;
	};

	/**
	 * Insert stream operator for Camera
	 */
	std::ostream& operator<<(std::ostream& o, const Camera& b);

} /* raytracer */

#endif /* _CAMERA_H_ */
