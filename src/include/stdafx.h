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
#include "SmartPointer.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



namespace shs {

class GameContext {
public:
	IrrlichtDevice *device;
	IVideoDriver *driver;
	ISceneManager *smgr;
	IGUIEnvironment *gui;

	GameContext(IrrlichtDevice *_device): device(_device),
	driver(device->getVideoDriver()),
	smgr(device->getSceneManager()),
	gui(device->getGUIEnvironment())
	{}


};

} /* namespace ShootSpacer */
#endif /* STDAFX_H_ */
