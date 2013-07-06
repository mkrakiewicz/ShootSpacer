/*
 * Ship.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Object3D.h"

namespace shs {

/**
 * Abstract class to represent general Ship object without handling input or control
 */
class Ship: public MovingObject3D {
public:

	Ship(irr::scene::ISceneNode *node);

	virtual ~Ship();

	virtual void update() = 0;
protected:
	Ship();

	irr::f32 maxSpeed;
	irr::f32 maxRotationSpeed;
	irr::f32 maxAcceleration;
	irr::f32 acceleration;

	inline irr::f32 calculateAccelerationNonLinear();

private:
	void init();
};

/**
 * Class to be later implemented as AI ship etc...
 */
class NonPlayerShip: public Ship {
public:
	NonPlayerShip(irr::scene::ISceneNode *node);

	void update();
};

} /* namespace shootspacer */
#endif /* SHIP_H_ */
