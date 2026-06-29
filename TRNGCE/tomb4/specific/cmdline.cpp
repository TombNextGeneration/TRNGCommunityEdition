#include "cmdline.h"
#include "../../inject.h"
#include "winmain.h"
#include "../game/gameflow.h"
#include "../../trng/zPatchesTomb4.h"
#include "registry.h"

namespace tomb4
{
	static long DSDeviceSelected = *reinterpret_cast<decltype(&DSDeviceSelected)>(0x4BFD5C);

	bool &fmvs_disabled = *reinterpret_cast<decltype(&fmvs_disabled)>(0x4BFD59);
	bool &start_setup = *reinterpret_cast<decltype(&start_setup)>(0x4BFD58);

	void InitDSDevice(HWND dlg, HWND hwnd)
	{
		SendMessage(hwnd, CB_RESETCONTENT, 0, 0);

		for (int i = 0; i < App.DXInfo.nDSInfo; i++)
			SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)App.DXInfo.DSInfo[i].About);

		DSDeviceSelected = 0;

		if (!App.DXInfo.nDSInfo)
		{
			SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)&gfStringWad[gfStringOffset[TXT_No_Sound_Card_Installed]]);
			EnableWindow(GetDlgItem(dlg, 1018), 0);
			SendMessage(GetDlgItem(dlg, 1018), BM_SETCHECK, 1, 0);
			EnableWindow(hwnd, 0);
		}

		trng::CambiaTitoloSetup(trng::WindSetup);
		// chiamare procedura per leggere le setting dal registro
		LoadSettings();
		trng::InitControlliSetup(trng::WindSetup);

		SendMessage(hwnd, CB_SETCURSEL, 0, 0);
	}
}

void Inject_Cmdline(bool replace)
{
	ProcessInject(0x46E3B0, (unsigned int)tomb4::InitDSDevice, replace);
}
