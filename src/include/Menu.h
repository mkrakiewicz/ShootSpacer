/*
 * Menu.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef MENU_H_
#define MENU_H_

#include "RenderLoop.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

class Menu : public RenderLoop {
protected:

	void beforeRender();
	void afterRender();
	void render();

	ISceneManager *smgr;
	IGUIEnvironment *gui;

public:
	Menu(GameContext * context);
	virtual ~Menu();

	void displayMenu();
};

} /* namespace shootspacer */
#endif /* MENU_H_ */
