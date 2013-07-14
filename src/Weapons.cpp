/*
 * Weapons.cpp
 *
 *  Created on: 10-07-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "Loader.h"
#include "Ship.h"
#include "Weapons.h"
#include "Object3D.h"
#include "ShootSpacer.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

Gun::Gun(Object3D *node, u32 limit) :
		node(node->getNode()), //if Object3D is refactored to derived ISceneNode, the GetNode method should be removed
		projectileLimit(limit), rpm(setRpm(120)), lastShotTime(0) {
	// TODO Auto-generated constructor stub

}

void Gun::updateProjectiles() {
	for (std::vector<Projectile*>::iterator it = activeProjectilePool.begin();
			it != activeProjectilePool.end(); ++it) {

	}
}

f32 Gun::getRpm() const {
	return rpm;
}

f32 Gun::setRpm(f32 rpm) {
	this->rpm = rpm;
// per minute = 60 sec * 1000 milisec
	delay = 60000 / rpm;

	return rpm;
}
void Gun::deleteProjectiles() {
	std::vector<Projectile*>::iterator itr;

	itr = projectilePool.begin();

	while (itr != projectilePool.end()) {
		Projectile* tmp = 0;
		tmp = *itr;
		if (tmp != 0) {

//			availableStates.erase(itr);

			delete tmp;
		}

		itr++;

	}
}
Gun::~Gun() {
	deleteProjectiles();
	// TODO Auto-generated destructor stub
}
////////////////////////////////////////////////////////////////////////////////////
SimpleGun::SimpleGun(Object3D* node, u32 limit) :
		Gun(node, limit) {

}

void SimpleGun::shoot() {
}

void SimpleGun::makeProjectiles(const ShootSpacer &parent) {

	for (int i = 0; i < projectileLimit; ++i) {
		//	projectilePool.push_back(new Projectile());
	}
}

SimpleGun::~SimpleGun() {
}

////////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(scene::ISceneNode* node) :
		Ship(node), distanceTravelled(0.f), maxDistance(1000), startTime(0) {
//startTime = smgr-
}

Projectile::~Projectile() {
}

void Projectile::start(core::vector3df& startPos) {
}

void Projectile::move() {

	node->setPosition(node->getPosition() + (velocityVector * getFrameDelta()));
	distanceTravelled += currentSpeed;

}

} /* namespace shs */

