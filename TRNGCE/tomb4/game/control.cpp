#include "control.h"
#include "../../inject.h"
#include "pickup.h"
#include "spotcam.h"
#include "../specific/function_stubs.h"
#include "../specific/input.h"
#include "gameflow.h"
#include "deltapak.h"
#include "newinv.h"
#include "lara.h"
#include "tomb4fx.h"
#include "../specific/LoadSave.h"
#include "../specific/gamemain.h"
#include "camera.h"
#include "../specific/3dmath.h"
#include "effect2.h"
#include "sphere.h"
#include "items.h"
#include "objects.h"
#include "effects.h"
#include "box.h"
#include "laramisc.h"
#include "sound.h"
#include "hair.h"
#include "voncroy.h"
#include "debris.h"
#include "scarab.h"
#include "croc.h"
#include "text.h"
#include "effects.h"
#include "health.h"
#include "savegame.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	static short &cdtrack = *reinterpret_cast<decltype(&cdtrack)>(0x4ACC00);

	short** &meshes = *reinterpret_cast<decltype(&meshes)>(0x533950);
	ANIM_STRUCT* &anims = *reinterpret_cast<decltype(&anims)>(0x533938);
	long* &bones = *reinterpret_cast<decltype(&bones)>(0x533958);
	ulong &FmvSceneTriggered = *reinterpret_cast<decltype(&FmvSceneTriggered)>(0x7FE0F0);
