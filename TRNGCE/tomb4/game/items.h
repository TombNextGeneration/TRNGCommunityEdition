#pragma once

namespace tomb4
{
	extern short &next_item_active;
	extern short &next_fx_active;

	void KillItem(short item_num);
}

void Inject_Items(bool replace);
