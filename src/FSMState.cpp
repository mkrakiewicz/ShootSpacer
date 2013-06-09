/*
 * FSMState.cpp
 *
 *  Created on: 08-06-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "FSMState.h"


namespace shs {

FSMState::FSMState() {
	// TODO Auto-generated constructor stub
}

FSMState::~FSMState() {
	// TODO Auto-generated destructor stub
}

FSMStateRenderLoop::FSMStateRenderLoop() :
		FSMRunnableState(), RenderLoop() {

}

FSMStateRenderLoop::~FSMStateRenderLoop() {
}

void FSMStateRenderLoop::run() {
	beforeRun();
	RenderLoop::run();
}

FSMStateRenderLoop::FSMStateRenderLoop(irr::IrrlichtDevice* context) : FSMRunnableState(), RenderLoop(context)
{
}

void FSMStateRenderLoop::stop() {
	beforeStop();
	RenderLoop::stop();
}

FSMRunnableState::FSMRunnableState() {
}

FSMRunnableState::~FSMRunnableState() {
}

} /* namespace shs */

