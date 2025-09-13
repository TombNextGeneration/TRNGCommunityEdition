#include "camera.h"

namespace tomb4
{
	CAMERA_INFO &camera = *reinterpret_cast<decltype(&camera)>(0x7FE700);
	long &LaserSight = *reinterpret_cast<decltype(&LaserSight)>(0x4BF2C8);
	long &BinocularRange = *reinterpret_cast<decltype(&BinocularRange)>(0x4BF2BC);
}
