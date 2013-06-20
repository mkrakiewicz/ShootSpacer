/*
 * PlayerShip.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "PlayerShip.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

PlayerShip::PlayerShip(IAnimatedMeshSceneNode *node,
		irr::scene::ICameraSceneNode *camera) :
		Ship(node), camera(camera) {

}

PlayerShip::PlayerShip() :
		Ship(), camera(0) {
}

PlayerShip::~PlayerShip() {
}

ISceneNode* PlayerShip::createPlayerShip(GameContext* c) {

	ISceneNode * node = NULL;

	node = c->smgr->addCubeSceneNode(50);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0,
				c->driver->getTexture(
						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/wall.bmp"));
	}

	return node;
}

void PlayerShip::setCameraBehind(irr::core::vector3df offset) {

	//get rotation matrix of node - Zeuss must be getRotation not getRelativeTransformation
	irr::core::matrix4 m;
	m.setRotationDegrees(node->getRotation());

	// transform forward vector of camera
	irr::core::vector3df frv = irr::core::vector3df(0.0f, 0.0f, 1.0f);
	m.transformVect(frv);

	// transform upvector of camera
	irr::core::vector3df upv = irr::core::vector3df(0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	// transform camera offset (thanks to Zeuss for finding it was missing)
	m.transformVect(offset);

	// set camera
	camera->setPosition(node->getPosition() + offset); //position camera in front of the ship
	camera->setUpVector(upv); //set up vector of camera >> Zeuss - tested with +node->getPostion() and it didnt work, but this works fine.
	camera->setTarget(node->getPosition() + frv); //set target of camera (look at point) >> Zeuss - Dont forget to add the node positiob

}

void PlayerShip::update() {

	handleMovement();
	handleCamera();
}

TestPlayerShip::TestPlayerShip() :
		PlayerShip() {
//	initKeys();
}

TestPlayerShip::TestPlayerShip(irr::scene::IAnimatedMeshSceneNode* node,
		irr::scene::ICameraSceneNode *camera) :
		PlayerShip(node, camera), handleCam(true) {
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
				handleCam = !handleCam;
//				if (handleCam)
//					camera->setParent(node);
//				else
//					camera->setParent(0);
			}
			break;
		case KEY_KEY_T:
			camera->setTarget(getPosition());
			break;
		default:
			break;
		}

	}
}

void PlayerShip::attachCamera(irr::scene::ICameraSceneNode* camera) {
	camera->setParent(node);
}

TestPlayerShip::~TestPlayerShip() {
}

IAnimatedMeshSceneNode* TestPlayerShip::createTestPlayerShipNode(
		const shs::GameContext & c) {

	IAnimatedMeshSceneNode * node = NULL;

	IAnimatedMesh* mesh = c.smgr->getMesh("img/rusty_ship.3ds");

	node = c.smgr->addAnimatedMeshSceneNode(mesh);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0, c.driver->getTexture("img/tex.png"));
	}

	node->setPosition(vector3df(0, 30, -340));

	return node;
}

void TestPlayerShip::bindCamera(irr::scene::ICameraSceneNode* cam) {
}

void TestPlayerShip::handleCamera() {
	if (handleCam) {
//		node->updateAbsolutePosition();
//		const core::matrix4 matr(node->getAbsoluteTransformation());
		setCameraBehind(vector3df(0,5,-10));
		//camera->setPosition(getIn() * vector3df(0, 2, -5));
		//	camera->setRotation(node->getRotation());
		//	camera->setUpVector(getIn() * vector3df(0, 1, 0));
//	camera->updateAbsolutePosition();
	}
//	node->setPosition(matr.getTranslation());
}

void TestPlayerShip::handleMovement() {

	if (keyStates[ACCELERATE] == true) {
		moveNodeInLocalSpace(vector3df(0, 0, 1), 35);
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
