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
#include "Level.h"
#include "LevelManager.h"

#include "ShootSpacer.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

const irr::IrrlichtDevice*& ShootSpacer::getDevice() const {
	return device;
}

const irr::video::IVideoDriver*& ShootSpacer::getDriver() const {
	return driver;
}

const ShootSpacerEvent*& ShootSpacer::getEventReceiver() const {
	return eventReceiver;
}

const irr::gui::IGUIEnvironment*& ShootSpacer::getGui() const {
	return gui;
}

const Menu*& ShootSpacer::getMenu() const {
	return menu;
}

const irr::scene::ISceneManager*& ShootSpacer::getSmgr() const {
	return smgr;
}

const shs::FSMStateRunner& ShootSpacer::getStateRunner() const {
	return stateRunner;
}

ShootSpacer::ShootSpacer() {

	/**
	 *  Init the game
	 */
	initialize();
}

void ShootSpacer::initialize() {

	hasGameStarted = false;

	device = this->createIrrlichtDevice();
	smgr = device->getSceneManager();
	driver = device->getVideoDriver();
	gui = device->getGUIEnvironment();

	enableFrameIndependentMovement();

	eventReceiver = new ShootSpacerEvent(this);

	device->setEventReceiver(eventReceiver);
	device->setWindowCaption(windowTitle.c_str());

	menu = new Menu(this);

}

void ShootSpacer::toggleGameState() {

}

void ShootSpacer::exit() {
	if (stateRunner.hasNext())
		stateRunner.endCurrentState();

}

void ShootSpacer::cleanup() {

	// all objects created with "new" operator must be deleted
	delete menu;
	delete eventReceiver;
	device->drop();

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

	if (!hasGameStarted) {

		hasGameStarted = true;

		LevelManager mgr(context);

		//TODO: implement level manager
		Level *testLevel = mgr.getCurrentLevel();

		MainMenu main_menu(context);

		stateRunner.saveStateAs(L"current_level", testLevel);
		stateRunner.saveStateAs(L"menu", menu);
		stateRunner.saveStateAs(L"main_menu", &main_menu);

		stateRunner.appendStateWithName("main_menu");

		while (stateRunner.hasNext() && device->run()) {
			stateRunner.runCurrentState();
		}
	}

}

//////////////////////////////////////////////////////////////////////////////

ShootSpacerInstance* ShootSpacerInstance::_instance = NULL;
int ShootSpacerInstance::_referenceCount = 0;

ShootSpacerInstance* shs::ShootSpacerInstance::getInstance() {

	if (NULL == _instance) {
		_instance = new ShootSpacerInstance();
	}
	_referenceCount++;
	return _instance;

}

void shs::ShootSpacerInstance::releaseInstance() {
	_referenceCount--;
	if ((0 == _referenceCount) && (NULL != _instance)) {
		delete _instance;
		_instance = NULL;
	}
}

ShootSpacerInstance::~ShootSpacerInstance() {
}

ShootSpacerInstance::ShootSpacerInstance() :
		ShootSpacer() {
	// creates the instance
}

} /* namespace shs */
