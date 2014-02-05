#include "stdafx.h"
#include "Spaceshooter.h"

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

	SpaceshooterInstance *s = SpaceshooterInstance::getInstance();
	s->startGame();
	SpaceshooterInstance::releaseInstance();

	return 0;
}
