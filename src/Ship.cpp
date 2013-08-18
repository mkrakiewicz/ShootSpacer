/*
 * Ship.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "Weapons.h"
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
		return (f * maxAcceleration);
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
//TODO: optimize, check for correct value
void Ship::rotate(f32 factor, const core::vector3df& axis)
{
	rotateNodeInLocalSpace(factor * maxRotationSpeed, axis);
}

void Ship::init() {
	maxAcceleration = maxRotationSpeed = maxSpeed = 0;
}

//////////////////////////////////////////////////////////////////////////


ShipWithGuns::ShipWithGuns(irr::scene::ISceneNode* node):Ship(node) {
}

void ShipWithGuns::update() {
	Ship::update();
	updateGuns();
}

void ShipWithGuns::addGun(irr::core::stringw name, Gun* gun) {
	std::map<irr::core::stringw, Gun*>::iterator i;
	i = guns.find(name);
	if (i == guns.end()) {
		// not found
		guns[name] = gun;

	} else {
		Gun *tmp = i->second;
		guns[name] = gun;
		delete tmp;
	}

}

ShipWithGuns::~ShipWithGuns() {
	delete guns["main"];
}

void ShipWithGuns::updateGuns() {
	std::map<irr::core::stringw, Gun*>::iterator gun;

	for (gun = guns.begin(); gun != guns.end(); gun++) {
		gun->second->updateProjectiles();
	}
}

///////////////////////////////////////////////////////////////////////////////

NonPlayerShip::NonPlayerShip(irr::scene::ISceneNode* node) :
		Ship(node) {

}

NonPlayerShip::~NonPlayerShip() {
}

} /* namespace shs */

