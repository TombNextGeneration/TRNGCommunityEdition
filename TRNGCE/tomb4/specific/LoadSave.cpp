#include "LoadSave.h"
#include "../../inject.h"
#include "../game/gameflow.h"
#include "../game/lara.h"
#include "../game/text.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../flep/PlugIn_trng.h"
#include "../../flep/structures_mine.h"
#include "3dmath.h"
#include "../../plugin/flycheat/PlugIn_trng.h"
#include "../../plugin/flycheat/trng.h"
#include "winmain.h"
#include "function_table.h"
#include "drawroom.h"
#include "polyinsert.h"
#include "output.h"

namespace tomb4
{
	static float &loadbar_pos = *reinterpret_cast<decltype(&loadbar_pos)>(0x577354);
	static long &loadbar_maxpos = *reinterpret_cast<decltype(&loadbar_maxpos)>(0x577328);

	long &MusicVolume = *reinterpret_cast<decltype(&MusicVolume)>(0x4B1710);
	long &SFXVolume = *reinterpret_cast<decltype(&SFXVolume)>(0x4B1714);
	long &SoundQuality = *reinterpret_cast<decltype(&SoundQuality)>(0x4B1718);
	long &ControlMethod = *reinterpret_cast<decltype(&ControlMethod)>(0x5B7360);
	long &HealthBarColourLeft = *reinterpret_cast<decltype(&HealthBarColourLeft)>(0x47B5B0);
	long &HealthBarColourRight = *reinterpret_cast<decltype(&HealthBarColourRight)>(0x47B5BA);
	uchar &HealthBarHeight = *reinterpret_cast<decltype(&HealthBarHeight)>(0x47B5C3);
	long &HealthBarWidth = *reinterpret_cast<decltype(&HealthBarWidth)>(0x47B5C5);
	long &LoadBarColourLeft = *reinterpret_cast<decltype(&LoadBarColourLeft)>(0x47B65A);
	long &LoadBarColourRight = *reinterpret_cast<decltype(&LoadBarColourRight)>(0x47B65F);
	uchar &LoadBarHeight = *reinterpret_cast<decltype(&LoadBarHeight)>(0x47B68F);
	long &LoadBarWidth = *reinterpret_cast<decltype(&LoadBarWidth)>(0x47B693);

	long S_LoadSave(long load_or_save, long mono)
	{
		__try { throw __func__; } __finally {}
	}

	long S_PauseMenu()
	{
		__try { throw __func__; } __finally {}
	}

	void S_DrawHealthBar(long pos, long flash_state)
	{
		trng::StrBarraCust* cust;
		long x, y, clr;

		if (plugin::flycheat::Trng.IdMyPlugin != -1 && plugin::flycheat::State[plugin::flycheat::COMMAND_FLY_CHEAT])
			return;

		if (flep::pPatchMap[flep::PATCH_ENABLE_GAME_OVER] && lara_item->hit_points <= 0 && flash_state)
			PrintString(ushort(phd_winwidth >> 1), phd_winymax >> 1, 3, &gfStringWad[gfStringOffset[TXT_GAME_OVER]], FF_CENTER);

		if (gfCurrentLevel)
		{
			if (lara.poisoned)
				clr = 0xFFFFFF00;	//yellow
			else
				clr = HealthBarColourLeft;

			x = font_height >> 2;
			y = x;

			cust = &trng::BaseCustomize.VetBar[trng::BAR_HEALTH];
			trng::ColorSlide = cust->ExtraLong; // colore slide

			if (cust->OrgX != -1)
				x = (ushort)cust->OrgX;

			if (cust->OrgY != -1)
				y = (ushort)cust->OrgYUpdated; // orgyupdate

			// vedere se c'e' flag per tipo slide
			if (cust->Flags & trng::FBAR_SOUND_BAR_ANIM)
			{
				// chiamare slider
				trng::CallSlide(x, y, HealthBarWidth, HealthBarHeight, pos, HealthBarColourRight, clr);
			}
			else
				DoBar(x, y, HealthBarWidth, HealthBarHeight, pos, HealthBarColourRight, clr);
		}
	}

	void DoBar(long x, long y, long width, long height, long pos, long clr1, long clr2)
	{
		__try { throw __func__; } __finally {}
	}

	void DoSlider(long x, long y, long width, long height, long pos, long clr1, long clr2, long clr3)
	{
		__try { throw __func__; } __finally {}
	}

	void S_LoadBar()
	{
		trng::StrBarraCust* cust;
		long x, y;
		bool skip;

		if (flep::pPatchMap[flep::PATCH_DISABLE_LOADSCREENS])
			return;

		if (gfCurrentLevel || App.dx.Flags & 0x80)
		{
			_BeginScene();
			InitBuckets();
			InitialiseSortList();
			App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
			App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
			App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 0);
			loadbar_pos += 100.0F / loadbar_maxpos;
			y = phd_winymax - font_height;

			// c'e' da calcare i due valori di origine
			// valori default
			// edx = orgy
			// eax (14h) = orgx

			cust = &trng::BaseCustomize.VetBar[trng::BAR_LOAD_LEVEL];
			trng::ColorSlide = cust->ExtraLong; // colore slide

			x = 20;

			if (cust->OrgX != -1)
				x = (ushort)cust->OrgX;

			if (cust->OrgY != -1)
				y = (ushort)cust->OrgYUpdated; // orgy update

			// se e' attiva immagine per loading level e c'e' flag per nascondere barra di progressione
			// saltare la visualizzazione
			skip = false;

			if (trng::GlobTomb4.BaseImgLoadingLevel.TestEnabled)
			{
				trng::RefreshImgLoadingLevel();

				if (trng::GlobTomb4.BaseImgLoadingLevel.Flags & trng::BKGDF_HIDE_LOADING_BAR)
					skip = true;
			}

			if (!skip)
			{
				// vedere se c'e' flag per tipo slide
				if (cust->Flags & trng::FBAR_SOUND_BAR_ANIM)
				{
					// chiamare slider
					trng::CallSlide(x, y, LoadBarWidth, LoadBarHeight, (long)loadbar_pos, LoadBarColourRight, LoadBarColourLeft);
				}
				else
					DoBar(x, y, LoadBarWidth, LoadBarHeight, (long)loadbar_pos, LoadBarColourRight, LoadBarColourLeft);
			}

			if (!trng::GlobTomb4.BaseImgLoadingLevel.TestEnabled)
				SortPolyList(SortCount, SortList);

			DrawSortList();
			S_DumpScreen();
		}
	}
}

void Inject_Loadsave(bool replace)
{
	ProcessInject(0x47AE70, (unsigned int)tomb4::S_LoadSave, false);
	ProcessInject(0x47ADB0, (unsigned int)tomb4::S_PauseMenu, false);
//	ProcessInject(0x47B590, (unsigned int)tomb4::S_DrawHealthBar, replace);
	ProcessInject(0x47AF60, (unsigned int)tomb4::DoBar, false);
	ProcessInject(0x478D20, (unsigned int)tomb4::DoSlider, false);
	ProcessInject(0x47B600, (unsigned int)tomb4::S_LoadBar, replace);
}
