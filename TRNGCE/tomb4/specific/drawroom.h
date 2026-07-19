#pragma once
#include "../types.h"

namespace tomb4
{
	extern TEXTUREBUCKET (&Bucket)[80];

	void ProcessMeshData(long num_meshes);
	void InsertRoom(ROOM_INFO* r);
	void InitBuckets();
}

void Inject_Drawroom(bool replace);
