#include "tomb4fx.h"
#include "../../inject.h"

namespace tomb4
{
	short &FadeScreenHeight = *reinterpret_cast<decltype(&FadeScreenHeight)>(0x4BF258);
	short &FlashFadeR = *reinterpret_cast<decltype(&FlashFadeR)>(0x4BF25E);
	short &FlashFadeG = *reinterpret_cast<decltype(&FlashFadeG)>(0x4BF260);
	short &FlashFadeB = *reinterpret_cast<decltype(&FlashFadeB)>(0x4BF262);
	short &FlashFader = *reinterpret_cast<decltype(&FlashFader)>(0x4BF264);

	void TriggerBlood(long x, long y, long z, long angle, long num)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Tomb4fx(bool replace)
{
	ProcessInject(0x4388E0, (unsigned int)tomb4::TriggerBlood, false);
}
