/*
 * EventReceiver.cpp
 *
 *  
 *      Author: Micha�
 */
#include "stdafx.h"
#include "SpaceshooterEvent.h"
#include "Spaceshooter.h"
#include "PlayerShip.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace shs {

SpaceshooterEvent::SpaceshooterEvent(Spaceshooter &parent)
		: gameInstance(parent)
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;

}

bool SpaceshooterEvent::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}

	gameInstance.handleEvent(event);

	return false;
}

SpaceshooterEvent::~SpaceshooterEvent()
{

}

void CursorHandler::handleInput(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED) {

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

void CursorHandler::handle()
{
	{
		position2di pos = _control->getPosition();

		const f32 maxDist = 200.f;

		s32 x_dist = checkMinMax(-maxDist, maxDist, pos.X - _halfX);
		s32 y_dist = checkMinMax(-maxDist, maxDist, pos.Y - _halfY);

		const f32 sensivity = 0.4f;

		_horizontalDelta += (sensivity * x_dist)/maxDist;
		_verticalDelta += (sensivity * y_dist)/maxDist;

		_horizontalDelta = checkMinMax(-1,1, _horizontalDelta);
		_verticalDelta = checkMinMax(-1,1,_verticalDelta);

		_control->setPosition(0.5f,0.5f);
	}
	decreaseDelta();
	postAction();
}

f32 CursorHandler::checkMinMax(const f32 &min,const  f32 &max,const  f32 &val) {
	f32 result = val;
	if (val < min)
		result = min;
	if (val > max)
		result = max;

	return result;

}

void PlayerShipCursorHandler::handle()
{
	CursorHandler::handle();
}

void ShipRotatingCursorHandler::handle()
{
	setShipRotation(_horizontalDelta, _verticalDelta);
	PlayerShipCursorHandler::handle();
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
	return (f32) (value - min) / (max - min);
}

} /* namespace shs */
