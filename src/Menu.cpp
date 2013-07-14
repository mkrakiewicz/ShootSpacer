/*
 * Menu.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */
#include "stdafx.h"
#include "ShootSpacer.h"
#include "Menu.h"
#include "FiniteStateMachine.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

Menu::Menu(const ShootSpacer &parent) :
		FSMStateRenderLoop(parent) {

	/**
	 * swap original scene manager with menu smgr
	 * */
	ISceneManager * tmp = smgr->createNewSceneManager();
	smgr = tmp;

//	gui = context->device->getGUIEnvironment();
	backgroundImg = driver->getTexture("img/space.jpg");

	builtInFont = device->getGUIEnvironment()->getBuiltInFont();

	menu_test_string = L"MENU: ShootSpacer ";
	menu_test_string += VERSION_INFO::CURRENT_VERSION_STRING;
	menu_test_string += "\nmenu to be implemented...";
}

void Menu::beforeRender() {

}

void Menu::afterRender() {
	if (builtInFont) {

		builtInFont->draw(menu_test_string, core::rect<s32>(10, 10, 400, 400),
				video::SColor(255, 255, 255, 255));

		builtInFont->draw(L"SPACESHOOTER", core::rect<s32>(10, 400, 700, 722),
				video::SColor(255, 255, 255, 255));
	}
}

Menu::~Menu() {
	smgr->drop();

}

void Menu::render() {
	driver->draw2DImage(backgroundImg, vector2d<int>(0, 0));
	smgr->drawAll();
	gui->drawAll();
}

void Menu::displayMenu() {

	gui->clear();

//	gui->addStaticText(L"SPACESHOOTER", rect<s32>(400, 400, 700, 722), true);

}

void Menu::beforeRun() {
	displayMenu();
}

void Menu::beforeStop() {
}


void Menu::handleEvent(const irr::SEvent& event) {
	//TODO: handel events. need to pass state manager with game context??
	//coz how else to set next state from here.

	//    // Remember whether each key is down or up
	//    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
	//        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	//
	if (!event.KeyInput.PressedDown) {
		if (event.KeyInput.Key == KEY_ESCAPE) {

			//	context.stateRunner->appendStateWithName(L"test_level");
			parent.getStateRunner().endCurrentState();

		} else if (event.KeyInput.Key == KEY_KEY_Q) {
			parent.getStateRunner().exit();
		}
	}
}

MainMenu::MainMenu(const ShootSpacer &parent) :
		Menu(parent) {

	menu_test_string = L"MAIN MENU: ShootSpacer ";
	menu_test_string += VERSION_INFO::CURRENT_VERSION_STRING;
	menu_test_string += "\nmenu to be implemented...";
}

MainMenu::~MainMenu() {
}

void MainMenu::displayMenu() {
	gui->clear();

	//	gui->addStaticText(L"SPACESHOOTER", rect<s32>(400, 400, 700, 722), true);

}

void MainMenu::afterRender() {
	if (builtInFont) {
		builtInFont->draw(menu_test_string, core::rect<s32>(10, 10, 400, 400),
				video::SColor(255, 255, 255, 255));

		builtInFont->draw(L"SPACESHOOTER MAIN MENU",
				core::rect<s32>(10, 400, 700, 822),
				video::SColor(255, 255, 255, 255));
	}

}

void MainMenu::handleEvent(const irr::SEvent& event) {
	if (!event.KeyInput.PressedDown) {

		switch (event.KeyInput.Key) {
		case KEY_ESCAPE:
		case KEY_KEY_Q:
			parent.getStateRunner().exit();
			break;
		case KEY_RETURN:
			parent.getStateRunner().appendStateWithName(L"current_level");
			this->stop();
			break;
		default:
			break;
		}

	}
}

} /* namespace shs */
