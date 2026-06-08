#include "specificfx.h"
#include "../../inject.h"

namespace tomb4
{
	void SetMapRoom()
	{
		__try { throw __func__; } __finally {}
	}

	void InitBinoculars()
	{
		__try { throw __func__; } __finally {}
	}

	void DrawJeepSpeedo(long ux, long uy, long vel, long maxVel, long turboVel, long size, long spriteSlot)	//ux and uy are not used
	{
		__try { throw __func__; } __finally {}
	}

	void DrawBikeSpeedo(long ux, long uy, long vel, long maxVel, long turboVel, long size, long unk)	//ux and uy are not used
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Specificfx(bool replace)
{
	ProcessInject(0x4863D0, (unsigned int)tomb4::SetMapRoom, false);
	ProcessInject(0x4859E0, (unsigned int)tomb4::InitBinoculars, false);
	ProcessInject(0x48B330, (unsigned int)tomb4::DrawJeepSpeedo, false);
	ProcessInject(0x48A480, (unsigned int)tomb4::DrawBikeSpeedo, false);
}
