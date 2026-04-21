#include "tomb4fx.h"
#include "../../inject.h"

namespace tomb4
{
	short &FadeScreenHeight = *reinterpret_cast<decltype(&FadeScreenHeight)>(0x4BF258);
	short &FlashFadeR = *reinterpret_cast<decltype(&FlashFadeR)>(0x4BF25E);
	short &FlashFadeG = *reinterpret_cast<decltype(&FlashFadeG)>(0x4BF260);
	short &FlashFadeB = *reinterpret_cast<decltype(&FlashFadeB)>(0x4BF262);
	short &FlashFader = *reinterpret_cast<decltype(&FlashFader)>(0x4BF264);
	short &ScreenFading = *reinterpret_cast<decltype(&ScreenFading)>(0x4BF254);
	short &ScreenFadedOut = *reinterpret_cast<decltype(&ScreenFadedOut)>(0x4BF252);

	void TriggerBlood(long x, long y, long z, long angle, long num)
	{
		__try { throw __func__; } __finally {}
	}

	void ClearFires()
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerLaraDrips()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateFireSparks()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateSmokeSparks()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateBubbles()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateBlood()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateDrips()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateGunShells()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateShockwaves()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateLightning()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateFadeClip()
	{
		__try { throw __func__; } __finally {}
	}

	void SetScreenFadeIn(short speed)
	{
		__try { throw __func__; } __finally {}
	}

	void SetScreenFadeOut(short speed, short back)
	{
		__try { throw __func__; } __finally {}
	}

	long ExplodingDeath2(short item_number, long mesh_bits, short Flags)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Tomb4fx(bool replace)
{
	ProcessInject(0x4388E0, (unsigned int)tomb4::TriggerBlood, false);
	ProcessInject(0x437F20, (unsigned int)tomb4::ClearFires, false);
	ProcessInject(0x439A10, (unsigned int)tomb4::TriggerLaraDrips, false);
	ProcessInject(0x437960, (unsigned int)tomb4::UpdateFireSparks, false);
	ProcessInject(0x438130, (unsigned int)tomb4::UpdateSmokeSparks, false);
	ProcessInject(0x439310, (unsigned int)tomb4::UpdateBubbles, false);
	ProcessInject(0x438780, (unsigned int)tomb4::UpdateBlood, false);
	ProcessInject(0x439910, (unsigned int)tomb4::UpdateDrips, false);
	ProcessInject(0x438D10, (unsigned int)tomb4::UpdateGunShells, false);
	ProcessInject(0x43A6A0, (unsigned int)tomb4::UpdateShockwaves, false);
	ProcessInject(0x43A910, (unsigned int)tomb4::UpdateLightning, false);
	ProcessInject(0x4396F0, (unsigned int)tomb4::UpdateFadeClip, false);
	ProcessInject(0x439790, (unsigned int)tomb4::SetScreenFadeIn, false);
	ProcessInject(0x439740, (unsigned int)tomb4::SetScreenFadeOut, false);
	ProcessInject(0x43A030, (unsigned int)tomb4::ExplodingDeath2, false);
}
