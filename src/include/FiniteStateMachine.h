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
private:
	std::vector<FSMState> stateContainer;
public:
	FiniteStateMachine();
	virtual ~FiniteStateMachine();
};

} /* namespace shs */
#endif /* FINITESTATEMACHINE_H_ */
