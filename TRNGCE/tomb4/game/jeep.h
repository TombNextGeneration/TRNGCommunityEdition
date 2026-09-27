#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &jeep_ignition_key_object;

	void JeepExplode(ITEM_INFO* item);
	void DrawJeepExtras(ITEM_INFO* item);
}

void Inject_Jeep(bool replace);
