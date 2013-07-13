#ifndef _OPENGL_HARDWARE_BUFFER_MANAGER_H_
#define _OPENGL_HARDWARE_BUFFER_MANAGER_H_ 

#include "rendersystem/HardwareBuffer.h"
#include "rendersystem/opengl/OpenGLHardwareBuffer.h"

namespace raytracer {

	class OpenGLHardwareBufferManager : public HardwareBufferManager, public Singleton<OpenGLHardwareBufferManager>
	{
		friend class Singleton<OpenGLHardwareBufferManager>;

	protected:
		OpenGLHardwareBufferManager() : HardwareBufferManager(this) { };

	public:
		virtual HardwareBuffer* createBuffer(int elementSize, int numElements);
	};

} /* raytracer */

#endif /* _OPENGL_HARDWARE_BUFFER_MANAGER_H_ */
