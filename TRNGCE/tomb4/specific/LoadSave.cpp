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

namespace tomb4
{
	long &MusicVolume = *reinterpret_cast<decltype(&MusicVolume)>(0x4B1710);
	long &SFXVolume = *reinterpret_cast<decltype(&SFXVolume)>(0x4B1714);
	long &SoundQuality = *reinterpret_cast<decltype(&SoundQuality)>(0x4B1718);
	long &ControlMethod = *reinterpret_cast<decltype(&ControlMethod)>(0x5B7360);

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
				clr = 0xFFFF0000;	//red

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
				trng::CallSlide(x, y, 150, 12, pos, 0xFF000000, clr);
			}
			else
				DoBar(x, y, 150, 12, pos, 0xFF000000, clr);
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
}

void Inject_Loadsave(bool replace)
{
	ProcessInject(0x47AE70, (unsigned int)tomb4::S_LoadSave, false);
	ProcessInject(0x47ADB0, (unsigned int)tomb4::S_PauseMenu, false);
//	ProcessInject(0x47B590, (unsigned int)tomb4::S_DrawHealthBar, replace);
	ProcessInject(0x47AF60, (unsigned int)tomb4::DoBar, false);
	ProcessInject(0x478D20, (unsigned int)tomb4::DoSlider, false);
}
