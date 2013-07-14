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

Gun::Gun(MovingObject3D *node, irr::ITimer &timer, u32 limit) :
		node(node), //if Object3D is refactored to derived ISceneNode, the GetNode method should be removed
		projectileLimit(limit), rpm(setRpm(120)), lastShotTime(0), timer(timer) {
	// TODO Auto-generated constructor stub

}

void Gun::updateProjectiles() {
	for (std::vector<Projectile*>::iterator it = activeProjectilePool.begin();
			it != activeProjectilePool.end(); ++it) {
		(*it)->move();

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

	itr = remainingProjectilePool.begin();

	while (itr != remainingProjectilePool.end()) {
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
SimpleGun::SimpleGun(MovingObject3D* node, irr::ITimer &timer, u32 limit) :
		Gun(node, timer, limit) {

}

void SimpleGun::shoot() {

	if (remainingProjectilePool.empty()) {
		// do something
	} else {
		Projectile * tmp = remainingProjectilePool.back();
		remainingProjectilePool.pop_back();
		tmp->start(node->getPosition(), node->getVelocityVector());
	}

}

void SimpleGun::makeProjectiles(const ShootSpacer &parent) {

//	scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
//		bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
//		bill->setMaterialTexture(0, driver->getTexture("../../media/particle.bmp"));
//		bill->setMaterialFlag(video::EMF_LIGHTING, false);
//		bill->setMaterialFlag(video::EMF_ZBUFFER, false);
//		bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
//		bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

	Loader &l = parent.getLoader();
	l.loadTexture("orange_particle", "img/orange_projectile.bmp");

	IBillboardSceneNode* tmp = 0;
	tmp = parent.getSmgr()->addBillboardSceneNode();
	tmp->setMaterialTexture(0, l.getTexture("orange_particle"));
	tmp->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	tmp->setMaterialFlag(video::EMF_ZBUFFER, false);
	tmp->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	tmp->setVisible(false);

	parent.getSmgr()->addBillboardSceneNode();

	for (u32 i = 0; i < projectileLimit; ++i) {
		remainingProjectilePool.push_back(new Projectile(tmp->clone(), timer));
	}

	tmp->drop();
}

SimpleGun::~SimpleGun() {
}

////////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(scene::ISceneNode* node, irr::ITimer &timer) :
		Ship(node), distanceTravelled(0.f), maxDistance(1000), startTime(0), timer(
				timer) {
//startTime = smgr-
}

Projectile::~Projectile() {
}

void Projectile::start(const core::vector3df& startPos,
		const irr::core::vector3df & startVect) {
	this->startPos = startPos;
	setVelocityVector(startVect);
	node->setVisible(true);

}

void Projectile::move() {
	vector3df translation = velocityVector * getFrameDelta();
	node->setPosition(node->getPosition() + translation);
	distanceTravelled += translation.getLength();

}

} /* namespace shs */

