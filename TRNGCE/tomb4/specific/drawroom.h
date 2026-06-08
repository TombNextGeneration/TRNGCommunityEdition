#pragma once
#include "../types.h"

namespace tomb4
{
	void ProcessMeshData(long num_meshes);
	void InsertRoom(ROOM_INFO* r);
}

void Inject_Drawroom(bool replace);
