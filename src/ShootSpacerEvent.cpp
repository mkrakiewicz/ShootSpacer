/*
 * EventReceiver.cpp
 *
 *  Created on: 19-05-2013
 *      Author: Micha³
 */
#include "stdafx.h"
#include "ShootSpacerEvent.h"
#include "ShootSpacer.h"



using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


namespace shs {

ShootSpacerEvent::ShootSpacerEvent(ShootSpacer *gameInstance)
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
    this->gameInstance = gameInstance;
}

bool ShootSpacerEvent::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
//
//	if (!event.KeyInput.PressedDown) {
//		if (event.KeyInput.Key == KEY_ESCAPE) {
//
//			gameInstance->toggleGameState();
//			return false;
//		} else if (event.KeyInput.Key == KEY_KEY_Q) {
//			gameInstance->exit();
//		}
//	}
	gameInstance->handleEvent(event);


    }

    return false;
}

ShootSpacerEvent::~ShootSpacerEvent() {

}

} /* namespace shs */
