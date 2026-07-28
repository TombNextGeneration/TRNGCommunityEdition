#include "spotcam.h"
#include <cmath>
#include "../../inject.h"
#include "lara.h"
#include "../specific/3dmath.h"
#include "../specific/input.h"
#include "gameflow.h"
#include "camera.h"
#include "control.h"
#include "switch.h"
#include "tomb4fx.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../trng/zRoomEditor.h"
#include "../../flep/PlugIn_trng.h"
#include "../../flep/structures_mine.h"
#include "../../flep/patches/quakecam.h"
#include "../../plugin/flycheat/trng.h"
#include "../../plugin/flycheat/PlugIn_trng.h"

namespace tomb4
{
	static long &LaraHealth = *reinterpret_cast<decltype(&LaraHealth)>(0x7F6DB0);
	static long &LaraAir = *reinterpret_cast<decltype(&LaraAir)>(0x7F5948);
	static short &first_camera = *reinterpret_cast<decltype(&first_camera)>(0x7F6DB4);
	static short &current_camera_cnt = *reinterpret_cast<decltype(&current_camera_cnt)>(0x7F5620);
	static long &current_spline_position = *reinterpret_cast<decltype(&current_spline_position)>(0x7F6DB8);
	static long (&camera_xposition)[18] = *reinterpret_cast<decltype(&camera_xposition)>(0x7F5720);
	static long (&camera_yposition)[18] = *reinterpret_cast<decltype(&camera_yposition)>(0x7F58A0);
	static long (&camera_zposition)[18] = *reinterpret_cast<decltype(&camera_zposition)>(0x7F57E0);
	static long (&camera_xtarget)[18] = *reinterpret_cast<decltype(&camera_xtarget)>(0x7F56C0);
	static long (&camera_ytarget)[18] = *reinterpret_cast<decltype(&camera_ytarget)>(0x7F6D60);
	static long (&camera_ztarget)[18] = *reinterpret_cast<decltype(&camera_ztarget)>(0x7F5840);
	static long (&camera_speed)[18] = *reinterpret_cast<decltype(&camera_speed)>(0x7F5900);
	static long (&camera_roll)[18] = *reinterpret_cast<decltype(&camera_roll)>(0x7F5780);
	static long (&camera_fov)[18] = *reinterpret_cast<decltype(&camera_fov)>(0x7F5660);
	static short &current_spline_camera = *reinterpret_cast<decltype(&current_spline_camera)>(0x7F57D0);
	static long &CameraFade = *reinterpret_cast<decltype(&CameraFade)>(0x7F564C);
	static short &spotcam_timer = *reinterpret_cast<decltype(&spotcam_timer)>(0x4BF5B0);
	static short &last_camera = *reinterpret_cast<decltype(&last_camera)>(0x7F594C);
	static long &spline_from_camera = *reinterpret_cast<decltype(&spline_from_camera)>(0x7F56BC);
	static PHD_VECTOR &LaraFixedPosition = *reinterpret_cast<decltype(&LaraFixedPosition)>(0x7F5640);
	static short &spotcam_loopcnt = *reinterpret_cast<decltype(&spotcam_loopcnt)>(0x7F5768);
	static long &spline_to_camera = *reinterpret_cast<decltype(&spline_to_camera)>(0x7F576C);

	short &number_spotcams = *reinterpret_cast<decltype(&number_spotcams)>(0x7F5708);
	SPOTCAM (&SpotCam)[320] = *reinterpret_cast<decltype(&SpotCam)>(0x45F764);
	long &bUseSpotCam = *reinterpret_cast<decltype(&bUseSpotCam)>(0x4BF5BC);
	long &bDisableLaraControl = *reinterpret_cast<decltype(&bDisableLaraControl)>(0x4BF5C0);
	long &bTrackCamInit = *reinterpret_cast<decltype(&bTrackCamInit)>(0x4BF5B4);
	short &CurrentFov = *reinterpret_cast<decltype(&CurrentFov)>(0x7F57D4);
	short &LastSequence = *reinterpret_cast<decltype(&LastSequence)>(0x7F6DBC);
	long &bCheckTrigger = *reinterpret_cast<decltype(&bCheckTrigger)>(0x4BF5B8);
	PHD_VECTOR &InitialCameraPosition = *reinterpret_cast<decltype(&InitialCameraPosition)>(0x7F56B0);
	PHD_VECTOR &InitialCameraTarget = *reinterpret_cast<decltype(&InitialCameraTarget)>(0x7F5630);
	short &InitialCameraRoom = *reinterpret_cast<decltype(&InitialCameraRoom)>(0x7F5828);
	short &LastFov = *reinterpret_cast<decltype(&LastFov)>(0x7F57D6);
	uchar &spotcam_screen_height = *reinterpret_cast<decltype(&spotcam_screen_height)>(0x46047A);

