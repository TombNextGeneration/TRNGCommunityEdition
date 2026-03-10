#include "sub.h"
#include "../../inject.h"

namespace flep
{
	char (&sub_index)[tomb4::NUMBER_OBJECTS] = *reinterpret_cast<decltype(&sub_index)>(0x90404C);
	short (&sub_slot_upv)[16] = *reinterpret_cast<decltype(&sub_slot_upv)>(0x90400C);
	short (&sub_slot_vehicle_anim)[16] = *reinterpret_cast<decltype(&sub_slot_vehicle_anim)>(0x90402C);

	long IsSubAssignedToItem(long index, tomb4::ITEM_INFO* item)
	{
		return IsSubAssigned(index) && sub_index[sub_slot_upv[index]] == index && item->object_number == sub_slot_upv[index];
	}

	long IsSubAssigned(long index)
	{
		return sub_slot_upv[index] != -1 && sub_slot_vehicle_anim[index] != -1;
	}
}

void Inject_Sub(bool replace)
{
	ProcessInject(*(unsigned int*)0x90C3D8, (unsigned int)flep::IsSubAssignedToItem, replace);
	ProcessInject(*(unsigned int*)0x90C380, (unsigned int)flep::IsSubAssigned, replace);
}
