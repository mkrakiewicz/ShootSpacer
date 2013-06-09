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
//
//void FSMState::begin() {
//	beforeBegin();
//	run();
//}
//
//void FSMState::end() {
//	beforeEnd();
//	stop();
//}

} /* namespace shs */

shs::FSMStateRenderLoop::FSMStateRenderLoop() :
		FSMState(), RenderLoop() {

}

shs::FSMStateRenderLoop::~FSMStateRenderLoop() {
}

void shs::FSMStateRenderLoop::run() {
	beforeRun();
	RenderLoop::run();
}

shs::FSMStateRenderLoop::FSMStateRenderLoop(irr::IrrlichtDevice* context) : FSMState(), RenderLoop(context)
{
}

void shs::FSMStateRenderLoop::stop() {
	beforeStop();
	RenderLoop::stop();
}
