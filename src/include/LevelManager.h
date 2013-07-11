/*
 * LevelManager.h
 *
 *  Created on: 10-06-2013
 *      Author: Micha³
 */

#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

#include "FiniteStateMachine.h"
#include "RenderLoop.h"

namespace shs {

class ShootSpacer;
class Level;
/**
 *  - Manages generated levels by itself!
 *  - Adds them to array/queue/vector
 *  - Deletes them in destructor OR if necessary before replacing them with another level
 *  - Will store level number, current bonuses, etc....
 */
class LevelManager: protected FiniteStateMachine, public IrrlichtClassBase {
public:
	LevelManager(const ShootSpacer* parent);
	virtual ~LevelManager();

	/**
	 * Gives current level
	 * DO NOT DELETE the object, deletion is handled by this manager
	 * @return pointer to current level
	 */
	Level* getCurrentLevel();

protected:

	Level *getTestLevel();

	//need to be replaced later with some sort of management of levels
	Level *testLevel;

};

} /* namespace shs */
#endif /* LEVELMANAGER_H_ */
