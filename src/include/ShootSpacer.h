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

/*
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
*/

class Menu;

class ShootSpacer: public RenderLoop/*,Singleton<ShootSpacer>*/{
private:

//	// default destructor
//	inline ~ShootSpacer() {
//	}

	// copy constructor
	inline ShootSpacer(const ShootSpacer&) {
	}

	// assignment operator
	inline ShootSpacer& operator=(const ShootSpacer&) {
		return *this;
	}

	ShootSpacer();

	static ShootSpacer* _instance;
	static int _referenceCount;

protected:
	IrrlichtDevice* createIrrlichtDevice();
	Menu *menu;

	void beforeRender();
	void afterRender();

public:

	void startGame();

	static ShootSpacer* getInstance();
	static void releaseInstance();

	virtual ~ShootSpacer();
};


} /* namespace shootspacer */
#endif /* SHOOTSPACER_H_ */

