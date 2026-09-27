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
	extern short &CameraDefaultSpeed;
	extern long &CameraDefaultDistance;
	extern short &ChaseCameraDefaultElevation;
	extern long &LookCameraDefaultTargetZ;
	extern long &LookCameraDefaultStartY;

	void CalculateCamera();
	void InitialiseCamera();
	void LaraTorch(PHD_VECTOR* Soffset, PHD_VECTOR* Eoffset, short yrot, long brightness);
}

void Inject_Camera(bool replace);
