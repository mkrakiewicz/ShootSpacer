/*
 * Object3D.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Object3D.h"

namespace shs {

Object3D::Object3D(ISceneNode *createdNode) : node(createdNode)
{
//	this->node = node;
}

Object3D::~Object3D() {
	// TODO Auto-generated destructor stub
}
//
//const vector3df& Object3D::getPosition() const {
//	return node->getAbsolutePosition();
//}
//
//void Object3D::setPosition(const vector3df& position) {
//	node->setPosition(position);
//
//}
//
//const vector3df& Object3D::getRotation() const {
//	return node->getRotation();
//}
//
//void Object3D::setRotation(const vector3df& rotation) {
//	node->setRotation(rotation);
//}

const vector3df& Object3D::getSpeedVector() const {
	return speedVector;
}

void Object3D::setSpeedVector(const vector3df& speedVector) {
	this->speedVector = speedVector;
}

void Object3D::rotateNodeInWorldSpace(f32 degs, const core::vector3df& axis) {

	core::quaternion q;
	q.fromAngleAxis(degs * core::DEGTORAD, axis);
	core::matrix4 m1 = q.getMatrix();

	node->updateAbsolutePosition();
	core::matrix4 m2 = node->getAbsoluteTransformation();

	core::matrix4 m = m1 * m2;
	node->setRotation(m.getRotationDegrees());

}

void Object3D::rotateNodeInLocalSpace(f32 degs, const core::vector3df& axis) {
	node->updateAbsolutePosition();
	core::matrix4 m2 = node->getAbsoluteTransformation();
	core::vector3df a = axis;
	m2.rotateVect(a);
	a.normalize();

	core::quaternion q;
	q.fromAngleAxis(degs * core::DEGTORAD, a);
	core::matrix4 m1 = q.getMatrix();

	core::matrix4 m = m1 * m2;
	node->setRotation(m.getRotationDegrees());

}

core::vector3df Object3D::getClosestPointOnLine(const core::vector3df& axis,
		const core::vector3df& pivot, const core::vector3df& point) {
	core::vector3df c = point - pivot;
	f32 t = axis.dotProduct(c);
	return pivot + axis * t;
}

void Object3D::moveNodeInLocalSpace(scene::ISceneNode* node,
		const core::vector3df& distVect) {
	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = distVect;
	m.rotateVect(d);

	core::vector3df pos = node->getAbsolutePosition() + d;
	node->setPosition(pos);
}

void Object3D::moveNodeInLocalSpace(scene::ISceneNode* node,
		const core::vector3df& dir, f32 dist) {
	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = dir;
	m.rotateVect(d);
	d.normalize();

	core::vector3df pos = node->getAbsolutePosition() + d * dist;
	node->setPosition(pos);
}

} /* namespace shootspacer */
