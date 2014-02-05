/*
 * Level.cpp
 *
 *  
 *      Author: Micha�
 */
#include "stdafx.h"
#include "Weapons.h"
#include "Level.h"
#include "Ship.h"
#include "Planet.h"
#include "FiniteStateMachine.h"
#include "PlayerShip.h"
#include "Camera.h"
#include "Spaceshooter.h"

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
 * void Spaceshooter::beforeRender() {

 #ifdef SHS_DEV

 node->rotateNodeInLocalSpace(15, vector3df(0, 1, 0));
 node->rotateNodeInLocalSpace(15, vector3df(1, 0, 0));
 node->rotateNodeInLocalSpace(15, vector3df(0, 0, 1));

 testPlanet->rotateNodeInLocalSpace(5, vector3df(0, 1, 0));

 #endif


 }

 void Spaceshooter::afterRender() {
 static int lastFPS = -1;
 int fps = driver->getFPS();

 if (lastFPS != fps) {
 //		core::stringw tmp(L"Spaceshooter [");
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
Level::Level(const Spaceshooter &parent) :
		FSMStateRenderLoop(parent), loader(parent.getLoader()) {
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
TestLevel::TestLevel(const Spaceshooter &parent) :
		Level(parent) {

	init();
}

TestLevel::~TestLevel() {
	delete node;
	delete testPlanet;

	delete ship;
	delete testEnemy;
}

void TestLevel::beforeRun() {

	//gui->clear();

	device->getCursorControl()->setVisible(false);
	gui->addStaticText(L"Game", rect<s32>(10, 10, 260, 22), true);

	ship->createGUI(parent);

}

void TestLevel::beforeStop() {
	device->getCursorControl()->setVisible(true);
}

void TestLevel::init() {

	loader.loadTexture("orange_particle", "img/orange_projectile.bmp");
	loader.loadTexture("sydney", "img/sydney.bmp");

//	IAnimatedMesh* mesh = smgr->getMesh("img/sydney.md2");

	IMeshSceneNode * tmpnode = smgr->addCubeSceneNode(40);

	if (tmpnode) {
		tmpnode->setMaterialFlag(EMF_LIGHTING, false);
//		tmpnode->setMD2Animation(scene::EMAT_STAND);
		tmpnode->setMaterialTexture(0, loader.getTexture("sydney"));
	}

	tmpnode->setPosition(vector3df(-222, 0, 0));

	ITriangleSelector * selector = parent.getSmgr()->createTriangleSelector(
			tmpnode->getMesh(), tmpnode);
	tmpnode->setTriangleSelector(selector);
	selector->drop();

	vector3df wsp(0, 5, -10);

	ship = new TestPlayerShip(TestPlayerShip::createTestPlayerShipNode(parent));
	ship->attachNewCamera(new StaticCamera(parent, ship));
	Gun * tmp = new SimpleGun(ship, *parent.getDevice()->getTimer());
	tmp->initialize(parent);
	tmp->setRpm(500);
	ship->addGun("main", tmp);
	ship->_cursorControl = new ShipRotatingCursorHandler(ship,parent.getDevice()->getCursorControl(),1024, 768);
//	ship.attachCamera(cam);

	this->node = new Planet(tmpnode);
	testPlanet = Planet::createTestPlanet(parent);

	ISceneNode *tmp2 = TestPlayerShip::createTestPlayerShipNode(parent);
	tmp2->setPosition(vector3df(-20, 20, -200));
	tmp2->setScale(vector3df(4,4,4));
	ISceneNodeAnimator * anim = parent.getSmgr()->createFlyCircleAnimator(
			tmp2->getPosition(), 50, 0.001);
	tmp2->addAnimator(anim);
	anim->drop();
	testEnemy = new ShipWithGuns(tmp2);
}

void TestLevel::beforeRender() {

	node->rotateNodeInLocalSpace(15.f, vector3df(0, 1, 0));
	node->rotateNodeInLocalSpace(15.f, vector3df(1, 0, 0));
	node->rotateNodeInLocalSpace(15.f, vector3df(0, 0, 1));

	testPlanet->rotateNodeInLocalSpace(5, vector3df(0, 1, 0));

	ship->update();

//	vector3df npos = ship.toWorldPos(vector3df(0, 5, -20));

//	cam->setPosition(npos);
//	cam->setRotation(ship.toWorldRot(ship.getRotation()));
//	cam->setTarget(ship.getPosition());
//	ship.moveNodeInLocalSpace(vector3df(0,0,1),15);

//cam->setRotation(ship.getNode()->getAbsoluteTransformation().g);

//cam->setTarget(ship.getPosition());

}

void TestLevel::afterRender() {
	static int lastFPS = -1;
	int fps = driver->getFPS();

	if (lastFPS != fps) {
		//		core::stringw tmp(L"Spaceshooter [");
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

			parent.getStateRunner().appendStateWithName(L"menu");
			this->stop();

		} else if (event.KeyInput.Key == KEY_KEY_Q) {
			parent.getStateRunner().endCurrentState();
		}
	}

	ship->handleInput(event);
}

} /* namespace shs */

