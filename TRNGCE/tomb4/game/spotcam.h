#pragma once
#include "types.h"

namespace tomb4
{
	extern short &number_spotcams;
	extern SPOTCAM (*&SpotCam)[320];
#define SpotCam (*SpotCam)
}
