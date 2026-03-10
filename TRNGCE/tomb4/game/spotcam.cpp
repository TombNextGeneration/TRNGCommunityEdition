#include "spotcam.h"
#include "../../inject.h"

namespace tomb4
{
	short &number_spotcams = *reinterpret_cast<decltype(&number_spotcams)>(0x7F5708);
	SPOTCAM (&SpotCam)[320] = *reinterpret_cast<decltype(&SpotCam)>(0x45F764);
	long &bUseSpotCam = *reinterpret_cast<decltype(&bUseSpotCam)>(0x4BF5BC);
	long &bDisableLaraControl = *reinterpret_cast<decltype(&bDisableLaraControl)>(0x4BF5C0);
	long &bTrackCamInit = *reinterpret_cast<decltype(&bTrackCamInit)>(0x4BF5B4);

	void CalculateSpotCams()
	{
		__try { throw __func__; } __finally {}
	}
}

__declspec(naked) static void** Inject_Spotcam_SpotCam() { __asm lea eax, [tomb4::SpotCam] __asm ret }

void Inject_Spotcam(bool replace)
{
	IndirectReferenceInject(Inject_Spotcam_SpotCam());

	ProcessInject(0x45FE50, (unsigned int)tomb4::CalculateSpotCams, false);
}
