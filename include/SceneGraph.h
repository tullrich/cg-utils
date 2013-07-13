#ifndef _SCENE_GRAPH_H_
#define _SCENE_GRAPH_H_ 

#include "common.h"
#include <list>
#include <set>
#include "aabb.h"
#include "Movable.h"
#include "WireFrameRenderable.h"
#include "ray.h"

namespace raytracer {


	class SceneGraph; // forward declaration

	/**
	 * class containing the result of a success full ray cast
	 */
	class TraceResult
	{
	public:
		Movable *mMovable; // primitive of intersection
		float mDistance;

		TraceResult() : mMovable(NULL), mDistance(0) {};
		TraceResult(Movable *m, float distance) : mMovable(m), mDistance(distance) {};
	};

	class SceneNode
	{
	public:
		SceneNode(SceneGraph *scenegraph, const Vector3 &translation = Vector3(), const Vector3 &scale = Vector3(1.0f, 1.0f, 1.0f),  const Quaternion &rotation = Quaternion());
		virtual ~SceneNode();

		SceneNode* createChild(const Vector3 &translation = Vector3(), const Vector3 &scale = Vector3(1.0f, 1.0f, 1.0f),  const Quaternion &rotation = Quaternion());

		void setParent(SceneNode *parent);
		void attachMovable(Movable *mv);

		void notifyParentMoved();
		void notifyChildBoundsChanged();
		Matrix4 getTransformToRoot();

		Vector4 getDerivedPosition();
		void setLocalPosition(const Vector3 &pos);
		void localRotate(const Quaternion &rot);
		void setLocalOrientation(const Quaternion &rot);
		Vector4 getDerivedScale();
		Quaternion getDerivedOrientation();

		SceneNode *getRoot();

		const AABB& getWorldBounds();

		void setDebug(bool debug);
		void drawDebugBounds(bool override, RenderableVisitor &r);
		void readyDebugRenderable();
		bool trace(const Ray &r, TraceResult &result);
	protected:
		void updateFromParent();
		void updateFromChildren();
		void setDirtyBounds();
		void setDirtyTransform();
	private:
		typedef std::list<SceneNode*> SceneNodeList;
		SceneNodeList mChildren;
		SceneNode *mParent;
		bool mDirtyParent;

		typedef std::list<Movable*> MovableList;
		MovableList mAttached;
		
		Vector4 mTranslation, mScale, mDerivedPosition, mDerivedScale;
		Quaternion mOrientation, mDerivedOrientation;

		AABB mWorldBounds;
		Matrix4 mTransformToRoot;
		bool mTransformToRootDirty, mDirtyBounds;

		WireFrameRenderable *mDebugRenderable;
		bool mDebug;

		SceneGraph *mSceneGraph;
	};


	class SceneGraph
	{
	public:
		SceneGraph();
		virtual ~SceneGraph();

		virtual void attachMovableToRoot(Movable *m);
		SceneNode* getRoot();
		void notifyMovableAttached(Movable *m);
		virtual void findVisibleObjects(MovableVisitor *v);
		void notifyNodeDebugStatus(bool debugOn);
		void drawDebugBounds(bool override, RenderableVisitor &r);

		bool trace(const Ray &r, TraceResult &result);
		void addDebugRenderable(Renderable *r);
	protected:
		typedef std::list<Renderable*> RenderableList;
		RenderableList mDebugRenderables;

		typedef std::set<Movable*> MovableSet;
		MovableSet mMovables;

		SceneNode *mRootNode;

		uint mNodeDebugCount;
	};

} /* raytracer */

#endif /* _SCENE_GRAPH_H_ */
