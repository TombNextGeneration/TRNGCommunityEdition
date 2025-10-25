#include "items.h"
#include "../../inject.h"

namespace tomb4
{
	short &next_item_active = *reinterpret_cast<decltype(&next_item_active)>(0x7FD0EA);
	short &next_fx_active = *reinterpret_cast<decltype(&next_fx_active)>(0x8011D0);

	void KillItem(short item_num)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Items(bool replace)
{
	ProcessInject(0x453690, (unsigned int)tomb4::KillItem, false);
}
