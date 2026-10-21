#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &jeep_ignition_key_object;

	void JeepExplode(ITEM_INFO* item);
	void DrawJeepExtras(ITEM_INFO* item);
	void JeepCollideStaticObjects(long x, long y, long z, short room_number, long height);
}

void Inject_Jeep(bool replace);
