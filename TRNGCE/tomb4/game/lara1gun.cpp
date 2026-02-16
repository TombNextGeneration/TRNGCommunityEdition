#include "lara1gun.h"
#include "../../inject.h"

namespace tomb4
{
	void TriggerUnderwaterExplosion(ITEM_INFO* item, long vehicle)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Lara1Gun(bool replace)
{
	ProcessInject(0x42B080, (unsigned int)tomb4::TriggerUnderwaterExplosion, false);
}
