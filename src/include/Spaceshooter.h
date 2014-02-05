/*
 * Spaceshooter.h
 *
 *  
 *      Author: Micha�
 */

#ifndef Spaceshooter_H_
#define Spaceshooter_H_
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "SpaceshooterEvent.h"
#include "Loader.h"

namespace shs {

class Menu;
class Planet;
/**
 * Main game class. Has protected contructors and assinment operator. Singleton functionality is implemented
 * in derived class in this file.
 */
class Spaceshooter {
public:

	/**
	 *  Start the game. All main objects are supposed to be created by this time.
	 */
	void startGame();

	/**
	 * Virtual destructor so that memory is cleaned after derived class is destroyed
	 */
	virtual ~Spaceshooter();

	/**
	 * getters for device, driver,gui,smgr...
	 * @return
	 */
	irr::IrrlichtDevice* getDevice() const;
	irr::video::IVideoDriver* getDriver() const;
	SpaceshooterEvent* getEventReceiver() const;
	irr::gui::IGUIEnvironment* getGui() const;
	irr::scene::ISceneManager* getSmgr() const;
	FSMStateRunner& getStateRunner() const;

	Loader& getLoader() const;
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

	Loader loader;

	/**
	 * Manages and runs states.
	 */
	FSMStateRunner stateRunner;
	/**
	 * Event listener/receiver.
	 */
	SpaceshooterEvent *eventReceiver;

	void exit();

	void toggleGameState();

	void cleanup();

	/**
	 * Call this to assign reference to current frame delta for all 3D Objects.
	 */
	void enableFrameIndependentMovement();

	friend bool shs::SpaceshooterEvent::OnEvent(const irr::SEvent& event);

	void handleEvent(const irr::SEvent& event);

	/**
	 * Variable to ensure the game is not started twice.
	 */
	bool hasGameStarted;

	//////////////////////////////////////////////////////////////////////////////

	/**
	 * Protected constructor to implement Singleton pattern.
	 */
	Spaceshooter();

	/**
	 * Protected copy constructor (singleton)
	 */
	inline Spaceshooter(const Spaceshooter& sh):loader(*this) {
		initialize();
	}

	/**
	 *  Protected assignment operator - singleton requirement
	 */
	inline Spaceshooter& operator=(const Spaceshooter&) {
		return *this;
	}

};

class SpaceshooterInstance: protected Spaceshooter {
public:

	static SpaceshooterInstance* getInstance();
	static void releaseInstance();

	virtual ~SpaceshooterInstance();

	/**
	 *  Start the game. All main objects are supposed to be created by this time.
	 */
	virtual void startGame() {
		Spaceshooter::startGame();
	}

private:

	/**
	 * Private constructor to implement Singleton pattern.
	 */
	SpaceshooterInstance();
	static SpaceshooterInstance* _instance;
	static int _referenceCount;

	/**
	 * Private copy constructor (singleton)
	 */
	inline SpaceshooterInstance(const SpaceshooterInstance& sh) {
		// nothing here
	}

	/**
	 *  Private assignment operator - singleton requirement
	 */
	inline SpaceshooterInstance& operator=(const SpaceshooterInstance&) {
		return *this;
	}
};

} /* namespace shs */
#endif /* Spaceshooter_H_ */

