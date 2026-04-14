#include "init.h"
#include "../../inject.h"
#include "control.h"
#include "lara.h"

namespace tomb4
{
	void InitialiseFlameEmitter3(short item_number)
	{
		ITEM_INFO* item;
		ITEM_INFO* item2;
		long i;

		item = &items[item_number];

		if (item->trigger_flags < 3 || level_items <= 0)
			return;

		if (item->trigger_flags >= 888 && item->trigger_flags <= 890)
		{
			item->item_flags[2] = lara.item_number;
			item->item_flags[3] = lara.item_number;
			return;
		}

		i = 0;

		do
		{
			item2 = &items[i];

			if (item2->object_number == ANIMATING3)
			{
				if (item2->trigger_flags == item->trigger_flags)
					item->item_flags[2] = (short)i;
				else if (!item2->trigger_flags)
					item->item_flags[3] = (short)i;
			}

			i++;
		} while (i < level_items);
	}
}

void Inject_Init(bool replace)
{
	ProcessInject(0x452730, (unsigned int)tomb4::InitialiseFlameEmitter3, replace);
}
