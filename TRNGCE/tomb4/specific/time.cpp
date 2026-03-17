#include "time.h"
#include "../../inject.h"

namespace tomb4
{
	bool TIME_Init()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Time(bool replace)
{
	ProcessInject(0x48C580, (unsigned int)tomb4::TIME_Init, false);
}
