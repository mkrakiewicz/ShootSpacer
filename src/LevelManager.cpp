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

LevelManager::LevelManager(const GameContext & context) :context(context),testLevel(0) {
	// TODO Auto-generated constructor stub

}

LevelManager::~LevelManager() {
	if (testLevel) {
		delete testLevel;
	}
}

Level* LevelManager::getTestLevel() {
	if (testLevel) {
			delete testLevel;
	}
	Level *tmp = new TestLevel(context);
	testLevel = tmp;
	return tmp;
}

} /* namespace shs */
