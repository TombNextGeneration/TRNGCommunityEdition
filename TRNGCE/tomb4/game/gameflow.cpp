#include "gameflow.h"
#include "../../inject.h"
#include "../specific/output.h"
#include "camera.h"
#include "savegame.h"
#include "draw.h"
#include "newinv.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "text.h"
#include "../../flep/PlugIn_trng.h"
#include "../../flep/structures_mine.h"

namespace tomb4
{
	static char &num_fmvs = *reinterpret_cast<decltype(&num_fmvs)>(0x4BF535);
	static char (&fmv_to_play)[2] = *reinterpret_cast<decltype(&fmv_to_play)>(0x4BF536);
	static ushort* &gfScriptOffset = *reinterpret_cast<decltype(&gfScriptOffset)>(0x4BF524);
	static uchar* &gfScriptWad = *reinterpret_cast<decltype(&gfScriptWad)>(0x4BF530);
	static uchar &gfLegendTime = *reinterpret_cast<decltype(&gfLegendTime)>(0x4BF53C);
	static uchar (&gfResidentCut)[4] = *reinterpret_cast<decltype(&gfResidentCut)>(0x7FD134);
	static uchar &gfInitialiseGame = *reinterpret_cast<decltype(&gfInitialiseGame)>(0x4AD43A);
	static uchar &gfResetHubDest = *reinterpret_cast<decltype(&gfResetHubDest)>(0x7FD168);
	static uchar &gfCutNumber = *reinterpret_cast<decltype(&gfCutNumber)>(0x4BF53E);
	static uchar &gfLegend = *reinterpret_cast<decltype(&gfLegend)>(0x7FD1C8);

	uchar &gfCurrentLevel = *reinterpret_cast<decltype(&gfCurrentLevel)>(0x7FD170);
	ushort &gfLevelFlags = *reinterpret_cast<decltype(&gfLevelFlags)>(0x7FD140);
	uchar &gfGameMode = *reinterpret_cast<decltype(&gfGameMode)>(0x4AD439);
	CVECTOR &gfLayer1Col = *reinterpret_cast<decltype(&gfLayer1Col)>(0x7FD144);
	CVECTOR &gfLayer2Col = *reinterpret_cast<decltype(&gfLayer2Col)>(0x7FD13C);
	char &gfLayer1Vel = *reinterpret_cast<decltype(&gfLayer1Vel)>(0x7FD132);
	char &gfLayer2Vel = *reinterpret_cast<decltype(&gfLayer2Vel)>(0x7FD131);
	uchar &gfLevelComplete = *reinterpret_cast<decltype(&gfLevelComplete)>(0x7FD190);
	ushort* &gfStringOffset = *reinterpret_cast<decltype(&gfStringOffset)>(0x7FD154);
	char* &gfStringWad = *reinterpret_cast<decltype(&gfStringWad)>(0x7FD198);
	GAMEFLOW* &Gameflow = *reinterpret_cast<decltype(&Gameflow)>(0x7FD158);
	long &gfStatus = *reinterpret_cast<decltype(&gfStatus)>(0x4BF528);
	char &gfUVRotate = *reinterpret_cast<decltype(&gfUVRotate)>(0x7FD1C9);
	uchar &gfNumMips = *reinterpret_cast<decltype(&gfNumMips)>(0x4BF53F);
	uchar &gfMirrorRoom = *reinterpret_cast<decltype(&gfMirrorRoom)>(0x7FD130);
	CVECTOR &gfFog = *reinterpret_cast<decltype(&gfFog)>(0x4BF538);
	char &skipped_level = *reinterpret_cast<decltype(&skipped_level)>(0x4BF2A6);
	PHD_VECTOR &gfLensFlare = *reinterpret_cast<decltype(&gfLensFlare)>(0x7FD180);
	CVECTOR &gfLensFlareColour = *reinterpret_cast<decltype(&gfLensFlareColour)>(0x7FD194);
	long &gfMirrorZPlane = *reinterpret_cast<decltype(&gfMirrorZPlane)>(0x7FDE44);
	uchar (&gfMips)[8] = *reinterpret_cast<decltype(&gfMips)>(0x7FD160);
	PHD_VECTOR &gfLoadCam = *reinterpret_cast<decltype(&gfLoadCam)>(0x533978);
	PHD_VECTOR &gfLoadTarget = *reinterpret_cast<decltype(&gfLoadTarget)>(0x533984);
	uchar &gfLoadRoom = *reinterpret_cast<decltype(&gfLoadRoom)>(0x4B0635);
	uchar &gfInitialLegendTime = *reinterpret_cast<decltype(&gfInitialLegendTime)>(0x450F59);
	ulong &GameTimer = *reinterpret_cast<decltype(&GameTimer)>(0x7FD138);
	long &menu_to_display = *reinterpret_cast<decltype(&menu_to_display)>(0x4BF54C);

