#pragma once
#include "../types.h"

namespace tomb4
{
	extern bool &fmvs_disabled;
	extern bool &start_setup;

	void InitDSDevice(HWND dlg, HWND hwnd);
}

void Inject_Cmdline(bool replace);
