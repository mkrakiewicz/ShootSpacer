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
};

} /* namespace shootspacer */
#endif /* SHIP_H_ */
