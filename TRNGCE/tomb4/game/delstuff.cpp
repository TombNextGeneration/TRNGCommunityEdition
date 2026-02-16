#include "delstuff.h"
#include "../../inject.h"

namespace tomb4
{
	void GetLaraJointPos(PHD_VECTOR* pos, long node)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Delstuff(bool replace)
{
	ProcessInject(0x41D890, (unsigned int)tomb4::GetLaraJointPos, false);
}
