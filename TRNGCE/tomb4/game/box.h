#pragma once
#include "../types.h"

namespace tomb4
{
	void AlertNearbyGuards(ITEM_INFO* item);
	void CreatureDie(short item_number, long explode);
}

void Inject_Box(bool replace);
