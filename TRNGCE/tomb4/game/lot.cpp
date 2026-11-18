#include "lot.h"
#include "../../inject.h"

namespace tomb4
{
	void DisableBaddieAI(short item_number)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Lot(bool replace)
{
	ProcessInject(0x454750, (unsigned int)tomb4::DisableBaddieAI, false);
}
