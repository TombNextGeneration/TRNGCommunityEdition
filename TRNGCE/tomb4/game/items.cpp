#include "items.h"
#include "../../inject.h"
#include "control.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	static short &next_item_free = *reinterpret_cast<decltype(&next_item_free)>(0x7FD0E8);

	short &next_item_active = *reinterpret_cast<decltype(&next_item_active)>(0x7FD0EA);
	short &next_fx_active = *reinterpret_cast<decltype(&next_fx_active)>(0x8011D0);

	void KillItem(short item_num)
	{
		__try { throw __func__; } __finally {}
	}

	void ItemNewRoom(short item_num, short room_num)
	{
		__try { throw __func__; } __finally {}
	}

	short CreateItem()
	{
		short item_num;

		item_num = next_item_free;

		if (item_num != NO_ITEM)
		{
			items[item_num].flags = 0;
			next_item_free = items[item_num].next_item;
			trng::GlobTomb4.BaseCreatedItems.VetNewItems[trng::GlobTomb4.BaseCreatedItems.TotNewItems] = item_num;
			trng::GlobTomb4.BaseCreatedItems.TotNewItems++;

			// aggiornare numero massimo di item
			if (item_num + 1 > trng::AdrGlobali.TotItemsMax)
				trng::AdrGlobali.TotItemsMax = item_num + 1;
		}

		return item_num;
	}

	void AddActiveItem(short item_num)
	{
		__try { throw __func__; } __finally {}
	}

	void RemoveActiveItem(short item_num)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Items(bool replace)
{
	ProcessInject(0x453690, (unsigned int)tomb4::KillItem, false);
	ProcessInject(0x453C80, (unsigned int)tomb4::ItemNewRoom, false);
	ProcessInject(0x453840, (unsigned int)tomb4::CreateItem, replace);
	ProcessInject(0x453C10, (unsigned int)tomb4::AddActiveItem, false);
	ProcessInject(0x453AC0, (unsigned int)tomb4::RemoveActiveItem, false);
}
