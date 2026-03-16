#pragma once
#include "../types.h"

namespace tomb4
{
	extern THREAD &MainThread;

	long S_SaveGame(long slot_num);
	long S_LoadGame(long slot_num);
}

void Inject_Gamemain(bool replace);
