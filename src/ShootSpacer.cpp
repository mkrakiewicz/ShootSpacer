/*
 * ShootSpacer.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "ShootSpacerEvent.h"
#include "ShootSpacer.h"
#include "Menu.h"
#include "Object3D.h"
#include "Planet.h"

namespace shs {

ShootSpacer* ShootSpacer::_instance = NULL;

int ShootSpacer::_referenceCount = 0;

ShootSpacer::ShootSpacer() :
		eventReceiver(new ShootSpacerEvent(this)), RenderLoop(createIrrlichtDevice()), state(INIT) {
	device->setEventReceiver(eventReceiver);
	device->setWindowCaption(L"ShootSpacer version 0.00001 pre alpha :P");

	Object3D::setFrameDeltaReference(getFrameDeltaTimePtr());

}

void ShootSpacer::initialize() {

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

ShootSpacer::~ShootSpacer() {
	delete node;
	delete testPlanet;
	delete menu;
	delete context;
	delete eventReceiver;
	device->drop();
}

void ShootSpacer::beforeRender() {
	node->rotateNodeInLocalSpace(15, vector3df(0, 1, 0));
	node->rotateNodeInLocalSpace(15, vector3df(1, 0, 0));
	node->rotateNodeInLocalSpace(15, vector3df(0, 0, 1));

	testPlanet->rotateNodeInLocalSpace(5, vector3df(0, 1, 0));

}

void ShootSpacer::afterRender() {

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

	IVideoDriver* driver = device->getVideoDriver();
	driver->getFPS();
	ISceneManager* smgr = device->getSceneManager();

	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(
			L"Hello World! This is the Irrlicht Software renderer!",
			rect<s32>(10, 10, 260, 22), true);

	IAnimatedMesh* mesh = smgr->getMesh(
			"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.md2");
	{
		IAnimatedMeshSceneNode * node = smgr->addAnimatedMeshSceneNode(mesh);

		if (node) {
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture(0,
					driver->getTexture(
							"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.bmp"));
		}

		this->node = new Object3D(node);
	}

	context = new GameContext(device);

	menu = new Menu(context);

	testPlanet = Planet::createTestPlanet(context);

	ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0, 30, -140),
			vector3df(0, 5, 0));

//	cam->setAspectRatio(16/9.f);

	state = RUN;
	bool run = true;

	while (run) {
		switch (state) {
		case MENU:
			menu->displayMenu();
			break;
		case RUN:
			this->run();
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
		delete _instance;
		_instance = NULL;
	}
}

} /* namespace shootspacer */
