#pragma once
#include "../types.h"

namespace tomb4
{
	extern CAMERA_INFO &camera;
	extern long &LaserSight;
	extern long &BinocularRange;
	extern camera_type &BinocularOldCamera;
	extern long &BinocularOn;
	extern long &bLaraTorch;

	void CalculateCamera();
	void InitialiseCamera();
	void LaraTorch(PHD_VECTOR* Soffset, PHD_VECTOR* Eoffset, short yrot, long brightness);
}

void Inject_Camera(bool replace);
