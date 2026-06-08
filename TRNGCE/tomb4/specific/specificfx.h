#pragma once

namespace tomb4
{
	void SetMapRoom();
	void InitBinoculars();
	void DrawJeepSpeedo(long ux, long uy, long vel, long maxVel, long turboVel, long size, long spriteSlot);
	void DrawBikeSpeedo(long ux, long uy, long vel, long maxVel, long turboVel, long size, long unk);
}

void Inject_Specificfx(bool replace);
