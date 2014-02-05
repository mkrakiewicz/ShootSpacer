/*
 * Weapons.h
 *
 *  
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
class Spaceshooter;
class HitEffect;
class StopEmitter;

class Gun {
public:
	// pass pointer to parent node.
	Gun(MovingObject3D *node, irr::ITimer &timer, irr::u32 limit);
	virtual ~Gun();

	virtual void shoot() = 0;

	virtual void initialize(const Spaceshooter &parent);



	void updateProjectiles();
	irr::f32 getRpm() const;
	irr::f32 setRpm(irr::f32 rpm);

protected:

	irr::scene::ISceneManager *smgr;

	 Loader  *loader;


	virtual void makeProjectiles(const Spaceshooter &parent) = 0;
	void deleteProjectiles();

	virtual void checkCollisions();

	virtual bool isCollision( Projectile *p);

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

	/**
	 *  Remaining and active projectile pool element numbers should be adjusted so that
	 *  remaining projectile pool has projectiles at the moment where "First" shot needs to be
	 *  removed... so that they don't disappear in the middle of the way when player shoots a lot
	 */

	// Pool of all projectiles. maybe this should be just an array?
	std::vector<Projectile*> remainingProjectilePool;

	// Pool of shoot projectiles. to process only those that were shot
	std::list<Projectile*> activeProjectilePool;

	// projectile limit in pool
	irr::u32 projectileLimit;

	irr::ITimer &timer;

	/**
	 *
	 * For each projectile there must be a "hit effect"...
	 * if the animation of effect finishes before it needs to be run again, then we need more
	 * nodes for effects
	 */

	irr::scene::ISceneCollisionManager* collisionManager;


};

class SimpleGun: public Gun {
public:
	SimpleGun(MovingObject3D *node, irr::ITimer &timer, irr::u32 limit = 30);
	virtual ~SimpleGun();

	void shoot();

	void makeProjectiles(const Spaceshooter &parent);
protected:

	void addHitEmitter();

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
			const irr::core::vector3df & startVect,
			const irr::core::vector3df &direction);
	bool isEnd();

	void end();

	virtual void move();

protected:

	irr::scene::IBillboardSceneNode *billboard;

	irr::f32 calculateOpacity();

	irr::f32 calculateOpacityFromTime();

	//speed of projectile when ship is not moving
	irr::f32 initialSpeed;

	//starting position for reference
	irr::core::vector3df startPos;

	//distance to be added instead of calculating vector length all the time
	irr::f32 distanceTravelled;

	//distance after which projectile will be destroyed
	irr::f32 maxDistance;

	// time in miliseconds at which
	irr::u32 startTime;

	irr::u32 timeTravelled;

	irr::u32 maxTravelTime;

	irr::ITimer &timer;

};

class HitEffect {

	static void addSimpleSmokeEffect();
};


class StopEmitter : public irr::scene::ISceneNodeAnimator {
public:
	StopEmitter(irr::u32 startTime, irr::u32 stopAfter = 100);

	virtual irr::scene::ISceneNodeAnimator * createClone (irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager=0);
	virtual void animateNode (irr::scene::ISceneNode *node, irr::u32 timeMs);
	virtual ~StopEmitter(){
		drop();
	}

protected:
	irr::u32 startTime;
	irr::u32 stopTime;
};

} /* namespace shs */
#endif /* WEAPONS_H_ */
