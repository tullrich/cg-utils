#include "WireFrameRenderable.h"

namespace raytracer {

	void AABBUpdateStrategy::update(const AABB &aabb)
	{
		mAABB = aabb;

		Vertex *verts = reinterpret_cast<Vertex*>(mVertHWBuffer->lock());
		for (int i = 0; i < 24; ++i)
		{
			verts[i] = Vertex(1.0f * i, 1.0f * i, 1.0f * i);
		}

		// horizontal top left edge
		verts[0] = mAABB.max;
		verts[1] = Vector3(mAABB.max.x, mAABB.max.y, mAABB.min.z);
		// vertical back left edge
		verts[2] = mAABB.max;
		verts[3] = Vector3(mAABB.max.x, mAABB.min.y, mAABB.max.z);
		// horizontal top back edge
		verts[4] = mAABB.max;
		verts[5] = Vector3(mAABB.min.x, mAABB.max.y, mAABB.max.z);

		// horizontal bottom right edge
		verts[6] = mAABB.min;
		verts[7] = Vector3(mAABB.min.x, mAABB.min.y, mAABB.max.z);
		// vertical front right edge
		verts[8] = mAABB.min;
		verts[9] = Vector3(mAABB.min.x, mAABB.max.y, mAABB.min.z);
		// horizontal bottom front edge
		verts[10] = mAABB.min;
		verts[11] = Vector3(mAABB.max.x, mAABB.min.y, mAABB.min.z);

		// right top back
		Vertex maxYOpp = Vector3(mAABB.min.x, mAABB.max.y, mAABB.max.z);
		// left bottom front
		Vertex minYOpp = Vector3(mAABB.max.x, mAABB.min.y, mAABB.min.z);

		// horizontal top right edge
		verts[12] = maxYOpp;
		verts[13] = Vector3(maxYOpp.x, maxYOpp.y, minYOpp.z);
		// vertical back right edge
		verts[14] = maxYOpp;
		verts[15] = Vector3(maxYOpp.x, minYOpp.y, maxYOpp.z);
		// horizontal top front edge
		verts[16] = Vector3(maxYOpp.x, maxYOpp.y, minYOpp.z); // right top front
		verts[17] = Vector3(minYOpp.x, maxYOpp.y, minYOpp.z); // left top front

		// horizontal bottom left
		verts[18] = minYOpp;
		verts[19] = Vector3(minYOpp.x, minYOpp.y, maxYOpp.z);
		// vertical front left
		verts[20] = minYOpp;
		verts[21] = Vector3(minYOpp.x, maxYOpp.y, minYOpp.z);
		// horizontal bottom back
		verts[22] = Vector3(minYOpp.x, minYOpp.y, maxYOpp.z); // left bottom front
		verts[23] = Vector3(maxYOpp.x, minYOpp.y, maxYOpp.z); // right bottom front

		mVertHWBuffer->unlock();
	}

} /* namespace raytracer */
