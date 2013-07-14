#include "ApplicationBase.h"
#include "rendersystem/SDL/SDLWindowSubSystem.h"

namespace raytracer {
	
	ApplicationBase::ApplicationBase() : mRoot(Root::getInstance())
	{
		/* Setup the listeners so we receive callbacks */
		mRoot.initialise(new SDLWindowSubSystem());
		mRoot.addFrameListener(this);
		mRoot.getMasterWindow()->addWindowListener(this);

		mCamera = mRoot.createCamera();
		mRoot.setMainCamera(mCamera);

		mScene = mRoot.getSceneGraph();
		std::cout << "Application Ready" << std::endl; 
	}

} /* namespace raytracer */
