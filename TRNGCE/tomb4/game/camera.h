#pragma once
#include "../types.h"

namespace tomb4
{
	extern CAMERA_INFO &camera;
	extern long &LaserSight;
	extern long &BinocularRange;
	extern camera_type &BinocularOldCamera;
	extern long &BinocularOn;

	void CalculateCamera();
}

void Inject_Camera(bool replace);
