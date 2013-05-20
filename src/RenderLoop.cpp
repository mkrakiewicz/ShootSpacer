/*
 * TimedLoop.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */
#include "stdafx.h"
#include "RenderLoop.h"

namespace shs {

RenderLoop::RenderLoop(IrrlichtDevice * context) :
		runLoop(false), device(context) {

	if (device) {
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		gui = device->getGUIEnvironment();
	} else {
		//Perhaps there should be some exceptions
	}

}

RenderLoop::~RenderLoop() {
	// TODO Auto-generated destructor stub
}

void RenderLoop::run() {
	runLoop = true;

	while (device->run() && runLoop) {

		beforeRender();
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		gui->drawAll();

		driver->endScene();

		afterRender();
	}

}

} /* namespace ShootSpacer */
