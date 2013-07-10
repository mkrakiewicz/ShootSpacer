/*
 * Loader.cpp
 *
 *  Created on: 10-07-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "GameContext.h"
#include "Loader.h"

namespace shs {

Loader::Loader(const GameContext& _context): context(_context) {
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

bool Loader::loadTexture(irr::core::stringw name, irr::core::stringw path) {
	addTexture(name,context.driver->getTexture(path));
	return true;
}

bool Loader::loadMesh(irr::core::stringw name, irr::core::stringw path) {
	addMesh(name,context.smgr->getMesh(path));
}

} /* namespace shs */
