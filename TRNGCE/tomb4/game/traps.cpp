#include "traps.h"
#include "../../inject.h"
#include "control.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	char (&LibraryTab)[8] = *reinterpret_cast<decltype(&LibraryTab)>(0x4BF1D8);

	long OnTwoBlockPlatform(ITEM_INFO* item, long x, long z)
	{
		__try { throw __func__; } __finally {}
	}

	void LaraBurn()
	{
		__try { throw __func__; } __finally {}
	}

	void OpenTrapDoor(ITEM_INFO* item)
	{
		ROOM_INFO* r;
		FLOOR_INFO* floor;
		ushort pitsky;

		trng::ControllaTrapDoor((trng::StrItemTr4*)item);
		pitsky = item->item_flags[3];
		r = &room[item->room_number];
		floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10)];

		if (item->pos.y_pos == r->minfloor)
		{
			floor->pit_room = pitsky & 0xFF;
			r = &room[floor->pit_room];
			floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10)];
			floor->sky_room = pitsky >> 8;
		}
		else
		{
			floor->sky_room = pitsky >> 8;
			r = &room[floor->sky_room];
			floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10)];
			floor->pit_room = pitsky & 0xFF;
		}

		item->item_flags[2] = 0;
	}
}

void Inject_Traps(bool replace)
{
	ProcessInject(0x415A10, (unsigned int)tomb4::OnTwoBlockPlatform, false);
	ProcessInject(0x414D90, (unsigned int)tomb4::LaraBurn, false);
	ProcessInject(0x4135F0, (unsigned int)tomb4::OpenTrapDoor, replace);
}
