#include "objlight.h"
#include "../../inject.h"
#include "control.h"
#include "../specific/function_stubs.h"
#include "effect2.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	short &WhiteLightFrameOn = *reinterpret_cast<decltype(&WhiteLightFrameOn)>(0x45693C);

	void ControlElectricalLight(short item_number)
	{
		ITEM_INFO* item;
		long shade, r, g, b;

		item = &items[item_number];

		if (!TriggerActive(item))
		{
			item->item_flags[0] = 0;
			return;
		}

		if (item->item_flags[0] < 16)
		{
			shade = (GetRandomControl() & 0x3F) << 2;
			item->item_flags[0]++;
		}
		else
		{
			if (item->item_flags[0] >= 96)
			{
				if (item->item_flags[0] >= WhiteLightFrameOn)
					shade = 255 - (GetRandomControl() & 0x1F);
				else
				{
					shade = 96 - (GetRandomControl() & 0x1F);

					if (!(GetRandomControl() & 0x1F) && item->item_flags[0] > 128)
						item->item_flags[0] = 160;
					else
						item->item_flags[0]++;
				}
			}
			else
			{
				if (wibble & 0x3F && GetRandomControl() & 7)
					shade = GetRandomControl() & 0x3F;
				else
					shade = 192 - (GetRandomControl() & 0x3F);

				item->item_flags[0]++;
			}
		}

		r = (shade * ((item->trigger_flags & 0x1F) << 3) >> 8) | trng::BaseCustomize.WhiteLight.Rosso;
		g = (shade * ((item->trigger_flags >> 2) & 0xF8) >> 8) | trng::BaseCustomize.WhiteLight.Verde;
		b = (shade * ((item->trigger_flags >> 7) & 0xF8) >> 8) | trng::BaseCustomize.WhiteLight.Blue;
		TriggerDynamic(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, trng::BaseCustomize.WhiteLight.Intensita, r, g, b);
	}
}

void Inject_Objlight(bool replace)
{
	ProcessInject(0x4568B0, (unsigned int)tomb4::ControlElectricalLight, replace);
}
