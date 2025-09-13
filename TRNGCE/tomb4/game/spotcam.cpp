#include "spotcam.h"

namespace tomb4
{
	short &number_spotcams = *reinterpret_cast<decltype(&number_spotcams)>(0x7F5708);
#undef SpotCam
	SPOTCAM (*&SpotCam)[320] = *reinterpret_cast<decltype(&SpotCam)>(0x45F764);
#define SpotCam (*tomb4::SpotCam)
	long &bUseSpotCam = *reinterpret_cast<decltype(&bUseSpotCam)>(0x4BF5BC);
	long &bDisableLaraControl = *reinterpret_cast<decltype(&bDisableLaraControl)>(0x4BF5C0);
}
