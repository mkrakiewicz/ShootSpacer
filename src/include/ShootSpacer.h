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

//
//template<class T>
//class Singleton
//{
//public:
//    static T &GetInstance( void )
//    {
//        static T obj;
//        return obj;
//    }
//
//    static T *GetInstancePtr( void )
//    {
//        return &(GetInstance());
//    }
//
//protected:
//    virtual ~Singleton(){};
//    Singleton(){};
//
//};

class Menu;

class ShootSpacer : public RenderLoop/*,Singleton<ShootSpacer>*/ {
protected:
	IrrlichtDevice* createIrrlichtDevice();
	Menu *menu;

	void beforeRender();
	void afterRender();


public:

	ShootSpacer();
	virtual ~ShootSpacer();

	void startGame();
};

} /* namespace shootspacer */
#endif /* SHOOTSPACER_H_ */

