/*
 * PlayerShip.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "Object3D.h"

namespace shootspacer {

class PlayerShip: public shootspacer::Object3D {
public:
	PlayerShip();
	virtual ~PlayerShip();
};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
