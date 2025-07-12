#include "../../inject.h"
#include "../types.h"

namespace tomb4
{
	long SoundEffect(sound_effect_names sfx, PHD_3DPOS* pos, sfx_options flags)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Sound(bool replace)
{
	ProcessInject(0x45E440, (unsigned int)tomb4::SoundEffect, false);
}
