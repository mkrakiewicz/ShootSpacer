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
 *
 */
class LevelManager : protected FiniteStateMachine {
protected:
//need to be replaced later with some sort of management of levels
	Level *testLevel;
public:
	LevelManager(const GameContext & context);
	virtual ~LevelManager();

	Level* getCurrentLevel();

protected:

	Level *getTestLevel();
	const GameContext & context;

};

} /* namespace shs */
#endif /* LEVELMANAGER_H_ */
