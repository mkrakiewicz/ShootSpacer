/*
 * PlayerShip.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha�
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "Object3D.h"

namespace shs {

class PlayerShip: public shs::Object3D {
public:
	PlayerShip();
	virtual ~PlayerShip();
};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
