#include "bike.h"
#include "../../inject.h"
#include "lara.h"
#include "control.h"
#include "newinv.h"
#include "objects.h"
#include "savegame.h"
#include "collide.h"
#include "laraflar.h"
#include "../specific/3dmath.h"
#include "../specific/input.h"
#include "sound.h"
#include "items.h"
#include "camera.h"
#include "sphere.h"
#include "../specific/function_stubs.h"
#include "tomb4fx.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	static short &bikefspeed = *reinterpret_cast<decltype(&bikefspeed)>(0x4BFADC);
	static char &dont_exit_bike = *reinterpret_cast<decltype(&dont_exit_bike)>(0x4BFAF8);

	static long UserControl(ITEM_INFO* item, long height, long* pitch)
	{
		__try { throw __func__; } __finally {}
	}

	static long DoDynamics(long height, long fallspeed, long* ypos, long zero)
	{
		__try { throw __func__; } __finally {}
	}

	static long BikeCheckGetOff()
	{
		__try { throw __func__; } __finally {}
	}

	static long CanGetOff(short num)	//always called with num = 1
	{
		__try { throw __func__; } __finally {}
	}

	void BikeTriggerExhaustSmoke(long x, long y, long z, short angle, long velocity, long thing)
	{
		__try { throw __func__; } __finally {}
	}

	void BikeCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
	{
		ITEM_INFO* item;
		BIKEINFO* bike;
		short angle;

		if (l->hit_points < 0 || lara.vehicle != NO_ITEM)
			return;

		item = &items[item_number];
		bike = (BIKEINFO*)item->data;

		if (bike->light_intensity)
		{
			bike->light_intensity = bike->light_intensity - (bike->light_intensity >> 3) - 1;
			TriggerBikeBeam(item);
		}

		if (GetOnBike(item_number, coll))
		{
			lara.vehicle = item_number;

			if (lara.gun_type == WEAPON_FLARE)
			{
				CreateFlare(FLARE_ITEM, 0);
				undraw_flare_meshes();
				lara.flare_control_left = 0;
				lara.gun_type = LG_NO_ARMS;
				lara.request_gun_type = WEAPON_NONE;
				lara.flare_age = 0;
			}

			lara.gun_status = LG_HANDS_BUSY;
			angle = short(phd_atan(item->pos.z_pos - l->pos.z_pos, item->pos.x_pos - l->pos.x_pos) - item->pos.y_rot);

			if (angle <= -8190 || angle >= 24570)
			{
				if (GLOBAL_inventoryitemchosen == PUZZLE_ITEM1)
				{
					l->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 28;
					GLOBAL_inventoryitemchosen = NO_ITEM;
					savegame.HaveBikeBooster = 1;
				}
				else
					l->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 9;

				l->goal_anim_state = 9;
				l->current_anim_state = 9;
			}

			l->frame_number = anims[l->anim_number].frame_base;
			item->hit_points = 1;
			l->pos.x_pos = item->pos.x_pos;
			l->pos.y_pos = item->pos.y_pos;
			l->pos.z_pos = item->pos.z_pos;
			l->pos.y_rot = item->pos.y_rot;
			lara.head_x_rot = 0;
			lara.head_y_rot = 0;
			lara.torso_x_rot = 0;
			lara.torso_y_rot = 0;
			lara.hit_direction = -1;
			AnimateItem(l);
			bike->unused1 = 0;
			item->flags |= IFL_TRIGGERED;
		}
		else
			ObjectCollision(item_number, l, coll);
	}

	void TriggerBikeBeam(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	long GetOnBike(short item_number, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	void BikeControl(short item_number)
	{
		static uchar ExhaustSmokeVel;

		ITEM_INFO* item;
		BIKEINFO* bike;
		FLOOR_INFO* floor;
		PHD_VECTOR flPos, frPos, fmPos;
		PHD_VECTOR pos;
		long front_left, front_right, front_mid;
		long hitWall, h, driving, killed, pitch, oldY, hdiff, smokeVel;
		short room_number, wheelRot, xRot, zRot;

		driving = -1;
		killed = 0;
		pitch = 0;					//originally uninitialized
		item = &items[lara.vehicle];
		bike = (BIKEINFO*)item->data;
		hitWall = BikeDynamics(item);

		if (hitWall == -888)	//hit the crocgod
		{
			ExplodingDeath2(lara.item_number, -1, 256);
			lara_item->hit_points = 0;
			lara_item->flags |= IFL_INVISIBLE;
			BikeExplode(item);
			return;
		}

		room_number = item->room_number;
		floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);
		GetHeight(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		GetCeiling(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		front_left = TestHeight(item, 500, -350, &flPos);
		front_right = TestHeight(item, 500, 128, &frPos);
		front_mid = TestHeight(item, -500, 0, &fmPos);
		room_number = item->room_number;
		floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);
		h = GetHeight(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		TestTriggers(trigger_index, 0, 0);
		TestTriggers(trigger_index, 1, 0);

		if (lara_item->hit_points <= 0)
		{
			killed = 1;
			input &= ~(IN_FORWARD | IN_BACK | IN_LEFT | IN_RIGHT);	//should be IN_ACTION instead?
		}

		if (bike->flags & 0xFF)
			hitWall = 0;
		else
		{
			TriggerBikeBeam(item);

			if (lara_item->current_anim_state < 9 || lara_item->current_anim_state > 10)
				driving = UserControl(item, h, &pitch);
			else
			{
				driving = -1;
				hitWall = 0;
			}
		}

		if (bike->velocity > 0 || bike->unused1)
		{
			bike->pitch2 = pitch;

			if (bike->pitch2 < -0x8000)
				bike->pitch2 = -0x8000;
			else if (bike->pitch2 > 0xA000)
				bike->pitch2 = 0xA000;

			SoundEffect(SFX_BIKE_MOVING, &item->pos, (bike->pitch2 << 8) + (SFX_SETPITCH | 0x1000000));
		}
		else
		{
			if (driving != -1)
			{
				SoundEffect(SFX_BIKE_IDLE, &item->pos, SFX_DEFAULT);
				SoundEffect(SFX_BIKE_MOVING, &item->pos, (bike->pitch2 << 8) + (SFX_SETPITCH | 0x1000000));
			}

			bike->pitch2 = 0;
		}

		item->floor = h;
		wheelRot = short(bike->velocity >> 2);
		bike->right_front_wheelrot -= wheelRot;
		bike->right_back_wheelrot -= wheelRot;
		bike->left_wheelrot -= wheelRot;
		bikefspeed = item->fallspeed;
		oldY = item->pos.y_pos;
		item->fallspeed = (short)DoDynamics(h, item->fallspeed, &item->pos.y_pos, 0);
		hdiff = (frPos.y + flPos.y) >> 1;

		if (fmPos.y < front_mid)
		{
			if (hdiff < (front_left + front_right) >> 1)
				xRot = (short)phd_atan(125, oldY - item->pos.y_pos);
			else
				xRot = (short)phd_atan(500, item->pos.y_pos - hdiff);
		}
		else
		{
			if (hdiff < (front_left + front_right) >> 1)
				xRot = (short)phd_atan(500, front_mid - item->pos.y_pos);
			else
				xRot = (short)phd_atan(1000, front_mid - hdiff);
		}

		zRot = (short)phd_atan(350, hdiff - flPos.y);
		item->pos.x_rot += (xRot - item->pos.x_rot) >> 2;
		item->pos.z_rot += (zRot - item->pos.z_rot) >> 2;

		if (!(bike->flags & 0x80))
		{
			if (room_number != item->room_number)
			{
				ItemNewRoom(lara.vehicle, room_number);
				ItemNewRoom(lara.item_number, room_number);
			}

			trng::CollBikeFinale((int*)&hitWall, killed);

			lara_item->pos.x_pos = item->pos.x_pos;
			lara_item->pos.y_pos = item->pos.y_pos;
			lara_item->pos.z_pos = item->pos.z_pos;
			lara_item->pos.x_rot = item->pos.x_rot;
			lara_item->pos.y_rot = item->pos.y_rot;
			lara_item->pos.z_rot = item->pos.z_rot;
			AnimateBike(item, hitWall, killed);
			AnimateItem(lara_item);
			item->anim_number = objects[MOTORBIKE].anim_index + lara_item->anim_number - *trng::GlobTomb4.pIndiceFirstAnimBike;
			item->frame_number = lara_item->frame_number + anims[item->anim_number].frame_base - anims[lara_item->anim_number].frame_base;
			camera.target_elevation = -5460;

			if (bike->flags & 0x40 && item->pos.y_pos == item->floor)
			{
				ExplodingDeath2(lara.item_number, -1, 256);
				lara_item->hit_points = 0;
				lara_item->flags |= IFL_INVISIBLE;
				BikeExplode(item);
				return;
			}
		}

		if (lara_item->current_anim_state == 9 || lara_item->current_anim_state == 10)
			ExhaustSmokeVel = 0;
		else
		{
			pos.x = 56;
			pos.y = -144;
			pos.z = -500;
			GetJointAbsPosition(item, &pos, 0);

			if (item->speed > 32)
			{
				if (item->speed < 64)
					BikeTriggerExhaustSmoke(pos.x, pos.y, pos.z, item->pos.y_rot + 0x8000, 64 - item->speed, 1);
			}
			else
			{
				if (ExhaustSmokeVel < 16)
				{
					smokeVel = ((GetRandomControl() & 7) + (GetRandomControl() & 0x10) + 2 * ExhaustSmokeVel) << 6;
					ExhaustSmokeVel++;
				}
				else if (GetRandomControl() & 3)
					smokeVel = 0;
				else
					smokeVel = ((GetRandomControl() & 0xF) + (GetRandomControl() & 0x10)) << 6;

				BikeTriggerExhaustSmoke(pos.x, pos.y, pos.z, item->pos.y_rot + 0x8000, smokeVel, 0);
			}
		}

		BikeCheckGetOff();
	}

	long BikeDynamics(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void BikeExplode(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	long TestHeight(ITEM_INFO* item, long z, long x, PHD_VECTOR* pos)
	{
		__try { throw __func__; } __finally {}
	}

	void AnimateBike(ITEM_INFO* item, long hitWall, long killed)
	{
		BIKEINFO* bike;
		short state, dmg;

		bike = (BIKEINFO*)item->data;
		state = lara_item->current_anim_state;

		if (item->pos.y_pos != item->floor && state != 8 && state != 17 && state != 20 && !killed)
		{
			if (bike->velocity < 0)
				lara_item->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 6;
			else
				lara_item->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 22;

			lara_item->goal_anim_state = 8;
			lara_item->current_anim_state = 8;
			lara_item->frame_number = anims[lara_item->anim_number].frame_base;
		}
		else if (hitWall && state != 12 && state != 11 && state != 13 && state != 14 && state != 20 && bike->velocity > 10922 && !killed)
		{
			switch (hitWall)
			{
			case 13:
				lara_item->goal_anim_state = 12;
				lara_item->current_anim_state = 12;
				lara_item->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 12;
				break;

			case 14:
				lara_item->goal_anim_state = 11;
				lara_item->current_anim_state = 11;
				lara_item->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 11;
				break;

			case 11:
				lara_item->goal_anim_state = 13;
				lara_item->current_anim_state = 13;
				lara_item->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 14;
				break;

			default:
				lara_item->goal_anim_state = 14;
				lara_item->current_anim_state = 14;
				lara_item->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 13;
				break;
			}

			lara_item->frame_number = anims[lara_item->anim_number].frame_base;
		}
		else
		{
			switch (lara_item->current_anim_state)
			{
			case 1:

				if (killed)
				{
					if (bike->velocity > 0x4000)
						lara_item->goal_anim_state = 19;
					else
						lara_item->goal_anim_state = 7;
				}
				else
				{
					if (bike->velocity & 0xFFFFFF00 || input & (IN_ACTION | IN_JUMP))
					{
						if (input & IN_LEFT)
							lara_item->goal_anim_state = 2;
						else if (input & IN_RIGHT)
							lara_item->goal_anim_state = 22;
						else if (input & IN_JUMP)
						{
							if (bike->velocity > 21844)
								lara_item->goal_anim_state = 6;
							else
								lara_item->goal_anim_state = 5;
						}
						else if (input & IN_BACK && bike->velocity <= 2048)
							lara_item->goal_anim_state = 3;
					}
					else
						lara_item->goal_anim_state = 15;
				}

				break;

			case 2:

				if (bike->velocity & 0xFFFFFF00)
				{
					if (input & IN_RIGHT || !(input & IN_LEFT))
						lara_item->goal_anim_state = 1;
				}
				else
					lara_item->goal_anim_state = 15;

				break;

			case 3:

				if (input & IN_BACK)
					lara_item->goal_anim_state = 4;
				else
					lara_item->goal_anim_state = 15;

				break;

			case 5:
			case 6:
			case 18:

				if (bike->velocity & 0xFFFFFF00)
				{
					if (input & IN_LEFT)
						lara_item->goal_anim_state = 2;
					else if (input & IN_RIGHT)
						lara_item->goal_anim_state = 22;
				}
				else
					lara_item->goal_anim_state = 15;

				break;

			case 8:

				if (item->pos.y_pos == item->floor)
				{
					lara_item->goal_anim_state = 17;
					dmg = short(bikefspeed - 140);

					if (dmg > 0)
					{
						if (dmg > 100)
							lara_item->hit_points = -1;
						else
							lara_item->hit_points += -1000 * dmg * dmg / 10000;
					}
				}
				else if (item->fallspeed > 220)
					bike->flags |= 0x40;

				break;

			case 11:
			case 12:
			case 13:
			case 14:

				if (input & (IN_ACTION | IN_JUMP))
					lara_item->goal_anim_state = 1;

				break;

			case 15:

				if (killed)
					lara_item->goal_anim_state = 7;
				else if (((input & (IN_JUMP | IN_RIGHT)) != (IN_JUMP | IN_RIGHT)) || bike->velocity || dont_exit_bike)
				{
					if (input & IN_ACTION && !(input & IN_JUMP))
						lara_item->goal_anim_state = 1;
					else if (input & IN_BACK)
						lara_item->goal_anim_state = 3;
				}
				else if (CanGetOff(1))
					lara_item->goal_anim_state = 10;

				break;

			case 22:

				if (bike->velocity & 0xFFFFFF00)
				{
					if (input & IN_LEFT || !(input & IN_RIGHT))
						lara_item->goal_anim_state = 1;
				}
				else
					lara_item->goal_anim_state = 15;

				break;
			}
		}

		if (room[item->room_number].flags & (ROOM_UNDERWATER | ROOM_QUICKSAND))
		{
			lara_item->goal_anim_state = 20;
			lara_item->hit_points = 0;
			BikeExplode(item);
		}
	}

	void BikeStart(ITEM_INFO* item, ITEM_INFO* l)
	{
		BIKEINFO* bike;

		bike = (BIKEINFO*)item->data;
		lara.gun_status = LG_HANDS_BUSY;
		lara.hit_direction = -1;
		l->goal_anim_state = 15;
		l->current_anim_state = 15;
		l->anim_number = *trng::GlobTomb4.pIndiceFirstAnimBike + 18;
		l->frame_number = anims[l->anim_number].frame_base;
		l->gravity_status = 0;
		item->anim_number = l->anim_number + objects[MOTORBIKE].anim_index - *trng::GlobTomb4.pIndiceFirstAnimBike;
		item->frame_number = l->frame_number + anims[item->anim_number].frame_base - anims[l->anim_number].frame_base;
		item->flags |= IFL_TRIGGERED;
		item->hit_points = 1;
		bike->unused1 = 0;
	}
}

void Inject_Bike(bool replace)
{
	ProcessInject(0x465D40, (unsigned int)tomb4::UserControl, false);
	ProcessInject(0x4647E0, (unsigned int)tomb4::DoDynamics, false);
	ProcessInject(0x464620, (unsigned int)tomb4::BikeCheckGetOff, false);
	ProcessInject(0x465B70, (unsigned int)tomb4::CanGetOff, false);

	ProcessInject(0x4643A0, (unsigned int)tomb4::BikeTriggerExhaustSmoke, false);
	ProcessInject(0x463820, (unsigned int)tomb4::BikeCollision, replace);
	ProcessInject(0x4639F0, (unsigned int)tomb4::TriggerBikeBeam, false);
	ProcessInject(0x463A90, (unsigned int)tomb4::GetOnBike, false);
	ProcessInject(0x463E00, (unsigned int)tomb4::BikeControl, replace);
	ProcessInject(0x464850, (unsigned int)tomb4::BikeDynamics, false);
	ProcessInject(0x464550, (unsigned int)tomb4::BikeExplode, false);
	ProcessInject(0x466EE0, (unsigned int)tomb4::TestHeight, false);
	ProcessInject(0x465740, (unsigned int)tomb4::AnimateBike, replace);
	ProcessInject(0x466120, (unsigned int)tomb4::BikeStart, replace);
}
