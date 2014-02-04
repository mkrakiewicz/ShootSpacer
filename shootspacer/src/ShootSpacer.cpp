/*
 * ShootSpacer.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "Menu.h"
#include "Ship.h"
#include "Planet.h"
#include "Level.h"
#include "LevelManager.h"
#include "ShootSpacer.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace shs;
namespace shs {


//////////////////////////////////////////////////////////////////////////////

//ShootSpacerInstance* ShootSpacerInstance::_instance = NULL;
int ShootSpacerInstance::_referenceCount = 0;

ShootSpacerInstance* shs::ShootSpacerInstance::getInstance() {

	if ( _instance == 0) {
		_instance(new ShootSpacerInstance());
		_referenceCount++;
	}
	return _instance;

}

void shs::ShootSpacerInstance::releaseInstance() {
//	_referenceCount--;
//	if ((0 == _referenceCount) && (NULL != _instance)) {
//		delete _instance;
//		_instance = NULL;
//	}
}

ShootSpacerInstance::~ShootSpacerInstance() {
}

ShootSpacerInstance::ShootSpacerInstance() :
		ShootSpacer() {
	// creates the instance
}

} /* namespace shs */
