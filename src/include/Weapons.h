/*
 * Weapons.h
 *
 *  Created on: 10-07-2013
 *      Author: Micha�
 */

#ifndef WEAPONS_H_
#define WEAPONS_H_

#include "Ship.h"
#include <list>
#include <vector>

namespace shs {

class Projectile;
class Loader;
class Object3D;
class ShootSpacer;

class Gun {
public:
	// pass pointer to parent node.
	Gun(MovingObject3D *node, irr::ITimer &timer, irr::u32 limit);
	virtual ~Gun();

	virtual void shoot() = 0;

	virtual void makeProjectiles(const ShootSpacer &parent) = 0;
	void deleteProjectiles();

	void updateProjectiles();
	irr::f32 getRpm() const;
	irr::f32 setRpm(irr::f32 rpm);

protected:

	/**
	 * maybe when we have some models there should be a gun model
	 */

	// rate per minute
	irr::f32 rpm;

	// in miliseconds? rpm/60*1000 ?
	irr::u32 delay;

	//to wait accordingly to delay
	irr::u32 lastShotTime;

	//TODO: add Type, etc

	// pointer to parent node.
	// if Object3D is refactored to derived ISceneNode, this should also be changed to Object3D.
	// but it's not necessary because of polymorphism...
	// this is also needed to set parent if model is applied later
	MovingObject3D *node;

	// Pool of all projectiles. maybe this should be just an array?
	std::vector<Projectile*> remainingProjectilePool;

	// Pool of shoot projectiles. to process only those that were shot
	std::list<Projectile*> activeProjectilePool;

	// projectile limit in pool
	irr::u32 projectileLimit;

	irr::ITimer &timer;

};

class SimpleGun: public Gun {
public:
	SimpleGun(MovingObject3D *node, irr::ITimer &timer, irr::u32 limit = 70);
	virtual ~SimpleGun();

	void shoot();

	void makeProjectiles(const ShootSpacer &parent);



};

/**
 * This class extends Ship because of it "free-flight" functions.
 * Actually projectile it's a kind of little micro space Ship : P
 *
 * Maybe this should be just Moving Object 3d class. we'll see.
 *
 */
class Projectile: public Ship {
public:

	// node of projectile, it could be billboard 2d...
	Projectile(irr::scene::ISceneNode *node, irr::ITimer &timer);
	virtual ~Projectile();

	//method to be called when shot
	void start(const irr::core::vector3df & startPos,
			const irr::core::vector3df & startVect,const irr::core::vector3df &direction);

	virtual void move();

protected:

	//starting position for reference
	irr::core::vector3df startPos;

	//distance to be added instead of calculating vector length all the time
	irr::f32 distanceTravelled;

	//distance after which projectile will be destroyed
	irr::f32 maxDistance;

	// time in miliseconds at which
	irr::u32 startTime;

	irr::ITimer &timer;

};

} /* namespace shs */
#endif /* WEAPONS_H_ */
