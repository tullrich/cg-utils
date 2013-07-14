#ifndef _SIMPLE_APPLICATION_H_
#define _SIMPLE_APPLICATION_H_

#include "cgutils.h"

using namespace raytracer;

class SimpleApplication : public ApplicationBase
{
public:
	SimpleApplication();

	virtual void onInputEvent(const InputEvent &e);
	virtual void onMouseMotionEvent(const MouseMotionEvent &e);
	virtual void frameStart(float timeStep);

private:
	void setupScene();
	void setupCamera();

	void handleMove(float timeStep);
	void selectEntity(int x, int y);

	Entity *mSelected;
	Vector3 mCenter;
	bool mMovingForward, mMovingBackward, mStrafingLeft, mStrafingRight;
	bool mMouseMotion, mBoost, mDebug, mRotate;
};

#endif