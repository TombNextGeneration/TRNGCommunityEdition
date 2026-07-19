#include "camera.h"
#include "../../inject.h"

namespace tomb4
{
	CAMERA_INFO &camera = *reinterpret_cast<decltype(&camera)>(0x7FE700);
	long &LaserSight = *reinterpret_cast<decltype(&LaserSight)>(0x4BF2C8);
	long &BinocularRange = *reinterpret_cast<decltype(&BinocularRange)>(0x4BF2BC);
	camera_type &BinocularOldCamera = *reinterpret_cast<decltype(&BinocularOldCamera)>(0x4BF2C4);
	long &BinocularOn = *reinterpret_cast<decltype(&BinocularOn)>(0x4BF2C0);
	long &bLaraTorch = *reinterpret_cast<decltype(&bLaraTorch)>(0x536DE0);

	void CalculateCamera()
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseCamera()
	{
		__try { throw __func__; } __finally {}
	}

	void LaraTorch(PHD_VECTOR* Soffset, PHD_VECTOR* Eoffset, short yrot, long brightness)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Camera(bool replace)
{
	ProcessInject(0x444040, (unsigned int)tomb4::CalculateCamera, false);
	ProcessInject(0x442630, (unsigned int)tomb4::InitialiseCamera, false);
	ProcessInject(0x445040, (unsigned int)tomb4::LaraTorch, false);
}
