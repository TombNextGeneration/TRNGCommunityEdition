#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &GlobalFogOff;
	extern FX_INFO* &effects;

	void SoundEffects();
	void KillActiveBaddies(ITEM_INFO* item);
	void ExplosionFX(ITEM_INFO* item);
}

void Inject_Effects(bool replace);
