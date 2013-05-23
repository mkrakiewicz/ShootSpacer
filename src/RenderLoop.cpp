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

RenderLoop::RenderLoop(IrrlichtDevice * context) :
		runLoop(false), device(context), frameDeltaTime(0.f) {

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

			int fps = driver->getFPS();

			if (lastFPS != fps) {
				core::stringw tmp(L"ShootSpacer [");
				tmp += driver->getName();
				tmp += L"] fps: ";
				tmp += fps;

				device->setWindowCaption(tmp.c_str());
				lastFPS = fps;
			}
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
