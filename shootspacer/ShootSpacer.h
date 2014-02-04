/*
 * ShootSpacer.h
 *
 *  Created on: 18-05-2013
 *      Author: Micha�
 */

#ifndef SHOOTSPACER_H_
#define SHOOTSPACER_H_
#include "FSMState.h"
#include "FiniteStateMachine.h"
#include "ShootSpacerEvent.h"
#include "Loader.h"
#include <boost/scoped_ptr.hpp>


using namespace shs;
namespace shs {

class ShootSpacer {
	friend class ShootSpacerInstance;
public:

	virtual ~ShootSpacer() {}

protected:
	ShootSpacer(){}

};

class ShootSpacerInstance {
public:
	static ShootSpacerInstance* getInstance();
	static void stop();
	static void releaseInstance();

	virtual ~ShootSpacerInstance();

private:
    static boost::scoped_ptr<ShootSpacerInstance> _instance((ShootSpacerInstance*)0);
    //	static ShootSpacerInstance* _instance;
	static int _referenceCount;


	ShootSpacerInstance();
	inline ShootSpacerInstance(const ShootSpacerInstance& sh) {}
	inline ShootSpacerInstance& operator=(const ShootSpacerInstance&) {		return *this;	}
};

} /* namespace shs */
#endif /* SHOOTSPACER_H_ */

