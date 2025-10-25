#include "pickup.h"
#include "../../inject.h"

namespace tomb4
{
	void RegeneratePickups()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Pickup(bool replace)
{
	ProcessInject(0x456AC0, (unsigned int)tomb4::RegeneratePickups, false);
}
