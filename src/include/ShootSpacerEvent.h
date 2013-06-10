/*
 * EventReceiver.h
 *
 *  Created on: 19-05-2013
 *      Author: Micha³
 */

#ifndef SHOOTSPACEREVENT_H_
#define SHOOTSPACEREVENT_H_

namespace shs {

//class irr::IEventReceiver;
class ShootSpacer;

class ShootSpacerEvent: public irr::IEventReceiver {
private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

	ShootSpacer *gameInstance;
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event);

	// This is used to check whether a key is being held down
	inline bool IsKeyDown(irr::EKEY_CODE keyCode) const {
		return KeyIsDown[keyCode];
	}

	ShootSpacerEvent(ShootSpacer *gameInstance);

	virtual ~ShootSpacerEvent();

};

} /* namespace shs */
#endif /* EVENTRECEIVER_H_ */
