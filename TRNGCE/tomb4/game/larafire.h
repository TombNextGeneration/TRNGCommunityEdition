#pragma once
#include "../types.h"

namespace tomb4
{
	extern WEAPON_INFO (&weapons)[9];

	void DoProperDetection(short item_number, long x, long y, long z, long xv, long yv, long zv);
	void HitTarget(ITEM_INFO* item, GAME_VECTOR* hitpos, long damage, long grenade);
}

void Inject_Larafire(bool replace);
