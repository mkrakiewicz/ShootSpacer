/*
 * PlayerShip.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha�
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
public:

	PlayerShip(irr::scene::IAnimatedMeshSceneNode *node);
	virtual ~PlayerShip();

//	void attachCamera(irr::scene::ICameraSceneNode *camera);

	static irr::scene::ISceneNode* createPlayerShip(GameContext *c);

	virtual void update();

	virtual void handleInput(const irr::SEvent& event) = 0;

	void attachNewCamera(AttachableCamera *camera);

protected:
	std::map<irr::EKEY_CODE, ShipKeys> availableStates;

	std::map<ShipKeys, bool> keyStates;

	virtual void handleCamera() = 0;
	virtual void handleKeystates() = 0;

	AttachableCamera *camera;

	bool isCameraHandled;

};

class TestPlayerShip: public PlayerShip {
public:

	TestPlayerShip(irr::scene::IAnimatedMeshSceneNode *node);

	virtual void handleInput(const irr::SEvent& event);
	static irr::scene::IAnimatedMeshSceneNode* createTestPlayerShipNode(
			const GameContext & c);

//	void bindCamera(irr::scene::ICameraSceneNode *cam);

	virtual ~TestPlayerShip();

//	virtual void update();
protected:

	virtual void handleCamera();
	virtual void handleKeystates();

	TestPlayerShip();

};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
