/*
 * GameContext.cpp
 *
 *  Created on: 10-06-2013
 *      Author: Micha�
 */

#include "stdafx.h"

namespace shs {

GameContext::GameContext(irr::IrrlichtDevice* context,
		FSMStateRunner* stateRunner) :
		device(context), stateRunner(stateRunner), driver(
				device->getVideoDriver()), smgr(device->getSceneManager()), gui(
				device->getGUIEnvironment()) {
}

GameContext::~GameContext() {
	device->drop();
}

}
