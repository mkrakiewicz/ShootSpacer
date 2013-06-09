/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef SHOOTSPACER_H_
#define SHOOTSPACER_H_
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "ShootSpacerEvent.h"

namespace shs {

class Menu;
class Ship;
class Planet;


/**
 * States used to identify current game state
 */
enum GameState {
	INIT, RUN, MENU, EXIT
};

//TODO: perhaps should change pointers to variables if possible for safety.
class ShootSpacer {
private:

	/**
	 * Private constructor to implement Singleton pattern.
	 */
	ShootSpacer();
	static ShootSpacer* _instance;
	static int _referenceCount;

	/**
	 * Private copy constructor (singleton)
	 */
	inline ShootSpacer(const ShootSpacer&):context(0) {
		initialize();
	}

	/**
	 *  Private assignment operator - singleton requirement
	 */
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}

protected:

	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *gui;

	/**
	 * Function to store params and create device
	 * @return
	 */
	irr::IrrlichtDevice* createIrrlichtDevice();

	/**
	 * Sets some params, creates main objects
	 */
	void initialize();

	/**
	 * A container to store game pointers (and other info)
	 */
	GameContext context;

	/**
	 * Pointer to menu object
	 */
	Menu *menu;

	/**
	 * Event listener/receiver.
	 */
	ShootSpacerEvent *eventReceiver;

	/**
	 * Manages and runs states.
	 */
	shs::FSMStateRunner stateRunner;

	void cleanup();

	/**
	 * Call this to assign reference to current frame delta for all 3D Objects.
	 */
	void enableFrameIndependentMovement();

	friend bool shs::ShootSpacerEvent::OnEvent(const irr::SEvent& event);

	void handleEvent(const irr::SEvent& event);

public:

	void toggleGameState();
	void startGame();
	void exit();

	static ShootSpacer* getInstance();
	static void releaseInstance();

	~ShootSpacer();
};

} /* namespace shs */
#endif /* SHOOTSPACER_H_ */

