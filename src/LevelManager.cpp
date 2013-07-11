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

LevelManager::LevelManager(const ShootSpacer* parent) :
		testLevel(0), IrrlichtClassBase(parent) {
	// TODO Auto-generated constructor stub
	testLevel = new TestLevel(parent);
}

LevelManager::~LevelManager() {
//	if (testLevel) {
//		delete testLevel;
//	}
}

Level* LevelManager::getCurrentLevel() {
	return getTestLevel();
}

Level* LevelManager::getTestLevel() {

	return testLevel;
}

} /* namespace shs */
