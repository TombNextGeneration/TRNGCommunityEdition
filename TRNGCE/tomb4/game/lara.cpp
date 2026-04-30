#include "lara.h"
#include "../../inject.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "collide.h"

namespace tomb4
{
	LARA_INFO &lara = *reinterpret_cast<decltype(&lara)>(0x80DEC0);
	ITEM_INFO* &lara_item = *reinterpret_cast<decltype(&lara_item)>(0x80E01C);
	short &DashTimer = *reinterpret_cast<decltype(&DashTimer)>(0x80E01A);

	void lara_col_swandive(ITEM_INFO* item, COLL_INFO* coll)
	{
		if (trng::BaseCustomize.BaseStillCollision.Flags & trng::COLL_ENABLED && trng::GlobTomb4.BaseCollisione.TestStillCollision)
		{
			trng::StopFarfalla();
			return;
		}

		lara.move_angle = item->pos.y_rot;
		coll->bad_pos = -NO_HEIGHT;
		coll->bad_neg = -384;
		coll->bad_ceiling = 192;
		GetLaraCollisionInfo(item, coll);
		LaraDeflectEdgeJump(item, coll);

		if (coll->mid_floor <= 0 && item->fallspeed > 0)
		{
			item->goal_anim_state = AS_STOP;
			item->fallspeed = 0;
			item->gravity_status = 0;

			if (coll->mid_floor != NO_HEIGHT)
				item->pos.y_pos += coll->mid_floor;
		}
	}

	void GetLaraCollisionInfo(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	void LaraDeflectEdgeJump(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	void lara_col_stop(ITEM_INFO* item, COLL_INFO* coll)
	{
		lara.move_angle = item->pos.y_rot;
		coll->bad_pos = 384;
		coll->bad_neg = -384;
		coll->bad_ceiling = 0;
		item->gravity_status = 0;
		item->fallspeed = 0;
		coll->slopes_are_pits = 1;
		coll->slopes_are_walls = 1;
		GetLaraCollisionInfo(item, coll);

		if (LaraHitCeiling(item, coll))
			return;

		if (LaraFallen(item, coll))
			return;

		if (TestLaraSlide(item, coll))
			return;

		ShiftItem(item, coll);

		if (trng::IsLaraInPalude())
		{
			// se palude
			if (coll->mid_floor >= 0)
			{
				if (coll->mid_floor != 0)
					item->pos.y_pos += 2;

				return;
			}
		}

		if (coll->mid_floor != NO_HEIGHT)
			item->pos.y_pos += coll->mid_floor;
	}

	long LaraHitCeiling(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long LaraFallen(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long TestLaraSlide(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Lara(bool replace)
{
	ProcessInject(0x4284F0, (unsigned int)tomb4::lara_col_swandive, replace);
	ProcessInject(0x422180, (unsigned int)tomb4::GetLaraCollisionInfo, false);
	ProcessInject(0x422A70, (unsigned int)tomb4::LaraDeflectEdgeJump, false);
	ProcessInject(0x424E50, (unsigned int)tomb4::lara_col_stop, replace);
	ProcessInject(0x4221C0, (unsigned int)tomb4::LaraHitCeiling, false);
	ProcessInject(0x420E10, (unsigned int)tomb4::LaraFallen, false);
	ProcessInject(0x420CD0, (unsigned int)tomb4::TestLaraSlide, false);
}
