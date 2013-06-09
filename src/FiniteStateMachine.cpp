/*
 * FiniteStateMachine.cpp
 *
 *  Created on: 09-06-2013
 *      Author: Micha³
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

//	delete stateContainer;
}

void FiniteStateMachine::addState(FSMRunnableState* state) {
	if (state != 0)
		stateContainer.push_back(state);
	else {
		//empty state!
	}
}

FSMRunnableState* FiniteStateMachine::getCurrentState() {
	if (hasNext()) {
		return stateContainer.back();
	} else
		return 0;
}

bool shs::FiniteStateMachine::hasNext() {
	if (stateContainer.size() > 0)
		return true;
	return false;
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
	stateContainer.pop_back();
}

void shs::FSMStateRunner::handleEvent(const irr::SEvent& event) {
	FSMRunnableState *state = getCurrentState();
		if (state) {
			state->handleEvent(event);
		}
}

void shs::FSMStateRunner::stopCurrentState() {
	FSMRunnableState *state = getCurrentState();
	if (state) {
		state->stop();
	}
}
