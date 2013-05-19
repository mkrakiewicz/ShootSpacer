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

class Planet: public shs::Object3D {
public:
	Planet();
	virtual ~Planet();
};

} /* namespace shootspacer */
#endif /* PLANET_H_ */
