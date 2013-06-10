/*
 * PlayerShip.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "Ship.h"

namespace shs {

class PlayerShip: public shs::Ship {
public:
	PlayerShip();
	PlayerShip(irr::scene::IAnimatedMeshSceneNode *node);
	virtual ~PlayerShip();

	virtual void handleInput(const irr::SEvent& event) = 0;
	void attachCamera(irr::scene::ICameraSceneNode *camera);

	static irr::scene::ISceneNode* createPlayerShip(GameContext *c);

};

class TestPlayerShip: public shs::PlayerShip {
public:
	TestPlayerShip();
	TestPlayerShip(irr::scene::IAnimatedMeshSceneNode *node);

	void handleInput(const irr::SEvent& event);
	static irr::scene::IAnimatedMeshSceneNode* createTestPlayerShipNode(
			const GameContext & c);

	virtual ~TestPlayerShip();
};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
