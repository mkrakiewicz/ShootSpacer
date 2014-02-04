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


/**
 * Main function. This file should not be changed. Here is created game instance.
 * @param argc
 * @param argv
 * @return 0
 */
int main(int argc, char **argv) {

	ShootSpacerInstance *s = ShootSpacerInstance::getInstance();
//	s->startGame();/
	ShootSpacerInstance::releaseInstance();

	return 0;
}
