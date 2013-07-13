#include "RayRenderable.h"

namespace raytracer {

	void RayUpdateStrategy::initRenderOperation()
	{
		InstancedDebugRenderableBase::initRenderOperation();
		mOp.mType = RenderOperation::PT_TRIANGLE_LIST;
	}


	void RayUpdateStrategy::oneTimeInitMesh()
	{
		std::cout << "ONETIMEMESHINITMESH" << std::endl; 
		Vertex *verts = reinterpret_cast<Vertex*>(mVertHWBuffer->lock());

		Ray temp(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -10.0f));
		Vertex rayEnd = temp.p + glm::normalize(temp.q) * (TAIL_LENGTH + HEAD_LENGTH);

		Vertex perpHead = HEAD_RADIUS * glm::normalize(glm::cross(glm::normalize(temp.q), Vector3(0.0f, 1.0f, 0.0f)));
		Vertex perpTail = TAIL_RADIUS * glm::normalize(glm::cross(glm::normalize(temp.q), Vector3(0.0f, 1.0f, 0.0f)));
		Vertex headStart = temp.p + glm::normalize(temp.q) * (TAIL_LENGTH - 0.15f);


		float angleDeg = 360.0f / TESSELLATION;
		Quaternion q = glm::angleAxis(angleDeg, glm::normalize(glm::normalize(temp.q)));
		for (int i = 0; i < TESSELLATION; ++i)
		{
			Vector3 currentHeadOuter = (headStart + perpHead);
			Vector3 currentTailOuter = (temp.p  + perpTail);
			perpHead = q * perpHead; perpTail = q * perpTail;
			Vector3 nextHeadOuter = (headStart + perpHead);
			Vector3 nextTailOuter = (temp.p  + perpTail);

			// Arrow face
			verts[i * 9 + 0] = rayEnd;
			verts[i * 9 + 1] = currentHeadOuter;//runningRotation * (headStart + perp);
			verts[i * 9 + 2] = nextHeadOuter;
			// Arrow back cap
			verts[i * 9 + 3] = currentHeadOuter;
			verts[i * 9 + 4] = headStart;
			verts[i * 9 + 5] = nextHeadOuter;
			// arrow tail
			verts[i * 9 + 6] = headStart;
			verts[i * 9 + 7] = currentTailOuter;
			verts[i * 9 + 8] = nextTailOuter;
		}

		mVertHWBuffer->unlock();
}
	
	void RayUpdateStrategy::update(const Ray &ray)
	{
		mRay = ray;
		mWorldSpaceTransform = mRay.toMatrix4();
	}

	void RayUpdateStrategy::getWorldTransform(Matrix4 &m) const
	{
		m = mWorldSpaceTransform;
	}

} /* namespace raytracer */
