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
protected:
	IMeshSceneNode *node;
//	vector3df position;
//	vector3df rotation;
	vector3df speedVector;
public:
	Object3D(IMeshSceneNode *node);
	virtual ~Object3D();

	/*
	 *
	 * getters and setters
	 *
	 * */

	const vector3df& getPosition() const;
	void setPosition(const vector3df& position);
	const vector3df& getRotation() const;
	void setRotation(const vector3df& rotation);
	const vector3df& getSpeedVector() const;
	void setSpeedVector(const vector3df& speedVector);


	/*
	 * functions by SMSO from Irrlicht forum:
	 * */

	void rotateNodeInLocalSpace(scene::ISceneNode* node, f32 degs, const core::vector3df& axis);

	void rotateNodeInWorldSpace(scene::ISceneNode* node, f32 degs, const core::vector3df& axis);

	// the line is defined by axis direction passing through the pivot
	// 3rd argument "point" is the external point
	core::vector3df getClosestPointOnLine(const core::vector3df& axis,
			const core::vector3df& pivot, const core::vector3df& point);



};

} /* namespace shootspacer */
#endif /* OBJECT3D_H_ */
