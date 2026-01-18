#include "traps.h"
#include "../../inject.h"

namespace tomb4
{
	char (&LibraryTab)[8] = *reinterpret_cast<decltype(&LibraryTab)>(0x4BF1D8);

	long OnTwoBlockPlatform(ITEM_INFO* item, long x, long z)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Traps(bool replace)
{
	ProcessInject(0x415A10, (unsigned int)tomb4::OnTwoBlockPlatform, false);
}
