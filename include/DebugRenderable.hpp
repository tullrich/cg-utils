#ifndef _DEBUG_RENDERABLE_H_
#define _DEBUG_RENDERABLE_H_

#include "common.h"
#include "ray.h"
#include "Renderable.h"

namespace raytracer {

	class DebugRenderableBase : public Renderable
	{
	protected:
		virtual void initRenderOperation()
		{

			mOp.mVertexData = mVertHWBuffer;
			mOp.mType = RenderOperation::PT_LINE_LIST;
		}

		virtual void initHardwareBuffer(int size)
		{
			HardwareBufferManager *hwm = HardwareBufferManager::getManager();
			this->mVertHWBuffer = hwm->createBuffer(sizeof(Vertex), size);
		}

		virtual void getWorldTransform(Matrix4 &m) const
		{
			m = Matrix4(); // Identity
		}

		HardwareBuffer *mVertHWBuffer;
		RenderOperation mOp;
		Material *mMaterial;
	};

	class InstancedDebugRenderableBase : public DebugRenderableBase
	{	
	protected:
		virtual void initHardwareBuffer(int size)
		{
			static HardwareBuffer *sVertHWBuffer = NULL;

			if(!sVertHWBuffer)
			{
				HardwareBufferManager *hwm = HardwareBufferManager::getManager();
				mVertHWBuffer = sVertHWBuffer = hwm->createBuffer(sizeof(Vertex), size);
				oneTimeInitMesh();
			}
			else
			{
				mVertHWBuffer = sVertHWBuffer;
			}
		}

		virtual void oneTimeInitMesh() = 0;
	};

	template< class ObjectRenderStrategy, typename T, int C>
	class DebugRenderable : public ObjectRenderStrategy
	{
		public:
			DebugRenderable(const T &object, const RGB &color = RGB(1.0f, 0.0f, 0.0f))
			{
				this->mMaterial = MaterialManager::getInstance().getDefaultObject();

				this->initHardwareBuffer(C);
				this->initRenderOperation();
				this->update(object);
			}

			virtual ~DebugRenderable()
			{
				delete this->mVertHWBuffer;
			}

			virtual void getRenderOperation(RenderOperation &p) const
			{
				p = this->mOp;
			}

			virtual const Material* getMaterial() const
			{
				return this->mMaterial;
			}
	};

}

#endif /* _DEBUG_RENDERABLE_H_ */