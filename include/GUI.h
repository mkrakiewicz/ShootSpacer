/*
 * GUI.h
 *
 *  Created on: 07-07-2013
 *      Author: Micha�
 */

#ifndef GUI_H_
#define GUI_H_

#include <map>

namespace shs {

/**
 * Base class of a "console". Basic functionality:
 *  - add static text as hashmap -> name, created obj
 *  - display and align text automatically:
 *    + in static console(StaticDisplay), added text would be just aligned on a screen properly and displayed
 *    + in dynamic, the text would flow like in a real console
 */

class Console {

};

class StaticDisplay: public Console {
public:
	StaticDisplay(){};
	void addElement(irr::core::stringw name, irr::gui::IGUIStaticText *element);
	void updateElement(irr::core::stringw name, irr::core::stringw text);
	std::map<irr::core::stringw, irr::gui::IGUIStaticText*> textElements;

protected:


};

/**
 * Abstract base class for polymorphism
 * To be implemented
 */
class GUI {
protected:

	/**
	 * Hashmap of storede elements
	 */
	std::map<irr::core::stringw, irr::gui::IGUIElement*> guiElements;

	/**
	 *
	 */
	irr::u32 lineHeight;

public:
	//virtual void handleEvent(const irr::SEvent& event) = 0;

	GUI();
	virtual ~GUI();
};

class LevelGUI: public GUI {

};

class ShipGUI: public GUI {
public:
	ShipGUI():GUI(){}
	ShipGUI(StaticDisplay &displayWithSpeedAndAcceleration) :
			GUI(), display(displayWithSpeedAndAcceleration) {

	}

	virtual ~ShipGUI() {
	}

	void addTextElement(irr::core::stringw name,
			irr::gui::IGUIStaticText *elem);

	void updateSpeed(const irr::f32 &speed);
	void updateAcceleration(const irr::f32 &acceleration);
	StaticDisplay display;

protected:


};

/**
 *
 */
//class FighterShipGUI: public GUI {
//
//};
} /* namespace shs */
#endif /* GUI_H_ */
