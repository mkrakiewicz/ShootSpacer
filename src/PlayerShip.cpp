/*
 * PlayerShip.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "PlayerShip.h"
#include "Camera.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

PlayerShip::PlayerShip(const GameContext &context, IAnimatedMeshSceneNode *node) :
		Ship(node), context(context), camera(
				new StaticCamera(context, this->node)) {

}



PlayerShip::~PlayerShip() {
	if (camera)
		delete camera;
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

void PlayerShip::update() {

	handleMovement();
	handleCamera();
}



TestPlayerShip::TestPlayerShip(const GameContext &context,
		irr::scene::IAnimatedMeshSceneNode* node) :
		PlayerShip(context, node), handleCam(true) {
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

		default:
			break;
		}

	}

	camera->handleInput(event);
}

//void PlayerShip::attachCamera(irr::scene::ICameraSceneNode* camera) {
//	camera->setParent(node);
//}

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

//void TestPlayerShip::bindCamera(irr::scene::ICameraSceneNode* cam) {
//}

void TestPlayerShip::handleCamera() {
	if (handleCam) {
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
