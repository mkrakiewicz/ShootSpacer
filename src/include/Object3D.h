/*
 * Object3D.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#ifndef OBJECT3D_H_
#define OBJECT3D_H_

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

class Object3D {
private:

	/**
	 * "Global" private reference for all 3D objects. only accessible by getFrameDelta()
	 */
	static f32 *frameDeltaTime;

protected:
	/**
	 * Irrlicht engine node type that will be a base for all objects.
	 */
	ISceneNode *node;

public:

	/**
	 * Default constructor
	 */
	Object3D() :
			node(0) {
	}

	/**
	 * Constructor
	 * @param node
	 */
	Object3D(ISceneNode *node);
	virtual ~Object3D();

	/**
	 *
	 * Setting frame delta reference for all objects
	 * @param ref
	 */
	static void setFrameDeltaReference(f32 *ref);

	/**
	 * Get frame delta time
	 * @return
	 */
	inline f32 getFrameDelta() {
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
	void rotateNodeInLocalSpace(f32 degs, const core::vector3df& axis);
	/**
	 *
	 * @param degs
	 * @param axis
	 */
	void rotateNodeInWorldSpace(f32 degs, const core::vector3df& axis);
	/**
	 *
	 * @param node
	 * @param distVect
	 */
	void moveNodeInLocalSpace(scene::ISceneNode* node,
			const core::vector3df& distVect);
	/**
	 *
	 * @param node
	 * @param dir
	 * @param dist
	 */
	void moveNodeInLocalSpace(scene::ISceneNode* node,
			const core::vector3df& dir, f32 dist);

	/**
	 * 	 	the line is defined by axis direction passing through the pivot
	 *		3rd argument "point" is the external point
	 * @param axis
	 * @param pivot
	 * @param point
	 * @return
	 */
	core::vector3df getClosestPointOnLine(const core::vector3df& axis,
			const core::vector3df& pivot, const core::vector3df& point);

};

/*******************************************
 * Moving object class
 *
 */
class MovingObject3D: public Object3D {
protected:

	/**
	 * Vector along which the object is supposed to move each frame. Must be multiplied by frame delta.
	 */
	vector3df speedVector;

public:

	/**
	 * Default constructor
	 */
	MovingObject3D() :
			Object3D(0) {
	}

	/**
	 * Constructor
	 * @param node
	 */
	MovingObject3D(ISceneNode *node) :
			Object3D(node) {
	}

	/**
	 * Get the speed vector
	 * TODO: Perhaps it should be already multiplied by frame delta?
	 * TODO: check if returning reference is good practice. it's supposed to be faster than returning by value...
	 * @return
	 */
	const vector3df& getSpeedVector() const;

	/**
	 * Set the speed vector
	 * @param speedVector
	 */
	void setSpeedVector(const vector3df& speedVector);
};

} /* namespace shs */
#endif /* OBJECT3D_H_ */
