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
	Gun(Object3D *node, irr::u32 limit);
	virtual ~Gun();

	virtual void shoot() = 0;

	void makeProjectiles(Loader *loader, irr::scene::ISceneManager *smgr) = 0;
	void deleteProjectiles() = 0;

	void updateProjectiles();

protected:

	/**
	 * maybe when we have some models there should be a gun model
	 */

	//TODO: add Type, etc

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

	Gun() :
			node(0), projectileLimit(0), loader(0), smgr(0) {
	};

};

class SimpleGun: public Gun {
public:
	SimpleGun(Object3D *node, irr::u32 limit = 50);
	virtual ~SimpleGun();

	void shoot();

	void makeProjectiles(Loader *loader, irr::scene::ISceneManager *smgr);
	void deleteProjectiles();


protected:

	SimpleGun() {
	}
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

};

} /* namespace shs */
#endif /* WEAPONS_H_ */
