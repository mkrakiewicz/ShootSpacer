/*
 * Menu.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef MENU_H_
#define MENU_H_

#include "RenderLoop.h"
#include "FSMState.h"

namespace shs {

class Menu : public RenderLoop, public FSMState {
protected:

	irr::video::ITexture *backgroundImg;

	void beforeRender();
	void afterRender();
	void render();

	irr::scene::ISceneManager *smgr;
//	IGUIEnvironment *gui;

	void beforeBegin();
	void beforeEnd();

public:
	Menu(GameContext * context);
	virtual ~Menu();

	void displayMenu();

	void begin();
	void end();


};

} /* namespace shootspacer */
#endif /* MENU_H_ */
