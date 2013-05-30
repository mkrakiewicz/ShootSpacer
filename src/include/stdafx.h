/*
 * stdafx.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef STDAFX_H_
#define STDAFX_H_

#include <irrlicht.h>
#include <iostream>
#include <memory>
#include <string>

#include "SmartPointer.h"

#include "version.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/**
 * #define SHOOTSPACER_DEVELOPMENT
 * -- means we are in development move. code needs to be not placed in according #ifdefs
 * Set this in project build settings instead of here.
 */


namespace shs {

class GameContext {
public:
	IrrlichtDevice *device;
	IVideoDriver *driver;
	ISceneManager *smgr;
	IGUIEnvironment *gui;

	GameContext(IrrlichtDevice * context): device(context),
	driver(device->getVideoDriver()),
	smgr(device->getSceneManager()),
	gui(device->getGUIEnvironment())
	{}


};

} /* namespace ShootSpacer */
#endif /* STDAFX_H_ */
