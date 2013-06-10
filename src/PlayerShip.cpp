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

PlayerShip::PlayerShip(IAnimatedMeshSceneNode *node) :
		Ship(node) {

}

PlayerShip::PlayerShip() :
		Ship() {
}

PlayerShip::~PlayerShip() {
}

ISceneNode* PlayerShip::createPlayerShip(GameContext* c) {

	ISceneNode * node = NULL;

#ifdef SHS_DEV

	node = c->smgr->addCubeSceneNode(50);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

		node->setMaterialTexture(0,
				c->driver->getTexture(
						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/wall.bmp"));
	}

#endif

	return node;
}



TestPlayerShip::TestPlayerShip() :
		PlayerShip() {
}

TestPlayerShip::TestPlayerShip(irr::scene::IAnimatedMeshSceneNode* node) :
		PlayerShip(node) {

}

void TestPlayerShip::handleInput(const irr::SEvent& event) {
}

void PlayerShip::attachCamera(irr::scene::ICameraSceneNode* camera) {
	camera->setParent(node);
}

TestPlayerShip::~TestPlayerShip() {
}

IAnimatedMeshSceneNode* TestPlayerShip::createTestPlayerShipNode(const shs::GameContext & c) {

	IAnimatedMeshSceneNode * node = NULL;

	IAnimatedMesh* mesh = c.smgr->getMesh("img/rusty_ship.3ds");

	node = c.smgr->addAnimatedMeshSceneNode(mesh);

	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);

//		node->setMaterialTexture(0,
//				c->driver->getTexture(
//						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/wall.bmp"));
	}

	node -> setPosition(vector3df(0, 30, -340));

	return node;
}
} /* namespace shootspacer */
