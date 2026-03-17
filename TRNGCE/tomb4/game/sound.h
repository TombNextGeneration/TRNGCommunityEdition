#pragma once
#include "../types.h"

namespace tomb4
{
	extern SoundSlot (&LaSlot)[32];
	extern long &sound_active;

	long SoundEffect(long sfx, PHD_3DPOS* pos, long flags);
	void SayNo();
}

void Inject_Sound(bool replace);
