#include "newinv.h"
#include "../../inject.h"

namespace tomb4
{
	long &GLOBAL_lastinvitem = *reinterpret_cast<decltype(&GLOBAL_lastinvitem)>(0x4AC05C);
	short (&options_table)[(long)invobj_types::NUM_INVOBJ] = *reinterpret_cast<decltype(&options_table)>(0x4AC9B8);
	INVOBJ (&inventry_objects_list)[(long)invobj_types::NUM_INVOBJ] = *reinterpret_cast<decltype(&inventry_objects_list)>(0x4AC068);
	long &GLOBAL_inventoryitemchosen = *reinterpret_cast<decltype(&GLOBAL_inventoryitemchosen)>(0x4AC064);
	long &GLOBAL_enterinventory = *reinterpret_cast<decltype(&GLOBAL_enterinventory)>(0x4AC060);
	long &InventoryActive = *reinterpret_cast<decltype(&InventoryActive)>(0x4BF2A0);

	long S_CallInventory2()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Newinv(bool replace)
{
	ProcessInject(0x43B0F0, (unsigned int)tomb4::S_CallInventory2, false);
}
