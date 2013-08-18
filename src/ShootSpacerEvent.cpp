/*
 * EventReceiver.cpp
 *
 *  Created on: 19-05-2013
 *      Author: Micha�
 */
#include "stdafx.h"
#include "ShootSpacerEvent.h"
#include "ShootSpacer.h"
#include "PlayerShip.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

ShootSpacerEvent::ShootSpacerEvent(ShootSpacer &parent)
		: gameInstance(parent)
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;

}

bool ShootSpacerEvent::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}

	gameInstance.handleEvent(event);

	return false;
}

ShootSpacerEvent::~ShootSpacerEvent()
{

}

void CursorHandler::handleInput(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED) {

			s32 x = event.MouseInput.X;
			s32 y = event.MouseInput.Y;

			/*if (!allowLeaveWindow) {
				bool boundsCrossed = false;

				const s32 border = 20;

				if (x < border) {
					x = border;
					boundsCrossed = true;
				} else if (x >= (_screenResX - border)) {
					x = _screenResX - border;
					boundsCrossed = true;
				}

				if (y < border) {
					boundsCrossed = true;
					y = border;
				} else if (y >= (_screenResY - border)) {
					y = _screenResY - border;
					boundsCrossed = true;
				}

				if (boundsCrossed) {
					_control->setPosition(vector2di(x,y));
				}

			}*/

			_horizontalDelta = (-1.f) + ((float)x / _screenResX) * 2.f;

			_verticalDelta = (-1.f) + ((float)y / _screenResY) * 2.f;

		//	_control->setPosition(0.5f,0.5f);
		}

	}
}

void CursorHandler::update()
{
	decreaseDelta();
	postAction();
}

void PlayerShipCursorHandler::update()
{
	CursorHandler::update();
}

void ShipRotatingCursorHandler::update()
{
	setShipRotation(_horizontalDelta, _verticalDelta);
	PlayerShipCursorHandler::update();
}

void ShipRotatingCursorHandler::setShipRotation(irr::f32 rotX, irr::f32 rotY)
{
	_ship->rotate(_verticalDelta, vector3df(1, 0, 0));
	_ship->rotate(_horizontalDelta, vector3df(0, 1, 0));
}

} /* namespace shs */
