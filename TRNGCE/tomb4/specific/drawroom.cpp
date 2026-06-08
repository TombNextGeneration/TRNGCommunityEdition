#include "drawroom.h"
#include "../../inject.h"

namespace tomb4
{
	void ProcessMeshData(long num_meshes)
	{
		__try { throw __func__; } __finally {}
	}

	void InsertRoom(ROOM_INFO* r)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Drawroom(bool replace)
{
	ProcessInject(0x46F4F0, (unsigned int)tomb4::ProcessMeshData, false);
	ProcessInject(0x470A70, (unsigned int)tomb4::InsertRoom, false);
}
