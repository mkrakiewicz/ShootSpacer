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

enum GameState {
	INIT, RUN, MENU, EXIT
};

class ShootSpacer: public RenderLoop {
protected:
	IrrlichtDevice* createIrrlichtDevice();
	void initialize();

	GameContext *context;

	Menu *menu;

	Ship *node;
	Planet *testPlanet;
	ShootSpacerEvent *eventReceiver;

	GameState state;

	void displayGame();

	void beforeRender();
	void afterRender();
	void render();

	void cleanup();

	ShootSpacer();
	static ShootSpacer* _instance;
	static int _referenceCount;

	// copy constructor
	inline ShootSpacer(const ShootSpacer&):RenderLoop(createIrrlichtDevice()) {
		initialize();
	}

	// assignment operator
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}

public:

	void toggleGameState();
	void startGame();
	void exit();

	static ShootSpacer* getInstance();
	static void releaseInstance();

	 ~ShootSpacer();
};

} /* namespace shootspacer */
#endif /* SHOOTSPACER_H_ */

