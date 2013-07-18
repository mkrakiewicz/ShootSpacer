/*
 * Weapons.cpp
 *
 *  Created on: 10-07-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "Loader.h"
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

	lastShotTime = timer.getTime();

}

void Gun::updateProjectiles() {
	std::list<Projectile*>::iterator it = activeProjectilePool.begin();
	while (it != activeProjectilePool.end()) {
		(*it)->move();
		if ((*it)->isEnd()) {
			(*it)->end();

			remainingProjectilePool.push_back(*it);
			activeProjectilePool.erase(it++);
		} else if (isCollision(*it)) {

			//create hit effect / explosion
			/**
			 * to be removed !!!!!!!!!!! TODO:
			 */
			IParticleSystemSceneNode* pas = 0;

			pas = smgr->addParticleSystemSceneNode(true);
			pas->setPosition((*it)->getPosition());

/*
			IParticleEmitter* em = pas->createBoxEmitter(
					aabbox3d<f32>(-4.f, 0.f, -4.f, 20.f,
							smoke[g].minparticleSize, 20.f), direction,
					smoke[g].minParticle, smoke[g].maxParticle,
					video::SColor(0, 0, 0, 0), video::SColor(0, 128, 128, 128),
					250, 4000, 60);

			em->setMinStartSize(
					dimension2d<f32>(smoke[g].minparticleSize,
							smoke[g].minparticleSize));
			em->setMaxStartSize(
					dimension2d<f32>(smoke[g].maxparticleSize,
							smoke[g].maxparticleSize));

			pas->setEmitter(em);
			em->drop();*/

			// particles get invisible
			IParticleAffector* paf = pas->createFadeOutParticleAffector(
					video::SColor(0, 0, 0, 0), 5000);
			pas->addAffector(paf);
			paf->drop();

			// particle system life time
			ISceneNodeAnimator* anim = smgr->createDeleteAnimator(5001);
			pas->addAnimator(anim);
			anim->drop();

			pas->setMaterialFlag(video::EMF_LIGHTING, false);
			pas->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
			pas->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			pas->setMaterialTexture(0,loader->getTexture(L"smoke")
					);

			(*it)->end();
			remainingProjectilePool.push_back(*it);
			activeProjectilePool.erase(it++);

		} else
			it++;

	}
}

void Gun::checkCollisions() {

	std::list<Projectile*>::iterator it = activeProjectilePool.begin();
	while (it != activeProjectilePool.end()) {
		if (isCollision(*it)) {

		}
	}

}

f32 Gun::getRpm() const {
	return rpm;
}

