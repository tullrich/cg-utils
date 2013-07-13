#ifndef _ROOT_H_
#define _ROOT_H_ 

#include "common.h"
#include "mesh.h"
#include "SceneGraph.h"
#include "camera.h"
#include "light.h"
#include "import/assetloader.h"
#include "rendersystem/rendersystem.h"

namespace raytracer {

	class FrameListener
	{
	public:
		virtual void frameStart(float timeStep) {};
		virtual void frameEnd(float timeStep) {};
	};

	class Root : public Singleton<Root>, public MovableVisitor, public RenderableVisitor
	{
		friend class Singleton<Root>;

	public:
		virtual ~Root() {};
		void initialise(const string &windowTitle = "");
		RenderSystem* getRenderSystem();

		Mesh* getMesh(const string &fileName);
		Entity* createEntity(const string &fileName);
		Light* createLight(Light::Type type, const std::string &name = "");
		Camera* createCamera();
		void setMainCamera(Camera *c);
		void renderObject(const Renderable &r);
		virtual void visit(const Movable &e);
		virtual void visit(const Renderable &e);

		void addFrameListener(FrameListener *f);
		void removeFrameListener(FrameListener *f);

		SceneGraph* getSceneGraph() { return mSceneGraph; }
		Window *getMasterWindow() { return mMasterWindow; }
		void start();

		void setDebugOverride(bool override) { mDebugOverride = override; }
	protected:
		Root();
		bool renderFrame();
		void pollEvent();
		RenderSystem* initialiseRenderSystem(const string &windowTitle);

		void fireFrameStart();
		void fireFrameEnd();

	private:
		bool mHasInitialised;
		SceneGraph *mSceneGraph;

		typedef std::list<Camera*> CameraList;
		CameraList mCameras;
		Camera *mMainCamera;

		typedef std::list<Light*> LightList;
		LightList mLights;

		typedef std::list<FrameListener*> FrameListenerList;
		FrameListenerList mFrameListeners;

		unsigned long mLastFrameStart, mLastFrameEnd;

		bool mDebugOverride;

#ifdef RENDERSYSTEM_ENABLED
		RenderSystem *mRenderSystem;
		Window *mMasterWindow;
#endif
	};

} /* raytracer */

#endif /* _ROOT_H_ */
