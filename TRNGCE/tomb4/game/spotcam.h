#pragma once
#include "../types.h"

namespace tomb4
{
	extern short &number_spotcams;
	inline struct { SPOTCAM (*&_)[320] = *reinterpret_cast<decltype(&_)>(0x45F764); decltype(*_) operator()() { return *_; } } SpotCam;
#define SpotCam SpotCam()
	extern long &bUseSpotCam;
	extern long &bDisableLaraControl;
	extern long &bTrackCamInit;

	void CalculateSpotCams();
}

void Inject_Spotcam(bool replace);
