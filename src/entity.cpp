#ifndef _IMPORTER_H_
#define _IMPORTER_H_

#include "entity.h"
#include "material.h"

namespace raytracer {


	Entity::Entity(Mesh *m) : mPosition(0), scale(0), name(""), mDebugRenderable(NULL), mDebug(false)
	{
		mMesh = m;

		Mesh::SubMeshIterator iter = m->getSubMeshIterator();
		for(Mesh::SubMeshIterator::iterator i = iter.begin(); i != iter.end(); i++)
		{
			SubEntity *se = new SubEntity(this, *i);
			mSubEntities.push_back(se);

			Material *m = (*i)->getMaterial();
			if(m)
				se->setMaterial(m);
		}
	}

	Entity::~Entity()
	{
		if(mDebugRenderable)
		{
			delete mDebugRenderable;
			mDebugRenderable = NULL;
		}
	}


	void Entity::visitRenderables(RenderableVisitor &r) const
	{
		SubEntityList::const_iterator i = mSubEntities.begin();
		for(; i != mSubEntities.end(); ++i)
		{
			r.visit(*static_cast<const Renderable*>(*i));
		}

		if(mDebug)
		{
			r.visit(*static_cast<const Renderable*>(mDebugRenderable));
		}
	}

	void Entity::setPosition(const Vector3 &pos)
	{
		mPosition = pos;
	}

	const AABB& Entity::getWorldBounds()
	{	
		mWorldBounds = mMesh->getLocalBounds();
		AABBTransform(mWorldBounds, getParentNodeFullTransform());
		return mWorldBounds;
	}

	void Entity::setDebug(bool debug)
	{
		if(debug)
		{
			if(!mDebugRenderable)
			{
				mDebugRenderable = new WireFrameRenderable(getWorldBounds());
			}
			else
			{
				mDebugRenderable->update(getWorldBounds());
			}
		}

		mDebug = debug;
	}

	void Entity::notifyNodeTransformChanged()
	{
		if(mDebug)
		{
			mDebugRenderable->update(getWorldBounds());
		}
	}

	SubEntity::SubEntity(Entity *parent, SubMesh *sm) : mParentEntity(parent), mSubMesh(sm)
	{
		mMaterial = MaterialManager::getInstance().getDefaultObject();
	}

	void SubEntity::getRenderOperation(RenderOperation &p) const
	{
		HardwareSubMesh *hwsm = reinterpret_cast<HardwareSubMesh*>(mSubMesh);
		p.mVertexData = hwsm->getVertexData();
		p.mIndexData = hwsm->getIndexData();
		if(hwsm->getUVData() != NULL)
		{
			p.mUVData = hwsm->getUVData();
		}
		if(hwsm->getNormalData() != NULL)
		{
			p.mNormalData = hwsm->getNormalData();
		}
		
		p.mType = RenderOperation::PT_TRIANGLE_LIST;
	}

	void SubEntity::getWorldTransform(Matrix4 &m) const
	{
		m = mParentEntity->getParentNodeFullTransform();
	}

	void SubEntity::setMaterial(Material *m)
	{
		mMaterial = m;

		if(!mMaterial)
		{
			mMaterial = MaterialManager::getInstance().getDefaultObject();
		}

		mMaterial->ensureLoaded();
	}

	const Material* SubEntity::getMaterial() const
	{
		return mMaterial;
	}

	std::ostream& operator<<(std::ostream& o, const Entity& b)
	{
		o << "Entity '" << b.name << "' {\n" \
			<< "\tposition: " << b.mPosition << "\n" \
			<< "\tscale: " << b.scale << "\n" \
			<< "\taabb: " << b.aabb << "\n" \
			<< "\tmeshes: \n";

			o << "\n}";

		return o;
	}

} /* namespace raytracer */

#endif /* _IMPORTER_H_ */
