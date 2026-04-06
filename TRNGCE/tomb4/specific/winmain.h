#pragma once
#include "../types.h"

namespace tomb4
{
	extern WINAPP &App;

	void WinClose();
}

void Inject_Winmain(bool replace);
