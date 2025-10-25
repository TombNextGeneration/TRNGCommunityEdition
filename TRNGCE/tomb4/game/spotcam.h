#pragma once
#include "../types.h"

namespace tomb4
{
	extern short &number_spotcams;
	extern SPOTCAM (*&SpotCam)[320];
#define SpotCam (*tomb4::SpotCam)
	extern long &bUseSpotCam;
	extern long &bDisableLaraControl;
	extern long &bTrackCamInit;

	void CalculateSpotCams();
}

void Inject_Spotcam(bool replace);
