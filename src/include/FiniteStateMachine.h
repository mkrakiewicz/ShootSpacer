/*
 * FiniteStateMachine.h
 *
 *  Created on: 09-06-2013
 *      Author: Micha�
 */

#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_

#include <vector>
#include <map>

namespace shs {

class FSMRunnableState;

class FiniteStateMachine {
public:
	FiniteStateMachine();
	virtual ~FiniteStateMachine();

	void appendState(FSMRunnableState *state);
	void appendStateWithName(irr::core::stringw name);

	void saveStateAs(irr::core::stringw name, FSMRunnableState *pointer);

	FSMRunnableState* getState(irr::core::stringw name);

	FSMRunnableState* getCurrentState();

	bool hasNext();

	void exit();
protected:

	/**
	 * Hashmap of available states...
	 */
	std::map<irr::core::stringw, FSMRunnableState*> availableStates;
	/**
	 * Last element is current State.
	 */
	std::vector<FSMRunnableState*> stateStack;

	void deleteAllStates();

};

class FSMStateRunner: public FiniteStateMachine {
protected:
	void runNext();

public:
	FSMStateRunner();
	virtual ~FSMStateRunner();

	void handleEvent(const irr::SEvent& event);
	void runCurrentState();

	void endCurrentState();
};

} /* namespace shs */
#endif /* FINITESTATEMACHINE_H_ */
