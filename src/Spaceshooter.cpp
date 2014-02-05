#include "stdafx.h"
#include "Menu.h"
#include "Ship.h"
#include "Planet.h"
#include "Level.h"
#include "LevelManager.h"
#include "Spaceshooter.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

irr::IrrlichtDevice* Spaceshooter::getDevice() const {
	return device;
}

irr::video::IVideoDriver* Spaceshooter::getDriver() const {
	return driver;
}

SpaceshooterEvent* Spaceshooter::getEventReceiver() const {
	return eventReceiver;
}

irr::gui::IGUIEnvironment* Spaceshooter::getGui() const {
	return gui;
}

irr::scene::ISceneManager* Spaceshooter::getSmgr() const {
	return smgr;
}
FSMStateRunner& Spaceshooter::getStateRunner() const {
	return const_cast<FSMStateRunner&>(stateRunner);
}

Loader& Spaceshooter::getLoader() const {
	return const_cast<Loader&>(loader);
}

Spaceshooter::Spaceshooter():loader(*this) {

	/**
	 *  Init the game
	 */
	initialize();
}

void Spaceshooter::initialize() {

	hasGameStarted = false;

	device = this->createIrrlichtDevice();
	smgr = device->getSceneManager();
	driver = device->getVideoDriver();
	gui = device->getGUIEnvironment();

	enableFrameIndependentMovement();

	eventReceiver = new SpaceshooterEvent(*this);

	device->setEventReceiver(eventReceiver);
	device->setWindowCaption(windowTitle.c_str());

}

void Spaceshooter::toggleGameState() {

}

void Spaceshooter::exit() {
	if (stateRunner.hasNext())
		stateRunner.endCurrentState();

}

void Spaceshooter::cleanup() {

	// all objects created with "new" operator must be deleted
	delete eventReceiver;
	device->drop();

}

void Spaceshooter::enableFrameIndependentMovement() {
	Object3D::setFrameDeltaReference(RenderLoop::getFrameDeltaTimePtr());
}

void Spaceshooter::handleEvent(const irr::SEvent& event) {
	stateRunner.handleEvent(event);
}

Spaceshooter::~Spaceshooter() {
	cleanup();
}

IrrlichtDevice* Spaceshooter::createIrrlichtDevice() {

	SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
	params.AntiAlias = true;
	params.DriverType = video::EDT_OPENGL;
	params.WindowSize = core::dimension2d<u32>(1024, 768);
	params.Fullscreen = false;

	return createDeviceEx(params);
}

void Spaceshooter::startGame() {

	if (!hasGameStarted) {

		hasGameStarted = true;

		LevelManager mgr(*this);

		//TODO: implement level manager
		Level *testLevel = mgr.getCurrentLevel();

		stateRunner.saveStateAs(L"current_level", testLevel);
		stateRunner.saveStateAs(L"menu", new Menu(*this));
		stateRunner.saveStateAs(L"main_menu", new MainMenu(*this));

		stateRunner.appendStateWithName("main_menu");

		while (stateRunner.hasNext() && device->run()) {
			stateRunner.runCurrentState();
		}
	}

}

//////////////////////////////////////////////////////////////////////////////

SpaceshooterInstance* SpaceshooterInstance::_instance = NULL;
int SpaceshooterInstance::_referenceCount = 0;

SpaceshooterInstance* shs::SpaceshooterInstance::getInstance() {

	if (NULL == _instance) {
		_instance = new SpaceshooterInstance();
	}
	_referenceCount++;
	return _instance;

}

void shs::SpaceshooterInstance::releaseInstance() {
	_referenceCount--;
	if ((0 == _referenceCount) && (NULL != _instance)) {
		delete _instance;
		_instance = NULL;
	}
}

SpaceshooterInstance::~SpaceshooterInstance() {
}

SpaceshooterInstance::SpaceshooterInstance() :
		Spaceshooter() {
	// creates the instance
}

} /* namespace shs */