	void CalculateSpotCams()
	{
		static long bFirstLook;

		SPOTCAM* FirstCam;
		SPOTCAM* CurrentCam;
		ITEM_INFO* item;
		CAMERA_INFO backup;
		camera_type ctype;
		long cpx, cpy, cpz, ctx, cty, ctz, cspeed, cfov, croll, next_spline_camera, cunt;
		long cs, cp, clen, tlen, cx, cy, cz, lx, ly, lz, sp;
		short spline_cnt;

		trng::RetValue = trng::PerformInFlyBy();

		if (!trng::RetValue)
			trng::RetValue = trng::ControllaEscapeFlyBy();

		if (trng::RetValue)
			return;

		if (bDisableLaraControl)
		{
			lara_item->hit_points = (short)LaraHealth;
			lara.air = (short)LaraAir;
		}

		FirstCam = &SpotCam[first_camera];

		if (FirstCam->flags & 8)
			spline_cnt = current_camera_cnt + 2;
		else
			spline_cnt = 4;

		cpx = Spline(current_spline_position, camera_xposition, spline_cnt);
		cpy = Spline(current_spline_position, camera_yposition, spline_cnt);
		cpz = Spline(current_spline_position, camera_zposition, spline_cnt);
		ctx = Spline(current_spline_position, camera_xtarget, spline_cnt);
		cty = Spline(current_spline_position, camera_ytarget, spline_cnt);
		ctz = Spline(current_spline_position, camera_ztarget, spline_cnt);
		cspeed = Spline(current_spline_position, camera_speed, spline_cnt);
		croll = Spline(current_spline_position, camera_roll, spline_cnt);
		cfov = Spline(current_spline_position, camera_fov, spline_cnt);
		CurrentCam = &SpotCam[current_spline_camera];

		if (CurrentCam->flags & 0x1000 && CameraFade != current_spline_camera)
			CameraFade = current_spline_camera;

		if (CurrentCam->flags & 0x2000 && CameraFade != current_spline_camera)
			CameraFade = current_spline_camera;

		if (FirstCam->flags & 8)
		{
			sp = 0;
			cp = 0;
			cs = 0x2000;
			lx = lara_item->pos.x_pos;
			ly = lara_item->pos.y_pos;
			lz = lara_item->pos.z_pos;

			for (int i = 0; i < 8; i++)
			{
				tlen = 0x10000;

				for (int j = 0; j < 8; j++)
				{
					cx = Spline(sp, camera_xposition, spline_cnt) - lx;
					cy = Spline(sp, camera_yposition, spline_cnt) - ly;
					cz = Spline(sp, camera_zposition, spline_cnt) - lz;
					clen = phd_sqrt(cx * cx + cy * cy + cz * cz);

					if (clen <= tlen)
					{
						cp = sp;
						tlen = clen;
					}

					sp += cs;

					if (sp > 0x10000)
						break;
				}

				cs >>= 1;
				sp = cp - ((cs & -2) << 1);

				if (sp < 0)
					sp = 0;
			}

			current_spline_position += (cp - current_spline_position) >> 5;

			if (FirstCam->flags & 1)
			{
				if (abs(cp - current_spline_position) > 0x8000)
					current_spline_position = cp;
			}

			if (current_spline_position < 0)
				current_spline_position = 0;
			else if (current_spline_position > 0x10000)
				current_spline_position = 0x10000;
		}
		else if (!spotcam_timer)
			current_spline_position += cspeed;

		if (plugin::flycheat::Trng.IdMyPlugin != -1 && gfCurrentLevel && plugin::flycheat::State[plugin::flycheat::COMMAND_SPOT_CAMS])
			current_spline_position = 0x10000;

		if (!(input & IN_LOOK))
			bFirstLook = 0;

		if (FirstCam->flags & 0x200 || !(input & IN_LOOK) || gfGameMode == 1)
		{
			camera.pos.x = cpx;
			camera.pos.y = cpy;
			camera.pos.z = cpz;

			if (FirstCam->flags & 0x28)
			{
				ctx = lara_item->pos.x_pos;
				cty = lara_item->pos.y_pos;
				ctz = lara_item->pos.z_pos;
			}

			if (CurrentCam->flags & 2)
			{
				item = &items[CurrentCam->timer];

				if (item)
				{
					ctx = item->pos.x_pos;
					cty = item->pos.y_pos;
					ctz = item->pos.z_pos;
				}
			}

			camera.target.x = ctx;
			camera.target.y = cty;
			camera.target.z = ctz;

			if (IsRoomOutside(cpx, cpy, cpz) == -2)
			{
				camera.pos.room_number = CurrentCam->room_number;
				GetFloor(camera.pos.x, camera.pos.y, camera.pos.z, &camera.pos.room_number);
			}
			else
				camera.pos.room_number = IsRoomOutsideNo;

			if (flep::pPatchMap[flep::PATCH_QUAKE_CAMERA])
				flep::do_spotcam_bounce();

			AlterFOV((short)cfov);
			phd_LookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.target.x, camera.target.y, camera.target.z, (short)croll);

			if (bCheckTrigger)
			{
				ctype = camera.type;
				camera.type = HEAVY_CAMERA;

				if (gfCurrentLevel)
					TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
				else
				{
					TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 0, 0);
					TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
				}

				camera.type = ctype;
				bCheckTrigger = 0;
			}