//	long (*&flip_stats)[32] = *reinterpret_cast<decltype(&flip_stats)>(0x4598AF);
//	long (*&flipmap)[32] = *reinterpret_cast<decltype(&flipmap)>(0x4598D8);
	long &flipeffect = *reinterpret_cast<decltype(&flipeffect)>(0x4ACBFC);
	long &fliptimer = *reinterpret_cast<decltype(&fliptimer)>(0x4BF2E8);
	long &flip_status = *reinterpret_cast<decltype(&flip_status)>(0x7FE0F8);
	char (&cd_flags)[128] = *reinterpret_cast<decltype(&cd_flags)>(0x7FE060);
	uchar &CurrentAtmosphere = *reinterpret_cast<decltype(&CurrentAtmosphere)>(0x7FE0FC);
	short &number_rooms = *reinterpret_cast<decltype(&number_rooms)>(0x53392C);
	ROOM_INFO* &room = *reinterpret_cast<decltype(&room)>(0x533934);
	long &level_items = *reinterpret_cast<decltype(&level_items)>(0x4BF564);
	ITEM_INFO* &items = *reinterpret_cast<decltype(&items)>(0x7FE16C);
	long &height_type = *reinterpret_cast<decltype(&height_type)>(0x7FE170);
	long &OnObject = *reinterpret_cast<decltype(&OnObject)>(0x7FE0E0);
	long &tiltyoff = *reinterpret_cast<decltype(&tiltyoff)>(0x7FE0F4);
	long &tiltxoff = *reinterpret_cast<decltype(&tiltxoff)>(0x7FE0EC);
	short (&SmashedMeshRoom)[16] = *reinterpret_cast<decltype(&SmashedMeshRoom)>(0x7FE240);
	MESH_INFO* (&SmashedMesh)[16] = *reinterpret_cast<decltype(&SmashedMesh)>(0x7FE680);
	short &SmashedMeshCount = *reinterpret_cast<decltype(&SmashedMeshCount)>(0x4BF2D6);
	uchar &IsAtmospherePlaying = *reinterpret_cast<decltype(&IsAtmospherePlaying)>(0x7FE1C4);
	uchar &InItemControlLoop = *reinterpret_cast<decltype(&InItemControlLoop)>(0x4BF2CD);
	long &SetDebounce = *reinterpret_cast<decltype(&SetDebounce)>(0x7FE040);
	long &framecount = *reinterpret_cast<decltype(&framecount)>(0x4BF2F8);
	ushort &GlobalCounter = *reinterpret_cast<decltype(&GlobalCounter)>(0x4BF2D2);
	long &reset_flag = *reinterpret_cast<decltype(&reset_flag)>(0x4BF2EC);
	uchar &WeaponDelay = *reinterpret_cast<decltype(&WeaponDelay)>(0x4BF2CC);
	short &XSoff1 = *reinterpret_cast<decltype(&XSoff1)>(0x753BD4);
	short &YSoff1 = *reinterpret_cast<decltype(&YSoff1)>(0x753BE4);
	short &ZSoff1 = *reinterpret_cast<decltype(&ZSoff1)>(0x753C14);
	short &XSoff2 = *reinterpret_cast<decltype(&XSoff2)>(0x753BD0);
	short &YSoff2 = *reinterpret_cast<decltype(&YSoff2)>(0x753BE8);
	short &ZSoff2 = *reinterpret_cast<decltype(&ZSoff2)>(0x753C18);
	char &PoisonFlag = *reinterpret_cast<decltype(&PoisonFlag)>(0x7FD0F4);
	short* &trigger_index = *reinterpret_cast<decltype(&trigger_index)>(0x7FE128);

	long ControlPhase(long nframes, long demo_mode)
	{
		ITEM_INFO* item;
		FX_INFO* fx;
		FLOOR_INFO* floor;
		MESH_INFO* mesh;
		short item_num, nex, fx_num;

		RegeneratePickups();

		if (nframes > 10)
			nframes = 10;

		if (bTrackCamInit)
			bUseSpotCam = 0;

		SetDebounce = 1;

		for (framecount += nframes; framecount > 0; framecount -= 2)
		{
			GlobalCounter++;
			trng::InizioCiclo();
			UpdateSky();

			if (cdtrack > 0)
				S_CDLoop();

			if (S_UpdateInput() == IN_ALL)
				return 0;

			if (bDisableLaraControl)
			{
				if (gfCurrentLevel)
					dbinput = 0;

				input &= IN_LOOK;
			}

			if (cutseq_trig)
			{
				input = 0;

				if (cutseq_num == 27)
					input = IN_ACTION;
			}

			SetDebounce = 0;

			if (gfCurrentLevel && (dbinput & IN_OPTION || GLOBAL_enterinventory != -1) && !cutseq_trig && lara_item->hit_points > 0)
			{
				if (S_CallInventory2())
					return 2;
			}

			if (gfLevelComplete)
				return 3;

			if (reset_flag || lara.death_count > 300 || lara.death_count > 60 && input)
			{
				if (Gameflow->DemoDisc && reset_flag)
				{
					reset_flag = 0;
					return 4;
				}

				reset_flag = 0;
				return 1;
			}

			if (demo_mode && input == IN_ALL)
				input = 0;

			if (!FadeScreenHeight)
			{
				if (input & IN_SAVE)
					S_LoadSave(IN_SAVE, 0);
				else if (input & IN_LOAD)
				{
					if (S_LoadSave(IN_LOAD, 0) >= 0)
						return 2;
				}

				if (input & IN_PAUSE && !gfGameMode)
				{
					if (S_PauseMenu() == 8)
						return 1;
				}
			}

			if (MainThread.ended)
				return 4;

			if (input & IN_LOOK && (lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH ||
				(lara.IsDucked && !(input & IN_DUCK) && lara_item->anim_number == ANIM_DUCKBREATHE && lara_item->goal_anim_state == AS_DUCK)))
			{
				if (!BinocularRange)
				{
					if (lara.gun_type == WEAPON_REVOLVER)
					{
						if (lara.sixshooter_type_carried & 4 && lara.gun_status == LG_READY)
						{
							BinocularRange = 128;
							BinocularOldCamera = camera.old_type;
							lara.Busy = 1;
							LaserSight = 1;
						}
					}
					else if (lara.gun_type == WEAPON_CROSSBOW && lara.crossbow_type_carried & 4 && lara.gun_status == LG_READY)
					{
						BinocularRange = 128;
						BinocularOldCamera = camera.old_type;
						lara.Busy = 1;
						LaserSight = 1;
					}
				}
			}
			else if (BinocularRange)
			{
				if (LaserSight)
				{
					BinocularRange = 0;
					LaserSight = 0;
					AlterFOV(14560);
					lara_item->mesh_bits = -1;
					lara.Busy = 0;
					camera.type = BinocularOldCamera;
					lara.head_y_rot = 0;
					lara.head_x_rot = 0;
					lara.torso_y_rot = 0;
					lara.torso_x_rot = 0;
					BinocularOn = -8;
				}
				else
					input |= IN_LOOK;
			}

			ClearDynamics();
			ClearFires();
			GotLaraSpheres = 0;
			InItemControlLoop = 1;
			item_num = next_item_active;

			while (item_num != -1)
			{
				item = &items[item_num];
				nex = item->next_active;

				if (item->after_death < 128)
				{
					if (objects[item->object_number].control)
						objects[item->object_number].control(item_num);
				}
				else
					KillItem(item_num);

				item_num = nex;
			}

			InItemControlLoop = 0;
			KillMoveItems();
			InItemControlLoop = 1;
			fx_num = next_fx_active;

			while (fx_num != -1)
			{
				fx = &effects[fx_num];
				nex = fx->next_active;

				if (objects[fx->object_number].control)
					objects[fx->object_number].control(fx_num);

				fx_num = nex;
			}

			InItemControlLoop = 0;
			KillMoveEffects();

			if (KillEverythingFlag)
				KillEverything();

			if (SmokeCountL)
				SmokeCountL--;

			if (SmokeCountR)
				SmokeCountR--;

			if (SplashCount)
				SplashCount--;

			if (WeaponDelay)
				WeaponDelay--;

			if (lara.blindTimer)
				lara.blindTimer--;

			if (lara.has_fired && !(wibble & 0x7F))
			{
				AlertNearbyGuards(lara_item);
				lara.has_fired = 0;
			}

			XSoff1 += 150;
			YSoff1 += 230;
			ZSoff1 += 660;
			XSoff2 += 270;
			YSoff2 += 440;
			ZSoff2 += 160;

			if (lara.poisoned && !GLOBAL_playing_cutseq)
			{
				if (lara.poisoned > 4096)
					lara.poisoned = 4096;
				else if (lara.dpoisoned)
					lara.dpoisoned++;

				if (lara.poisoned >= 256 && !(wibble & 0xFF))
				{
					lara_item->hit_points -= lara.poisoned >> 8;
					PoisonFlag = 16;
				}
			}

			InItemControlLoop = 1;

			if (!GLOBAL_playing_cutseq && !gfGameMode)
				LaraControl(0);

			InItemControlLoop = 0;

			while (SmashedMeshCount)
			{
				SmashedMeshCount--;
				mesh = SmashedMesh[SmashedMeshCount];
				floor = GetFloor(mesh->x, mesh->y, mesh->z, &SmashedMeshRoom[SmashedMeshCount]);
				GetHeight(floor, mesh->x, mesh->y, mesh->z);
				TestTriggers(trigger_index, 1, 0);
				floor->stopper = 0;
				SmashedMesh[SmashedMeshCount] = 0;
			}

			KillMoveItems();

			if (GLOBAL_inventoryitemchosen != -1)
			{
				SayNo();
				GLOBAL_inventoryitemchosen = -1;
			}

			if (!GLOBAL_playing_cutseq)
			{
				HairControl(0, 0, 0);

				if (gfLevelFlags & GF_YOUNGLARA)
					HairControl(0, 1, 0);
			}

			if (!GLOBAL_playing_cutseq)
			{
				if (bUseSpotCam)
					CalculateSpotCams();
				else if (!bVoncroyCutScene)
					CalculateCamera();
			}
			else
			{
				camera.type = CINEMATIC_CAMERA;
				CalculateCamera();
			}

			CamRot.y = (mGetAngle(camera.pos.z, camera.pos.x, camera.target.z, camera.target.x) >> 4) & 0xFFF;
			wibble = (wibble + 4) & 0xFC;
			TriggerLaraDrips();
			UpdateSparks();
			UpdateFireSparks();
			UpdateSmokeSparks();
			UpdateBubbles();
			UpdateSplashes();
			UpdateDebris();
			UpdateBlood();
			UpdateDrips();
			UpdateGunShells();
			UpdateScarabs();
			UpdateLocusts();
			UpdateShockwaves();
			UpdateLightning();
			AnimateWaterfalls();
			UpdatePulseColour();
			SoundEffects();
			health_bar_timer--;

			if (!gfGameMode)
			{
				GameTimer++;

				if (savegame.Level.Timer)
				{
					if (!GLOBAL_playing_cutseq)
						savegame.Level.Timer++;
				}
			}

			UpdateFadeClip();
		}

		return 0;
	}

	void UpdateSky()
	{
		__try { throw __func__; } __finally {}
	}

	void KillMoveItems()
	{
		__try { throw __func__; } __finally {}
	}

	void KillMoveEffects()
	{
		__try { throw __func__; } __finally {}
	}

	FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number)
	{
		__try { throw __func__; } __finally {}
	}

	long GetHeight(FLOOR_INFO* floor, long x, long y, long z)
	{
		__try { throw __func__; } __finally {}
	}

	void TestTriggers(short* data, long heavy, long HeavyFlags)
	{
		__try { throw __func__; } __finally {}
	}

	void RefreshCamera(short type, short* data)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Control(bool replace)
{
	ProcessInject(0x448B10, (unsigned int)tomb4::ControlPhase, replace);
	ProcessInject(0x448A90, (unsigned int)tomb4::UpdateSky, false);
	ProcessInject(0x4489D0, (unsigned int)tomb4::KillMoveItems, false);
	ProcessInject(0x448A30, (unsigned int)tomb4::KillMoveEffects, false);
	ProcessInject(0x449880, (unsigned int)tomb4::GetFloor, false);
	ProcessInject(0x449BD0, (unsigned int)tomb4::GetHeight, false);
	ProcessInject(0x44A1F0, (unsigned int)tomb4::TestTriggers, false);
	ProcessInject(0x44A0C0, (unsigned int)tomb4::RefreshCamera, false);
}