void Gun::initialize(const ShootSpacer &parent) {
	collisionManager = parent.getSmgr()->getSceneCollisionManager();
	smgr = parent.getSmgr();
	loader = &parent.getLoader();
	loader->loadTexture(L"smoke",L"img/smoke2.jpg");
	makeProjectiles(parent);
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

	u32 time = timer.getTime();

	if ((time - lastShotTime) > delay) {
		if (remainingProjectilePool.empty()) {
			// do something
			//

			for (int i = 0; i < (projectileLimit / 3); i++) {
				Projectile * tmp = *activeProjectilePool.begin();
				activeProjectilePool.pop_front();
				remainingProjectilePool.push_back(tmp);
			}
		}

		Projectile * tmp = remainingProjectilePool.back();
		remainingProjectilePool.pop_back();
		activeProjectilePool.push_back(tmp);
		irr::core::matrix4 m;
		m.setRotationDegrees(node->getRotation());

		// transform forward vector of camera
		irr::core::vector3df frv = irr::core::vector3df(0.0f, 0.0f, 1.0f);
		m.transformVect(frv);

		tmp->start(node->getPosition(), node->getVelocityVector(), frv);

		lastShotTime = timer.getTime();
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
	l.loadTexture("blue_particle", "img/blue_projectile.bmp");

	IBillboardSceneNode* tmp = 0;
	tmp = parent.getSmgr()->addBillboardSceneNode();
	tmp->setMaterialTexture(0, l.getTexture("blue_particle"));
	tmp->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	tmp->setMaterialFlag(video::EMF_LIGHTING, false);
//	tmp->setMaterialFlag(video::EMF_ZBUFFER, false);
	tmp->setSize(core::dimension2d<f32>(10.0f, 10.0f));
	tmp->setVisible(false);

	parent.getSmgr()->addBillboardSceneNode();

	for (u32 i = 0; i < projectileLimit; ++i) {
		remainingProjectilePool.push_back(new Projectile(tmp->clone(), timer));
	}

//	tmp->drop();
}

SimpleGun::~SimpleGun() {
}

////////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(scene::ISceneNode* node, irr::ITimer &timer) :
		Ship(node), distanceTravelled(0.f), maxDistance(3000), startTime(0), timer(
				timer), maxTravelTime(10000), initialSpeed(1000) {
//startTime = smgr-
	billboard = (IBillboardSceneNode*) node;
}

Projectile::~Projectile() {
}

void Projectile::start(const core::vector3df& startPos,
		const irr::core::vector3df & startVect,
		const irr::core::vector3df &direction) {
	this->startPos = startPos;
	node->setPosition(startPos);

	setVelocityVector(
			startVect + (vector3df(direction).normalize() * initialSpeed));
	node->setVisible(true);
	distanceTravelled = 0;
	timeTravelled = 0;
	startTime = timer.getTime();

}

bool Projectile::isEnd() {
	if (distanceTravelled >= maxDistance) //TODO: or if time exceeds...
		return true;
	if (timeTravelled >= maxTravelTime)
		return true;

	return false;
}

void Projectile::end() {
	node->setVisible(false);
}

void Projectile::move() {
	vector3df translation = velocityVector * getFrameDelta();
	node->setPosition(node->getPosition() + translation);
	distanceTravelled += translation.getLength();
	timeTravelled = timer.getTime() - startTime;
	billboard->getMaterial(0).MaterialTypeParam = calculateOpacityFromTime();
	//TODO: HOW TO SET OPACITY
//	billboard->setColor(SColor(calculateOpacityFromTime(),255,255,255));

}

irr::f32 Projectile::calculateOpacity() {
	//TODO: implement
}

irr::f32 Projectile::calculateOpacityFromTime() {
	return 1.f - (timeTravelled / (f32) maxTravelTime);
//	return timeTravelled%255;
}

void SimpleGun::addHitEmitter() {
}

bool Gun::isCollision(Projectile *p) {
	core::line3d<f32> ray;
	ray.start = vector3df(p->getPosition());
	ray.end = ray.start
			+ vector3df(p->getVelocityVector()) * Object3D::getFrameDelta();

	// Tracks the current intersection point with the level or a mesh
	core::vector3df intersection;
	// Used to show with triangle has been hit
	core::triangle3df hitTriangle;

	// This call is all you need to perform ray/triangle collision on every scene node
	// that has a triangle selector, including the Quake level mesh.  It finds the nearest
	// collision point/triangle, and returns the scene node containing that point.
	// Irrlicht provides other types of selection, including ray/triangle selector,
	// ray/box and ellipse/triangle selector, plus associated helpers.
	// See the methods of ISceneCollisionManager
	scene::ISceneNode * selectedSceneNode =
			collisionManager->getSceneNodeAndCollisionPointFromRay(ray,
					intersection, // This will be the position of the collision
					hitTriangle); // This will be the triangle hit in the collision
	// This ensures that only nodes that we have
	// set up to be pickable are considered
	// Check the entire scene (this is actually the implicit default)

	// If the ray hit anything, move the billboard to the collision position
	// and draw the triangle that was hit.
	if (selectedSceneNode) {
		if (selectedSceneNode != node->getNode()) {
			return true;
		}
	}
	return false;

}

} /* namespace shs */

