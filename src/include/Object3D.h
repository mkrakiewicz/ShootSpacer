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
	inline static irr::f32 getFrameDelta() {
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

	const irr::core::vector3df& getPosition();
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

protected:
	/**
	 * Irrlicht engine node type that will be a base for all objects.
	 */
	irr::scene::ISceneNode *node;

	irr::core::vector3df getIn();

	/**
	 * Default constructor - can't create without node as all operations rely on it
	 */
	Object3D() :
			node(0) {
	}

private:

	/**
	 * "Global" private reference for all 3D objects. only accessible by getFrameDelta()
	 */
	static irr::f32 *frameDeltaTime;

};

/*******************************************
 * Moving object class
 *
 */
class MovingObject3D: public Object3D {
public:

	/**
	 * Constructor
	 * @param node
	 */
	MovingObject3D(irr::scene::ISceneNode *node);

	~MovingObject3D();

	/**
	 * function to be called every frame
	 */
	virtual void updateMovement();

	/**
	 * Get the velocity vector
	 * TODO: Perhaps it should be already multiplied by frame delta
	 * @return
	 */
	irr::core::vector3df& getVelocityVector();

protected:

	/**
	 *  Created new velocity vector from vector. vector(0,0,1) - front by default
	 */
	void makeVelocityVector(irr::core::vector3df localDirection =
			irr::core::vector3df(0, 0, 1));

	/**
	 * Set the velocity vector (will be normalized)
	 * @param speedVector
	 */
	void setVelocityVector(const irr::core::vector3df& vector);

	/**
	 * Moves by velocityVector
	 */
	void move();

	/**
	 * Getter
	 * @return
	 */
	irr::f32 getSpeed() const;

	/**
	 * Setter for speed. Move direction is unchanged
	 * @param currentVelocity
	 */
	void setSpeed(irr::f32 currentVelocity);

	/**
	 * Vector along which the object is supposed to move each frame.
	 * Must be normalized! - it is done in set method
	 */
	irr::core::vector3df velocityVector;

	/**
	 * Velocity,Speed
	 */
	irr::f32 currentSpeed;

	/**
	 * Default constructor
	 */
	MovingObject3D();

};

class AcceleratingObject3D: public MovingObject3D {
public:
	AcceleratingObject3D(irr::scene::ISceneNode *node);
	~AcceleratingObject3D();

	/**
	 * function to be called every frame
	 */
	virtual void updateMovement();

protected:

	/**
	 *
	 * @param vector
	 */
	void setAcceleration(const irr::core::vector3df& vector);

	/**
	 *
	 * @param acceleration
	 */
	void setAcceleration(irr::f32 acceleration);

	irr::f32 getAcceleration();

	void clearAcceleration();

	/**
	 *
	 * @param localDirection
	 */
	void makeAccelerationVector(irr::core::vector3df localDirection =
			irr::core::vector3df(0, 0, 1));

	void accelerationToVelocity();

	irr::f32 acceleration;
	irr::core::vector3df accelerationVector;

	/**
	 * Default constructor
	 */
	AcceleratingObject3D();

};

} /* namespace shs */
#endif /* OBJECT3D_H_ */
