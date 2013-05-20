/*
 * EventReceiver.h
 *
 *  Created on: 19-05-2013
 *      Author: Micha³
 */

#ifndef EVENTRECEIVER_H_
#define EVENTRECEIVER_H_

#include <IEventReceiver.h>

namespace ShootSpacer {

class EventReceiver: public irr::IEventReceiver {
public:
	EventReceiver();
	virtual ~EventReceiver();
};

} /* namespace ShootSpacer */
#endif /* EVENTRECEIVER_H_ */
