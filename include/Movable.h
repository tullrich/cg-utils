#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "common.h"
#include "aabb.h"
#include "Renderable.h"

namespace raytracer {

	class SceneNode; // forward declaration

	class Movable
	{
	public:
		Movable() : mParentNode(NULL) {};
		virtual ~Movable() {};
	
		void setParentNode(SceneNode *n);
		SceneNode* getParentNode() { return mParentNode; };
		Matrix4 getParentNodeFullTransform() const;
		Vector4 getPosition() const;

		virtual void visitRenderables(RenderableVisitor &r) const = 0;
		virtual const AABB& getWorldBounds() = 0;
		virtual void notifyNodeTransformChanged() { };
	protected:
		SceneNode *mParentNode;
	};

	class MovableVisitor : public Visitor<Movable> {};

} /* raytracer */

#endif /* _MOVABLE_H_ */
