#include "sound.h"
#include "../../inject.h"

namespace tomb4
{
	SoundSlot (&LaSlot)[32] = *reinterpret_cast<decltype(&LaSlot)>(0x7F7100);

	long SoundEffect(sound_effect_names sfx, PHD_3DPOS* pos, sfx_options flags)
	{
		__try { throw __func__; } __finally {}
	}

	void SayNo()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Sound(bool replace)
{
	ProcessInject(0x45E440, (unsigned int)tomb4::SoundEffect, false);
	ProcessInject(0x45ECB0, (unsigned int)tomb4::SayNo, false);
}
