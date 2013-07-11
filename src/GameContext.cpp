/*
 * GameContext.cpp
 *
 *  Created on: 10-06-2013
 *      Author: Micha³
 */

#include "stdafx.h"

namespace shs {

GameContext::GameContext(irr::IrrlichtDevice* context,
		FSMStateRunner* stateRunner) :
		device(context), driver(device->getVideoDriver()), smgr(
				device->getSceneManager()), gui(device->getGUIEnvironment()), stateRunner(
				stateRunner) {
}

GameContext::~GameContext() {
	device->drop();
}

}
