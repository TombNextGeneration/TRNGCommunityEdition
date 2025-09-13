#include "setup.h"
#include "../../inject.h"

namespace tomb4
{
	void InitialiseObjects()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Setup(bool replace)
{
	ProcessInject(0x45B4A0, (unsigned int)tomb4::InitialiseObjects, false);
}