			if (FirstCam->flags & 8)
				bTrackCamInit = 1;
			else if (current_spline_position > 0x10000 - cspeed)
			{
				next_spline_camera = current_spline_camera;

				if (CurrentCam->flags & 0x4000)
					bCheckTrigger = 1;

				if (CurrentCam->flags & 0x100)
				{
					if (spotcam_timer)
						spotcam_timer--;
					else
						spotcam_timer = CurrentCam->timer >> 4;
				}

				if (!spotcam_timer)
				{
					current_spline_position = 0;

					if (current_spline_camera == first_camera)
						next_spline_camera = last_camera;
					else
						next_spline_camera--;

					cunt = 1;

					if (spline_from_camera)
					{
						spline_from_camera = 0;
						next_spline_camera = first_camera - 1;
					}
					else
					{
						if (CurrentCam->flags & 0x800)
							bDisableLaraControl = 0;

						if (CurrentCam->flags & 0x400)
						{
							SetFadeClip(spotcam_screen_height, 1);
							bDisableLaraControl = 1;
						}

						cunt = 0;

						if (CurrentCam->flags & 0x80)
						{
							next_spline_camera = first_camera + (CurrentCam->timer & 0xF);
							current_spline_camera = (short)next_spline_camera;
							SetSplineData(cunt, next_spline_camera);	//INLINED
							cunt = 1;
						}

						SetSplineData(cunt, next_spline_camera);	//INLINED
						cunt++;
					}

					next_spline_camera++;

					while (cunt < 4)
					{
						if (FirstCam->flags & 4)
						{
							if (next_spline_camera > last_camera)
								next_spline_camera = first_camera;
						}
						else if (next_spline_camera > last_camera)
							next_spline_camera = last_camera;

						SetSplineData(cunt, next_spline_camera);	//INLINED
						next_spline_camera++;
						cunt++;
					}

					current_spline_camera++;

					if (current_spline_camera > last_camera)
					{
						if (FirstCam->flags & 4)
						{
							spotcam_loopcnt++;
							current_spline_camera = first_camera;
						}
						else if (FirstCam->flags & 0x40 || spline_to_camera)
						{
							if (bCheckTrigger)
							{
								ctype = camera.type;
								camera.type = HEAVY_CAMERA;

								if (gfCurrentLevel)
									TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
								else
								{
									TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 0, 0);
									TestTriggersAtXYZ(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number, 1, 0);
								}

								camera.type = ctype;
								bCheckTrigger = 0;
							}

							SetFadeClip(0, 1);
							bUseSpotCam = 0;
							bDisableLaraControl = 0;
							bCheckTrigger = 0;
							camera.old_type = FIXED_CAMERA;
							camera.type = CHASE_CAMERA;
							camera.speed = 1;

							if (FirstCam->flags & 0x40)
							{
								camera.pos.x = InitialCameraPosition.x;
								camera.pos.y = InitialCameraPosition.y;
								camera.pos.z = InitialCameraPosition.z;
								camera.target.x = InitialCameraTarget.x;
								camera.target.y = InitialCameraTarget.y;
								camera.target.z = InitialCameraTarget.z;
								camera.pos.room_number = InitialCameraRoom;
							}

							AlterFOV(LastFov);
						}
						else
						{
							current_spline_camera--;
							SetSplineData(0, current_spline_camera - 1);	//both INLINEDDDDDDDDD
							SetSplineData(1, current_spline_camera);
							memcpy(&backup, &camera, sizeof(CAMERA_INFO));
							camera.old_type = FIXED_CAMERA;
							camera.type = CHASE_CAMERA;
							camera.speed = 1;
							CalculateCamera();
							InitialCameraPosition.x = camera.pos.x;
							InitialCameraPosition.y = camera.pos.y;
							InitialCameraPosition.z = camera.pos.z;
							InitialCameraTarget.x = camera.target.x;
							InitialCameraTarget.y = camera.target.y;
							InitialCameraTarget.z = camera.target.z;
							camera_xposition[2] = camera.pos.x;
							camera_yposition[2] = camera.pos.y;
							camera_zposition[2] = camera.pos.z;
							camera_xtarget[2] = camera.target.x;
							camera_ytarget[2] = camera.target.y;
							camera_ztarget[2] = camera.target.z;
							camera_roll[2] = 0;
							camera_fov[2] = CurrentFov;
							camera_speed[2] = camera_speed[1];
							camera_xposition[3] = camera.pos.x;
							camera_yposition[3] = camera.pos.y;
							camera_zposition[3] = camera.pos.z;
							camera_xtarget[3] = camera.target.x;
							camera_ytarget[3] = camera.target.y;
							camera_ztarget[3] = camera.target.z;
							camera_roll[3] = 0;
							camera_fov[3] = CurrentFov;
							camera_speed[3] = camera_speed[1] >> 1;
							memcpy(&camera, &backup, sizeof(CAMERA_INFO));
							phd_LookAt(backup.pos.x, backup.pos.y, backup.pos.z, backup.target.x, backup.target.y, backup.target.z, (short)croll);
							spline_to_camera = 1;
						}
					}
				}
			}
		}
		else if (FirstCam->flags & 8)
		{
			if (!bFirstLook)
			{
				camera.old_type = FIXED_CAMERA;
				bFirstLook = 1;
			}

			CalculateCamera();
		}
		else
		{
			SetFadeClip(0, 1);
			bUseSpotCam = 0;
			bDisableLaraControl = 0;
			camera.speed = 1;
			AlterFOV(LastFov);
			CalculateCamera();
			bCheckTrigger = 0;
		}
	}

	long Spline(long x, long* knots, long nk)
	{
		long* k;
		long span, c1, c2;

		span = x * (nk - 3) >> 16;

		if (span >= nk - 3)
			span = nk - 4;

		k = &knots[span];
		c1 = x * (nk - 3) - span * 65536;
		c2 = (__int64)((k[1] >> 1) - (k[2] >> 1) - k[2] + k[1] + (k[3] >> 1) + ((-k[0] - 1) >> 1)) * c1 >> 16;
		c2 = (__int64)(c2 - 2 * k[1] + 2 * k[2] - (k[1] >> 1) - (k[3] >> 1) + k[0]) * c1 >> 16;
		c2 = (__int64)(c2 + (k[2] >> 1) + ((-k[0] - 1) >> 1)) * c1 >> 16;
		return c2 + k[1];
	}

	void SetSplineData(long num, long cam)
	{
		SPOTCAM* spotcam;
		ITEM_INFO* item;

		spotcam = &SpotCam[cam];

		camera_xposition[num] = spotcam->x;
		camera_yposition[num] = spotcam->y;
		camera_zposition[num] = spotcam->z;
		camera_xtarget[num] = spotcam->tx;
		camera_ytarget[num] = spotcam->ty;
		camera_ztarget[num] = spotcam->tz;

		if (spotcam->flags & 0x10)
		{
			camera_xtarget[num] = LaraFixedPosition.x;
			camera_ytarget[num] = LaraFixedPosition.y;
			camera_ztarget[num] = LaraFixedPosition.z;
		}
		else//useless
		{
			camera_xtarget[num] = spotcam->tx;
			camera_ytarget[num] = spotcam->ty;
			camera_ztarget[num] = spotcam->tz;
		}

		if (spotcam->flags & 2)
		{
			item = &items[spotcam->timer];

			if (item)
			{
				camera_xtarget[num] = item->pos.x_pos;
				camera_ytarget[num] = item->pos.y_pos;
				camera_ztarget[num] = item->pos.z_pos;
			}
		}

		camera_roll[num] = spotcam->roll;
		camera_speed[num] = spotcam->speed;
		camera_fov[num] = spotcam->fov;
	}

	void InitialiseSpotCam(short Sequence)
	{
		__try { throw __func__; } __finally {}
	}
}

__declspec(naked) static void** Inject_Spotcam_SpotCam() { __asm lea eax, [tomb4::SpotCam] __asm ret }

void Inject_Spotcam(bool replace)
{
	IndirectReferenceInject(Inject_Spotcam_SpotCam());

	ProcessInject(0x45FE50, (unsigned int)tomb4::CalculateSpotCams, replace);
	ProcessInject(0x45F500, (unsigned int)tomb4::Spline, replace);
	ProcessInject(0x45FD30, (unsigned int)tomb4::SetSplineData, replace);
	ProcessInject(0x45F600, (unsigned int)tomb4::InitialiseSpotCam, false);
}
