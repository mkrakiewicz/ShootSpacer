/*
 * FSMState.h
 *
 *  Created on: 08-06-2013
 *      Author: Micha³
 */

#ifndef FSMSTATE_H_
#define FSMSTATE_H_

#include "RenderLoop.h"

namespace shs {

class FSMState {
protected:


public:
	FSMState();
	virtual ~FSMState();


};

class FSMRunnableState {
public:
	FSMRunnableState();
	virtual ~FSMRunnableState();

	virtual void handleEvent(const irr::SEvent& event) = 0;

	virtual void run() = 0;

	virtual void stop() = 0;

};

class FSMStateRenderLoop : public FSMRunnableState, protected RenderLoop{
protected:
	virtual void beforeRun() = 0;
	virtual void beforeStop() = 0;
public:
//	FSMStateRenderLoop();
	FSMStateRenderLoop(const GameContext &context);
	virtual ~FSMStateRenderLoop();

	void run();
	void stop();


};

} /* namespace shs */
#endif /* FSMSTATE_H_ */
