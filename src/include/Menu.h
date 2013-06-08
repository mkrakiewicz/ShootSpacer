/*
 * Menu.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#ifndef MENU_H_
#define MENU_H_

#include "RenderLoop.h"

namespace shs {

class Menu : public RenderLoop {
protected:

	irr::video::ITexture *backgroundImg;

	void beforeRender();
	void afterRender();
	void render();

	irr::scene::ISceneManager *smgr;
//	IGUIEnvironment *gui;

public:
	Menu(GameContext * context);
	virtual ~Menu();

	void displayMenu();
};

} /* namespace shootspacer */
#endif /* MENU_H_ */
