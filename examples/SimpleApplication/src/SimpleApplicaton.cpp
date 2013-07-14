#include "SimpleApplication.h"

SimpleApplication::SimpleApplication()
	: mCenter(0.0f, 0.0f, 0.0f) , mMouseMotion(false), mBoost(false), mDebug(false), mRotate(false)
	, mMovingForward(false), mMovingBackward(false), mStrafingLeft(false), mStrafingRight(false)
	, mSelected(NULL)
{
	setupCamera();
	setupScene();
}

void SimpleApplication::setupCamera()
{
	mCamera->setPosition(Vector3(0.0f, 3.0f, 20.0f));
}

void SimpleApplication::setupScene()
{
	mScene = mRoot.getSceneGraph();
	SceneNode *sn = mScene->getRoot()->createChild(Vector3(0.0f, 0.0f, 5.0f), Vector3(1.0f, 1.0f, 1.0f), glm::angleAxis(180.0f, Vector3(0.0f, 1.0f, 0.0f)));
	//sn->attachMovable( mRoot.createEntity("Bats/Cape.obj"));
	//sn->attachMovable( mRoot.createEntity("Iron_Man/Iron_Man.obj"));
	Entity *mIronMan = mRoot.createEntity("Iron_Man/Iron_Man.obj");
	sn->attachMovable(mIronMan );

	SceneNode *sn2 = mScene->getRoot()->createChild(Vector3(0.0f, -2.0f, 0.0f));
	sn2->attachMovable( mRoot.createEntity("Sinbad/Sinbad.mesh.xml"));

	SceneNode *sn3 = sn2->createChild(Vector3(0.0f, 3.0f, 0.0f));
	sn3->attachMovable( mRoot.createEntity("CornellBox-Geraldo.obj") );

	SceneNode *sn4 = mScene->getRoot()->createChild(Vector3(0.0f, 0.0f, -4.0f));
	Entity *teapot = mRoot.createEntity("texture-teapot.obj");
	sn4->attachMovable( teapot );


	Light *l = mRoot.createLight(Light::LIGHT_OMNI, "MainLamp");
	l->setColor(RGB(0.15f, 0.15f, 0.15f), RGB(0.8f, 0.8f, 0.8f), RGB(1.0f, 1.0f, 1.0f));
	SceneNode *sn5 = mScene->getRoot()->createChild(Vector3(0.0f, 0.0f, 0.0f));
	sn5->attachMovable( l );
}

