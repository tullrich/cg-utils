#include "rendersystem/windowsubsystem.h"
#include "SDL.h"
#include "GL/glew.h"

namespace raytracer {


	Window::~Window()
	{
		SDL_DestroyRenderer(mSDLRenderer);
    	SDL_DestroyWindow(mSDLWin);
	}

	void Window::init(const string &windowTitle)
	{
		mSDLWin = NULL;
	    mSDLWin = SDL_CreateWindow(windowTitle.c_str(), 100, 100, mHeight, mWidth,
	    	SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	    mSDLWinID = SDL_GetWindowID(mSDLWin);

	    //SDL_GLContext glcontext = SDL_GL_CreateContext(mSDLWin);

	    if (mSDLWin == NULL){
	        std::cout << SDL_GetError() << std::endl;
	    }

     	mSDLRenderer = nullptr;
	    mSDLRenderer = SDL_CreateRenderer(mSDLWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	    if (mSDLRenderer == nullptr){
	        std::cout << SDL_GetError() << std::endl;
	    }

	    int multiSampBuffers = -1;
	    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &multiSampBuffers);

	    int multiSamps = -1;
	    SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &multiSamps);

	    std::cout << "SDL_GL_MULTISAMPLEBUFFERS: " << multiSampBuffers
	    	<< " SDL_GL_MULTISAMPLESAMPLES:" << multiSamps << std::endl;

	    if (GLEW_ARB_multisample)
    	{
    		std::cout << "GLEW_ARB_multisample" << std::endl; 
    	}
    	else
    	{
    		std::cout << "no GLEW_ARB_multisample!" << std::endl; 
    	}

	    if (GLEW_ARB_multisample)
    	{
    		std::cout << "GLEW_ARB_multisample" << std::endl; 
    	}
    	else
    	{
    		std::cout << "no GLEW_ARB_multisample!" << std::endl; 
    	}
	}

	void Window::swapBuffers()
	{
		SDL_GL_SwapWindow(mSDLWin);
	}

	void Window::fireInputEvent(InputType type, const std::string key, int x, int y)
	{
		InputEvent e;
		e.type = type;
		e.key = key;
		e.x = x;
		e.y = y;
		WindowListenerSet::iterator i = mListeners.begin();
		for(; i != mListeners.end(); i++)
		{
			(*i)->onInputEvent(e);
		}
	}

	void Window::readyMouseButtonEvent(SDL_Event &e)
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

	void Window::fireMouseMotionEvent(int x, int y, int xrel, int yrel)
	{
		MouseMotionEvent e;
		e.x = x;
		e.y = y;
		e.xDelta = xrel;
		e.yDelta = yrel;
		WindowListenerSet::iterator i = mListeners.begin();
		for(; i != mListeners.end(); i++)
		{
			(*i)->onMouseMotionEvent(e);
		}
	}

	void Window::notifyWindowEvent(SDL_Event &e)
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

	void Window::addWindowListener(WindowListener *listener)
	{
		mListeners.insert(listener);
	}

	void Window::removeWindowListener(WindowListener *listener)
	{
		WindowListenerSet::iterator i = mListeners.find(listener);
		if(i != mListeners.end())
			mListeners.erase(listener);
	}

	void Window::setCamera(Camera *c)
	{
		mCamera = c;
		mCamera->setWindow(this);
	}

	void WindowSubSystem::start()
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

	Window* WindowSubSystem::createWindow(RenderSystem *rs, const string& windowTitle)
	{
		Window *win = new Window();
		win->init(windowTitle);
		mWindows[win->getID()] = win;
		return win;
	}

	void WindowSubSystem::stop()
	{
		SDL_Quit();
	}

	void WindowSubSystem::notifyWindowEvent(SDL_Event &e)
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
				(*i).second->notifyWindowEvent(e);
			}
		}
	}

	void WindowSubSystem::pollEvent()
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
					notifyWindowEvent(e);
					break;

			}
		}
	}

} /* namespace raytracer */
