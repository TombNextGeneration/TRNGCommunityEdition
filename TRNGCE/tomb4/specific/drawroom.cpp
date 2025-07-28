#include "drawroom.h"
#include "../../inject.h"

namespace tomb4
{
	void ProcessMeshData(long num_meshes)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Drawroom(bool replace)
{
	ProcessInject(0x46F4F0, (unsigned int)tomb4::ProcessMeshData, false);
}
