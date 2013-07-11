/*
 * Weapons.cpp
 *
 *  Created on: 10-07-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Ship.h"
#include "Weapons.h"

namespace shs {

Gun::Gun(Object3D *node, irr::u32 limit) :
		node(node->getNode()), //if Object3D is refactored to derived ISceneNode, the GetNode method should be removed
		projectileLimit(limit), rpm(setRpm(120)),lastShotTime(0) {
	// TODO Auto-generated constructor stub

}

Gun::~Gun() {
	deleteProjectiles();
	// TODO Auto-generated destructor stub
}
////////////////////////////////////////////////////////////////////////////////////
SimpleGun::SimpleGun(Object3D* node, irr::u32 limit) :
		Gun(node, limit) {

}

void SimpleGun::shoot() {
}

void SimpleGun::makeProjectiles(Loader *loader,
		irr::scene::ISceneManager *smgr) {

	for (int i = 0; i < projectileLimit; ++i) {
		//	projectilePool.push_back(new Projectile());
	}
}

SimpleGun::~SimpleGun() {
}

void SimpleGun::deleteProjectiles() {
	// stl iteroato
	//for (irr::u32 i = 0; i < projectileLimit; ++i) {
		//	projectilePool
	//}
}
////////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(irr::scene::ISceneNode* node) :
		Ship(node), distanceTravelled(0.f) {
//startTime = smgr-
}

Projectile::~Projectile() {
}

void Projectile::start(irr::core::vector3df& startPos) {
}

void Projectile::move() {

node->setPosition(node->getPosition() + (velocityVector * getFrameDelta()));
distanceTravelled += currentSpeed;

}

void Gun::updateProjectiles() {
for (std::vector<Projectile*>::iterator it = activeProjectilePool.begin();
		it != activeProjectilePool.end(); ++it) {

}
}

irr::f32 Gun::getRpm() const {
return rpm;
}

void Gun::setRpm(irr::f32 rpm) {
this->rpm = rpm;
// per minute = 60 sec * 1000 milisec
delay = 60000 / rpm;
}

} /* namespace shs */

