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

const stringw ShootSpacer::windowTitle = (stringw(L"ShootSpacer ") + VERSION_INFO::CURRENT_VERSION_STRING + " ");

ShootSpacer::ShootSpacer() :
		FSMStateRenderLoop(createIrrlichtDevice()) {

	/**
	 *  Init the game
	 */
	initialize();
}

void ShootSpacer::initialize() {

	state = INIT;

	enableFrameIndependentMovement();

	eventReceiver = new ShootSpacerEvent(this);

	device->setEventReceiver(eventReceiver);
	device->setWindowCaption(windowTitle.c_str());

#ifdef SHS_DEV

#endif

	context = new GameContext(device);

	menu = new Menu(context);

	ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0, 30, -140),
			vector3df(0, 5, 0));

//	cam->setAspectRatio(16/9.f);
}

void ShootSpacer::render() {

	smgr->drawAll();
	gui->drawAll();
}

void ShootSpacer::toggleGameState() {
	if (state == MENU) {
		state = RUN;
		menu->stop();
	} else {
		state = MENU;
		stop();
	}
}

void ShootSpacer::displayGame() {
	context->gui->clear();

	context->gui->addStaticText(L"Game", rect<s32>(10, 10, 260, 22), true);

	run();
}

void ShootSpacer::exit() {
	if (state == RUN)
		stop();
	else
		menu->stop();
	state = EXIT;

}

void ShootSpacer::cleanup() {

#ifdef SHS_DEV

	delete node;
	delete testPlanet;

#endif

	delete menu;
	delete context;
	delete eventReceiver;
	device->drop();
}

void ShootSpacer::enableFrameIndependentMovement() {
	Object3D::setFrameDeltaReference(getFrameDeltaTimePtr());
}

void ShootSpacer::beforeRun() {
}

void ShootSpacer::beforeStop() {
}

ShootSpacer::~ShootSpacer() {
	cleanup();
}

void ShootSpacer::beforeRender() {

#ifdef SHS_DEV

	node->rotateNodeInLocalSpace(15, vector3df(0, 1, 0));
	node->rotateNodeInLocalSpace(15, vector3df(1, 0, 0));
	node->rotateNodeInLocalSpace(15, vector3df(0, 0, 1));

	testPlanet->rotateNodeInLocalSpace(5, vector3df(0, 1, 0));

#endif


}

void ShootSpacer::afterRender() {
	static int lastFPS = -1;
	int fps = driver->getFPS();

	if (lastFPS != fps) {
//		core::stringw tmp(L"ShootSpacer [");
//		tmp += driver->getName();
//		tmp += L"] fps: ";
//		tmp += fps;

		device->setWindowCaption((windowTitle + L"FPS: " + stringw(fps)).c_str());
		lastFPS = fps;
	}



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

#ifdef SHS_DEV

	IAnimatedMesh* mesh = smgr->getMesh(
			"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.md2");

	IAnimatedMeshSceneNode * node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0,
				driver->getTexture(
						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.bmp"));
	}

	this->node = new Ship(node);
	testPlanet = Planet::createTestPlanet(context);

#endif

	state = MENU;
	bool run = true;

	while (run && device->run()) {
		switch (state) {
		case MENU:
			menu->displayMenu();
			break;
		case RUN:
			displayGame();
			break;
		case EXIT:
			run = false;
			break;
		default:
			break;
		}

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
