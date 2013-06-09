#include "stdafx.h"
#include "ShootSpacer.h"


using namespace std;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace shs;



int main(int argc, char **argv) {

//	setvbuf(stdout, NULL, _IONBF, 0);
//	setvbuf(stderr, NULL, _IONBF, 0);

	ShootSpacerInstance *s = ShootSpacerInstance::getInstance();
	s->startGame();
	ShootSpacerInstance::releaseInstance();

	return 0;
}
