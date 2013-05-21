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
class Object3D;
class Planet;
class ShootSpacerEvent;

enum GameState {
	INIT,
	RUN,
	MENU,
	EXIT
};

class ShootSpacer: public RenderLoop/*,Singleton<ShootSpacer>*/{
private:

	ShootSpacer();

	static ShootSpacer* _instance;
	static int _referenceCount;

	void beforeRender();
	void afterRender();
	void render();

//	std::string windowTitle =

	// copy constructor
	inline ShootSpacer(const ShootSpacer&) {
	}

	// assignment operator
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}


protected:
	IrrlichtDevice* createIrrlichtDevice();
	void initialize();

	GameContext *context;

	Menu *menu;

	Object3D *node;
	Planet *testPlanet;
	ShootSpacerEvent *eventReceiver;

	GameState state;

public:

	void toggleGameState();
	void startGame();

	static ShootSpacer* getInstance();
	static void releaseInstance();

	virtual ~ShootSpacer();
};

} /* namespace shootspacer */
#endif /* SHOOTSPACER_H_ */

