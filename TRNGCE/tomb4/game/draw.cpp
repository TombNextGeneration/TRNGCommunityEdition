#include "../../inject.h"
#include "types.h"

namespace tomb4
{
	short* GetBoundsAccurate(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Draw(bool replace)
{
	ProcessInject(0x4504E0, (unsigned int)tomb4::GetBoundsAccurate, false);
}
