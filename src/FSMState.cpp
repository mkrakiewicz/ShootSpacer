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

}

FSMState::~FSMState() {

}

//FSMStateRenderLoop::FSMStateRenderLoop() :
//		FSMRunnableState(), RenderLoop() {
//
//}

FSMStateRenderLoop::~FSMStateRenderLoop() {
}

void FSMStateRenderLoop::run() {
	beforeRun();
	RenderLoop::run();
}

FSMStateRenderLoop::FSMStateRenderLoop(const GameContext &context) : FSMRunnableState(), RenderLoop(context)
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

