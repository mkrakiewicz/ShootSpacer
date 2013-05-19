/*
 * Object3D.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Object3D.h"

namespace shs {

Object3D::Object3D() {
	// TODO Auto-generated constructor stub
}

Object3D::~Object3D() {
	// TODO Auto-generated destructor stub
}

const vector3df& Object3D::getPosition() const {
	return position;
}

void Object3D::setPosition(const vector3df& position) {
	this->position = position;
}

const vector3df& Object3D::getRotation() const {
	return rotation;
}

void Object3D::setRotation(const vector3df& rotation) {
	this->rotation = rotation;
}

const vector3df& Object3D::getSpeedVector() const {
	return speedVector;
}

void Object3D::setSpeedVector(const vector3df& speedVector) {
	this->speedVector = speedVector;
}

} /* namespace shootspacer */
