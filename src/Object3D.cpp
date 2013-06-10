/*
 * Object3D.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Object3D.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

f32* Object3D::frameDeltaTime = 0;

Object3D::Object3D(ISceneNode *createdNode) :
		node(createdNode)
{
//	this->node = node;
}

Object3D::~Object3D() {

}


void Object3D::rotateNodeInWorldSpace(f32 degs, const core::vector3df& axis) {

	f32 mult = 1.f;
	if (getFrameDelta() != 0) {
		mult = getFrameDelta();
	}

	core::quaternion q;
	q.fromAngleAxis(degs * mult * core::DEGTORAD, axis);
	core::matrix4 m1 = q.getMatrix();

	node->updateAbsolutePosition();
	core::matrix4 m2 = node->getAbsoluteTransformation();

	core::matrix4 m = m1 * m2;
	node->setRotation(m.getRotationDegrees());

}

void Object3D::rotateNodeInLocalSpace(f32 degs, const core::vector3df& axis) {
	f32 mult = 1.f;
	if (getFrameDelta() != 0) {
		mult = getFrameDelta();
	}
	node->updateAbsolutePosition();
	core::matrix4 m2 = node->getAbsoluteTransformation();
	core::vector3df a = axis;
	m2.rotateVect(a);
	a.normalize();

	core::quaternion q;
	q.fromAngleAxis(degs * mult * core::DEGTORAD, a);
	core::matrix4 m1 = q.getMatrix();

	core::matrix4 m = m1 * m2;
	node->setRotation(m.getRotationDegrees());

}

void Object3D::setFrameDeltaReference(f32 *ref) {

	Object3D::frameDeltaTime = ref;
}

core::vector3df Object3D::getClosestPointOnLine(const core::vector3df& axis,
		const core::vector3df& pivot, const core::vector3df& point) {
	core::vector3df c = point - pivot;
	f32 t = axis.dotProduct(c);
	return pivot + axis * t;
}

void Object3D::moveNodeInLocalSpace(const core::vector3df& distVect) {

	f32 mult = 1.f;
	if (getFrameDelta() != 0) {
		mult = getFrameDelta();
	}

	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = distVect * mult;
	m.rotateVect(d);

	core::vector3df pos = node->getAbsolutePosition() + d;
	node->setPosition(pos);
}

void Object3D::moveNodeInLocalSpace(const core::vector3df& dir, f32 dist) {
	f32 mult = 1.f;
	if (getFrameDelta() != 0) {
		mult = getFrameDelta();
	}

	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = dir;
	m.rotateVect(d);
	d.normalize();

	core::vector3df pos = node->getAbsolutePosition() + d * dist * mult;
	node->setPosition(pos);
}


const vector3df& MovingObject3D::getSpeedVector() const {
	return speedVector;
}

void MovingObject3D::setSpeedVector(const vector3df& speedVector) {
	this->speedVector = speedVector;
}

irr::core::vector3df Object3D::getPosition() {
	return node->getAbsolutePosition();
}

} /* namespace shootspacer */
