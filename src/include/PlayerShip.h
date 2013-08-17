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
#include "GUI.h"

namespace shs {

enum ShipKeys {
	ACCELERATE = irr::KEY_SPACE,

	SHOOT = irr::KEY_KEY_C,

	PITCH_UPWARDS = irr::KEY_KEY_W,
	PITCH_DOWNWARDS = irr::KEY_KEY_S,
	TURN_RIGHT = irr::KEY_KEY_D,
	TURN_LEFT = irr::KEY_KEY_A

};

class AttachableCamera;
class Loader;

class CursorControl {
public:
	CursorControl(irr::gui::ICursorControl* control, irr::u32 screenResX = 800, irr::u32 screenResY = 600):
		_horizontalDelta(0.f),_verticalDelta(0.f),
		_screenResX(screenResX),_screenResY(screenResY), _control(control) {

		_halfX = _screenResX/2.f;
		_halfY = _screenResY/2.f;

		//reset cursor position to middle
		_control->setPosition(_halfX,_halfY);
	}

	inline irr::f32 getHorizontalDelta() { return _horizontalDelta; }
	inline irr::f32 getVerticalDelta() { return _verticalDelta; }

	virtual  ~CursorControl() {}

protected:
	void handleInput(const irr::SEvent& event);
	virtual void update();

	virtual void decreaseDelta() = 0;

	// to put something like: _control->setPosition(_halfX,_halfY);
	virtual void postAction() = 0;

	irr::f32
	// value range -1(100% left) to 1 (100% right)
	_horizontalDelta,

	// value range -1(100% top) to 1 (100% bottom)
	// because Irrlicht's Y axis goes from top to bottom.
	_verticalDelta,
	//helper variables
	_halfX, _halfY;

	irr::u32 _screenResX, _screenResY;

	irr::gui::ICursorControl* _control;

};

/**
 * PlayerShip will always have guns
 */
class PlayerShip: public ShipWithGuns {
public:

	PlayerShip(irr::scene::IAnimatedMeshSceneNode *node);
	virtual ~PlayerShip();

//	void attachCamera(irr::scene::ICameraSceneNode *camera);

	static irr::scene::ISceneNode* createPlayerShip(const ShootSpacer &parent);

	virtual void update();

	virtual void handleInput(const irr::SEvent& event) = 0;

	void attachNewCamera(AttachableCamera *camera);
	void createGUI(const ShootSpacer &parent);


protected:

	ShipGUI shipGUI;

	std::map<irr::EKEY_CODE, ShipKeys> availableStates;

	std::map<ShipKeys, bool> keyStates;

	virtual void handleCamera() = 0;
	virtual void handleKeystates() = 0;

	AttachableCamera *camera;

	bool isCameraHandled;

	CursorControl *_cursorControl;



};

class TestPlayerShip: public PlayerShip {
public:

	TestPlayerShip(irr::scene::IAnimatedMeshSceneNode *node);

	virtual void handleInput(const irr::SEvent& event);
	static irr::scene::IAnimatedMeshSceneNode* createTestPlayerShipNode(
			const ShootSpacer &parent);

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
