/*
 * Menu.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */
#include "stdafx.h"
#include "Menu.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


namespace shs {

Menu::Menu(GameContext * context):
	FSMStateRenderLoop(context->device){

	/**
	 * swap original scene manager with menu smgr
	 * */
	smgr = context->smgr->createNewSceneManager();
//	gui = context->device->getGUIEnvironment();
	backgroundImg = driver->getTexture("img/space.jpg");
}

void Menu::beforeRender() {
}

void Menu::afterRender() {
}

Menu::~Menu() {

}

void Menu::render() {
	driver->draw2DImage(backgroundImg,vector2d<int>(0,0));
	smgr->drawAll();
	gui->drawAll();
}



void Menu::displayMenu() {

	gui->clear();
	 core::stringw tmp = L"MENU: ShootSpacer ";
	tmp += VERSION_INFO::CURRENT_VERSION_STRING;
	tmp += "\nmenu to be implemented...";
	gui->addStaticText(
					tmp.c_str(),
					rect<s32>(10, 10, 260, 52), true)->setOverrideColor(SColor(255,255,255,255));

	gui->addStaticText(L"SPACESHOOTER",
						rect<s32>(400, 400, 700, 722), true);

	run();

}

void Menu::beforeRun() {
}

void Menu::beforeStop() {
}

} /* namespace shootspacer */
