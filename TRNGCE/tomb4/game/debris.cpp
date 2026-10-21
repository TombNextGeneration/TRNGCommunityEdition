#include "debris.h"
#include "../../inject.h"

namespace tomb4
{
	char (&tsv_buffer)[16384] = *reinterpret_cast<decltype(&tsv_buffer)>(0x804E60);

	void UpdateDebris()
	{
		__try { throw __func__; } __finally {}
	}

	void ShatterObject(SHATTER_ITEM* shatter_item, MESH_INFO* StaticMesh, short Num, short RoomNumber, long NoXZVel)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Debris(bool replace)
{
	ProcessInject(0x432DC0, (unsigned int)tomb4::UpdateDebris, false);
	ProcessInject(0x432F00, (unsigned int)tomb4::ShatterObject, false);
}
