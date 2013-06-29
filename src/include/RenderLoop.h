/*
 * RenderLoop.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

namespace shs {

class GameContext;

/**
 * Abstract base class for Menu and ShootSpacer
 */
class RenderLoop {
private:
	static irr::f32 frameDeltaTime;
protected:
	bool isRunning;

	const GameContext &context;

	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *gui;

	void run();
	virtual void beforeRender() = 0;
	virtual void afterRender() = 0;
	virtual void render() = 0;


//	RenderLoop():isRunning(false),device(0),driver(0),smgr(0),gui(0){
//	}

public:
	RenderLoop(const GameContext & context);
	virtual ~RenderLoop();

	static irr::f32 getFrameDeltaTime();
	static irr::f32* getFrameDeltaTimePtr();

	void stop();
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
