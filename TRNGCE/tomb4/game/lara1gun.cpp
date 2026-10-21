#include "lara1gun.h"
#include "../../inject.h"
#include "control.h"
#include "lara.h"
#include "items.h"
#include "../../trng/zPatchesTomb4.h"
#include "tomb4fx.h"
#include "../specific/function_stubs.h"
#include "../specific/polyinsert.h"
#include "../specific/3dmath.h"
#include "effect2.h"
#include "larafire.h"
#include "collide.h"
#include "debris.h"
#include "objects.h"
#include "switch.h"
#include "box.h"
#include "sound.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	long &CrossbowOffsetX = *reinterpret_cast<decltype(&CrossbowOffsetX)>(0x429F94);
	long &CrossbowOffsetY = *reinterpret_cast<decltype(&CrossbowOffsetY)>(0x429F9C);
	long &CrossbowOffsetZ = *reinterpret_cast<decltype(&CrossbowOffsetZ)>(0x429FA4);
	uchar &GrenadeWeight = *reinterpret_cast<decltype(&GrenadeWeight)>(0x429676);
	long &GrenadeRotation = *reinterpret_cast<decltype(&GrenadeRotation)>(0x42966F);
#define GrenadeRotation (GrenadeRotation != 0x660000B8)
	uchar &GrenadeOneTouch = *reinterpret_cast<decltype(&GrenadeOneTouch)>(0x429796);
