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

	parent.getLoader().loadTexture("resume_button", "img/b_resume.png");
	parent.getLoader().loadTexture("resume_button_pressed",
			"img/b_resume_pressed.png");
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

	addButton("resume_button", "resume_button_pressed", vector2di(50, 50), RESUME_GAME);
	addButton("options_button", "options_button_pressed", vector2di(50, 150),
			OPTIONS);
	addButton("exit_button", "exit_button_pressed", vector2di(50, 250), EXIT);
//	gui->addStaticText(L"SPACESHOOTER", rect<s32>(400, 400, 700, 722), true);

}

void Menu::beforeRun() {
	displayMenu();
}

void Menu::beforeStop() {
	gui->clear();
}

void Menu::handleEvent(const irr::SEvent& event) {

	if (event.EventType == EET_KEY_INPUT_EVENT) {
			if (!event.KeyInput.PressedDown) {

				switch (event.KeyInput.Key) {
				case KEY_ESCAPE:
					parent.getStateRunner().endCurrentState();
					break;
				case KEY_KEY_Q:
					parent.getStateRunner().exit();
					break;
				default:
					break;
				}

			}
		} else if (event.EventType == EET_GUI_EVENT) {
			if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
				switch (event.GUIEvent.Caller->getID()) {
				case RESUME_GAME:
					parent.getStateRunner().endCurrentState();
					break;
				case OPTIONS:
					break;
				case EXIT:
					parent.getStateRunner().endCurrentState();
					//UGLY HACK: TODO: improve;
					parent.getStateRunner().endCurrentState();
					break;
				default:
					break;

				}
			}
		}
}

void Menu::addButton(stringw texture_name, stringw pressed_texture_name,
		vector2di startPosition, s32 buttonID) {
	ITexture *buttonTexture = parent.getLoader().getTexture(texture_name);

	u32 btn_x = startPosition.X, btn_y = startPosition.Y;

	dimension2du btnDimension = buttonTexture->getSize();

	recti btnAlignment(btn_x, btn_y, btn_x + btnDimension.Width,
			btn_y + btnDimension.Height);
	IGUIButton *startButton = gui->addButton(btnAlignment, 0, buttonID);
	//	startButton->setIsPushButton(true);
	startButton->setImage(buttonTexture);
	startButton->setPressedImage(
			parent.getLoader().getTexture(pressed_texture_name));
	startButton->setUseAlphaChannel(true);
	startButton->setDrawBorder(false);
}

//////////////////////////////////////////////////////////////////////////////////////
MainMenu::MainMenu(const ShootSpacer &parent) :
		Menu(parent) {

	menu_test_string = L"MAIN MENU: ShootSpacer ";
	menu_test_string += VERSION_INFO::CURRENT_VERSION_STRING;
	menu_test_string += "\nmenu to be implemented...";
	this->parent.getLoader().loadTexture("start_button", "img/b_start.png");
	this->parent.getLoader().loadTexture("start_button_pressed",
			"img/b_start_pressed.png");

	this->parent.getLoader().loadTexture("options_button", "img/b_options.png");
	this->parent.getLoader().loadTexture("options_button_pressed",
			"img/b_options_pressed.png");

	this->parent.getLoader().loadTexture("exit_button", "img/b_exit.png");
	this->parent.getLoader().loadTexture("exit_button_pressed",
			"img/b_exit_pressed.png");

}

MainMenu::~MainMenu() {
}

void MainMenu::displayMenu() {
	gui->clear();

	addButton("start_button", "start_button_pressed", vector2di(50, 50),
			START_GAME);
	addButton("options_button", "options_button_pressed", vector2di(50, 150),
			OPTIONS);
	addButton("exit_button", "exit_button_pressed", vector2di(50, 250), EXIT);

//	startButton->set

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
	if (event.EventType == EET_KEY_INPUT_EVENT) {
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
	} else if (event.EventType == EET_GUI_EVENT) {
		if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
			switch (event.GUIEvent.Caller->getID()) {
			case START_GAME:
				parent.getStateRunner().appendStateWithName(L"current_level");
				this->stop();
				break;
			case OPTIONS:
				break;
			case EXIT:
				parent.getStateRunner().exit();
				break;
			default:
				break;

			}
		}
	}
}

} /* namespace shs */
