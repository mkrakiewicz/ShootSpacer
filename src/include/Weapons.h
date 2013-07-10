/*
 * Weapons.h
 *
 *  Created on: 10-07-2013
 *      Author: Micha³
 */

#ifndef WEAPONS_H_
#define WEAPONS_H_

#include <vector>

namespace shs {

class Projectile;

class Gun {
public:
	// pass pointer to parent node.
	Gun(Object3D *node, Loader *loader, irr::u32 limit);
	virtual ~Gun();

	virtual void shoot() = 0;

protected:

	/**
	 * maybe when we have some models there should be a gun model
	 */

	// pointer to parent node.
	// if Object3D is refactored to derived ISceneNode, this should also be changed to Object3D.
	// but it's not necessary because of polymorphism...
	// this is also needed to set parent if model is applied later
	irr::scene::ISceneNode *node;

	// Pool of all projectiles. maybe this should be just an array?
	std::vector<Projectile*> projectilePool;

	// Pool of shoot projectiles. to process only those that were shot
	std::vector<Projectile*> activeProjectilePool;

	// projectile limit in pool
	irr::u32 projectileLimit;

	// loader
	Loader *loader,

	Gun():node(0),projectileLimit(0){};

};


class SimpleGun : public Gun {
public:
	SimpleGun(Object3D *node, irr::u32 limit = 50);
	virtual ~SimpleGun();

	void shoot();

protected:
	void makeProjectiles();
	void deleteProjectiles();

	SimpleGun(){}
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
	Projectile(irr::scene::ISceneNode *node);
	virtual ~Projectile();

	//method to be called when shot
	void start(irr::core::vector3df & startPos);

	void move();

protected:

	//starting position for reference
	irr::core::vector3df startPos;

	//distance to be added instead of calculating vector length all the time
	irr::f32 distanceTravelled;

};

} /* namespace shs */
#endif /* WEAPONS_H_ */
