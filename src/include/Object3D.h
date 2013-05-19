/*
 * Object3D.h
 *
 *  Created on: 17-05-2013
 *      Author: Micha³
 */

#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include <irrlicht.h>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

class Object3D {
public:
	Object3D();
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

protected:
	vector3df position;
	vector3df rotation;
	vector3df speedVector;
};

} /* namespace shootspacer */
#endif /* OBJECT3D_H_ */
