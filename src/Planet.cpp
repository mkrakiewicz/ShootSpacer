/*
 * Planet.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "ShootSpacer.h"
#include "Planet.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace shs;

namespace shs {

Planet::Planet(ISceneNode *createdNode) :
		Object3D(createdNode) {

}

Planet::~Planet() {
}

Planet* Planet::createTestPlanet(const ShootSpacer &parent) {

	IMeshSceneNode *tmp = parent.getSmgr()->addSphereSceneNode(180, 128);

	tmp->setPosition(vector3df(100, 10, 0));
	if (tmp) {
		tmp->setMaterialFlag(EMF_LIGHTING, false);

		tmp->setMaterialTexture(0,
				parent.getDriver()->getTexture("img/earth.jpg"));
	}

	ITriangleSelector * selector = parent.getSmgr()->createTriangleSelector(
			tmp->getMesh(), tmp);
	tmp->setTriangleSelector(selector);
	selector->drop();

	Planet *p = new Planet(tmp);
	return p;
}

} /* namespace shootspacer */
