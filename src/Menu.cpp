/*
 * Menu.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "Menu.h"

namespace shs {

Menu::Menu(GameContext * context):
	RenderLoop(context->device) {


	/*
	 * swap original scene manager with menu smgr
	 * */

	smgr = context->smgr->createNewSceneManager();
	gui = context->device->getGUIEnvironment();
}

void Menu::beforeRender() {
}

void Menu::afterRender() {
}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

void Menu::render() {

	smgr->drawAll();
	gui->drawAll();
}

void Menu::displayMenu() {
	gui->addStaticText(
					L"Hello World! This is the Irrlicht Software renderer!",
					rect<s32>(10, 10, 260, 22), true);
	run();

}

} /* namespace shootspacer */
