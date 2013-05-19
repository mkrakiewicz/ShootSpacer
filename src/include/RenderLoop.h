/*
 * TimedLoop.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

/**
 * Abstract base class for Menu and ShootSpacer
 */
class RenderLoop {
protected:
	bool runLoop;

	IrrlichtDevice *device;
	IVideoDriver *driver;
	ISceneManager *smgr;
	IGUIEnvironment *gui;

public:
	RenderLoop(IrrlichtDevice * context);
	virtual ~RenderLoop();

	void run();

//	virtual void beforeRender() = 0;
//	virtual void afterRender() = 0;

};

/**
 *
 * Helper class to count FPS
 */
class FPSCounter {
protected:

	int currentFPS;
	int frameCounter;
	long lastTime;

	long tmp_current;

public:

	FPSCounter();
	void nextFrame();

	int getFPS() {
		return currentFPS;
	}
};

} /* namespace ShootSpacer */
#endif /* TIMEDLOOP_H_ */