#define GrenadeOneTouch (GrenadeOneTouch == 0x90)

	void TriggerUnderwaterExplosion(ITEM_INFO* item, long vehicle)
	{
		__try { throw __func__; } __finally {}
	}

	void undraw_shotgun(long weapon_type)
	{
		ITEM_INFO* item;

		item = &items[lara.weapon_item];

		if (lara.water_status == LW_SURFACE)
			item->goal_anim_state = 9;
		else
			item->goal_anim_state = 3;

		AnimateItem(item);

		if (item->status == ITEM_DEACTIVATED)
		{
			lara.gun_status = LG_NO_ARMS;
			lara.target = 0;
			lara.right_arm.lock = 0;
			lara.left_arm.lock = 0;
			KillItem(lara.weapon_item);
			lara.weapon_item = NO_ITEM;
			lara.right_arm.frame_number = 0;
			lara.left_arm.frame_number = 0;
		}
		else if (item->current_anim_state == 3)
		{
			trng::ValGlobale = trng::TrovaFrameArmaPesante();

			if (item->frame_number - anims[item->anim_number].frame_base == trng::ValGlobale)
				undraw_shotgun_meshes(weapon_type);
		}

		lara.right_arm.frame_base = anims[item->anim_number].frame_ptr;
		lara.left_arm.frame_base = lara.right_arm.frame_base;
		lara.right_arm.frame_number = item->frame_number - anims[item->anim_number].frame_base;
		lara.left_arm.frame_number = lara.right_arm.frame_number;
		lara.right_arm.anim_number = item->anim_number;
		lara.left_arm.anim_number = lara.right_arm.anim_number;
	}

	void undraw_shotgun_meshes(long weapon_type)
	{
		__try { throw __func__; } __finally {}
	}

	void ControlGrenade(short item_number)
	{
		ITEM_INFO** itemlist;
		MESH_INFO** meshlist;
		ITEM_INFO* item;
		ITEM_INFO* item2;
		ITEM_INFO* target;
		MESH_INFO* mesh;
		FLOOR_INFO* floor;
		long oldx, oldy, oldz, abovewater, x, y, z, xv, yv, zv, exploded, rad, j;
		short new_num, yrot, room_number, NumTrigs;
		short TriggerItems[8];
		bool skip;

		item = &items[item_number];

		if (item->item_flags[1])
		{
			item->item_flags[1]--;

			if (!item->item_flags[1])
			{
				KillItem(item_number);
				return;
			}

			if (item->item_flags[0] == 3)
			{
				if (item->item_flags[1] == 1)
				{
					FlashFadeR = 255;
					FlashFadeG = 255;
					FlashFadeB = 255;
					lara.blindTimer = 120;
				}
				else
				{
					FlashFadeR = (GetRandomControl() & 0x1F) + 224;
					FlashFadeG = FlashFadeR - (GetRandomControl() & 0x1F);
					FlashFadeB = FlashFadeG;
				}

				FlashFader = 32;

				if (IsVolumetric())
					FlashFader = 0;

				TriggerFlashSmoke(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
				TriggerFlashSmoke(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
			}
			else
			{
				new_num = CreateItem();

				if (new_num != NO_ITEM)
				{
					item2 = &items[new_num];
					item2->shade = -0x3DF0;
					item2->object_number = GRENADE;
					item2->room_number = item->room_number;
					item2->pos.x_pos = (GetRandomControl() & 0x1FF) + item->pos.x_pos - 256;
					item2->pos.y_pos = item->pos.y_pos - 256;
					item2->pos.z_pos = (GetRandomControl() & 0x1FF) + item->pos.z_pos - 256;
					InitialiseItem(new_num);
					item2->pos.x_rot = (GetRandomControl() & 0x3FFF) + 0x2000;
					item2->pos.y_rot = short(GetRandomControl() * 2);
					item2->pos.z_rot = 0;
					item2->speed = 64;
					item2->fallspeed = (-64 * phd_sin(item2->pos.x_rot)) >> W2V_SHIFT;
					item2->current_anim_state = item2->pos.x_rot;
					item2->goal_anim_state = item2->pos.y_rot;
					item2->required_anim_state = 0;
					AddActiveItem(new_num);
					item2->status = ITEM_INVISIBLE;
					item2->item_flags[0] = 4;
					item2->item_flags[2] = item->item_flags[2];

					if (room[item2->room_number].flags & ROOM_UNDERWATER)
						item2->hit_points = 1;
					else
						item2->hit_points = 3000;
				}
			}

			return;
		}

		oldx = item->pos.x_pos;
		oldy = item->pos.y_pos;
		oldz = item->pos.z_pos;
		item->shade = -0x3DF0;

		if (room[item->room_number].flags & ROOM_UNDERWATER)
		{
			abovewater = 0;
			item->fallspeed += (5 - item->fallspeed) >> 1;
			item->speed -= item->speed >> 2;

			if (item->speed)
			{
				item->pos.z_rot += 182 * ((item->speed >> 4) + 3);

				if (item->required_anim_state)
					item->pos.y_rot += 182 * ((item->speed >> 2) + 3);
				else
					item->pos.x_rot += 182 * ((item->speed >> 2) + 3);
			}
		}
		else
		{
			abovewater = 1;
			item->fallspeed += GrenadeWeight;

			if (GrenadeRotation && item->speed)
			{
				item->pos.z_rot += 182 * ((item->speed >> 2) + 7);

				if (item->required_anim_state)
					item->pos.y_rot += 182 * ((item->speed >> 1) + 7);
				else
					item->pos.x_rot += 182 * ((item->speed >> 1) + 7);
			}
		}

		if (item->speed && abovewater)
		{
			phd_PushUnitMatrix();
			phd_mxptr[M03] = 0;
			phd_mxptr[M13] = 0;
			phd_mxptr[M23] = 0;
			phd_RotYXZ(item->pos.y_rot + 0x8000, item->pos.x_rot, item->pos.z_rot);
			phd_TranslateRel(0, 0, -64);
			x = phd_mxptr[M03] >> W2V_SHIFT;
			y = phd_mxptr[M13] >> W2V_SHIFT;
			z = phd_mxptr[M23] >> W2V_SHIFT;
			phd_PopMatrix();

			TriggerRocketSmoke(item->pos.x_pos + x, item->pos.y_pos + y, item->pos.z_pos + z, -1);
		}

		xv = (item->speed * phd_sin(item->goal_anim_state)) >> W2V_SHIFT;
		yv = item->fallspeed;
		zv = (item->speed * phd_cos(item->goal_anim_state)) >> W2V_SHIFT;
		item->pos.x_pos += xv;
		item->pos.y_pos += yv;
		item->pos.z_pos += zv;

		if (GrenadeOneTouch || item->item_flags[0] == 4)
		{
			room_number = item->room_number;
			floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);

			if (GetHeight(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) < item->pos.y_pos ||
				GetCeiling(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) > item->pos.y_pos)
				item->hit_points = 1;
		}
		else
		{
			yrot = item->pos.y_rot;
			item->pos.y_rot = item->goal_anim_state;
			DoProperDetection(item_number, oldx, oldy, oldz, xv, yv, zv);
			item->goal_anim_state = item->pos.y_rot;
			item->pos.y_rot = yrot;
		}

		room_number = item->room_number;
		GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);

		if (room[room_number].flags & ROOM_UNDERWATER && abovewater)
		{
			splash_setup.x = item->pos.x_pos;
			splash_setup.y = room[room_number].maxceiling;
			splash_setup.z = item->pos.z_pos;
			splash_setup.InnerRad = 32;
			splash_setup.InnerSize = 8;
			splash_setup.InnerRadVel = 320;
			splash_setup.InnerYVel = -40 * item->fallspeed;
			splash_setup.pad1 = 48;
			splash_setup.MiddleRad = 32;
			splash_setup.MiddleSize = 480;
			splash_setup.MiddleYVel = 32;
			splash_setup.MiddleRadVel = -20 * item->fallspeed;
			splash_setup.pad2 = 128;
			splash_setup.OuterRad = 544;
			SetupSplash(&splash_setup);

			if (item->item_flags[0] == 4)
				item->hit_points = 1;
		}

		if (item->item_flags[0] == 4)
			TriggerFireFlame(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, -1, 1);

		exploded = 0;
		rad = 0;

		if (item->hit_points)
		{
			item->hit_points--;

			if (!item->hit_points)
			{
				rad = 2048;
				exploded = 1;
			}
			else if (item->hit_points > 118)
				return;
		}

		if (item->item_flags[0] != 3 || !exploded)
		{
			for (int i = 0; i < 2; i++)
			{
				itemlist = (ITEM_INFO**)&tsv_buffer[0x2000];
				meshlist = (MESH_INFO**)&tsv_buffer[0x3000];
				GetCollidedObjects(item, rad, 1, itemlist, meshlist, 1);

				if (!exploded)
				{
					if (!itemlist[0] && !meshlist[0])
						return;

					exploded = 1;

					if (item->item_flags[0] == 3)
						break;

					rad = 2048;
					continue;
				}

				j = 0;
				target = itemlist[j];

				while (target)
				{
					if (target->object_number >= SMASH_OBJECT1 && target->object_number <= SMASH_OBJECT8)
					{
						TriggerExplosionSparks(target->pos.x_pos, target->pos.y_pos, target->pos.z_pos, 3, -2, 0, target->room_number);
						target->pos.y_pos -= 128;
						TriggerShockwave((PHD_VECTOR*)&target->pos, 0x1300030, 96, 0x18806000, 0);
						target->pos.y_pos += 128;
						ExplodeItemNode(target, 0, 0, 128);
						SmashObject(short(target - items));
						KillItem(short(target - items));
					}
					else if ((target->object_number == SWITCH_TYPE7 || target->object_number == SWITCH_TYPE8) && !(target->flags & IFL_SWITCH_ONESHOT))
					{
						if (!(target->flags & IFL_CODEBITS) || (target->flags & IFL_CODEBITS) == IFL_CODEBITS)
						{
							NumTrigs = (short)GetSwitchTrigger(target, TriggerItems, 1);

							for (int k = NumTrigs - 1; k >= 0; k--)
							{
								AddActiveItem(TriggerItems[k]);
								items[TriggerItems[k]].status = ITEM_ACTIVE;
								items[TriggerItems[k]].flags |= IFL_CODEBITS;
							}
						}
						else
						{
							room_number = target->room_number;
							GetHeight(GetFloor(target->pos.x_pos, target->pos.y_pos - 256, target->pos.z_pos, &room_number),
								target->pos.x_pos, target->pos.y_pos - 256, target->pos.z_pos);
							TestTriggers(trigger_index, 1, target->flags & IFL_CODEBITS);
						}

						if (target->object_number == SWITCH_TYPE7)
							ExplodeItemNode(target, objects[SWITCH_TYPE7].nmeshes - 1, 0, 64);

						AddActiveItem(short(target - items));
						target->status = ITEM_ACTIVE;
						target->flags |= IFL_SWITCH_ONESHOT | IFL_CODEBITS;
					}
					else if (objects[target->object_number].intelligent || target->object_number == LARA)
						DoGrenadeDamageOnBaddie(target, item);

					j++;
					target = itemlist[j];
				}

				j = 0;
				mesh = meshlist[0];

				while (mesh)
				{
					if (mesh->static_number >= trng::GlobTomb4.pBaseCustomize->ShatterInizio && mesh->static_number <= trng::GlobTomb4.pBaseCustomize->ShatterFine)
					{
						skip = false;

						if (mesh->Flags & trng::OCBS_SHATTER_SPECIFIC)
						{
							// e' di tipo shatter specific. scoprire se granata era stata lanciata da lara o da sas
							// in edi record di granata
							if (item->item_flags[2] == 1)
							{
								// sas spara
								trng::ResultCheckSpecific = trng::CheckShatterSpecific(GRENADE, false);
							}
							else
								trng::ResultCheckSpecific = trng::CheckShatterSpecific(LARA, true);

							if (!trng::ResultCheckSpecific)
							{
								// saltare al next
								skip = true;
							}
						}

						if (!skip)
						{
							Log(0, "Shatter");
							TriggerExplosionSparks(mesh->x, mesh->y, mesh->z, 3, -2, 0, item->room_number);
							mesh->y -= 128;
							TriggerShockwave((PHD_VECTOR*)&mesh->x, 0xB00028, 64, 0x10806000, 0);
							mesh->y += 128;
							ShatterObject(0, mesh, -128, item->room_number, 0);
							SmashedMeshRoom[SmashedMeshCount] = item->room_number;
							SmashedMesh[SmashedMeshCount] = mesh;
							SmashedMeshCount++;
							mesh->Flags &= ~1;
						}
					}

					j++;
					mesh = meshlist[j];
				}
			}

			if (!exploded)
				return;
		}

		if (item->item_flags[0] == 3)
		{
			FlashFader = 32;
			FlashFadeR = 255;
			FlashFadeG = 255;
			FlashFadeB = 255;

			if (IsVolumetric())
			{
				FlashFader = 0;
				TriggerFXFogBulb(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 4096, 255, 255, 255, 255, item->room_number);
			}

			TriggerFlashSmoke(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
			TriggerFlashSmoke(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
		}
		else if (room[item->room_number].flags & ROOM_UNDERWATER)
			TriggerUnderwaterExplosion(item, 0);
		else
		{
			item->pos.y_pos -= 128;
			TriggerShockwave((PHD_VECTOR*)&item->pos, 0x1300030, 96, 0x18806000, 0);
			item->pos.y_pos += 128;
			TriggerExplosionSparks(oldx, oldy, oldz, 3, -2, 0, item->room_number);

			for (int i = 0; i < 2; i++)
				TriggerExplosionSparks(oldx, oldy, oldz, 3, -1, 0, item->room_number);
		}

		AlertNearbyGuards(item);
		SoundEffect(SFX_EXPLOSION1, &item->pos, 0x1800004);
		SoundEffect(SFX_EXPLOSION2, &item->pos, 0);

		if (item->item_flags[0] == 1 || item->item_flags[0] == 4)
			KillItem(item_number);
		else
		{
			item->mesh_bits = 0;

			if (item->item_flags[0] == 2)
				item->item_flags[1] = 4;
			else
				item->item_flags[1] = 16;
		}
	}

	void DoGrenadeDamageOnBaddie(ITEM_INFO* baddie, ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Lara1Gun(bool replace)
{
	ProcessInject(0x42B080, (unsigned int)tomb4::TriggerUnderwaterExplosion, false);
	ProcessInject(0x42AC40, (unsigned int)tomb4::undraw_shotgun, replace);
	ProcessInject(0x428B20, (unsigned int)tomb4::undraw_shotgun_meshes, false);
	ProcessInject(0x4293B0, (unsigned int)tomb4::ControlGrenade, replace);
	ProcessInject(0x42B250, (unsigned int)tomb4::DoGrenadeDamageOnBaddie, false);
}
