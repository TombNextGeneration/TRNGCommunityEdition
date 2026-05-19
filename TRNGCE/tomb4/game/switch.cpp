#include "switch.h"
#include "../../inject.h"
#include "control.h"
#include "items.h"
#include "../../trng/trng_keypad.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	uchar &CurrentSequence = *reinterpret_cast<decltype(&CurrentSequence)>(0x7F55E0);
	uchar (&SequenceUsed)[6] = *reinterpret_cast<decltype(&SequenceUsed)>(0x7F55E8);
	uchar (&Sequences)[3] = *reinterpret_cast<decltype(&Sequences)>(0x7F561C);

	long SwitchTrigger(short item_number, short timer)
	{
		ITEM_INFO* item;

		trng::StoreResult = trng::VerificaSwitchKeypad();

		if (trng::StoreResult & 1)
		{
			// concluso con successo
			return 1;
		}

		item = &items[item_number];

		if (item->status == ITEM_DEACTIVATED)
		{
			if (((item->current_anim_state || item->object_number == JUMP_SWITCH) &&
				(item->current_anim_state != 1 || item->object_number != JUMP_SWITCH)) || timer <= 0)
			{
				RemoveActiveItem(item_number);
				item->status = ITEM_INACTIVE;

				if (item->item_flags[0])
					item->flags |= IFL_INVISIBLE;
			}
			else
			{
				item->timer = timer;
				item->status = ITEM_ACTIVE;

				if (timer != 1)
					item->timer *= 30;
			}

			return 1;
		}

		if (item->status != ITEM_INACTIVE)
		{
			if (item->flags & IFL_INVISIBLE)
				return 1;
		}

		return 0;
	}
}

void Inject_Switch(bool replace)
{
	ProcessInject(0x460CE0, (unsigned int)tomb4::SwitchTrigger, replace);
}
