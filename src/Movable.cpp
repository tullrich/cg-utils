#include "Movable.h"
#include "SceneGraph.h"

namespace raytracer {
	
	void Movable::setParentNode(SceneNode *n)
	{
		CGUTILS_ASSERT(mParentNode == NULL);
		mParentNode = n;
	}

	Matrix4 Movable::getParentNodeFullTransform() const
	{
		if(mParentNode)
		{
			return mParentNode->getTransformToRoot();
		}
		else
		{
			std::cout << "Error getParentNodeFullTransform in unattached Movable" << std::endl; 
		}

		return Matrix4();
	}

	Vector4 Movable::getPosition() const
	{
		return mParentNode->getDerivedPosition();
	}

} /* namespace raytracer */
