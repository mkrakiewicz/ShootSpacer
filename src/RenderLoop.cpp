/*
 * TimedLoop.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
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

irr::f32 RenderLoop::frameDeltaTime = 1.f;

RenderLoop::RenderLoop(const GameContext & _context) :
		isRunning(false), context(_context) {

	device = this->context.device;

	if (device) {

		driver = context.driver;
		smgr = context.smgr;
		gui = context.gui;
	} else {
		//Perhaps there should be some exceptions
	}

}

f32 RenderLoop::getFrameDeltaTime() {
	return frameDeltaTime;
}

RenderLoop::~RenderLoop() {

}

void RenderLoop::run() {
	isRunning = true;

	int lastFPS = -1;

	u32 then = device->getTimer()->getTime();

	while (device->run() && isRunning) {

		if (device->isWindowActive()) {

			const u32 now = device->getTimer()->getTime();
			frameDeltaTime = (f32) (now - then) / 1000.f; // Time in seconds
			then = now;
			driver->beginScene(true, true, SColor(255, 33, 33, 33));

			beforeRender();

			render();

			afterRender();

			driver->endScene();

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
	isRunning = false;
}

} /* namespace ShootSpacer */
