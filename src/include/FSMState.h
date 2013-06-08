/*
 * FSMState.h
 *
 *  Created on: 08-06-2013
 *      Author: Micha³
 */

#ifndef FSMSTATE_H_
#define FSMSTATE_H_

namespace shs {

class FSMState {
protected:
	virtual void beforeBegin() = 0;
	virtual void beforeEnd() = 0;

public:
	FSMState();
	virtual ~FSMState();

	virtual void begin() = 0;

	virtual void end() = 0;

};

} /* namespace shs */
#endif /* FSMSTATE_H_ */
