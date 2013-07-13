#include "rendersystem/SDL/SDLWindow.h"

namespace raytracer {
	
	SDLWindow::~SDLWindow()
	{
    	SDL_DestroyWindow(mSDLWin);
	}

	void SDLWindow::init(const string &windowTitle)
	{
		mSDLWin = NULL;
	    mSDLWin = SDL_CreateWindow(windowTitle.c_str(), 100, 100, mHeight, mWidth,
	    	SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	    mSDLWinID = SDL_GetWindowID(mSDLWin);

	    //SDL_GLContext glcontext = SDL_GL_CreateContext(mSDLWin);

	    if (mSDLWin == NULL){
	        std::cout << SDL_GetError() << std::endl;
	    }
	}

	void SDLWindow::swapBuffers()
	{
		SDL_GL_SwapWindow(mSDLWin);
	}

	void SDLWindow::readyMouseButtonEvent(SDL_Event &e)
	{
		std::string btn;
		if(e.button.button == SDL_BUTTON_LEFT)
			btn = "LeftMouse";
		else if (e.button.button == SDL_BUTTON_RIGHT)
			btn = "RightMouse";

		InputType t;
		t = (e.type == SDL_MOUSEBUTTONDOWN) ? InputType::MOUSEDOWN : InputType::MOUSEUP;
		fireInputEvent(t, btn, e.button.x, e.button.y);
	}

	void SDLWindow::notifyWindowEvent(SDL_Event &e)
	{
		switch(e.type)
		{
			case SDL_WINDOWEVENT:
				break;
			case SDL_KEYDOWN:
				fireInputEvent(InputType::KEYDOWN, SDL_GetKeyName(e.key.keysym.sym));
				break;
			case SDL_KEYUP:
				fireInputEvent(InputType::KEYUP, SDL_GetKeyName(e.key.keysym.sym));
				break;
			case SDL_MOUSEMOTION:
				fireMouseMotionEvent(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				readyMouseButtonEvent(e);
				break;
			default:
				break;
		}
	}

} /* namespace raytracer */
