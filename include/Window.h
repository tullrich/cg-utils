#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "common.h"
#include "camera.h"
#include <set>

namespace raytracer {

	class Camera; // forward declaration

	enum InputType
	{
		KEYUP,
		KEYDOWN,
		MOUSEUP,
		MOUSEDOWN,
	};

	struct InputEvent
	{
		InputType type;
		std::string key;
		union 
		{
			struct
			{
				int x;
				int y;
			};
		};
	};

	struct MouseMotionEvent
	{
 		int x;
 		int y;
 		int xDelta;
 		int yDelta;
	};

	class WindowListener
	{
	public:
		virtual void onResize() {}; //TODO
		virtual void onInputEvent(const InputEvent &e) {};
		virtual void onMouseMotionEvent(const MouseMotionEvent &e) {};
	};

	class Window
	{
	public:
		Window(const string& title) : mTitle(title), mHeight(920), mWidth(920) {};
		virtual ~Window() {};

		virtual void init(const string &windowTitle) = 0;
		virtual void swapBuffers() = 0;
		virtual uint32_t getID() = 0;
		void addWindowListener(WindowListener *listener);
		void removeWindowListener(WindowListener *listener);
		void setCamera(Camera *c);

		int getHeight() const { return mHeight; }
		int getWidth() const { return mWidth; }
	protected:
		void fireInputEvent(InputType type, const std::string key, int x = 0, int y = 0);
		void fireMouseMotionEvent(int x, int y, int xrel, int yrel);

		int mHeight, mWidth;

		Camera *mCamera;
		string mTitle;
		
	private:
		typedef std::set<WindowListener*> WindowListenerSet;
		WindowListenerSet mListeners;
	};

} /* namespace raytracer */

#endif