#include "box.h"
#include "../../inject.h"

namespace tomb4
{
	BOX_INFO* &boxes = *reinterpret_cast<decltype(&boxes)>(0x7FE890);

	void AlertNearbyGuards(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void CreatureDie(short item_number, long explode)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Box(bool replace)
{
	ProcessInject(0x441D90, (unsigned int)tomb4::AlertNearbyGuards, false);
	ProcessInject(0x440840, (unsigned int)tomb4::CreatureDie, false);
}
