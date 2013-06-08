/*
 * TimedLoop.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */
#include "stdafx.h"
#include "RenderLoop.h"


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


namespace shs {

RenderLoop::RenderLoop(IrrlichtDevice * context) :
		frameDeltaTime(1.f), runLoop(false), device(context) {

	if (device) {
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		gui = device->getGUIEnvironment();
	} else {
		//Perhaps there should be some exceptions
	}

}

f32 RenderLoop::getFrameDeltaTime() const {
	return frameDeltaTime;
}


RenderLoop::~RenderLoop() {
	// TODO Auto-generated destructor stub
}

void RenderLoop::run() {
	runLoop = true;

	int lastFPS = -1;

	u32 then = device->getTimer()->getTime();

	while (device->run() && runLoop) {

		if (device->isWindowActive()) {

			const u32 now = device->getTimer()->getTime();
			frameDeltaTime = (f32) (now - then) / 1000.f; // Time in seconds
			then = now;

			beforeRender();

			driver->beginScene(true, true, SColor(255, 100, 101, 140));

			render();

			driver->endScene();

			afterRender();


		} else {
			device->yield();
		}
	}

}

f32* RenderLoop::getFrameDeltaTimePtr() {
	f32* tmp = &frameDeltaTime;
	return tmp;
}

void RenderLoop::stop() {
	runLoop = false;
}

} /* namespace ShootSpacer */
