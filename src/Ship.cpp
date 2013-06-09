/*
 * Ship.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
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

}

Ship::Ship(ISceneNode* node) : MovingObject3D(node) {
}

Ship::~Ship() {
}

} /* namespace shootspacer */
