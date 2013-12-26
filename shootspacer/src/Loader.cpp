/*
 * Loader.cpp
 *
 *  Created on: 10-07-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "shootspacer/ShootSpacer.h"
#include "Loader.h"

namespace shs {

Loader::Loader(const ShootSpacer &parent): parent(parent) {
}

Loader::~Loader() {
	// TODO Auto-generated destructor stub
}

irr::scene::IMesh* Loader::getMesh(irr::core::stringw name) const {
	return meshes.at(name);
}

void Loader::addMesh(irr::core::stringw name, irr::scene::IMesh* mesh) {
	meshes[name] = mesh;
}

irr::video::ITexture* Loader::getTexture(irr::core::stringw name) const {
	return textures.at(name);
}

void Loader::addTexture(irr::core::stringw name,
		irr::video::ITexture* texture) {
	textures[name] = texture;
}

irr::video::ITexture* Loader::loadTexture(irr::core::stringw name, irr::core::stringw path) {
	addTexture(name,parent.getDriver()->getTexture(path));
	return getTexture(name);
}

bool Loader::loadMesh(irr::core::stringw name, irr::core::stringw path) {
	addMesh(name,parent.getSmgr()->getMesh(path));
	return true;
}

} /* namespace shs */
