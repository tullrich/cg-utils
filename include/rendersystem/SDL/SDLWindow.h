#ifndef _SDL_WINDOW_H
#define _SDL_WINDOW_H

#include "Window.h"
#include "SDL.h"

namespace raytracer {
		
	class SDLWindow : public Window
	{
	public:
		SDLWindow(const string &title) : Window(title), mSDLWin(NULL), mSDLWinID(0)  {};
		virtual ~SDLWindow();
		virtual uint32_t getID() { return mSDLWinID; }
		void notifyWindowEvent(SDL_Event &e);

		virtual void init(const string &windowTitle);
		virtual void swapBuffers();

	private:
		void readyMouseButtonEvent(SDL_Event &e);

		Uint32 mSDLWinID;
		SDL_Window *mSDLWin;
	};

} /* namespace raytracer */

#endif	