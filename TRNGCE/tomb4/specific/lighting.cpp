#include "lighting.h"
#include "../../inject.h"

namespace tomb4
{
	void MallocD3DLights()
	{
		__try { throw __func__; } __finally {}
	}

	void CreateD3DLights()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Lighting(bool replace)
{
	ProcessInject(0x4761B0, (unsigned int)tomb4::MallocD3DLights, false);
	ProcessInject(0x476210, (unsigned int)tomb4::CreateD3DLights, false);
}
