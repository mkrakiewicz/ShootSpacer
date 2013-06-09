/*
 * FiniteStateMachine.h
 *
 *  Created on: 09-06-2013
 *      Author: Micha³
 */

#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_

#include <vector>

namespace shs {

class FiniteStateMachine {
protected:
	/**
	 * Last element is current State.
	 */
	std::vector<FSMRunnableState*> stateContainer;
public:
	FiniteStateMachine();
	virtual ~FiniteStateMachine();

	void addState(FSMRunnableState *state);
	FSMRunnableState* getCurrentState();

	bool hasNext();

};

class FSMStateRunner: public FiniteStateMachine {
protected:
	void runCurrentState();


public:
	FSMStateRunner();

	void handleEvent(const irr::SEvent& event);

	void runNext();
	void stopCurrentState();
};

} /* namespace shs */
#endif /* FINITESTATEMACHINE_H_ */
