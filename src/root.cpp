#include "root.h"

namespace raytracer {
	
	Root::Root() : mHasInitialised(false), mRenderSystem(NULL), mDebugOverride(false)
	{
/*		mWorkQueue = new WorkQueue();
		mBackgroundQueue = new BackgroundQueue();

		mBackgroundQueue->initialise(*mWorkQueue);
		mWorkQueue->startup();*/
	}

	void Root::initialise(WindowSubSystem *sys, const string &windowTitle)
	{
		if (mHasInitialised)
			return;

		mRenderSystem = initialiseRenderSystem(sys, windowTitle);
		mRenderSystem->setClearColor(RGBA(0.7f, 0.7f, 0.7f, 1.0f));
		mRenderSystem->setFog(FogParameters(RGB(0.7f, 0.7f, 0.7f), 10.0f, 35.0f, 1.0f));
		mSceneGraph = new SceneGraph();

		mLastFrameStart = mLastFrameEnd = getNow();

		mHasInitialised = true;
	}

	RenderSystem* Root::initialiseRenderSystem(WindowSubSystem *sys, const string &windowTitle)
	{
#ifdef RENDERSYSTEM_ENABLED
		RenderSystem *rs = new CompiledRenderSystem(sys);
		mMasterWindow = rs->initialise(windowTitle);

		if(mMasterWindow)
			return rs;

		delete rs;
		return NULL;
#else
		return NULL;
#endif
	}

	RenderSystem* Root::getRenderSystem()
	{
#ifdef RENDERSYSTEM_ENABLED
		return mRenderSystem;
#else
		return NULL;
#endif
	}


	Mesh* Root::getMesh(const string &fileName)
	{
		std::unique_ptr<AssetLoader> ld = AssetLoaderFactory::getReaderForFilename(fileName);
		Mesh *m = NULL;
		if(ld)
		{
			ld->open(fileName);
			m = ld->loadMeshByName();
			if(!m)
			{
				std::cout << "Error in Root::createMesh, no mesh!" << std::endl; 
			}
			return m;
		}

		return m;
	}

	Entity* Root::createEntity(const string &fileName)
	{
		Mesh *m = getMesh(fileName);

		Entity *e = NULL;
		if(m)
		{
			e = new Entity(m);
		}
		else
		{
			std::cout << "Cannot load mesh from fileName " << fileName << std::endl; 
		}
		return e;
	}

	Light* Root::createLight(Light::Type type, const std::string &name)
	{
		Light *l = NULL;
		switch(type)
		{
			case Light::LIGHT_OMNI:
				l = new PointLight(name);
				break;
			default:
				std::cout << "Error creating unsupported Light::Type" << std::endl; 
		}

		if(l)
		{
			mLights.push_back(l);
		}

		return l;
	}

	Camera* Root::createCamera()
	{
		Camera *c = NULL;
		if (mHasInitialised)
		{
			c = new Camera();
			mCameras.push_back(c);
			mMasterWindow->setCamera(c); // TODO: temporary setup
		}
		return c;
	}

	void Root::setMainCamera(Camera *c)
	{
		mMainCamera = c;
	}

	void Root::start()
	{
		if(!mRenderSystem)
		{
			std::cout << "Root Error in start() no RenderSystem!" << std::endl; 
		}

		while(true)
		{
			pollEvent();

			if(!renderFrame())
				break;
		}
	}

	void Root::pollEvent()
	{
		if(mRenderSystem)
		{
			mRenderSystem->pollEvent();
		}
	}

	bool Root::renderFrame()
	{
		mRenderSystem->clear();

		fireFrameStart();

		if(mMainCamera)
		{
			mRenderSystem->setProjectionMatrix(mMainCamera->getProjectionMatrix());
			mRenderSystem->setViewMatrix(mMainCamera->getViewMatrix());
		}
		else
		{
			// load identity
			mRenderSystem->setProjectionMatrix();
			mRenderSystem->setViewMatrix();
		}

		mRenderSystem->useLights(mLights);
		mSceneGraph->findVisibleObjects(this);
		mSceneGraph->drawDebugBounds(mDebugOverride, *this);

		mRenderSystem->renderGUI();

		fireFrameEnd();
		mRenderSystem->swapAllWindows();
		return true;
	}

	void Root::fireFrameStart()
	{
		unsigned long now = getNow();
		float timeStep = (now - mLastFrameStart) / 1000000.0f;
		mLastFrameStart = now;

		FrameListenerList::iterator i = mFrameListeners.begin();
		for(; i != mFrameListeners.end(); i++)
		{
			(*i)->frameStart(timeStep);
		}
	}

	void Root::fireFrameEnd()
	{	
		unsigned long now = getNow();
		float timeStep = (now - mLastFrameEnd) / 1000000.0f;
		mLastFrameEnd = now;

		FrameListenerList::iterator i = mFrameListeners.begin();
		for(; i != mFrameListeners.end(); i++)
		{
			(*i)->frameEnd(timeStep);
		}
	}

	void Root::renderObject(const Renderable &r)
	{
		RenderOperation ro;
		r.getRenderOperation(ro);

		Matrix4 worldTransform;
		r.getWorldTransform(worldTransform);
		mRenderSystem->setCurrentMaterial(r.getMaterial());
		mRenderSystem->setWorldMatrix(worldTransform);
		mRenderSystem->updateGPUParameters();

		mRenderSystem->render(ro);
	}

	void  Root::visit(const Movable &e)
	{
		e.visitRenderables(*this);
	}

	void  Root::visit(const Renderable &e)
	{ 
		renderObject(e);
	}

	void Root::addFrameListener(FrameListener *f)
	{
		FrameListenerList::iterator i = mFrameListeners.begin();
		for(; i != mFrameListeners.end(); i++)
		{
			if ((*i) == f)
				return;
		}
		mFrameListeners.push_back(f);
	}

	void Root::removeFrameListener(FrameListener *f)
	{
		FrameListenerList::iterator i = mFrameListeners.begin();
		for(; i != mFrameListeners.end(); i++)
		{
			if ((*i) == f)
			{
				mFrameListeners.erase(i);
				return;
			}
		}
	}
	
} /* namespace raytracer */