	void DoGameflow()
	{
		uchar* gf;
		uchar n;

		do_boot_screen(Gameflow->Language);
		num_fmvs = 0;
		fmv_to_play[0] = 0;
		fmv_to_play[1] = 0;

		if (flep::pPatchMap[flep::PATCH_24_SAVEGAME_SLOTS_BUGFIXED])
			small_font_scale = 0.5F;

		gfCurrentLevel = Gameflow->TitleEnabled ? 0 : 1;
		gf = &gfScriptWad[gfScriptOffset[gfCurrentLevel]];
		trng::LeggiNG_ScriptForLevel();

		while (1)
		{
			switch (n = *gf++)
			{
			case CMD_FMV:
				trng::SalvaTagFmv(gf[0]);
				gf++;
				break;

			case CMD_LEVEL:
				gfLevelFlags = gf[1] | (gf[2] << 8);
				trng::ImpostaCapelliLara(&gfLevelFlags);

				if (!(gfLevelFlags & GF_NOLEVEL))
					DoLevel(gf[3], gf[4]);
				else
				{
					gfStatus = 999;
					gfCurrentLevel++;
				}

				gfLegendTime = 0;
				LaserSight = 0;
				BinocularRange = 0;
				gfResidentCut[0] = 0;
				gfResidentCut[1] = 0;
				gfResidentCut[2] = 0;
				gfResidentCut[3] = 0;
				gfUVRotate = 0;
				gfNumMips = 0;
				gfMirrorRoom = uchar(-1);

				if (gfStatus != 3 || gfLevelFlags & GF_RESETHUB && gfLevelComplete == gfResetHubDest || skipped_level)
				{
					gfFog.b = 0;
					gfFog.g = 0;
					gfFog.r = 0;
				}

				gfFog.a = 0;

				switch (gfStatus)
				{
				case 1:
					gfInitialiseGame = 1;
					gfCurrentLevel = Gameflow->TitleEnabled ? 0 : 1;
					break;

				case 2:
					gfGameMode = 4;
					gfCurrentLevel = savegame.CurrentLevel & 0x7F;
					break;

				case 3:

					if (gfLevelFlags & GF_RESETHUB && gfLevelComplete == gfResetHubDest || skipped_level)
					{
						sgInitialiseHub(0);
						skipped_level = 0;
					}
					else
						sgSaveLevel();

					if (Gameflow->DemoDisc || Gameflow->nLevels == 2)
						gfCurrentLevel = 0;
					else
					{
						if (gfLevelComplete > Gameflow->nLevels)
							gfCurrentLevel = 0;
						else
							gfCurrentLevel = gfLevelComplete;
					}

					break;

				case 4:
					return;
				}

				gf = &gfScriptWad[gfScriptOffset[gfCurrentLevel]];
				trng::LeggiNG_ScriptForLevel();
				break;

			case CMD_TITLE:
				gfLevelFlags = gf[0] | (gf[1] << 8);
				trng::ImpostaCapelliLara(&gfLevelFlags);
				DoTitle(gf[2], gf[3]);
				gfResidentCut[0] = 0;
				gfResidentCut[1] = 0;
				gfResidentCut[2] = 0;
				gfResidentCut[3] = 0;
				gfUVRotate = 0;
				gfNumMips = 0;
				gfMirrorRoom = uchar(-1);

				switch (gfStatus)
				{
				case 2:
					gfGameMode = 4;
					gfCurrentLevel = savegame.CurrentLevel & 0x7F;
					break;

				case 3:
					gfGameMode = 0;
					gfCurrentLevel = gfLevelComplete;
					gfInitialiseGame = 1;
					break;

				case 4:
					return;
				}

				gf = &gfScriptWad[gfScriptOffset[gfCurrentLevel]];
				trng::LeggiNG_ScriptForLevel();
				break;

			case CMD_ENDSEQ:
				continue;

			case CMD_PLAYCUT:
				gfCutNumber = gf[0];
				gf++;
				break;

			case CMD_CUT1:
				gfResidentCut[0] = gf[0];
				gf++;
				break;

			case CMD_CUT2:
				gfResidentCut[1] = gf[0];
				gf++;
				break;

			case CMD_CUT3:
				gfResidentCut[2] = gf[0];
				gf++;
				break;

			case CMD_CUT4:
				gfResidentCut[3] = gf[0];
				gf++;
				break;

			case CMD_LAYER1:
				LightningRGB[0] = gf[0];
				LightningRGBs[0] = gf[0];
				gfLayer1Col.r = gf[0];

				LightningRGB[1] = gf[1];
				LightningRGBs[1] = gf[1];
				gfLayer1Col.g = gf[1];

				LightningRGB[2] = gf[2];
				LightningRGBs[2] = gf[2];
				gfLayer1Col.b = gf[2];

				gfLayer1Vel = gf[3];
				gf += 4;
				break;

			case CMD_LAYER2:
				LightningRGB[0] = gf[0];
				LightningRGBs[0] = gf[0];
				gfLayer2Col.r = gf[0];

				LightningRGB[1] = gf[1];
				LightningRGBs[1] = gf[1];
				gfLayer2Col.g = gf[1];

				LightningRGB[2] = gf[2];
				LightningRGBs[2] = gf[2];
				gfLayer2Col.b = gf[2];

				gfLayer2Vel = gf[3];
				gf += 4;
				break;

			case CMD_UVROT:
				gfUVRotate = gf[0];
				gf++;
				break;

			case CMD_LEGEND:
				gfLegend = gf[0];
				gf++;

				if (gfGameMode != 4)
					gfLegendTime = gfInitialLegendTime;

				break;

			case CMD_LENSFLARE:
				gfLensFlare.x = ((gf[1] << 8) | gf[0]) << 8;
				gfLensFlare.y = short((gf[3] << 8) | gf[2]) << 8;
				gfLensFlare.z = ((gf[5] << 8) | gf[4]) << 8;
				gfLensFlareColour.r = gf[6];
				gfLensFlareColour.g = gf[7];
				gfLensFlareColour.b = gf[8];
				gf += 9;
				break;

			case CMD_MIRROR:
				gfMirrorRoom = gf[0];
				gfMirrorZPlane = (gf[4] << 24) | (gf[3] << 16) | (gf[2] << 8) | gf[1];
				gf += 5;
				break;

			case CMD_FOG:
				gfFog.r = gf[0];
				gfFog.g = gf[1];
				gfFog.b = gf[2];
				gf += 3;
				break;

			case CMD_ANIMATINGMIP:
				gfMips[gfNumMips] = gf[0];
				gfNumMips++;
				gf++;
				break;

			case CMD_CAMERA:
				gfLoadCam.x = (gf[3] << 24) | (gf[2] << 16) | (gf[1] << 8) | gf[0];
				gfLoadCam.y = (gf[7] << 24) | (gf[6] << 16) | (gf[5] << 8) | gf[4];
				gfLoadCam.z = (gf[11] << 24) | (gf[10] << 16) | (gf[9] << 8) | gf[8];
				gfLoadTarget.x = (gf[15] << 24) | (gf[14] << 16) | (gf[13] << 8) | gf[12];
				gfLoadTarget.y = (gf[19] << 24) | (gf[18] << 16) | (gf[17] << 8) | gf[16];
				gfLoadTarget.z = (gf[23] << 24) | (gf[22] << 16) | (gf[21] << 8) | gf[20];
				gfLoadRoom = gf[24];
				gf += 25;
				break;

			case CMD_RESETHUB:
				gfResetHubDest = gf[0];
				gf++;
				break;

			default:
				if (n >= CMD_KEY1 && n <= CMD_KEY12)
					n -= 82;
				else if (n >= CMD_PUZZLE1 && n <= CMD_PUZZLE12)
					n -= 122;
				else if (n >= CMD_PICKUP1 && n <= CMD_PICKUP4)
					n -= 78;
				else if (n >= CMD_EXAMINE1 && n <= CMD_EXAMINE3)
					n -= 59;
				else if (n >= CMD_KEYCOMBO1_1 && n <= CMD_KEYCOMBO8_2)
					n -= 101;
				else if (n >= CMD_PUZZLECOMBO1_1 && n <= CMD_PUZZLECOMBO8_2)
					n -= 145;
				else if (n >= CMD_PICKUPCOMBO1_1 && n <= CMD_PICKUPCOMBO4_2)
					n -= 113;
				else
					break;

				inventry_objects_list[n].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[n].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[n].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[n].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[n].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[n].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[n].flags = gf[12] | (gf[13] << 8);
				gf += 14;
				break;
			}
		}
	}

	void DoLevel(uchar Name, uchar Audio)
	{
		__try { throw __func__; } __finally {}
	}

	void DoTitle(uchar Name, uchar Audio)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Gameflow(bool replace)
{
	ProcessInject(0x450DB0, (unsigned int)tomb4::DoGameflow, replace);
	ProcessInject(0x451CF0, (unsigned int)tomb4::DoLevel, false);
	ProcessInject(0x451440, (unsigned int)tomb4::DoTitle, false);
}
