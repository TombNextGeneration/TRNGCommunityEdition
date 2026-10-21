#include "larafire.h"
#include "../../inject.h"

namespace tomb4
{
	WEAPON_INFO (&weapons)[9] = *reinterpret_cast<decltype(&weapons)>(0x4AB830);

	void DoProperDetection(short item_number, long x, long y, long z, long xv, long yv, long zv)
	{
		__try { throw __func__; } __finally {}
	}

	void HitTarget(ITEM_INFO* item, GAME_VECTOR* hitpos, long damage, long grenade)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Larafire(bool replace)
{
	ProcessInject(0x42E6B0, (unsigned int)tomb4::DoProperDetection, false);
	ProcessInject(0x42E490, (unsigned int)tomb4::HitTarget, false);
}
