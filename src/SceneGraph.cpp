#include "SceneGraph.h"

namespace raytracer {

	SceneNode::SceneNode(SceneGraph *scenegraph, const Vector3 &translation, const Vector3 &scale, const Quaternion &rotation) 
		: mSceneGraph(scenegraph), mParent(NULL), mTranslation(translation, 1.0f), mOrientation(rotation), mScale(scale, 1.0f)
		, mTransformToRootDirty(true), mDirtyParent(true), mDebug(false), mDebugRenderable(NULL)
	{

	}

	SceneNode::~SceneNode()
	{
		SceneNodeList::iterator i = mChildren.begin();
		for(; i != mChildren.end(); i++)
		{
			delete *i;
		}
		mChildren.clear();
	}

	SceneNode* SceneNode::createChild(const Vector3 &translation, const Vector3 &scale, const Quaternion &rotation)
	{
		SceneNode *fresh = new SceneNode(mSceneGraph, translation, scale, rotation);
		fresh->setParent(this);
		mChildren.push_back(fresh);
		return fresh;
	}

	void SceneNode::attachMovable(Movable *mv)
	{
		mAttached.push_back(mv);
		mv->setParentNode(this);
		mSceneGraph->notifyMovableAttached(mv);

		setDirtyBounds();
	}

	void SceneNode::setDirtyBounds()
	{	
		mDirtyBounds = true;
		if(mParent)
		{
			mParent->notifyChildBoundsChanged();
		}
	}

	void SceneNode::updateFromChildren()
	{
		mWorldBounds = AABB();
		AABBTransform(mWorldBounds, getTransformToRoot());

		MovableList::iterator mI = mAttached.begin();
		for(; mI != mAttached.end(); mI++)
		{
			AABBContainAABB(mWorldBounds, (*mI)->getWorldBounds());
		}

		SceneNodeList::iterator nI = mChildren.begin();
		for(; nI != mChildren.end(); nI++)
		{
			AABBContainAABB(mWorldBounds, (*nI)->getWorldBounds());
		}

		if(mDebug && mDebugRenderable)
			mDebugRenderable->update(mWorldBounds);

		mDirtyBounds = false;
	}

	void SceneNode::setParent(SceneNode *parent)
	{
		CGUTILS_ASSERT(mParent == NULL)
		mParent = parent;

		setDirtyBounds();
	}

	Matrix4 SceneNode::getTransformToRoot()
	{
		if(mTransformToRootDirty)
		{
			Vector4 translation = getDerivedPosition();
			//Matrix4 translationMatrix = toTranslationMatrix(translation);
			Vector4 scale = getDerivedScale();
			Matrix4 scalingMatrix = toScaleMatrix(scale);
			Matrix4 rotationMatrix = glm::mat4_cast(getDerivedOrientation());

			mTransformToRoot = rotationMatrix * scalingMatrix;
			translate(mTransformToRoot, translation);
			mTransformToRootDirty = false;
		}
		return mTransformToRoot;
	}

	void SceneNode::updateFromParent()
	{
		if (mParent)
		{
			// translation
			mDerivedPosition = Vector4(Vector3(mParent->getDerivedPosition() + mTranslation), 1.0f);

			// scale
			mDerivedScale = mParent->getDerivedScale() * mScale;

			// orientation
			mDerivedOrientation = mParent->getDerivedOrientation() * mOrientation;
		}
		else
		{
			mDerivedPosition = mTranslation;
			mDerivedScale = mScale;
			mDerivedOrientation = mOrientation;
		}

		mTransformToRootDirty = true;
		mDirtyParent = false;
	}

	void SceneNode::setDirtyTransform()
	{
		mDirtyParent = true;
		mTransformToRootDirty = true;

		MovableList::iterator mI = mAttached.begin();
		for(; mI != mAttached.end(); mI++)
		{
			(*mI)->notifyNodeTransformChanged();
		}
	}


	void SceneNode::setLocalPosition(const Vector3 &pos)
	{
		mTranslation = Vector4(pos, 1.0f);

		setDirtyTransform();
		setDirtyBounds();
	}

	void SceneNode::setLocalOrientation(const Quaternion &rot)
	{
		mOrientation = rot;

		setDirtyTransform();
		setDirtyBounds();
	}

	void SceneNode::localRotate(const Quaternion &rot)
	{
		setLocalOrientation(rot * mOrientation);
	}

	Vector4 SceneNode::getDerivedPosition()
	{
		if(mDirtyParent)
		{
			updateFromParent();
		}

		return mDerivedPosition;
	}

