#ifndef _WIREFRAME_RENDERABLE_
#define _WIREFRAME_RENDERABLE_

#include "common.h"
#include "aabb.h"
#include "DebugRenderable.hpp"

namespace raytracer {

	class AABBUpdateStrategy : public DebugRenderableBase
	{
	public:
		void update(const AABB &aabb);

	private:
		AABB mAABB;
	};

	typedef DebugRenderable<AABBUpdateStrategy, AABB, 24> WireFrameRenderable;

} /* namespace raytracer */


#endif /* _WIREFRAME_RENDERABLE_ */