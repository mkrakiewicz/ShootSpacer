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

class LevelManager : protected FiniteStateMachine {
public:
	LevelManager(const GameContext & context);
	virtual ~LevelManager();

	Level *getTestLevel();
protected:

	const GameContext & context;

};

} /* namespace shs */
#endif /* LEVELMANAGER_H_ */
