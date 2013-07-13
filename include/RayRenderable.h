#ifndef _RAY_RENDERABLE_H_
#define _RAY_RENDERABLE_H_

#include "common.h"
#include "ray.h"
#include "DebugRenderable.hpp"

namespace raytracer {

#define TAIL_LENGTH 3.0f
#define TAIL_RADIUS 0.1f
#define HEAD_LENGTH 1.0f
#define HEAD_RADIUS 0.2f
#define TESSELLATION 25

	class RayUpdateStrategy : public InstancedDebugRenderableBase
	{
	public:
		void update(const Ray &ray);
		void getWorldTransform(Matrix4 &m) const;
		
	protected:
		virtual void initRenderOperation();
		virtual void oneTimeInitMesh();

	private:
		Ray mRay;
		Matrix4 mWorldSpaceTransform;
	};

	typedef DebugRenderable<RayUpdateStrategy, Ray, TESSELLATION * 9> RayRenderable;

} /* namespace raytracer */


#endif /* _RAY_RENDERABLE_H_ */