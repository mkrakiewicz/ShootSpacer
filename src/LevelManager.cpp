/*
 * LevelManager.cpp
 *
 *  Created on: 10-06-2013
 *      Author: Micha³
 */
#include "stdafx.h"
#include "Level.h"
#include "LevelManager.h"

namespace shs {

LevelManager::LevelManager(const GameContext & context) :context(context) {
	// TODO Auto-generated constructor stub

}

LevelManager::~LevelManager() {
	// TODO Auto-generated destructor stub
}

Level* LevelManager::getTestLevel() {
	Level *tmp = new TestLevel(context);
	return tmp;
}

} /* namespace shs */
