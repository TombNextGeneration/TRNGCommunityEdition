#pragma once
#include "../types.h"

namespace tomb4
{
	extern TEXTUREBUCKET (&Bucket)[80];
	extern MESH_DATA** &mesh_vtxbuf;

	void ProcessMeshData(long num_meshes);
	void InsertRoom(ROOM_INFO* r);
	void InitBuckets();
}

void Inject_Drawroom(bool replace);
