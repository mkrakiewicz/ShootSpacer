/*
 * Menu.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Menu.h"

namespace shs {

Menu::Menu(IrrlichtDevice * context):
	RenderLoop(context) {


	/*
	 * swap original scene manager with menu smgr
	 * */
	ISceneManager *menuSmgr;
	menuSmgr = smgr->createNewSceneManager();
	smgr = menuSmgr;
}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

} /* namespace shootspacer */
