/*
 * PlayerShip.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "PlayerShip.h"

namespace shs {

PlayerShip::PlayerShip(IAnimatedMeshSceneNode *node) :
		Ship(node) {
	// TODO Auto-generated constructor stub

}

PlayerShip::PlayerShip() :
		Ship() {
}

PlayerShip::~PlayerShip() {
	// TODO Auto-generated destructor stub
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

} /* namespace shootspacer */

