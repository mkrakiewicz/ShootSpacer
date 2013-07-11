/*
 * PlayerShip.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "ShootSpacer.h"
#include "PlayerShip.h"
#include "Camera.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

PlayerShip::PlayerShip(IAnimatedMeshSceneNode *node, Loader *loader) :
		Ship(node), camera(0), isCameraHandled(false), loader(loader) {

}



PlayerShip::~PlayerShip() {
	if (camera)
		delete camera;
}

ISceneNode* PlayerShip::createPlayerShip(const ShootSpacer* parent) {

	ISceneNode * node = NULL;

	node = parent->getSmgr()->addCubeSceneNode(50);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0,
				parent->getDriver()->getTexture(
						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/wall.bmp"));
	}

	return node;
}

void PlayerShip::update() {

	handleKeystates();

	updateMovement();
	clearAcceleration();

	handleCamera();
}



TestPlayerShip::TestPlayerShip(irr::scene::IAnimatedMeshSceneNode* node, Loader *loader) :
		PlayerShip(node, loader) {
	currentSpeed = 0;
	setMaxAcceleration(30 );
	setMaxRotationSpeed(20);
	setMaxSpeed(50);
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
		const ShootSpacer* parent) {

	IAnimatedMeshSceneNode * node = NULL;

	IAnimatedMesh* mesh = parent->getSmgr()->getMesh("img/rusty_ship.3ds");

	node = parent->getSmgr()->addAnimatedMeshSceneNode(mesh);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0,  parent->getDriver()->getTexture("img/tex.png"));
	}

	node->setPosition(vector3df(0, 30, -340));

	return node;
}

//void TestPlayerShip::bindCamera(irr::scene::ICameraSceneNode* cam) {
//}

void TestPlayerShip::handleCamera() {
	if (isCameraHandled) {
		camera->update();
//		node->updateAbsolutePosition();
//		const core::matrix4 matr(node->getAbsoluteTransformation());

//camera->setPosition(getIn() * vector3df(0, 2, -5));
//	camera->setRotation(node->getRotation());
//	camera->setUpVector(getIn() * vector3df(0, 1, 0));
//	camera->updateAbsolutePosition();
	}
//	node->setPosition(matr.getTranslation());
}

void TestPlayerShip::handleKeystates() {

	if (keyStates[ACCELERATE] == true) {
		accelerate();

//		currentVelocity=30;
	}

	if (keyStates[PITCH_UPWARDS] == true) {
		rotateNodeInLocalSpace(-30, vector3df(1, 0, 0));
	}

	if (keyStates[PITCH_DOWNWARDS] == true) {
		rotateNodeInLocalSpace(30, vector3df(1, 0, 0));

	}
	if (keyStates[TURN_RIGHT] == true) {
		rotateNodeInLocalSpace(30, vector3df(0, 1, 0));

	}
	if (keyStates[TURN_LEFT] == true) {
		rotateNodeInLocalSpace(-30, vector3df(0, 1, 0));

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

void PlayerShip::attachNewCamera(AttachableCamera* camera) {
	this->camera = camera;
	isCameraHandled = true;
}

} /* namespace shootspacer */
