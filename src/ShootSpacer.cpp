/*
 * ShootSpacer.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha³
 */

#include "stdafx.h"
#include "ShootSpacer.h"
#include "RenderLoop.h"

namespace shs {

ShootSpacer::ShootSpacer(IrrlichtDevice *device):
	RenderLoop(device){



	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

		    IVideoDriver* driver = device->getVideoDriver();
		    ISceneManager* smgr = device->getSceneManager();
		    IGUIEnvironment* guienv = device->getGUIEnvironment();

		    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		        rect<s32>(10,10,260,22), true);

			IAnimatedMesh* mesh = smgr->getMesh("D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.md2");

			IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );


			if (node)
			{
				node->setMaterialFlag(EMF_LIGHTING, false);
				node->setMD2Animation(scene::EMAT_STAND);
				node->setMaterialTexture( 0, driver->getTexture("D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.bmp") );
		    }

		    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

}

ShootSpacer::~ShootSpacer() {
	// TODO Auto-generated destructor stub
}

void ShootSpacer::beforeRender() {
}

void ShootSpacer::afterRender() {
}

} /* namespace shootspacer */
