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
 * Ship : short of "SpaceShip". It doesn't float on water :D
 * Abstract class to represent general Ship object without handling input or control
 */
class Ship: public AcceleratingObject3D {
public:

	Ship(irr::scene::ISceneNode *node);

	virtual ~Ship();

	virtual void update();
	void setMaxAcceleration(irr::f32 maxAcceleration);
	void setMaxRotationSpeed(irr::f32 maxRotationSpeed);
	void setMaxSpeed(irr::f32 maxSpeed);

	void accelerate();

protected:
	Ship();

	irr::f32 maxSpeed;
	irr::f32 maxRotationSpeed;
	irr::f32 maxAcceleration;


	inline irr::f32 calculateAccelerationNonLinear();


//	virtual void makeVelocityVector(irr::core::vector3df localDirection =
//			irr::core::vector3df(0, 0, 1));

private:
	void init();
};

/**
 * Class to be later implemented as AI ship etc...
 */
class NonPlayerShip: public Ship {
public:
	NonPlayerShip(irr::scene::ISceneNode *node);


};

} /* namespace shootspacer */
#endif /* SHIP_H_ */
