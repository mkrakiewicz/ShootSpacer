/*
 * Level.h
 *
 *  
 *      Author: Micha�
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "FSMState.h"
#include "PlayerShip.h"
#include "Loader.h"

namespace shs {

class Ship;
class Planet;
class TestPlayerShip;

class Level: public FSMStateRenderLoop {
protected:
	/**
	 * Virtual overloaded methods from RenderLoop
	 */
	void beforeRender();
	void afterRender();
	void render();

	void beforeRun();
	void beforeStop();

	Loader &loader;

public:
//	Level();
	Level(const Spaceshooter &parent);

	virtual ~Level();
};

class TestLevel: public Level {
protected:

	void beforeRender();
	void afterRender();

	void beforeRun();
	void beforeStop();

	irr::scene::ICameraSceneNode *cam;

	Planet *node;
	Planet *testPlanet;
	ShipWithGuns *testEnemy;

	TestPlayerShip *ship;
	void init();

public:
//	TestLevel();
	TestLevel(const Spaceshooter &parent);

	virtual ~TestLevel();

	virtual void handleEvent(const irr::SEvent& event);

};

} /* namespace shs */
#endif /* LEVEL_H_ */
