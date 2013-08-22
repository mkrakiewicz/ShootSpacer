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

			_horizontalDelta = 0;
			_verticalDelta = 0;

			if (forceCursorStayInWindow) {

				handleWindowBounds(x, y);

			}

			if (x < x_min) {
				x = x_min;
			} else if (x > x_max) {
				x = x_max;
			}

			if (y < y_min) {
				y = y_min;
			} else if (y > y_max) {
				y = y_max;
			}

			s32 x_dist = x - _halfX;
			s32 y_dist = y - _halfY;

			_horizontalDelta = -1.f + normalizeCoordinate(x_min, x_max, x) * 2.f;
			_verticalDelta = -1.f + normalizeCoordinate(y_min, y_max, y) * 2.f;
		}

	}
}

CursorHandler::CursorHandler(irr::gui::ICursorControl* control,
      irr::u32 screenResX, irr::u32 screenResY)
		: _horizontalDelta(0.f), _verticalDelta(0.f), _screenResX(screenResX), _screenResY(
		      screenResY), _control(control), maxDistFromCenter(200), maxDistFromWindowEdge(
		      40)
{

	_halfX = _screenResX / 2.f;
	_halfY = _screenResY / 2.f;

	//reset cursor position to middle
	_control->setPosition(_halfX, _halfY);

	forceCursorStayInWindow = true;

	x_min = _halfX - maxDistFromCenter;
	x_max = _halfX + maxDistFromCenter;

	y_min = _halfY - maxDistFromCenter;
	y_max = _halfY + maxDistFromCenter;

}

void CursorHandler::update()
{
	{

		//	_control->setPosition(0.5f,0.5f);
	}
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

bool CursorHandler::handleWindowBounds(irr::s32& x, irr::s32&y)
{
	bool mousePositionChanged = false;
	s32 nx, ny;
	nx = x;
	ny = y;
	if (x < maxDistFromWindowEdge) {
		mousePositionChanged = true;
		nx = x_min;
	} else if (x >= (_screenResX - maxDistFromWindowEdge)) {
		mousePositionChanged = true;
		nx = x_max;
	}

	if (y < maxDistFromWindowEdge) {
		mousePositionChanged = true;
		ny = y_min;
	} else if (y >= (_screenResY - maxDistFromWindowEdge)) {
		mousePositionChanged = true;
		ny = y_max;
	}

	if (mousePositionChanged) {
		_control->setPosition(nx, ny);
	}

	return mousePositionChanged;
}

irr::f32 CursorHandler::normalizeCoordinate(irr::u32& min, irr::u32& max,
      irr::s32& value)
{
	return (f32)(value - min) / (max - min);
}

} /* namespace shs */
