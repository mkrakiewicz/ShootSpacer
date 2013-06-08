/*
 * Planet.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Object3D.h"

namespace shs {

class Planet: public Object3D {
public:
	Planet(irr::scene::ISceneNode *createdNode);
	virtual ~Planet();

	static Planet* createTestPlanet(GameContext* c);
};

} /* namespace shootspacer */
#endif /* PLANET_H_ */
