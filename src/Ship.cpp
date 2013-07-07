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

Ship::Ship() :
		MovingObject3D() {
	init();
}

Ship::Ship(ISceneNode* node) :
		MovingObject3D(node) {
	init();
}

f32 Ship::calculateAccelerationNonLinear() {
	if (maxSpeed != 0.f) {
		f32 f = 1 - pow((f32)(currentVelocity / maxSpeed), 2);
		return f * maxAcceleration;
	}
	return 0.f;
}

Ship::~Ship() {
}

NonPlayerShip::NonPlayerShip(irr::scene::ISceneNode* node) :
		Ship(node) {

}

void NonPlayerShip::update() {
}

void Ship::init() {
	maxAcceleration = maxRotationSpeed = maxSpeed = 0;
}

} /* namespace shootspacer */
