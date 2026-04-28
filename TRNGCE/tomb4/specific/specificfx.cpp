#include "specificfx.h"
#include "../../inject.h"

namespace tomb4
{
	void SetMapRoom()
	{
		__try { throw __func__; } __finally {}
	}

	void InitBinoculars()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Specificfx(bool replace)
{
	ProcessInject(0x4863D0, (unsigned int)tomb4::SetMapRoom, false);
	ProcessInject(0x4859E0, (unsigned int)tomb4::InitBinoculars, false);
}
