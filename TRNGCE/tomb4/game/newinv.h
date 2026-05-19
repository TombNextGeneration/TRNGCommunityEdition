#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &GLOBAL_lastinvitem;
	extern short (&options_table)[NUM_INVOBJ];
	extern INVOBJ (&inventry_objects_list)[NUM_INVOBJ];
	extern long &GLOBAL_inventoryitemchosen;
	extern long &GLOBAL_enterinventory;
	extern long &InventoryActive;

	long S_CallInventory2();
	long convert_obj_to_invobj(short obj);
	void update_laras_weapons_status();
}

void Inject_Newinv(bool replace);
