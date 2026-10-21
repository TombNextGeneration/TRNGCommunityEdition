#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &GlobalFogOff;
	extern FX_INFO* &effects;

	void SoundEffects();
	void KillActiveBaddies(ITEM_INFO* item);
	void ExplosionFX(ITEM_INFO* item);
	short DoBloodSplat(long x, long y, long z, short speed, short ang, short room_number);
}

void Inject_Effects(bool replace);
