/*
 * PlayerShip.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_


#include "Ship.h"
#include <map>

namespace shs {

enum ShipKeys {
	ACCELERATE = irr::KEY_SPACE,

	PITCH_UPWARDS = irr::KEY_KEY_W,
	PITCH_DOWNWARDS = irr::KEY_KEY_S,
	TURN_RIGHT = irr::KEY_KEY_D,
	TURN_LEFT = irr::KEY_KEY_A


};



class PlayerShip: public shs::Ship {
protected:
	std::map< irr::EKEY_CODE,ShipKeys> availableStates;

	std::map<ShipKeys,bool> keyStates;
public:
	PlayerShip();
	PlayerShip(irr::scene::IAnimatedMeshSceneNode *node);
	virtual ~PlayerShip();

	virtual void handleInput(const irr::SEvent& event) = 0;
	void attachCamera(irr::scene::ICameraSceneNode *camera);

	static irr::scene::ISceneNode* createPlayerShip(GameContext *c);

	virtual void update() = 0;

};

class TestPlayerShip: public shs::PlayerShip {
public:
	TestPlayerShip();
	TestPlayerShip(irr::scene::IAnimatedMeshSceneNode *node);

	void handleInput(const irr::SEvent& event);
	static irr::scene::IAnimatedMeshSceneNode* createTestPlayerShipNode(
			const GameContext & c);

	virtual ~TestPlayerShip();

	void update();
};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
