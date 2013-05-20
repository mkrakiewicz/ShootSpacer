/*
 * Planet.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "Object3D.h"

using namespace shs;

namespace shs {

class Planet: public Object3D {
public:
	Planet(IAnimatedMeshSceneNode &createdNode);
	virtual ~Planet();
};

} /* namespace shootspacer */
#endif /* PLANET_H_ */
