/*
 * TimedLoop.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */
#include "stdafx.h"
#include "ShootSpacer.h"
#include "RenderLoop.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

irr::f32 RenderLoop::frameDeltaTime = 1.f;

RenderLoop::RenderLoop(const ShootSpacer &parent) :
		isRunning(false), IrrlichtClassBase(parent) {
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

/////////////////////////////////////////////////////

IrrlichtClassBase::IrrlichtClassBase(const ShootSpacer &parent) :
		parent(parent), device(0), driver(0), smgr(0), gui(0) {

	this->device = this->parent.getDevice();

	if (device) {

		driver = parent.getDriver();
		smgr = parent.getSmgr();
		gui = parent.getGui();
	} else {
		//Perhaps there should be some exceptions
	}
}

IrrlichtClassBase::~IrrlichtClassBase() {
}

} /* namespace ShootSpacer */

