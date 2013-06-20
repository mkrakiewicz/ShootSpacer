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

class Ship : public MovingObject3D {
public:

	Ship();

	Ship(irr::scene::ISceneNode *node);

	virtual ~Ship();

	virtual void update() = 0;
};

class NonPlayerShip : public  Ship {
public:
	NonPlayerShip(irr::scene::ISceneNode *node);

	void update();
};

} /* namespace shootspacer */
#endif /* SHIP_H_ */
