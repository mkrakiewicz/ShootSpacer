/*
 * PlayerShip.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "shootspacer/ShootSpacer.h"
#include "PlayerShip.h"
#include "shootspacer/Camera.h"
#include "Weapons.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {


PlayerShip::PlayerShip(IAnimatedMeshSceneNode *node) :
		ShipWithGuns(node), camera(0), isCameraHandled(false), _cursorControl(0) {

}

PlayerShip::~PlayerShip() {
	if (camera)
		delete camera;
}

ISceneNode* PlayerShip::createPlayerShip(const ShootSpacer &parent) {

	ISceneNode * node = 0;

	node = parent.getSmgr()->addCubeSceneNode(50);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0,
				parent.getDriver()->getTexture(
						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/wall.bmp"));
	}

	return node;
}

void PlayerShip::update() {

	handleKeystates();
	shipGUI.updateSpeed(currentSpeed);
	shipGUI.updateAcceleration(acceleration);

	ShipWithGuns::update();

	if (_cursorControl) {
		_cursorControl->handle();
	}

	handleCamera();

//	shipGUI.updateAcceleration(acceleration);
}

void PlayerShip::attachNewCamera(AttachableCamera* camera) {
	this->camera = camera;
	isCameraHandled = true;
}

void PlayerShip::createGUI(const ShootSpacer& parent) {
	IGUIStaticText *tmp = parent.getGui()->addStaticText(L"Speed:",
			recti(5, 5, 200, 50), true, true);
	tmp->setBackgroundColor(SColor(22, 255, 255, 0));
	tmp->setDrawBorder(true);

	shipGUI.addTextElement(stringw(L"speed"), tmp);

	tmp = 0;
	tmp = parent.getGui()->addStaticText(L"Acceleration:",
			recti(5, 60, 200, 110), true, true);

	tmp->setBackgroundColor(SColor(22, 255, 255, 0));
	tmp->setDrawBorder(true);
	shipGUI.addTextElement(stringw(L"acceleration"), tmp);


	//shipGUI.addTextElement(L"speed",tmp);
}

TestPlayerShip::TestPlayerShip(irr::scene::IAnimatedMeshSceneNode* node) :
		PlayerShip(node) {
	currentSpeed = 0;
	setMaxAcceleration(30);
	setMaxRotationSpeed(50);
	setMaxSpeed(150);
//	initKeys();
}

void TestPlayerShip::handleInput(const irr::SEvent& event) {

	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {

		switch (event.KeyInput.Key) {
		case ACCELERATE:

		case PITCH_UPWARDS:
		case PITCH_DOWNWARDS:
		case TURN_RIGHT:
		case TURN_LEFT:
		case SHOOT:
			keyStates[(ShipKeys) event.KeyInput.Key] = true;
			if (!event.KeyInput.PressedDown) {
				keyStates[(ShipKeys) event.KeyInput.Key] = false;
			}
			break;

// debug - to be removed:
		case KEY_KEY_G:
			if (event.KeyInput.PressedDown) {
				isCameraHandled = !isCameraHandled;
//				if (handleCam)
//					camera->setParent(node);
//				else
//					camera->setParent(0);
			}
			break;

		default:
			break;
		}

	}

	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			keyStates[SHOOT] = true;
			break;
		case irr::EMIE_LMOUSE_LEFT_UP:
			keyStates[SHOOT] = false;
			break;
		default:
			break;
		}

		if (_cursorControl) {
			_cursorControl->handleInput(event);
		}

	}

	if (isCameraHandled) {
		camera->handleInput(event);
	}
}

//void PlayerShip::attachCamera(irr::scene::ICameraSceneNode* camera) {
//	camera->setParent(node);
//}

TestPlayerShip::~TestPlayerShip() {
}

IAnimatedMeshSceneNode* TestPlayerShip::createTestPlayerShipNode(
		const ShootSpacer &parent) {

	IAnimatedMeshSceneNode * node = 0;

	IAnimatedMesh* mesh = parent.getSmgr()->getMesh("img/rusty_ship.3ds");

	node = parent.getSmgr()->addAnimatedMeshSceneNode(mesh);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0,
				parent.getDriver()->getTexture("img/tex.png"));
	}

	node->setPosition(vector3df(0, 30, -340));

	ITriangleSelector * selector = parent.getSmgr()->createTriangleSelector(
			node->getMesh(), node);
	node->setTriangleSelector(selector);
	selector->drop();

	return node;
}

void TestPlayerShip::handleCamera() {
	if (isCameraHandled) {
		camera->update();
	}
}

void TestPlayerShip::handleKeystates() {

	if (keyStates[ACCELERATE] == true) {
		accelerate();

//		currentVelocity=30;
	}

	if (keyStates[SHOOT]) {

		//TODO: force creation of a gun
		guns["main"]->shoot();
	}

	if (keyStates[PITCH_UPWARDS] == true) {
		rotate(-1, vector3df(1, 0, 0));
	}

	if (keyStates[PITCH_DOWNWARDS] == true) {
		rotate(1, vector3df(1, 0, 0));

	}
	if (keyStates[TURN_RIGHT] == true) {
		rotate(1, vector3df(0, 1, 0));

	}
	if (keyStates[TURN_LEFT] == true) {
		rotate(-1, vector3df(0, 1, 0));

	}

//	node->setPosition(node->getPosition() + velocityVector*2);
}

//void TestPlayerShip::initKeys() {
//availableStates[KEY_SPACE] = ACCELERATE;
//availableStates[KEY_KEY_W] = PITCH_UPWARDS;
//availableStates[KEY_KEY_S] = PITCH_DOWNWARDS;
//availableStates[KEY_KEY_D] = TURN_RIGHT;
//availableStates[KEY_KEY_A] = TURN_LEFT;
//
//}

} /* namespace shootspacer */

