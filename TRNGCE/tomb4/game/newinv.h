#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &GLOBAL_lastinvitem;
	extern short (&options_table)[(long)invobj_types::NUM_INVOBJ];
	extern INVOBJ (&inventry_objects_list)[(long)invobj_types::NUM_INVOBJ];
	extern long &GLOBAL_inventoryitemchosen;
	extern long &GLOBAL_enterinventory;
	extern long &InventoryActive;

	long S_CallInventory2();
}

void Inject_Newinv(bool replace);
