#ifndef _APPLICATION_BASE_H
#define _APPLICATION_BASE_H

#include "common.h"
#include "root.h"

namespace raytracer {
	
	class ApplicationBase : public FrameListener, public WindowListener
	{
	public:
		ApplicationBase();

	protected:
		Root &mRoot;
		Camera *mCamera;
		SceneGraph *mScene;
	};

} /* namespace raytracer */


#endif