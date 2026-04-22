#include "laraswim.h"
#include "../../inject.h"

namespace tomb4
{
	long GetWaterDepth(long x, long y, long z, short room_number)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Laraswim(bool replace)
{
	ProcessInject(0x432700, (unsigned int)tomb4::GetWaterDepth, false);
}
