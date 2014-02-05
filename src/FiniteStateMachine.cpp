/*
 * FiniteStateMachine.cpp
 *
 *      Author: Micha�
 */
#include "stdafx.h"
#include "FSMState.h"
#include "FiniteStateMachine.h"

using namespace std;

namespace shs {

FiniteStateMachine::FiniteStateMachine() {
//	stateContainer = new vector<FSMState>();
}

FiniteStateMachine::~FiniteStateMachine() {

	/**
	 * WARNING! deleting handled by the manager
	 */
	deleteAllStates();

}

void FiniteStateMachine::appendState(FSMRunnableState* state) {
	if (state != 0)
		stateStack.push_back(state);
	else {
		//empty state!
	}
}

FSMRunnableState* FiniteStateMachine::getCurrentState() {
	if (hasNext()) {
		return stateStack.back();
	} else
		return 0;
}

void FiniteStateMachine::appendStateWithName(irr::core::stringw name) {
	appendState(getState(name));
}

void FiniteStateMachine::saveStateAs(irr::core::stringw name,
		FSMRunnableState* pointer) {
	availableStates[name] = pointer;
}

FSMRunnableState* FiniteStateMachine::getState(irr::core::stringw name) {
	return availableStates[name];
}

bool FiniteStateMachine::hasNext() {
	if (stateStack.size() > 0)
		return true;
	return false;
}

void FiniteStateMachine::exit() {
	getCurrentState()->stop();
	stateStack.clear();
}

void FiniteStateMachine::deleteAllStates() {
	map<irr::core::stringw, FSMRunnableState*>::iterator itr;

	itr = availableStates.begin();

	while (itr != availableStates.end()) {
		FSMRunnableState* tmp = 0;
		tmp = itr->second;
		if (tmp != 0) {

//			availableStates.erase(itr);

			delete tmp;
		}

		itr++;

	}

}

} /* namespace shs */

shs::FSMStateRunner::FSMStateRunner() :
		FiniteStateMachine() {
}

void shs::FSMStateRunner::runCurrentState() {
	FSMRunnableState *state = getCurrentState();
	if (state) {
		state->run();
	}

}

void shs::FSMStateRunner::runNext() {
	runCurrentState();
	stateStack.pop_back();
}

void shs::FSMStateRunner::handleEvent(const irr::SEvent& event) {
	FSMRunnableState *state = getCurrentState();
	if (state) {
		state->handleEvent(event);
	}
}

shs::FSMStateRunner::~FSMStateRunner() {
}

void shs::FSMStateRunner::endCurrentState() {
	FSMRunnableState *state = getCurrentState();
	if (state) {
		state->stop();
	}
	stateStack.pop_back();
}
