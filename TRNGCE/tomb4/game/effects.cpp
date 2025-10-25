#include "effects.h"
#include "../../inject.h"

namespace tomb4
{
	long &GlobalFogOff = *reinterpret_cast<decltype(&GlobalFogOff)>(0x4BF248);
	FX_INFO* &effects = *reinterpret_cast<decltype(&effects)>(0x8011C0);

	void SoundEffects()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Effects(bool replace)
{
	ProcessInject(0x436B30, (unsigned int)tomb4::SoundEffects, false);
}
