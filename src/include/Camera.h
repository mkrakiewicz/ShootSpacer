/*
 * Camera.h
 *
 *  Created on: 25-06-2013
 *      Author: Micha³
 */

#ifndef CAMERA_H_
#define CAMERA_H_

namespace shs {

class Object3D;

class Camera {
protected:
	GameContext context;

	irr::scene::ICameraSceneNode *camera;
public:
	Camera();
	Camera(const GameContext& context);
	virtual ~Camera();

	virtual void update() = 0;
	virtual void handleInput(const irr::SEvent& event) = 0;
};

class AttachableCamera: public Camera {
protected:
	void setPositionAtOffset();

	irr::scene::ISceneNode * node;
	irr::core::vector3df offset;
public:
	AttachableCamera(const GameContext & context, shs::Object3D * obj,
			irr::core::vector3df offset = irr::core::vector3df(0, 10, -40));

	void setOffset(irr::core::vector3df offset);

	virtual void update();
	virtual void handleInput(const irr::SEvent& event);

	virtual ~AttachableCamera();
};

class StaticCamera: public AttachableCamera {
public:
	StaticCamera(const GameContext & context, shs::Object3D * obj,
			irr::core::vector3df offset = irr::core::vector3df(0, 10, -40));

	virtual void update();
	virtual void handleInput(const irr::SEvent& event);

	virtual ~StaticCamera();

};

//class DynamicCamera: public AttachableCamera {
//
//};

} /* namespace shs */


#endif /* CAMERA_H_ */
