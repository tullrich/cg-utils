#ifndef _WINDOW_SUB_SYSTEM_H_
#define _WINDOW_SUB_SYSTEM_H_

#include "common.h"
#include <map>
#include "Window.h"

namespace raytracer {

	class RenderSystem; // forward declaration
	class Camera; // forward declaration


	class WindowSubSystem
	{
	public:
		WindowSubSystem() {};
		virtual ~WindowSubSystem() {};

		virtual void start() = 0;
		virtual void stop() = 0;
		Window* createWindow(RenderSystem *rs, const string& windowTitle);
		virtual void pollEvent();
	protected:
		virtual Window* createWindowImpl(const string& windowTitle) = 0;
		
		typedef std::map<uint32_t, Window*> WindowMap;
		WindowMap mWindows;
	};

} /* namespace raytracer  */

#endif