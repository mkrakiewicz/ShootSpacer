/*
 * Camera.h
 *
 *  
 *      Author: Micha�
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "RenderLoop.h"

namespace shs {

class Object3D;

class Camera : public IrrlichtClassBase {
protected:


	irr::scene::ICameraSceneNode *camera;
public:
	Camera();
	Camera(const Spaceshooter &parent);
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
	AttachableCamera(const Spaceshooter &parent, shs::Object3D * obj,
			irr::core::vector3df offset);

	void setOffset(irr::core::vector3df offset);

	virtual void update();
	virtual void handleInput(const irr::SEvent& event);

	virtual ~AttachableCamera();
};

class StaticCamera: public AttachableCamera {
public:
	StaticCamera(const Spaceshooter &parent, shs::Object3D * obj,
			irr::core::vector3df offset = irr::core::vector3df(0.f, 10.f, -40.f));

	virtual void update();
	virtual void handleInput(const irr::SEvent& event);

	virtual ~StaticCamera();

};

//class DynamicCamera: public AttachableCamera {
//
//};

} /* namespace shs */


#endif /* CAMERA_H_ */
