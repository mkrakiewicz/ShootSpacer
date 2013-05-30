/*
 * PlayerShip.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha�
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "Ship.h"

namespace shs {

class PlayerShip: public shs::Ship {
public:
	PlayerShip();
	PlayerShip(IAnimatedMeshSceneNode *node);
	virtual ~PlayerShip();

	static ISceneNode* createPlayerShip(GameContext *c);

};

} /* namespace shootspacer */
#endif /* PLAYERSHIP_H_ */
