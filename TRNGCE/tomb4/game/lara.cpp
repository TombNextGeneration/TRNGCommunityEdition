#include "lara.h"
#include "../../inject.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "collide.h"
#include "../specific/input.h"
#include "laramisc.h"
#include "control.h"
#include "camera.h"

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

	void LaraCollideStop(ITEM_INFO* item, COLL_INFO* coll)
	{
		switch (coll->old_anim_state)
		{
		case AS_STOP:
		case AS_TURN_R:
		case AS_TURN_L:
		case AS_FASTTURN:
			item->current_anim_state = coll->old_anim_state;
			item->anim_number = coll->old_anim_number;
			item->frame_number = coll->old_frame_number;

			if (input & IN_LEFT)
				item->goal_anim_state = AS_TURN_L;
			else if (input & IN_RIGHT)
				item->goal_anim_state = AS_TURN_R;
			else
				item->goal_anim_state = AS_STOP;

			AnimateLara(item);
			break;

		default:
			item->anim_number = ANIM_STOP;

			if (coll->old_anim_state == AS_BACK || coll->old_anim_state == AS_STEPRIGHT || coll->old_anim_state == AS_STEPLEFT || coll->old_anim_state == AS_WALK)
			{
				if (coll->old_anim_state == AS_WALK)
				{
					// attivare blocco dummy in avanti
					// se c'era anche conditional dummy attivato
					if (trng::GlobTomb4.TestDummyFalse)
						trng::GlobTomb4.TestDummyBlockForward = true;
				}

				item->current_anim_state = AS_STOP;
				item->goal_anim_state = AS_WALK;
			}

			item->frame_number = anims[ANIM_STOP].frame_base;
			break;
		}
	}

	void lara_as_wade(ITEM_INFO* item, COLL_INFO* coll)
	{
		if (item->hit_points <= 0)
		{
			item->goal_anim_state = AS_STOP;
			return;
		}

		camera.target_elevation = -4004;

		if (trng::IsLaraInPalude())
		{
			// codice palude (preso da tr3)
			if (input & IN_LEFT)
			{
				// lara gira a sinistra
				lara.turn_rate -= 409;

				if (lara.turn_rate < -728)
					lara.turn_rate = -728;

				item->pos.z_rot -= 273;

				if (item->pos.z_rot < -1001)
					item->pos.z_rot = -1001;
			}
			else if (input & IN_RIGHT)
			{
				lara.turn_rate += 409;

				if (lara.turn_rate > 728)
					lara.turn_rate = 728;

				item->pos.z_rot += 273;

				if (item->pos.z_rot > 1001)
					item->pos.z_rot = 1001;
			}

			if (input & IN_FORWARD)
			{
				// se si muove in avanti state id diventa 41
				// porca vacca ma sono certo che anche in tomb4 il 41h era lo stesso?
				item->goal_anim_state = AS_WADE;
			}
			else
				item->goal_anim_state = AS_STOP;

			return;
		}

		if (input & IN_LEFT)
		{
			lara.turn_rate -= 409;

			if (lara.turn_rate < -1456)
				lara.turn_rate = -1456;

			item->pos.z_rot -= 273;

			if (item->pos.z_rot < -2002)
				item->pos.z_rot = -2002;
		}
		else if (input & IN_RIGHT)
		{
			lara.turn_rate += 409;

			if (lara.turn_rate > 1456)
				lara.turn_rate = 1456;

			item->pos.z_rot += 273;

			if (item->pos.z_rot > 2002)
				item->pos.z_rot = 2002;
		}

		if (input & IN_FORWARD)
		{
			if (lara.water_status == LW_ABOVE_WATER)
				item->goal_anim_state = AS_RUN;
			else
				item->goal_anim_state = AS_WADE;
		}
		else
			item->goal_anim_state = AS_STOP;
	}

	void lara_col_dash(ITEM_INFO* item, COLL_INFO* coll)
	{
		lara.move_angle = item->pos.y_rot;
		coll->bad_pos = -NO_HEIGHT;
		coll->bad_neg = -384;
		coll->bad_ceiling = 0;
		coll->slopes_are_walls = 1;
		GetLaraCollisionInfo(item, coll);

		if (LaraHitCeiling(item, coll))
			return;

		if (trng::BaseCustomize.BaseStillCollision.Flags & trng::COLL_ENABLED && trng::GlobTomb4.BaseCollisione.TestStillCollision)
		{
			trng::StopSuScatto();

			// stoppare
			return;
		}

		if (TestLaraVault(item, coll))
			return;

		if (LaraDeflectEdge(item, coll))
		{
			item->pos.z_rot = 0;

			if (TestWall(item, 256, 0, -640))
			{
				item->current_anim_state = AS_SPLAT;
				item->anim_number = ANIM_HITWALLLEFT;
				item->frame_number = anims[ANIM_HITWALLLEFT].frame_base;
				return;
			}

			LaraCollideStop(item, coll);
		}

		if (LaraFallen(item, coll))
			return;

		if (coll->mid_floor >= -384 && coll->mid_floor < -128)
		{
			if (item->frame_number >= 3 && item->frame_number <= 14)
			{
				item->anim_number = ANIM_RUNSTEPUP_LEFT;
				item->frame_number = anims[ANIM_RUNSTEPUP_LEFT].frame_base;
			}
			else
			{
				item->anim_number = ANIM_RUNSTEPUP_RIGHT;
				item->frame_number = anims[ANIM_RUNSTEPUP_RIGHT].frame_base;
			}
		}

		if (TestLaraSlide(item, coll))
			return;

		if (coll->mid_floor < 50)
		{
			if (coll->mid_floor != NO_HEIGHT)
				item->pos.y_pos += coll->mid_floor;
		}
		else
			item->pos.y_pos += 50;
	}

	long TestLaraVault(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long LaraDeflectEdge(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long TestWall(ITEM_INFO* item, long front, long right, long down)
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
	ProcessInject(0x4227F0, (unsigned int)tomb4::LaraCollideStop, replace);
	ProcessInject(0x427390, (unsigned int)tomb4::lara_as_wade, replace);
	ProcessInject(0x422030, (unsigned int)tomb4::lara_col_dash, replace);
	ProcessInject(0x4222B0, (unsigned int)tomb4::TestLaraVault, false);
	ProcessInject(0x422230, (unsigned int)tomb4::LaraDeflectEdge, false);
	ProcessInject(0x4226F0, (unsigned int)tomb4::TestWall, false);
}
