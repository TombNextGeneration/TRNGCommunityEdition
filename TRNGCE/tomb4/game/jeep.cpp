#include "jeep.h"
#include "../../inject.h"
#include "lara.h"
#include "../specific/specificfx.h"
#include "../specific/3dmath.h"

namespace tomb4
{
	void JeepExplode(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void DrawJeepExtras(ITEM_INFO* item)
	{
		JEEPINFO* jeep;

		// in esp+4 c'e' stritemtr4 di veicolo a cui appartiene questo drawextra
		if (item->object_number != JEEP)
			return;

		jeep = (JEEPINFO*)item->data;
		DrawJeepSpeedo(phd_winwidth - 64, phd_winheight - 16, jeep->velocity, 0x6000, 0x8000, 32, jeep->gear);
	}
}

void Inject_Jeep(bool replace)
{
	ProcessInject(0x466D40, (unsigned int)tomb4::JeepExplode, false);
	ProcessInject(0x4665C0, (unsigned int)tomb4::DrawJeepExtras, replace);
}
