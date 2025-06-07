#include "types.h"

namespace tomb4
{
	short &number_spotcams = *reinterpret_cast<decltype(&number_spotcams)>(0x7F5708);
	SPOTCAM (*&SpotCam)[320] = *reinterpret_cast<decltype(&SpotCam)>(0x45F764);
#define SpotCam (*SpotCam)
}
