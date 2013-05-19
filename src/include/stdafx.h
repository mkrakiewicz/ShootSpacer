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

struct GameContext {
public:
	IrrlichtDevice *device;

	GameContext(IrrlichtDevice *_device): device(_device) {}


};

} /* namespace ShootSpacer */
#endif /* STDAFX_H_ */
