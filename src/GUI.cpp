/*
 * GUI.cpp
 *
 *      Author: Micha�
 */

#include "stdafx.h"
#include "GUI.h"


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

GUI::GUI() {
	// TODO Auto-generated constructor stub

}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}


void StaticDisplay::addElement(irr::core::stringw name,
		irr::gui::IGUIStaticText* element) {

	textElements[name] = element;

}

void StaticDisplay::updateElement(irr::core::stringw name,
		irr::core::stringw text) {

	std::map<irr::core::stringw, irr::gui::IGUIStaticText*>::iterator itr;

	itr = textElements.find(name);
	u32 size = textElements.size();
	if (itr != textElements.end()) {
		IGUIStaticText *tmp = 0;
		tmp = itr->second;
		if (tmp)
			tmp->setText(text.c_str());
	}
}

void ShipGUI::addTextElement(irr::core::stringw name,
		irr::gui::IGUIStaticText* elem) {
	display.addElement(name,elem);
}

void ShipGUI::updateSpeed(const irr::f32& speed) {
	display.updateElement(L"speed",stringw(L"Speed: ") + stringw(speed));
}

void ShipGUI::updateAcceleration(const irr::f32& acceleration) {
	display.updateElement(L"acceleration",stringw(L"Acceleration: ") + stringw(acceleration));

}


} /* namespace shs */
