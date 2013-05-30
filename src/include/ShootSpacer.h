/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef SHOOTSPACER_H_
#define SHOOTSPACER_H_
#include "RenderLoop.h"

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

class ShootSpacer: public RenderLoop {
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
	inline ShootSpacer(const ShootSpacer&) :
			RenderLoop(createIrrlichtDevice()) {
		initialize();
	}

	/**
	 *  Private assignment operator - singleton requirement
	 */
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}

protected:

	static const stringw windowTitle;

	/**
	 * Function to store params and create device
	 * @return
	 */
	IrrlichtDevice* createIrrlichtDevice();

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

