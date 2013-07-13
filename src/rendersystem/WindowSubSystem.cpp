#include "rendersystem/WindowSubSystem.h"

namespace raytracer {
	
	Window* WindowSubSystem::createWindow(RenderSystem *rs, const string& windowTitle)
	{
		Window *win = createWindowImpl(windowTitle);
		win->init(windowTitle);
		mWindows[win->getID()] = win;
		return win;
	}

	void WindowSubSystem::pollEvent()
	{
		exit(1); // unsupported op
	}

} /* namespace raytracer */
