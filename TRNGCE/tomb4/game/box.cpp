#include "box.h"
#include "../../inject.h"
#include "control.h"
#include "items.h"
#include "lot.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	BOX_INFO* &boxes = *reinterpret_cast<decltype(&boxes)>(0x7FE890);

	void AlertNearbyGuards(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void CreatureDie(short item_number, long explode)
	{
		__try { throw __func__; } __finally {}
	}

	long CreatureActive(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void GetAITarget(CREATURE_INFO* creature)
	{
		__try { throw __func__; } __finally {}
	}

	void CreatureAIInfo(ITEM_INFO* item, AI_INFO* info)
	{
		__try { throw __func__; } __finally {}
	}

	void GetCreatureMood(ITEM_INFO* item, AI_INFO* info, long violent)
	{
		__try { throw __func__; } __finally {}
	}

	void CreatureMood(ITEM_INFO* item, AI_INFO* info, long violent)
	{
		__try { throw __func__; } __finally {}
	}

	short CreatureTurn(ITEM_INFO* item, short maximum_turn)
	{
		__try { throw __func__; } __finally {}
	}

	short CreatureEffectT(ITEM_INFO* item, BITE_INFO* bite, short damage, short angle, short (*generate)(long x, long y, long z, short damage, short angle, short room_number))
	{
		__try { throw __func__; } __finally {}
	}

	long CreatureAnimation(short item_number, short angle, short tilt)
	{
		__try { throw __func__; } __finally {}
	}

	void CreatureFloat(short item_number)
	{
		ITEM_INFO* item;
		long water_level;
		short room_number;

		item = &items[item_number];
		item->hit_points = -16384;
		item->pos.x_rot = 0;
		water_level = GetWaterHeight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);

		if (item->pos.y_pos > water_level)
			item->pos.y_pos -= 32;

		if (item->pos.y_pos < water_level)
			item->pos.y_pos = water_level;

		AnimateItem(item);
		room_number = item->room_number;
		item->floor = GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number),
			item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

		if (item->room_number != room_number)
			ItemNewRoom(item_number, room_number);

		if (item->pos.y_pos <= water_level && item->frame_number == anims[item->anim_number].frame_base)
		{
			item->status = ITEM_DEACTIVATED;
			item->collidable = 0;
			item->pos.y_pos = water_level;
			DisableBaddieAI(item_number);
			RemoveActiveItem(item_number);
			item->after_death = !trng::GlobTomb4.pBaseCustomize->TestKeepNemiciMorti;
		}
	}
}

void Inject_Box(bool replace)
{
	ProcessInject(0x441D90, (unsigned int)tomb4::AlertNearbyGuards, false);
	ProcessInject(0x440840, (unsigned int)tomb4::CreatureDie, false);
	ProcessInject(0x43F370, (unsigned int)tomb4::CreatureActive, false);
	ProcessInject(0x441EE0, (unsigned int)tomb4::GetAITarget, false);
	ProcessInject(0x43F3E0, (unsigned int)tomb4::CreatureAIInfo, false);
	ProcessInject(0x43FBD0, (unsigned int)tomb4::GetCreatureMood, false);
	ProcessInject(0x43FE10, (unsigned int)tomb4::CreatureMood, false);
	ProcessInject(0x441430, (unsigned int)tomb4::CreatureTurn, false);
	ProcessInject(0x441940, (unsigned int)tomb4::CreatureEffectT, false);
	ProcessInject(0x4409F0, (unsigned int)tomb4::CreatureAnimation, false);
	ProcessInject(0x441750, (unsigned int)tomb4::CreatureFloat, replace);
}
