/*
 * Planet.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Object3D.h"

using namespace shs;

namespace shs {

class Planet: public Object3D {
public:
	Planet(ISceneNode *createdNode);
	virtual ~Planet();

	static Planet* createTestPlanet(GameContext* c);
};

} /* namespace shootspacer */
#endif /* PLANET_H_ */
