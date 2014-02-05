/*
 * Planet.h
 *
 *  
 *      Author: Micha�
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Object3D.h"

namespace shs {

class Spaceshooter;

class Planet: public Object3D {
public:
	Planet(irr::scene::ISceneNode *createdNode);
	virtual ~Planet();

	static Planet* createTestPlanet(const Spaceshooter &parent);
};

} /* namespace Spaceshooter */
#endif /* PLANET_H_ */
