/*
 * Ship.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Ship.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


namespace shs {

Ship::Ship() : MovingObject3D() {
	// TODO Auto-generated constructor stub

}

Ship::Ship(ISceneNode* node) : MovingObject3D(node) {
}

Ship::~Ship() {
	// TODO Auto-generated destructor stub
}

} /* namespace shootspacer */
