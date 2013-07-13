#include "Window.h"

namespace raytracer
{

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
}