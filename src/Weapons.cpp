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

Gun::Gun(Object3D *node, Loader *loader, irr::u32 limit) :
		node(node->getNode()), //if Object3D is refactored to derived ISceneNode, the GetNode method should be removed
		projectileLimit(limit), loader(loader) {
	// TODO Auto-generated constructor stub

}

Gun::~Gun() {
	// TODO Auto-generated destructor stub
}
////////////////////////////////////////////////////////////////////////////////////
SimpleGun::SimpleGun(Object3D* node, irr::u32 limit) :
		Gun(node, limit) {

}

void SimpleGun::shoot() {
}

void SimpleGun::makeProjectiles() {

	for (int i = 0; i < projectileLimit; ++i) {
//		projectilePool.push_back(new Projectile());
	}
}

SimpleGun::~SimpleGun() {
}

void SimpleGun::deleteProjectiles() {
	for (int i = 0; i < projectileLimit; ++i) {
		//	projectilePool
	}
}
////////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(irr::scene::ISceneNode* node) :
		Ship(node), distanceTravelled(0.f) {
}

Projectile::~Projectile() {
}

void Projectile::start(irr::core::vector3df& startPos) {
}

void Projectile::move() {

	node->setPosition(node->getPosition() + (velocityVector * getFrameDelta()));
	distanceTravelled += currentSpeed;

}

} /* namespace shs */

