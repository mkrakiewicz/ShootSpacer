/*
 * stdafx.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#ifndef STDAFX_H_
#define STDAFX_H_

#include <irrlicht.h>
#include <iostream>
#include <memory>
#include <string>

#include "shootspacer/version.h"

namespace shs {

const irr::core::stringw windowTitle = (irr::core::stringw(L"ShootSpacer ")
		+ VERSION_INFO::CURRENT_VERSION_STRING + " ");



} /* namespace ShootSpacer */
#endif /* STDAFX_H_ */
