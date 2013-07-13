#include "rendersystem/SDL/SDLWindowSubSystem.h"

namespace raytracer {

	void SDLWindowSubSystem::start()
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
		{
	        std::cout << SDL_GetError() << std::endl;
    	}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		if(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1) == -1)
		{
	        std::cout << SDL_GetError() << std::endl;
		}
		if(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8) == -1)
		{
	        std::cout << SDL_GetError() << std::endl;
		}

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		 
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	}

	Window* SDLWindowSubSystem::createWindowImpl(const string &windowTitle)
	{
		return new SDLWindow(windowTitle);
	}

	void SDLWindowSubSystem::stop()
	{
		SDL_Quit();
	}

	void SDLWindowSubSystem::notifyWindow(SDL_Event &e)
	{
		WindowMap::iterator i = mWindows.find(e.window.windowID);
		if(i != mWindows.end())
		{
			if(e.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				delete (*i).second;
				mWindows.erase(i);
			}
			else
			{
				static_cast<SDLWindow*>((*i).second)->notifyWindowEvent(e);
			}
		}
	}

	void SDLWindowSubSystem::pollEvent()
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					std::cout << "SDL_QUIT" << std::endl;
					exit(0);
					break;
				case SDL_WINDOWEVENT:
				case SDL_KEYDOWN:
				case SDL_KEYUP:
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
					notifyWindow(e);
					break;

			}
		}
	}

} /* namespace raytracer  */