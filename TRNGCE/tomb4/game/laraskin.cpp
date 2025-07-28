#include "laraskin.h"
#include "../../inject.h"

namespace tomb4
{
	void CreateSkinningData()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Laraskin(bool replace)
{
	ProcessInject(0x430AE0, (unsigned int)tomb4::CreateSkinningData, false);
}
