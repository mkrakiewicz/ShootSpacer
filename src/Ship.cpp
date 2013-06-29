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

}

Ship::Ship(ISceneNode* node) : MovingObject3D(node) {
}

Ship::~Ship() {
}


NonPlayerShip::NonPlayerShip(irr::scene::ISceneNode* node): Ship(node) {

}

void NonPlayerShip::update() {
}


} /* namespace shootspacer */
