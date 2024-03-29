/*
 * Loader.h
 *
 *  Created on: 10-07-2013
 *      Author: Micha�
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <map>

namespace shs {

class ShootSpacer;
/**
 * Temporary class! need to find better solution...
 * Should implement the following functionality:
 *   -load everything during level loading, or initialization. perhaps via constructor,
 *   so that it's not possible to load inside loop?
 *   -if loading same mesh twice, resolve that somehow
 *   -get loaded resources by name
 */
class Loader {
public:
	Loader(const ShootSpacer &parent);
	virtual ~Loader();

	irr::scene::IMesh* getMesh(irr::core::stringw name) const;
	void addMesh(irr::core::stringw name, irr::scene::IMesh* mesh);
	irr::video::ITexture* getTexture(irr::core::stringw name) const;
	void addTexture(irr::core::stringw name, irr::video::ITexture* texture);

	irr::video::ITexture* loadTexture(irr::core::stringw name, irr::core::stringw path);
	bool loadMesh(irr::core::stringw name, irr::core::stringw path);

protected:

	const ShootSpacer &parent;

	/**
	 * Now, I know they both derive form IReferenceCounted... but then I won't know what resource is this, basing only on type
	 */

	// textures container
	std::map<irr::core::stringw, irr::video::ITexture*> textures;

	//meshes container
	std::map<irr::core::stringw, irr::scene::IMesh*> meshes;

};

} /* namespace shs */
#endif /* LOADER_H_ */
