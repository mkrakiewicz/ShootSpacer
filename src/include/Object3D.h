/*
 * Object3D.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#ifndef OBJECT3D_H_
#define OBJECT3D_H_

namespace shs {

class Object3D {
private:

	/**
	 * "Global" private reference for all 3D objects. only accessible by getFrameDelta()
	 */
	static irr::f32 *frameDeltaTime;

protected:
	/**
	 * Irrlicht engine node type that will be a base for all objects.
	 */
	irr::scene::ISceneNode *node;

	irr::core::vector3df getIn();

	/**
	 * Default constructor
	 */
	Object3D() :
			node(0) {
	}
public:

	/**
	 * Constructor
	 * @param node
	 */
	Object3D(irr::scene::ISceneNode *node);
	virtual ~Object3D();

	/**
	 *
	 * Setting frame delta reference for all objects
	 * @param ref
	 */
	static void setFrameDeltaReference(irr::f32 *ref);

	/**
	 * Get frame delta time
	 * @return
	 */
	inline irr::f32 getFrameDelta() {
		if (!frameDeltaTime)
			return 1.f;

		return *frameDeltaTime;

	}

	/******************************************
	 * Rotation and translation of 3D Object. *
	 * Functions by SMSO from Irrlicht forum: *
	 ******************************************
	 ******************************************
	 ******************************************/

	/**
	 *
	 * @param degs
	 * @param axis
	 */
	void rotateNodeInLocalSpace(irr::f32 degs,
			const irr::core::vector3df& axis);
	/**
	 *
	 * @param degs
	 * @param axis
	 */
	void rotateNodeInWorldSpace(irr::f32 degs,
			const irr::core::vector3df& axis);
	/**
	 *
	 * @param node
	 * @param distVect
	 */
	void moveNodeInLocalSpace(const irr::core::vector3df& distVect);
	/**
	 *
	 * @param node
	 * @param dir
	 * @param dist
	 */
	void moveNodeInLocalSpace(const irr::core::vector3df& dir, irr::f32 dist);

	/**
	 * 	 	the line is defined by axis direction passing through the pivot
	 *		3rd argument "point" is the external point
	 * @param axis
	 * @param pivot
	 * @param point
	 * @return
	 */
	irr::core::vector3df getClosestPointOnLine(const irr::core::vector3df& axis,
			const irr::core::vector3df& pivot,
			const irr::core::vector3df& point);

	//both axis and pivot are in world space
	void revolveNodeInWorldSpace(irr::f32 degs,
			const irr::core::vector3df& axis,
			const irr::core::vector3df& pivot);

	//both axis and pivot are in local space
	void revolveNodeInLocalSpace(irr::f32 degs,
			const irr::core::vector3df& axis,
			const irr::core::vector3df& pivot);

	//axis is in local space and pivot in world space
	void revolveNodeAboutLocalAxis(irr::f32 degs,
			const irr::core::vector3df& axis,
			const irr::core::vector3df& pivot);

	irr::core::vector3df toWorldPos(
			const irr::core::vector3df pos_in_node_space);
	irr::core::vector3df toWorldRot(
			const irr::core::vector3df rot_in_node_space);

	irr::core::vector3df getPosition();
	irr::core::vector3df getRotation();

	/**
	 *
	 * TODO: TO BE REMOVED
	 *
	 * BREAKS ALL OOP RULES... need to refactor Object3D as derived from ISceneNode ............. !! ??
	 * @return
	 */
	inline irr::scene::ISceneNode * getNode() {
		return node;
	}

};

/*******************************************
 * Moving object class
 *
 */
class MovingObject3D: public Object3D {
protected:

	/**
	 * Vector along which the object is supposed to move each frame. Must be multiplied by frame delta. TODO: ?
	 * If
	 */
	irr::core::vector3df velocityVector;

	/**
	 * Default constructor
	 */
	MovingObject3D() :
			Object3D(0) {
	}
public:

	/**
	 * Constructor
	 * @param node
	 */
	MovingObject3D(irr::scene::ISceneNode *node) :
			Object3D(node) {
	}

	/**
	 * Get the velocity vector
	 * TODO: Perhaps it should be already multiplied by frame delta?
	 * TODO: check if returning reference is good practice. it's supposed to be faster than returning by value...
	 * @return
	 */
	const irr::core::vector3df& getVelocityVector() const;

	/**
	 * Set the speed vector
	 * @param speedVector
	 */
	void setVelocityVector(const irr::core::vector3df& vector);
};

} /* namespace shs */
#endif /* OBJECT3D_H_ */
