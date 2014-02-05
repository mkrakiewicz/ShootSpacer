/*
 * FSMState.cpp
 *
 *      Author: Micha�
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

FSMStateRenderLoop::FSMStateRenderLoop(const Spaceshooter &parent) : FSMRunnableState(), RenderLoop(parent)
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

