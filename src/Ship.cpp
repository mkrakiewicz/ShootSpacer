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
		AcceleratingObject3D() {
	init();
}

Ship::Ship(ISceneNode* node) :
		AcceleratingObject3D(node) {
	init();
}

f32 Ship::calculateAccelerationNonLinear() {
	if (maxSpeed != 0.f) {
		f32 f = 1 - pow((f32) (currentSpeed / maxSpeed), 2);
		return (f * maxAcceleration * getFrameDelta());
	}
	return 0.f;
}

Ship::~Ship() {
}

void Ship::setMaxAcceleration(irr::f32 maxAcceleration) {
	this->maxAcceleration = maxAcceleration;
}

void Ship::setMaxRotationSpeed(irr::f32 maxRotationSpeed) {
	this->maxRotationSpeed = maxRotationSpeed;
}

void Ship::setMaxSpeed(irr::f32 maxSpeed) {
	this->maxSpeed = maxSpeed;
}

void Ship::accelerate() {
	acceleration = calculateAccelerationNonLinear();
	makeAccelerationVector();
}

void Ship::update() {
	updateMovement();
	clearAcceleration();
}

void Ship::init() {
	maxAcceleration = maxRotationSpeed = maxSpeed = 0;
}

//////////////////////////////////////////////////////////////////////////

NonPlayerShip::NonPlayerShip(irr::scene::ISceneNode* node) :
		Ship(node) {

}

} /* namespace shootspacer */

shs::ShipWithGuns::ShipWithGuns(irr::scene::ISceneNode* node, Loader* loader,
		irr::scene::ISceneManager* smgr) {
}

void shs::ShipWithGuns::update() {
	Ship::update();
	updateGuns();
}

void shs::ShipWithGuns::updateGuns() {
	std::map<irr::core::stringw,Gun*>::iterator gun;

	for (gun = guns.begin(); gun != guns.end(); gun++) {
		gun->second->
	}
}
