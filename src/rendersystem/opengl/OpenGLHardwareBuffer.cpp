#include "rendersystem/opengl/OpenGLHardwareBuffer.h"

namespace raytracer {

	OpenGLHardwareBuffer::OpenGLHardwareBuffer(int elementSize, GLsizei numElements) : mGLBufIdent(0), mNumElements(numElements)
	{
		glGenBuffers(1, &mGLBufIdent);

		if(!mGLBufIdent)
		{
			std::cout << "Error in OpenGLHardwareBuffer with glGenBuffers" << std::endl; 
		}

		glBindBuffer(GL_ARRAY_BUFFER, mGLBufIdent);
		glBufferData(GL_ARRAY_BUFFER, elementSize * numElements, NULL, GL_STATIC_DRAW);
	}

	OpenGLHardwareBuffer::~OpenGLHardwareBuffer()
	{
		glDeleteBuffers(1, &mGLBufIdent);
	}
		
	void* OpenGLHardwareBuffer::lock()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mGLBufIdent);
		void* pBuffer = glMapBuffer( GL_ARRAY_BUFFER, GL_READ_WRITE);

		if(!pBuffer)
		{
			std::cout << "Error in OpenGLHardwareBuffer::lock with glMapBuffer" << std::endl; 
		}
			
		return pBuffer;
	}

	void OpenGLHardwareBuffer::unlock()
	{
		if(!glUnmapBuffer(GL_ARRAY_BUFFER))
		{
			std::cout << "Error in OpenGLHardwareBuffer::unlock with glUnmapBuffer" << std::endl; 
		}
	}
	
} /* namespace raytracer */
