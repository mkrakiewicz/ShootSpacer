/*
 * ShootSpacer.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Menu.h"
#include "Ship.h"
#include "Planet.h"
#include "ShootSpacerEvent.h"

#include "ShootSpacer.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

ShootSpacer* ShootSpacer::_instance = NULL;
int ShootSpacer::_referenceCount = 0;


ShootSpacer::ShootSpacer():
	context(this->createIrrlichtDevice())
		{

	/**
	 *  Init the game
	 */
	initialize();
}

void ShootSpacer::initialize() {

	device = context.device;
	smgr = context.smgr;
	driver = context.driver;
	gui = context.gui;


	enableFrameIndependentMovement();

	eventReceiver = new ShootSpacerEvent(this);

	device->setEventReceiver(eventReceiver);
	device->setWindowCaption(windowTitle.c_str());

	menu = new Menu(context);

	ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0, 30, -140),
			vector3df(0, 5, 0));

//	cam->setAspectRatio(16/9.f);
}


void ShootSpacer::toggleGameState() {
//	if (state == MENU) {
//		state = RUN;
//		menu->stop();
//	} else {
//		state = MENU;
//		stop();
//	}
}


void ShootSpacer::exit() {
	if (stateRunner.hasNext())
		stateRunner.stopCurrentState();

}

void ShootSpacer::cleanup() {

	delete menu;

	delete eventReceiver;

}

void ShootSpacer::enableFrameIndependentMovement() {
	Object3D::setFrameDeltaReference(RenderLoop::getFrameDeltaTimePtr());
}

void ShootSpacer::handleEvent(const irr::SEvent& event) {
	stateRunner.handleEvent(event);
}

ShootSpacer::~ShootSpacer() {
	cleanup();
}



IrrlichtDevice* ShootSpacer::createIrrlichtDevice() {

	SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
	params.AntiAlias = true;
	params.DriverType = video::EDT_OPENGL;
	params.WindowSize = core::dimension2d<u32>(1024, 768);
	params.Fullscreen = false;

	return createDeviceEx(params);
}

void ShootSpacer::startGame() {


	stateRunner.addState(menu);
	bool run = true;

	while (stateRunner.hasNext() && device->run()) {
		stateRunner.runNext();
	}

}

ShootSpacer* shs::ShootSpacer::getInstance() {

	if (NULL == _instance) {
		_instance = new ShootSpacer();
	}
	_referenceCount++;
	return _instance;

}

void shs::ShootSpacer::releaseInstance() {
	_referenceCount--;
	if ((0 == _referenceCount) && (NULL != _instance)) {
//		_instance->cleanup();
		delete _instance;
		_instance = NULL;
	}
}

} /* namespace shootspacer */
