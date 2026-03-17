#pragma once
#include "../types.h"

namespace tomb4
{
	void UpdateDebris();
	void ShatterObject(SHATTER_ITEM* shatter_item, MESH_INFO* StaticMesh, short Num, short RoomNumber, long NoXZVel);
}

void Inject_Debris(bool replace);
