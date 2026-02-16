#include "bike.h"
#include "../../inject.h"

namespace tomb4
{
	void BikeTriggerExhaustSmoke(long x, long y, long z, short angle, long velocity, long thing)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Bike(bool replace)
{
	ProcessInject(0x4643A0, (unsigned int)tomb4::BikeTriggerExhaustSmoke, false);
}