	Vector4 SceneNode::getDerivedScale()
	{
		if(mDirtyParent)
		{
			updateFromParent();
		}

		return mDerivedScale;
	}

	Quaternion SceneNode::getDerivedOrientation()
	{
		if(mDirtyParent)
		{
			updateFromParent();
		}

		return mDerivedOrientation;
	}

	void SceneNode::notifyParentMoved()
	{
		setDirtyTransform();
	}

	void SceneNode::notifyChildBoundsChanged()
	{
		setDirtyBounds();
	}

	const AABB& SceneNode::getWorldBounds()
	{
		if(mDirtyBounds)
		{
			updateFromChildren();
		}

		return mWorldBounds;
	}

	void SceneNode::readyDebugRenderable()
	{
		if(!mDebugRenderable)
		{
			mDebugRenderable = new WireFrameRenderable(getWorldBounds());
		}
		
		// must be an override, the old mDebugRenderable wont be
		// kept up to date by updateFromChildren();
		if(!mDebug)
		{
			mDebugRenderable->update(getWorldBounds());
		}
	}

	void SceneNode::setDebug(bool debug)
	{
		if(debug)
		{
			readyDebugRenderable();
		}

		mDebug = debug;
		mSceneGraph->notifyNodeDebugStatus(mDebug);
	}

	void SceneNode::drawDebugBounds(bool override, RenderableVisitor &r)
	{
		if(override || mDebug)
		{
			readyDebugRenderable();
			r.visit(*static_cast<const Renderable*>(mDebugRenderable));
		}

		// propegate request downward
		SceneNodeList::iterator nI = mChildren.begin();
		for(; nI != mChildren.end(); nI++)
		{
			(*nI)->drawDebugBounds(override, r);
		}
	}

	bool SceneNode::trace(const Ray &r, TraceResult &result)
	{
		// early out if the ray does not cross this region
		Vector3 intersectionPoint;
		if(!r.intersects(getWorldBounds(), intersectionPoint))
			return false;

		float distanceToBest = -1.0f;

		MovableList::iterator mI = mAttached.begin();
		for(; mI != mAttached.end(); mI++)
		{
			if(r.intersects((*mI)->getWorldBounds(), intersectionPoint))
			{
				float distanceTo = glm::length(intersectionPoint - r.p);
				if(distanceTo < distanceToBest || distanceToBest == -1)
				{
					result.mMovable = (*mI);
					result.mDistance = distanceToBest = distanceTo;
				}
			}
		}

		TraceResult childResult;
		SceneNodeList::iterator nI = mChildren.begin();
		for(; nI != mChildren.end(); nI++)
		{
			if((*nI)->trace(r, childResult))
			{
				if(childResult.mDistance < distanceToBest || distanceToBest == -1)
				{
					result = childResult;
					distanceToBest = result.mDistance;
				}
			}
		}

		return distanceToBest != -1;
	}

	SceneGraph::SceneGraph() : mNodeDebugCount(0)
	{
		mRootNode = new SceneNode(this);
	}

	SceneGraph::~SceneGraph()
	{
		mMovables.clear();
		delete mRootNode; // will delete children
	}

	void SceneGraph::notifyNodeDebugStatus(bool debugOn)
	{
		if(debugOn)
		{
			mNodeDebugCount++;
		}
		else
		{
			mNodeDebugCount--;
		}
	}

	void SceneGraph::drawDebugBounds(bool override, RenderableVisitor &r)
	{
		if(override || mNodeDebugCount > 0)
		{
			mRootNode->drawDebugBounds(override, r);
		}

		RenderableList::iterator i = mDebugRenderables.begin();
		for(; i != mDebugRenderables.end(); i++)
		{
			r.visit(*static_cast<const Renderable*>(*i));
		}
	}

	void SceneGraph::addDebugRenderable(Renderable *r)
	{
		mDebugRenderables.push_back(r);
	}

	void SceneGraph::attachMovableToRoot(Movable *m)
	{
		mRootNode->attachMovable(m);
	}

	SceneNode* SceneGraph::getRoot()
	{
		return mRootNode;
	}
	
	void SceneGraph::notifyMovableAttached(Movable *m)
	{
		mMovables.insert(m);
	}

	void SceneGraph::findVisibleObjects(MovableVisitor *v)
	{
		MovableSet::iterator i = mMovables.begin();
		for(;i != mMovables.end(); i++)
		{
			v->visit(*static_cast<const Movable*>(*i));
		}
	}

	bool SceneGraph::trace(const Ray &r, TraceResult &result)
	{
		return mRootNode->trace(r, result);
	}

} /* namespace rayracer */
