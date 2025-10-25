#pragma once
#include "../types.h"

namespace tomb4
{
	extern SoundSlot (&LaSlot)[32];

	long SoundEffect(sound_effect_names sfx, PHD_3DPOS* pos, sfx_options flags);
	void SayNo();
}

void Inject_Sound(bool replace);
