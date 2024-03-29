/*
 * Object3D.cpp
 *
 *  Created on: 17-05-2013
 *      Author: Micha�
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
		node(createdNode) {
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

	// TODO: check performance loss of this call... maybe it could be called in the "update" method somewhere?? (once)
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

const irr::core::vector3df& Object3D::getPosition() {
	return node->getPosition();
}

void Object3D::revolveNodeInWorldSpace(irr::f32 degs,
		const irr::core::vector3df& axis, const irr::core::vector3df& pivot) {

	node->updateAbsolutePosition();
	core::vector3df p1 = node->getAbsolutePosition();
	core::vector3df p2 = getClosestPointOnLine(axis, pivot, p1);
	core::vector3df vect = p1 - p2;

	core::quaternion q;
	q.fromAngleAxis(degs * core::DEGTORAD, axis);
	q.getMatrix().rotateVect(vect);

	node->setPosition(p2 + vect);

}

void Object3D::revolveNodeInLocalSpace(irr::f32 degs,
		const irr::core::vector3df& axis, const irr::core::vector3df& pivot) {

	moveNodeInLocalSpace(pivot);
	rotateNodeInLocalSpace(degs, axis);
	moveNodeInLocalSpace(-pivot);

}

void Object3D::revolveNodeAboutLocalAxis(irr::f32 degs,
		const irr::core::vector3df& axis, const irr::core::vector3df& pivot) {

	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df a = axis;
	m.rotateVect(a);
	a.normalize();

	core::vector3df p1 = node->getAbsolutePosition();
	core::vector3df p2 = getClosestPointOnLine(a, pivot, p1);
	core::vector3df vect = p1 - p2;

	core::quaternion q;
	q.fromAngleAxis(degs * core::DEGTORAD, a);
	q.getMatrix().rotateVect(vect);

	node->setPosition(p2 + vect);

}

irr::core::vector3df Object3D::toWorldPos(
		const irr::core::vector3df pos_in_node_space) {

	core::vector3df pos_in_world_space(pos_in_node_space);
	node->getAbsoluteTransformation().transformVect(pos_in_world_space);
	return pos_in_world_space;

}

irr::core::vector3df Object3D::toWorldRot(
		const irr::core::vector3df rot_in_node_space) {
	core::vector3df rot_in_world_space(rot_in_node_space);
	node->getAbsoluteTransformation().transformVect(rot_in_world_space);
	return rot_in_world_space;
}

irr::core::vector3df Object3D::getIn() {

	if (node) {
		matrix4 mat = node->getRelativeTransformation();
		vector3df in(mat[8], mat[9], mat[10]);

		in.normalize();
		return in;
	} else
		return vector3df(0, 0, 0);

}

irr::core::vector3df Object3D::getRotation() {
	return node->getRotation();
}

///////////////////////////////////////////////////////////////////////////////////////////

MovingObject3D::MovingObject3D(irr::scene::ISceneNode* node) :
		Object3D(node), velocityVector(0, 0, 0), currentSpeed(0) {
}

MovingObject3D::~MovingObject3D() {
}

irr::f32 MovingObject3D::getSpeed() const {
	return currentSpeed;
}

void MovingObject3D::makeVelocityVector(irr::core::vector3df localDirection) {

	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = vector3df(localDirection).normalize();
	m.rotateVect(d);

	velocityVector = d * currentSpeed;

	/*node->setPosition(pos);
	 setVelocityVector(node->getRotation().rotationToDirection());*/
//	setVelocityVector( node->getAbsoluteTransformation().getTranslation() );
}

void MovingObject3D::setSpeed(irr::f32 currentSpeed) {
	this->currentSpeed = currentSpeed;
	velocityVector = velocityVector * currentSpeed;
}

void MovingObject3D::move() {
	node->setPosition(node->getPosition() + (velocityVector * getFrameDelta()));
}

vector3df& MovingObject3D::getVelocityVector() {
	return velocityVector;
}

void MovingObject3D::setVelocityVector(const vector3df& velocityVector) {
	this->velocityVector = vector3df(velocityVector);
	this->currentSpeed = velocityVector.getLength();
}

void MovingObject3D::updateMovement() {
	move();
}

MovingObject3D::MovingObject3D() :
		Object3D(0), velocityVector(0, 0, 0), currentSpeed(0) {
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
AcceleratingObject3D::AcceleratingObject3D(irr::scene::ISceneNode* node) :
		MovingObject3D(node), acceleration(0), accelerationVector(0, 0, 0) {

}

AcceleratingObject3D::~AcceleratingObject3D() {
}

void AcceleratingObject3D::setAcceleration(const irr::core::vector3df& vector) {
	this->accelerationVector = vector3df(vector);
	acceleration = accelerationVector.getLength();
}

void AcceleratingObject3D::setAcceleration(irr::f32 acceleration) {
	this->acceleration = acceleration;
	this->accelerationVector = (accelerationVector.normalize()) * acceleration;

}

irr::f32 AcceleratingObject3D::getAcceleration() {
	return acceleration;
}

void AcceleratingObject3D::clearAcceleration() {
	if (acceleration != 0)
		setAcceleration(vector3df(0, 0, 0));
}

void AcceleratingObject3D::makeAccelerationVector(
		irr::core::vector3df localDirection) {

	node->updateAbsolutePosition();
	core::matrix4 m = node->getAbsoluteTransformation();
	core::vector3df d = vector3df(localDirection).normalize();
	m.rotateVect(d);

	accelerationVector = (d * acceleration);

	/*node->setPosition(pos);
	 setVelocityVector(node->getRotation().rotationToDirection());*/
	//	setVelocityVector( node->getAbsoluteTransformation().getTranslation() );
}

void AcceleratingObject3D::accelerationToVelocity() {
	if (acceleration != 0.f) {
		velocityVector += (accelerationVector * getFrameDelta());
		currentSpeed = velocityVector.getLength();
	}
}

void AcceleratingObject3D::updateMovement() {
	accelerationToVelocity();
	move();
}

AcceleratingObject3D::AcceleratingObject3D() :
		MovingObject3D(), acceleration(0), accelerationVector(0, 0, 0) {
}

} /* namespace shootspacer */

