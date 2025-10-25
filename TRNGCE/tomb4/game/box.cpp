#include "box.h"
#include "../../inject.h"

namespace tomb4
{
	void AlertNearbyGuards(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Box(bool replace)
{
	ProcessInject(0x441D90, (unsigned int)tomb4::AlertNearbyGuards, false);
}
