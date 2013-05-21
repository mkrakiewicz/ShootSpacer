/*
 * ShootSpacer.cpp
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#include "stdafx.h"
#include "ShootSpacer.h"
#include "Menu.h"
#include "Object3D.h"
#include "Planet.h"

namespace shs {

ShootSpacer* ShootSpacer::_instance = NULL;

int ShootSpacer::_referenceCount = 0;

ShootSpacer::ShootSpacer() :
		RenderLoop(createIrrlichtDevice()) {

	device->setWindowCaption(L"ShootSpacer version 0.00001 pre alpha :P");

	Object3D::setFrameDeltaReference(getFrameDeltaTimePtr());

}

ShootSpacer::~ShootSpacer() {
	delete node;
	delete testPlanet;
	device->drop();
}

void ShootSpacer::beforeRender() {
	node->rotateNodeInLocalSpace(15,vector3df(0,1,0));
	node->rotateNodeInLocalSpace(15,vector3df(1,0,0));
	node->rotateNodeInLocalSpace(15,vector3df(0,0,1));

	testPlanet->rotateNodeInLocalSpace(180,vector3df(0,1,0));




}

void ShootSpacer::afterRender() {

}

IrrlichtDevice* ShootSpacer::createIrrlichtDevice() {
	return createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);
}

void ShootSpacer::startGame() {

		IVideoDriver* driver = device->getVideoDriver();
		driver->getFPS();
		ISceneManager* smgr = device->getSceneManager();

		IGUIEnvironment* guienv = device->getGUIEnvironment();

		guienv->addStaticText(
				L"Hello World! This is the Irrlicht Software renderer!",
				rect<s32>(10, 10, 260, 22), true);

		IAnimatedMesh* mesh = smgr->getMesh(
				"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.md2");
	{
		IAnimatedMeshSceneNode * node  = smgr->addAnimatedMeshSceneNode(
				mesh);

		if (node) {
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture(0,
					driver->getTexture(
							"D:/Pliki/irrlicht-1.8/irrlicht-1.8/media/sydney.bmp"));
		}

		this->node = new Object3D(node);
	}

	GameContext gc(device);


	testPlanet = Planet::createTestPlanet(&gc);
		smgr->addCameraSceneNode(0, vector3df(0, 30, -140), vector3df(0, 5, 0));

	run();
}

ShootSpacer* shs::ShootSpacer::getInstance() {

	if (NULL == _instance) {
		_instance = new ShootSpacer();
	}
	_referenceCount++;
	return _instance;

}

void shs::ShootSpacer::releaseInstance() {
	_referenceCount--;
	if ((0 == _referenceCount) && (NULL != _instance)) {
		delete _instance;
		_instance = NULL;
	}
}

} /* namespace shootspacer */
