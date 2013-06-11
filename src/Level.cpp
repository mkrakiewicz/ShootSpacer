/*
 * Level.cpp
 *
 *  Created on: 09-06-2013
 *      Author: Micha³
 */
#include "stdafx.h"
#include "Level.h"
#include "Ship.h"
#include "Planet.h"
#include "FiniteStateMachine.h"
#include "PlayerShip.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
/**
 *
 *
 */

/**
 * void ShootSpacer::beforeRender() {

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
 */
namespace shs {

//Level::Level() :
//		FSMStateRenderLoop() {
//
//
//}
Level::Level(const GameContext &context) :
		FSMStateRenderLoop(context) {
}

void Level::beforeRender() {
}

void Level::afterRender() {
}

void Level::render() {
	smgr->drawAll();
	gui->drawAll();
}

void Level::beforeRun() {
}

void Level::beforeStop() {
}

Level::~Level() {
}

/***
 *
 * TestLevel
 */

//TestLevel::TestLevel() :
//		Level() {
//}
TestLevel::TestLevel(const GameContext &context) :
		Level(context),
		ship(TestPlayerShip::createTestPlayerShipNode(context))
{

	init();
}

TestLevel::~TestLevel() {
	delete node;
	delete testPlanet;

}


void TestLevel::beforeRun() {

	gui->clear();

	gui->addStaticText(L"Game", rect<s32>(10, 10, 260, 22), true);

}

void TestLevel::beforeStop() {
}

void TestLevel::init() {

	IAnimatedMesh* mesh = smgr->getMesh(
			"img/sydney.md2");

	IAnimatedMeshSceneNode * tmpnode = smgr->addAnimatedMeshSceneNode(mesh);

	if (tmpnode) {
		tmpnode->setMaterialFlag(EMF_LIGHTING, false);
		tmpnode->setMD2Animation(scene::EMAT_STAND);
		tmpnode->setMaterialTexture(0,
				driver->getTexture(
						"img/sydney.bmp"));
	}

	cam = smgr->addCameraSceneNode(0,ship.getPosition()+vector3df(0, 5, -10),ship.getPosition());
	smgr->setActiveCamera(cam);


	this->node = new Ship(tmpnode);
	testPlanet = Planet::createTestPlanet(context);

}

void TestLevel::beforeRender() {

	node->rotateNodeInLocalSpace(15.f, vector3df(0, 1, 0));
	node->rotateNodeInLocalSpace(15.f, vector3df(1, 0, 0));
	node->rotateNodeInLocalSpace(15.f, vector3df(0, 0, 1));

	testPlanet->rotateNodeInLocalSpace(5, vector3df(0, 1, 0));

//	ship.moveNodeInLocalSpace(vector3df(0,0,1),15);
	ship.update();
	//cam->setTarget(ship.getPosition());

}

void TestLevel::afterRender() {
	static int lastFPS = -1;
	int fps = driver->getFPS();

	if (lastFPS != fps) {
		//		core::stringw tmp(L"ShootSpacer [");
		//		tmp += driver->getName();
		//		tmp += L"] fps: ";
		//		tmp += fps;

		device->setWindowCaption(
				(windowTitle + L"FPS: " + stringw(fps)).c_str());
		lastFPS = fps;
	}
}

void TestLevel::handleEvent(const irr::SEvent& event) {
	if (!event.KeyInput.PressedDown) {
		if (event.KeyInput.Key == KEY_ESCAPE) {

			context.stateRunner->appendStateWithName(L"menu");
			this->stop();

		} else if (event.KeyInput.Key == KEY_KEY_Q) {
			context.stateRunner->endCurrentState();
		}
	}

	ship.handleInput(event);
}

} /* namespace shs */

