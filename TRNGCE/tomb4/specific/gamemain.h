#pragma once
#include "../types.h"

namespace tomb4
{
	extern THREAD &MainThread;
	extern char (&savegame_format_string)[256];
	extern LPDIRECT3DVERTEXBUFFER &DestVB;
	extern short* &clipflags;

	long S_SaveGame(long slot_num);
	long S_LoadGame(long slot_num);
	void GameClose();
}

void Inject_Gamemain(bool replace);
