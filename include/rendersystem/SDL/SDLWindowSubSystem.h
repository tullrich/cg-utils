#ifndef _SDL_WINDOW_SUBSYSTEM_H_
#define _SDL_WINDOW_SUBSYSTEM_H_

#include "../WindowSubSystem.h"
#include <SDL.h>
#include "SDLWindow.h"

namespace raytracer {
	
class SDLWindowSubSystem : public WindowSubSystem
{
	public:
		SDLWindowSubSystem() {};
		virtual ~SDLWindowSubSystem() {};

		virtual void start();
		virtual void stop();
		virtual void pollEvent();
	protected:
		void notifyWindow(SDL_Event &e);
		virtual Window* createWindowImpl(const string& windowTitle);
};

} /* namespace raytracer */


#endif