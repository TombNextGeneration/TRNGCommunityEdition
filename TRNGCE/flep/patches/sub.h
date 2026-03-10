#pragma once
#include "../../tomb4/types.h"

namespace flep
{
	extern char (&sub_index)[tomb4::NUMBER_OBJECTS];
	extern short (&sub_slot_upv)[16];
	extern short (&sub_slot_vehicle_anim)[16];

	long IsSubAssignedToItem(long index, tomb4::ITEM_INFO* item);
	long IsSubAssigned(long index);
}

void Inject_Sub(bool replace);
