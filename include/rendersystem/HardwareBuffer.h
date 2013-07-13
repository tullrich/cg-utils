#ifndef _HARDWARE_BUFFER_H_
#define _HARDWARE_BUFFER_H_ 

#include "common.h"
#include <list>

namespace raytracer {

	/**
	 * Abstract hardware buffer. Rendersystems will implement concrete
	 * versions using a hw api to allocate/deallocate buffers
	 */
	class HardwareBuffer
	{
	public:
		HardwareBuffer() {};
		virtual ~HardwareBuffer() {};
		virtual void* lock() = 0;
		virtual void unlock() = 0;
		virtual int getNumElements() const = 0;
	};

	class HardwareBufferManager; // forward declaration

	class HardwareBufferManager
	{
	protected:
		HardwareBufferManager(HardwareBufferManager *instance) { gInstance = instance; };

		typedef std::list<HardwareBuffer*> BufferList;
		BufferList mBuffers;

	public:
		static HardwareBufferManager* getManager() { return gInstance; };
		virtual HardwareBuffer* createBuffer(int elementSize, int numElements) = 0;

	private:
		static HardwareBufferManager* gInstance;
	};

} /* raytracer */

#endif /* _HARDWARE_BUFFER_H_ */
