#include "jeep.h"
#include "../../inject.h"

namespace tomb4
{
	void JeepExplode(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Jeep(bool replace)
{
	ProcessInject(0x466D40, (unsigned int)tomb4::JeepExplode, false);
}
