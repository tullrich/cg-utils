#ifndef _OPENGL_HARDWARE_BUFFER_H_
#define _OPENGL_HARDWARE_BUFFER_H_ 

#include "rendersystem/HardwareBuffer.h"
#include "GL/glew.h"

namespace raytracer {

	class OpenGLHardwareBuffer : public HardwareBuffer
	{
	public:
		OpenGLHardwareBuffer(int elementSize, GLsizei numElements);
		virtual ~OpenGLHardwareBuffer();
		virtual void* lock();
		virtual void unlock();
		virtual int getNumElements() const { return mNumElements; }
		GLuint getBufferID() { return mGLBufIdent; }
	private:
		GLuint mGLBufIdent;
		GLsizei mNumElements;
	};

} /* raytracer */

#endif /* _OPENGL_HARDWARE_BUFFER_H_ */