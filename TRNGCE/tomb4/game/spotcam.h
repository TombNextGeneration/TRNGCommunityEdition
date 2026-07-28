#pragma once
#include "../types.h"

namespace tomb4
{
	extern short &number_spotcams;
	extern SPOTCAM (&SpotCam)[320];
	extern long &bUseSpotCam;
	extern long &bDisableLaraControl;
	extern long &bTrackCamInit;
	extern short &CurrentFov;
	extern short &LastSequence;
	extern long &bCheckTrigger;
	extern PHD_VECTOR &InitialCameraPosition;
	extern PHD_VECTOR &InitialCameraTarget;
	extern short &InitialCameraRoom;
	extern short &LastFov;
	extern uchar &spotcam_screen_height;

	void CalculateSpotCams();
	long Spline(long x, long* knots, long nk);
	void SetSplineData(long num, long cam);
	void InitialiseSpotCam(short Sequence);
}

void Inject_Spotcam(bool replace);
