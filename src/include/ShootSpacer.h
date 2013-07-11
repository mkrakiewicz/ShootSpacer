/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef SHOOTSPACER_H_
#define SHOOTSPACER_H_
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "ShootSpacerEvent.h"

namespace shs {

class Menu;
class Ship;
class Planet;

/**
 * Main game class. Has protected contructors and assinment operator. Singleton functionality is implemented
 * in derived class in this file.
 */
class ShootSpacer {
public:

	/**
	 *  Start the game. All main objects are supposed to be created by this time.
	 */
	virtual void startGame();

	/**
	 * Virtual destructor so that memory is cleaned after derived class is destroyed
	 */
	virtual ~ShootSpacer();

	/**
	 * getters for device, driver,gui,smgr...
	 * @return
	 */
	const irr::IrrlichtDevice*& getDevice() const;
	const irr::video::IVideoDriver*& getDriver() const;
	const ShootSpacerEvent*& getEventReceiver() const;
	const irr::gui::IGUIEnvironment*& getGui() const;
	const Menu*& getMenu() const;
	const irr::scene::ISceneManager*& getSmgr() const;
	const shs::FSMStateRunner& getStateRunner() const;

protected:

	/**
	 * Irrlicht Engine necessary pointers.
	 */
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *gui;

	/**
	 * Function to store params and create device
	 * @return
	 */
	irr::IrrlichtDevice* createIrrlichtDevice();

	/**
	 * Creates main objects, assigns pointers
	 */
	void initialize();

/////////////////////////////////////////////////////////////////////////////////

	/**
	 * Manages and runs states.
	 */
	shs::FSMStateRunner stateRunner;

	/**
	 * Pointer to menu object
	 */
	Menu *menu;

	/**
	 * Event listener/receiver.
	 */
	ShootSpacerEvent *eventReceiver;

	void exit();

	void toggleGameState();

	void cleanup();

	/**
	 * Call this to assign reference to current frame delta for all 3D Objects.
	 */
	void enableFrameIndependentMovement();

	friend bool shs::ShootSpacerEvent::OnEvent(const irr::SEvent& event);

	void handleEvent(const irr::SEvent& event);

	/**
	 * Variable to ensure the game is not started twice.
	 */
	bool hasGameStarted;

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * Protected constructor to implement Singleton pattern.
	 */
	ShootSpacer();

	/**
	 * Protected copy constructor (singleton)
	 */
	inline ShootSpacer(const ShootSpacer& sh) {
		initialize();
	}

	/**
	 *  Protected assignment operator - singleton requirement
	 */
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}

};

class ShootSpacerInstance: protected ShootSpacer {
public:

	static ShootSpacerInstance* getInstance();
	static void releaseInstance();

	virtual ~ShootSpacerInstance();

	/**
	 *  Start the game. All main objects are supposed to be created by this time.
	 */
	virtual void startGame() {
		ShootSpacer::startGame();
	}

private:

	/**
	 * Private constructor to implement Singleton pattern.
	 */
	ShootSpacerInstance();
	static ShootSpacerInstance* _instance;
	static int _referenceCount;

	/**
	 * Private copy constructor (singleton)
	 */
	inline ShootSpacerInstance(const ShootSpacerInstance& sh) {
		// nothing here
	}

	/**
	 *  Private assignment operator - singleton requirement
	 */
	inline ShootSpacerInstance& operator=(const ShootSpacerInstance&) {
		return *this;
	}
};

} /* namespace shs */
#endif /* SHOOTSPACER_H_ */

