/*
 * Camera.cpp
 *
 *  Created on: 25-06-2013
 *      Author: Micha�
 */
#include "stdafx.h"
#include "ShootSpacer.h"
#include "Camera.h"
#include "Object3D.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

Camera::Camera(const ShootSpacer &parent) :
		IrrlichtClassBase(parent) {
	camera = smgr->addCameraSceneNode(0);
	smgr->setActiveCamera(camera);
	camera->setFarValue(11000.f);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


void AttachableCamera::setPositionAtOffset() {

	vector3df offset = this->offset;
	//get rotation matrix of node - Zeuss must be getRotation not getRelativeTransformation
	irr::core::matrix4 m;
	m.setRotationDegrees(node->getRotation());

	// transform forward vector of camera
	irr::core::vector3df frv = irr::core::vector3df(0.0f, 0.0f, 1.0f);
	m.transformVect(frv);

	// transform upvector of camera
	irr::core::vector3df upv = irr::core::vector3df(0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	// transform camera offset (thanks to Zeuss for finding it was missing)
	m.transformVect(offset);

	// set camera
	camera->setPosition(node->getPosition() + offset); //position camera in front of the ship
	camera->setUpVector(upv); //set up vector of camera >> Zeuss - tested with +node->getPostion() and it didnt work, but this works fine.
	camera->setTarget(node->getPosition() + node->getRotation().rotationToDirection()*1000.f); //set target of camera (look at point) >> Zeuss - Dont forget to add the node positiob

}

void AttachableCamera::setOffset(irr::core::vector3df offset) {
	this->offset = offset;
}

void AttachableCamera::update() {
	setPositionAtOffset();
}

void AttachableCamera::handleInput(const irr::SEvent& event) {
}

AttachableCamera::AttachableCamera(const ShootSpacer &parent,
		shs::Object3D * obj, irr::core::vector3df offset) :
		Camera(parent), node(obj->getNode()), offset(offset) {

	camera->setPosition(node->getPosition() + offset);
	camera->setTarget(node->getPosition());
	camera->bindTargetAndRotation(true);
}

AttachableCamera::~AttachableCamera() {
}

} /* namespace shs */

shs::StaticCamera::StaticCamera(const ShootSpacer &parent,
		shs::Object3D * obj, irr::core::vector3df offset) :

		AttachableCamera(parent, obj, offset) {
}

void shs::StaticCamera::update() {
	setPositionAtOffset();
}

void shs::StaticCamera::handleInput(const irr::SEvent& event) {
}

shs::StaticCamera::~StaticCamera() {
}
