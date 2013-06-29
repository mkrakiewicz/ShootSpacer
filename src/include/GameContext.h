/*
 * GameContext.h
 *
 *  Created on: 10-06-2013
 *      Author: Micha³
 */

#ifndef GAMECONTEXT_H_
#define GAMECONTEXT_H_

namespace shs {

class FSMStateRunner;

class GameContext {
public:
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *gui;

	FSMStateRunner *stateRunner;

	GameContext(irr::IrrlichtDevice * context, FSMStateRunner *stateRunner);

	virtual ~GameContext();

};

}

#endif /* GAMECONTEXT_H_ */
