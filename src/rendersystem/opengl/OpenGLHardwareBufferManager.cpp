#include "rendersystem/opengl/OpenGLHardwareBufferManager.h"

namespace raytracer {
	
HardwareBuffer* OpenGLHardwareBufferManager::createBuffer(int elementSize, int numElements)
{
	OpenGLHardwareBuffer *buf = new OpenGLHardwareBuffer(elementSize, numElements);
	mBuffers.push_back(buf);
	return buf;
}

} /* namespace raytracer */
