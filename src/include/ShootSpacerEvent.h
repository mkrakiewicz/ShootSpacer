/*
 * EventReceiver.h
 *
 *  Created on: 19-05-2013
 *      Author: Micha�
 */

#ifndef SHOOTSPACEREVENT_H_
#define SHOOTSPACEREVENT_H_

namespace shs {

//class irr::IEventReceiver;
class ShootSpacer;

class ShootSpacerEvent: public irr::IEventReceiver
{
	private:
		// We use this array to store the current state of each key
		bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

		ShootSpacer &gameInstance;
	public:
		// This is the one method that we have to implement
		virtual bool OnEvent(const irr::SEvent& event);

		// This is used to check whether a key is being held down
		inline bool IsKeyDown(irr::EKEY_CODE keyCode) const
		{
			return KeyIsDown[keyCode];
		}

		ShootSpacerEvent(ShootSpacer &parent);

		virtual ~ShootSpacerEvent();

};

class CursorHandler
{
	public:
		CursorHandler(irr::gui::ICursorControl* control, irr::u32 screenResX,
		      irr::u32 screenResY);

		virtual ~CursorHandler()
		{
		}

		void handleInput(const irr::SEvent& event);
		virtual void handle();

		bool forceCursorStayInWindow;

	protected:
		virtual void decreaseDelta() = 0;

		// to put something like: _control->setPosition(_halfX,_halfY);
		virtual void postAction() = 0;

		irr::f32 _horizontalDelta, // value range -1(100% left) to 1 (100% right)
		      _verticalDelta,

		      // value range -1(100% top) to 1 (100% bottom)
		      // because Irrlicht's Y axis goes from top to bottom.

		      //helper variables
		      _halfX, _halfY;

		irr::u32 _screenResX, _screenResY;

		irr::gui::ICursorControl* _control;

		const irr::u32 maxDistFromCenter;
		const irr::u32 maxDistFromWindowEdge;

		irr::u32 x_min, x_max, y_min, y_max;

		bool handleWindowBounds(irr::s32& x,irr::s32&y);

		irr::f32 normalizeCoordinate(irr::u32 &min, irr::u32 &max, irr::s32 & value);
		irr::f32 checkMinMax(const irr::f32 &min,const  irr::f32 &max,const  irr::f32 &val);

};

class PlayerShip;

class PlayerShipCursorHandler: public CursorHandler
{
	public:
		PlayerShipCursorHandler(PlayerShip *shipToHandle,
		      irr::gui::ICursorControl* control, irr::u32 screenResX = 800,
		      irr::u32 screenResY = 600)
				: CursorHandler(control, screenResX, screenResY), _ship(
				      shipToHandle)
		{

		}

		virtual void handle();

		virtual ~PlayerShipCursorHandler()
		{
		}

	protected:
		PlayerShip *_ship;

};

class ShipRotatingCursorHandler: public PlayerShipCursorHandler
{
	public:
		ShipRotatingCursorHandler(PlayerShip *shipToHandle,
		      irr::gui::ICursorControl* control, irr::u32 screenResX = 800,
		      irr::u32 screenResY = 600)
				: PlayerShipCursorHandler(shipToHandle, control, screenResX,
				      screenResY)

		{
		}

		virtual void handle();

	protected:

		void setShipRotation(irr::f32 rotX, irr::f32 rotY);

		// empty - no decreasing delta
		virtual void decreaseDelta()
		{
		}

		// empty - no post action
		virtual void postAction()
		{
		}

};

} /* namespace shs */
#endif /* EVENTRECEIVER_H_ */
