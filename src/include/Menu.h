/*
 * Menu.h
 *
 *  
 *      Author: Micha�
 */

#ifndef MENU_H_
#define MENU_H_

#include "RenderLoop.h"
#include "FSMState.h"

namespace shs {

class Spaceshooter;

class Menu: public FSMStateRenderLoop {
public:
	Menu(const Spaceshooter &parent);
	virtual ~Menu();

	virtual void displayMenu();

	virtual void handleEvent(const irr::SEvent& event);
protected:
	enum BUTTONS {
			RESUME_GAME,
			OPTIONS,
			EXIT
	};

	void addButton(irr::core::stringw texture_name,irr::core::stringw pressed_texture_name, irr::core::vector2di startPosition, irr::s32 buttonID);


	irr::video::ITexture *backgroundImg;

	void beforeRender();
	void afterRender();
	void render();

//	IGUIEnvironment *gui;

	void beforeRun();
	void beforeStop();

	irr::core::stringw menu_test_string;

	irr::gui::IGUIFont* builtInFont;


};

class MainMenu: public Menu {
public:
	MainMenu(const Spaceshooter &parent);
	virtual ~MainMenu();

	void displayMenu();

	virtual void handleEvent(const irr::SEvent& event);

protected:
	enum BUTTONS {
		START_GAME,
		OPTIONS,
		EXIT
	};

	void afterRender();

};

} /* namespace Spaceshooter */
#endif /* MENU_H_ */
