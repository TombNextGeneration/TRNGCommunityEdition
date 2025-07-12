#pragma once
#include "../types.h"

namespace tomb4
{
	long SoundEffect(sound_effect_names sfx, PHD_3DPOS* pos, sfx_options flags);
}

void Inject_Sound(bool replace);
