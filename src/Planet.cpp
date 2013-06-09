/*
 * Planet.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "Planet.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


using namespace shs;



namespace shs {

Planet::Planet(ISceneNode *createdNode):Object3D(createdNode)
{

}

Planet::~Planet() {
}

Planet* Planet::createTestPlanet(const GameContext &context) {

	GameContext *c = &context;

	ISceneNode *tmp = (c->smgr->addSphereSceneNode(80,64));

	tmp->setPosition(vector3df(100,10,0));
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