void SimpleApplication::frameStart(float timeStep)
{
	if(mRotate)
	{
		float angleDeg = timeStep * 45.0f;
		Vector3 pMinusC = mCamera->getPosition() - mCenter;
		Quaternion q = glm::angleAxis(angleDeg, Vector3(0.0f, 1.0f, 0.0f));
		Vector3 F = q * pMinusC + mCenter;
		mCamera->setPosition(F);
		//mCamera->rotate(q);
		mCamera->lookAt(Vector3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		handleMove(timeStep);
	}

	//rotateIronMan(timeStep);
}

void SimpleApplication::handleMove(float timeStep)
{
	float velocity = (mBoost) ? 20.0f : 7.0f;
	if (mMovingForward)
	{
		mCamera->move(mCamera->getOrientation() * Vector3(0.0f, 0.0f, -velocity) * timeStep);
	}
	else if(mMovingBackward)
	{
		mCamera->move(mCamera->getOrientation() * Vector3(0.0f, 0.0f, velocity) * timeStep);
	}

	if (mStrafingLeft)
	{
		mCamera->move(mCamera->getOrientation() * Vector3(-velocity, 0.0f, 0.0f) * timeStep);
	}
	else if(mStrafingRight)
	{
		mCamera->move(mCamera->getOrientation() * Vector3(velocity, 0.0f, 0.0f) * timeStep);
	}
}

void SimpleApplication::onInputEvent(const InputEvent &e)
{

	if(e.key == "Up" || e.key == "W")
	{
		if(mMovingForward && e.type == InputType::KEYUP)
			mMovingForward = false;
		else
			mMovingForward = true;
	}

	if(e.key == "Down" || e.key == "S")
	{
		if(mMovingBackward && e.type == InputType::KEYUP)
			mMovingBackward = false;
		else
			mMovingBackward = true;
	}

	if(e.key == "Left" || e.key == "A")
	{
		if(mStrafingLeft && e.type == InputType::KEYUP)
			mStrafingLeft = false;
		else
			mStrafingLeft = true;
	}

	if(e.key == "Right" || e.key == "D")
	{
		if(mStrafingRight && e.type == InputType::KEYUP)
			mStrafingRight = false;
		else
			mStrafingRight = true;
	}

	if(e.key == "Left Shift")
	{
		if(mBoost && e.type == InputType::KEYUP)
			mBoost = false;
		else
			mBoost = true;
	}

	if(e.key == "RightMouse")
	{
		if(mMouseMotion && e.type == InputType::MOUSEUP)
			mMouseMotion = false;
		else
			mMouseMotion = true;
	}

	if(e.key == "LeftMouse")
	{
		if(e.type == InputType::MOUSEUP)
		{
			selectEntity(e.x, e.y);
		}
	}

	if(e.key == "R" && e.type == InputType::KEYUP)
	{
		mRotate = !mRotate;
		std::cout << "Rotation Mode " << ((mRotate) ? "ENABLED" : "DISABLED") << std::endl; 
	}

	if(e.key == "P" && e.type == InputType::KEYUP)
	{
		mDebug = !mDebug;
		std::cout << "Debug Mode " << ((mDebug) ? "ENABLED" : "DISABLED") << std::endl; 
		mRoot.setDebugOverride(mDebug);
	}

	if (mDebug)
	{
		std::cout << "Key "<< ((e.type == InputType::KEYUP) ? "PRESSED":"RELEASED")
			<< ": '" << e.key << "' " << std::endl; 
	}
}

void SimpleApplication::selectEntity(int x, int y)
{
	Ray ray = mCamera->genPickRay(x, y);
/*		if(!mRay)%  
	{
		mRay = new RayRenderable(ray);
		mScene->addDebugRenderable(mRay);
	}
	else
	{
		mRay->update(ray);
	}*/

	TraceResult result;

	if(mSelected)
	{
		mSelected->setDebug(false);
		mSelected = NULL;
	}
	if(mScene->trace(ray, result))
	{
		mSelected = reinterpret_cast<Entity*>(result.mMovable);
		mSelected->setDebug(true);
	}
}

void SimpleApplication::onMouseMotionEvent(const MouseMotionEvent &e)
{
	if(!mMouseMotion)
		return;

/*		Quaternion q = glm::angleAxis(angleDeg, Vector3(0.0f, 1.0f, 0.0f));
	mCamera->move(mCamera->getOrientation() * Vector3(0.0f, 0.0f, -5.0f));*/
	Quaternion xRot = glm::angleAxis(0.5f * ((float)e.xDelta), Vector3(0.0f, -1.0f, 0.0f));
	Quaternion yRot = glm::angleAxis(0.5f * ((float)e.yDelta), Vector3(-1.0f, 0.0f, 0.0f));

	Quaternion combined = mCamera->getOrientation() * xRot * yRot;
	Vector3 forward;
	Matrix4 rot = glm::toMat4(combined);
		forward.x = rot[2][0];
    forward.y = rot[2][1];
    forward.z = rot[2][2];
	Vector3 right = cross(forward, Vector3(0.0f, 1.0f, 0.0f));
	Vector3 perpUp = cross(right, forward);
	vec3 currentUp = combined * vec3(0.0f, 1.0f, 0.0f);
	quat correction = rotationBetweenVectors(currentUp, perpUp);
	mCamera->setOrientation(correction * combined);
}

int main()
{
	SimpleApplication sa;
	Root::getInstance().start();

	return 0;
}