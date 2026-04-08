#pragma once

namespace tomb4
{
	extern short &next_item_active;
	extern short &next_fx_active;

	void KillItem(short item_num);
	void ItemNewRoom(short item_num, short room_num);
	short CreateItem();
}

void Inject_Items(bool replace);
