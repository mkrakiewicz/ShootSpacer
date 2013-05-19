#include "stdafx.h"
#include "ShootSpacer.h"
#include <memory>


using namespace std;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace shs;

int main(int argc, char **argv)
{
	std::cout << "Hello";

	IrrlichtDevice *device =
	        createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
	            false, false, false, 0);

	    if (!device)
	        return 1;


	    ShootSpacer s(device);

	    s.run();

	    device->drop();



	return 0;
}
