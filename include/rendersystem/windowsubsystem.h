#ifndef _WINDOW_SUBSYSTEM_
#define _WINDOW_SUBSYSTEM_ 

#include "common.h"
#include "camera.h"
#include <SDL.h>
#include <map>
#include <set>

namespace raytracer {

	class RenderSystem; // forward declaration
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
		Window() : mSDLWin(NULL), mSDLWinID(0), mHeight(920), mWidth(920) {};
		virtual ~Window();

		void init(const string &windowTitle);
		void swapBuffers();
		Uint32 getID() { return mSDLWinID; }
		void notifyWindowEvent(SDL_Event &e);
		void addWindowListener(WindowListener *listener);
		void removeWindowListener(WindowListener *listener);
		void setCamera(Camera *c);

		int getHeight() const { return mHeight; }
		int getWidth() const { return mWidth; }
	protected:
		void readyMouseButtonEvent(SDL_Event &e);
		void fireInputEvent(InputType type, const std::string key, int x = 0, int y = 0);
		void fireMouseMotionEvent(int x, int y, int xrel, int yrel);
	private:
		typedef std::set<WindowListener*> WindowListenerSet;
		WindowListenerSet mListeners;

		int mHeight, mWidth;

		Uint32 mSDLWinID;
		SDL_Window *mSDLWin;
		SDL_Renderer *mSDLRenderer;

		Camera *mCamera;
	};


	class WindowSubSystem
	{
	public:
		WindowSubSystem() {};

		void start();
		void stop();
		Window* createWindow(RenderSystem *rs, const string& windowTitle);
		void pollEvent();
	protected:
		void notifyWindowEvent(SDL_Event &e);
	private:
		typedef std::map<Uint32, Window*> WindowMap;
		WindowMap mWindows;
	};

} /* raytracer */

#endif /* _WINDOW_SUBSYSTEM_ */
