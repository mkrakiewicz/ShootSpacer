/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
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
public:

	void startGame();

	~ShootSpacer();
protected:

	void exit();


	void toggleGameState();
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
	 * Manages and runs states.
	 */
	shs::FSMStateRunner stateRunner;

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

	void cleanup();

	/**
	 * Call this to assign reference to current frame delta for all 3D Objects.
	 */
	void enableFrameIndependentMovement();

	friend bool shs::ShootSpacerEvent::OnEvent(const irr::SEvent& event);

	void handleEvent(const irr::SEvent& event);

	bool hasGameStarted;

	/**
	 * Protected constructor to implement Singleton pattern.
	 */
	ShootSpacer();

	/**
	 * Protected copy constructor (singleton)
	 */
	inline ShootSpacer(const ShootSpacer& sh) :
			context(sh.context) {
		initialize();
	}

	/**
	 *  Protected assignment operator - singleton requirement
	 */
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}

};

class ShootSpacerInstance: public ShootSpacer {
public:
	static ShootSpacerInstance* getInstance();
	static void releaseInstance();

	virtual ~ShootSpacerInstance();

private:

	/**
	 * Private constructor to implement Singleton pattern.
	 */
	ShootSpacerInstance();
	static ShootSpacerInstance* _instance;
	static int _referenceCount;

	/**
	 * Private copy constructor (singleton)
	 */
	inline ShootSpacerInstance(const ShootSpacerInstance& sh) {
		// nothing here
	}

	/**
	 *  Private assignment operator - singleton requirement
	 */
	inline ShootSpacerInstance& operator=(const ShootSpacerInstance&) {
		return *this;
	}
};

} /* namespace shs */
#endif /* SHOOTSPACER_H_ */

