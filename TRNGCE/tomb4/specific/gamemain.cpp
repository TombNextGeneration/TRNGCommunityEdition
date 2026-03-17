#include "gamemain.h"
#include "../../inject.h"

namespace tomb4
{
	THREAD &MainThread = *reinterpret_cast<decltype(&MainThread)>(0x5339D4);

	long S_SaveGame(long slot_num)
	{
		__try { throw __func__; } __finally {}
	}

	long S_LoadGame(long slot_num)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Gamemain(bool replace)
{
	ProcessInject(0x475630, (unsigned int)tomb4::S_SaveGame, false);
	ProcessInject(0x4757D0, (unsigned int)tomb4::S_LoadGame, false);
}
