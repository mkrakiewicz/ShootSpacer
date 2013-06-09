/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#ifndef SHOOTSPACER_H_
#define SHOOTSPACER_H_
#include "FSMState.h"

namespace shs {

class Menu;
class Ship;
class Planet;
class ShootSpacerEvent;

/**
 * States used to identify current game state
 */
enum GameState {
	INIT, RUN, MENU, EXIT
};

class ShootSpacerInstance: public FSMStateRenderLoop {
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
	inline ShootSpacerInstance(const ShootSpacerInstance&) :
		FSMStateRenderLoop(createIrrlichtDevice()) {
		initialize();
	}

	/**
	 *  Private assignment operator - singleton requirement
	 */
	inline ShootSpacerInstance& operator=(const ShootSpacerInstance&) {
		return *this;
	}

protected:

	static const irr::core::stringw windowTitle;

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
	GameContext *context;

	/**
	 * Pointer to menu object
	 */
	Menu *menu;

#ifdef SHS_DEV
	Ship *node;
	Planet *testPlanet;
#endif

	/**
	 * Event listener/receiver.
	 */
	ShootSpacerEvent *eventReceiver;

	/**
	 * Stores current state.
	 */
	GameState state;

	void displayGame();

	/**
	 * Virtual overloaded methods from RenderLoop
	 */
	void beforeRender();
	void afterRender();
	void render();

	void cleanup();

	/**
	 * Call this to assign reference to current frame delta for all 3D Objects.
	 */
	void enableFrameIndependentMovement();

	void beforeRun();
	void beforeStop();


public:

	void toggleGameState();
	void startGame();
	void exit();

	static ShootSpacerInstance* getInstance();
	static void releaseInstance();

	~ShootSpacerInstance();
};

} /* namespace shs */
#endif /* SHOOTSPACER_H_ */

