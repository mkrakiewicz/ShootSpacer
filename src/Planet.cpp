/*
 * Planet.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Planet.h"

using namespace shs;

namespace shs {

Planet::Planet(ISceneNode *createdNode):Object3D(createdNode)
{
	// TODO Auto-generated constructor stub

}

Planet::~Planet() {
	// TODO Auto-generated destructor stub
}

Planet* Planet::createTestPlanet(GameContext* c) {

	ISceneNode *tmp = (c->smgr->addSphereSceneNode(10));

	tmp->setPosition(vector3df(50,0,0));
	if (tmp) {
		tmp->setMaterialFlag(EMF_LIGHTING, false);

		tmp->setMaterialTexture(0,
				c->driver->getTexture(
						"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/earth.jpg"));
	}

	Planet *p = new Planet(tmp);
	return p;
}

} /* namespace shootspacer */
