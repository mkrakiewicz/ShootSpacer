/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#ifndef SHOOTSPACER_H_
#define SHOOTSPACER_H_
#include "RenderLoop.h"

namespace shs {

class RenderLoop;

class ShootSpacer : public RenderLoop {
public:
	ShootSpacer(IrrlichtDevice *device);
	virtual ~ShootSpacer();

void beforeRender();
void afterRender();
};

} /* namespace shootspacer */
#endif /* SHOOTSPACER_H_ */
/*
device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");


	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();


	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10,10,260,22), true);


	IAnimatedMesh* mesh = smgr->getMesh("D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );


	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.bmp") );
	}


	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));*/
