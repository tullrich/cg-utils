#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <list>
#include "common.h"
#include "mesh.h"
#include "WireFrameRenderable.h"
#include "Movable.h"

namespace raytracer {

	using namespace::glm;

	class SubEntity; // forward declaration

	class Entity : public Movable
	{
	private:
		typedef std::list<mesh_data::mesh_ptr> mesh_list;
	public:
		Entity(Mesh *p);
		virtual ~Entity();

		typedef std::shared_ptr<Entity> entity_ptr;

		/**
		 * Set the name of this entity
		 * @param name the new name
		 */
		void setName(const std::string& name) { this->name = name; };

		void setPosition(const Vector3 &pos);

		virtual void visitRenderables(RenderableVisitor &r) const;


		Matrix4 getSceneGraphTransform();

		virtual void notifyNodeTransformChanged();

		virtual const AABB& getWorldBounds();


		void setDebug(bool debug);

		/**
		 * position of the entity in world space
		 */
		Vector3 mPosition;

		/**
		 * scale of the entity in world space
		 */
		glm::vec3 scale;

		/**
		 * rotation of the entity in world space
		 */
		glm::quat rotation;


		/**
		 * Axial-aligned bounding box encompssing all meshes of this model
		 */
		AABB aabb;

	private:
		/**
		 * name of the mesh
		 */
		std::string name;

		/**
		 * Mesh renderable of this entity
		 */
		Mesh *mMesh;

		typedef std::list<SubEntity*> SubEntityList;
		SubEntityList mSubEntities;

		AABB mWorldBounds;
		WireFrameRenderable *mDebugRenderable;

		bool mDebug;

		/**
		 * access to private members
		 */
		friend std::ostream& operator<<(std::ostream& o, const Entity& b);
	};

	class SubEntity : public Renderable
	{
	public:
		SubEntity(Entity *parent, SubMesh *sm);
		~SubEntity();

		virtual void getRenderOperation(RenderOperation &p) const;
		virtual void getWorldTransform(Matrix4 &m) const;
		virtual const Material* getMaterial() const;

		void setMaterial(Material *m);
	private:
		Material* mMaterial;
		SubMesh *mSubMesh;
		Entity *mParentEntity;
	};

	/**
	 * Insert stream operator for Entity
	 */
	std::ostream& operator<<(std::ostream& o, const Entity& b);

	/**
	 * Helper class for visiting Entities
	 */
	typedef cgutils::Visitor<Entity> EntityVisitor;

} /* namespace raytracer */

#endif /* _ENTITY_H_ */
