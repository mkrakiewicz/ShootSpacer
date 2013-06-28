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

class AttachableCamera;

class PlayerShip: public shs::Ship {
protected:
	std::map<irr::EKEY_CODE, ShipKeys> availableStates;

	std::map<ShipKeys, bool> keyStates;

	virtual void handleCamera() = 0;
	virtual void handleMovement() = 0;

	const GameContext &context;

	AttachableCamera *camera;

public:

	PlayerShip(const GameContext &context,
			irr::scene::IAnimatedMeshSceneNode *node);
	virtual ~PlayerShip();

//	void attachCamera(irr::scene::ICameraSceneNode *camera);

	static irr::scene::ISceneNode* createPlayerShip(GameContext *c);

	virtual void update();

	virtual void handleInput(const irr::SEvent& event) = 0;

};

class TestPlayerShip: public PlayerShip {
protected:

	virtual void handleCamera();
	virtual void handleMovement();

	TestPlayerShip();

public:
	bool handleCam;

	TestPlayerShip(const GameContext &context,
			irr::scene::IAnimatedMeshSceneNode *node);

	virtual void handleInput(const irr::SEvent& event);
	static irr::scene::IAnimatedMeshSceneNode* createTestPlayerShipNode(
			const GameContext & c);

//	void bindCamera(irr::scene::ICameraSceneNode *cam);

	virtual ~TestPlayerShip();

//	virtual void update();

};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
