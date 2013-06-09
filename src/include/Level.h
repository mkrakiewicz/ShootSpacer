/*
 * Level.h
 *
 *  Created on: 09-06-2013
 *      Author: Micha³
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "FSMState.h"

namespace shs {

class Ship;
class Planet;

class Level: public shs::FSMStateRenderLoop {
protected:
	/**
	 * Virtual overloaded methods from RenderLoop
	 */
	void beforeRender();
	void afterRender();
	void render();

	void beforeRun();
	void beforeStop();



public:
	Level();
	Level(const GameContext &context);

	virtual ~Level();
};

class TestLevel: public Level {
protected:

	void beforeRender();
	void afterRender();
	void render();

	void beforeRun();
	void beforeStop();


	Ship *node;
	Planet *testPlanet;

	void init();


public:
	TestLevel();
	TestLevel(const GameContext &context);

	virtual ~TestLevel();

	virtual void handleEvent(const irr::SEvent& event);

};

} /* namespace shs */
#endif /* LEVEL_H_ */
