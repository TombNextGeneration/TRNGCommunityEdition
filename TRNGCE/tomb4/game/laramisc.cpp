#include "laramisc.h"
#include "../../inject.h"

namespace tomb4
{
	void LaraControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Laramisc(bool replace)
{
	ProcessInject(0x42FDD0, (unsigned int)tomb4::LaraControl, false);
}
