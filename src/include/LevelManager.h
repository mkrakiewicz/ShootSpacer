/*
 * LevelManager.h
 *
 *  Created on: 10-06-2013
 *      Author: Micha³
 */

#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

#include "FiniteStateMachine.h"

namespace shs {

class Level;
/**
 *  - Manages generated levels by itself!
 *  - Adds them to array/queue/vector
 *  - Deletes them in destructor OR if necessary before replacing them with another level
 *  - Will store level number, current bonuses, etc....
 */
class LevelManager: protected FiniteStateMachine {
public:
	LevelManager(const GameContext & context);
	virtual ~LevelManager();

	/**
	 * Gives current level
	 * DO NOT DELETE the object, deletion is handled by this manager
	 * @return pointer to current level
	 */
	Level* getCurrentLevel();

protected:

	Level *getTestLevel();
	const GameContext & context;

	//need to be replaced later with some sort of management of levels
	Level *testLevel;

};

} /* namespace shs */
#endif /* LEVELMANAGER_H_ */
