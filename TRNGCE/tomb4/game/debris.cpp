#include "debris.h"
#include "../../inject.h"

namespace tomb4
{
	void UpdateDebris()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Debris(bool replace)
{
	ProcessInject(0x432DC0, (unsigned int)tomb4::UpdateDebris, false);
}
