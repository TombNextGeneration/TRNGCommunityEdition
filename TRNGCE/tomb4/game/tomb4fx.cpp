#include "../../inject.h"

namespace tomb4
{
	void TriggerBlood(long x, long y, long z, long angle, long num)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Tomb4fx(bool replace)
{
	ProcessInject(0x4388E0, (unsigned int)tomb4::TriggerBlood, false);
}
