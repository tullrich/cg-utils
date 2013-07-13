#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_ 

#include "common.h"
#include "material.h"
#include "rendersystem/HardwareBuffer.h"

namespace raytracer {

	class RenderOperation
	{
	public:
		enum PrimitiveType
		{
			PT_TRIANGLE_LIST,
			PT_LINE_LIST,
		};

		PrimitiveType mType;
		HardwareBuffer *mVertexData;
		HardwareBuffer *mIndexData;
		HardwareBuffer *mUVData;
		HardwareBuffer *mNormalData;

	public:
		RenderOperation() : mType(PT_TRIANGLE_LIST), mVertexData(NULL), mIndexData(NULL), mUVData(NULL), mNormalData(NULL) {};

	};

	class Renderable
	{
	public:
		virtual void getRenderOperation(RenderOperation &p) const = 0;
		virtual void getWorldTransform(Matrix4 &m) const = 0;
		virtual const Material* getMaterial() const = 0;
	};

	class RenderableVisitor : public Visitor<Renderable> {};

} /* raytracer */

#endif /* _RENDERABLE_H_ */
