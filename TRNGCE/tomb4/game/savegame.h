#pragma once
#include "../types.h"

namespace tomb4
{
	extern SAVEGAME_INFO &savegame;

	void SaveLevelData(long FullSave);
	void WriteSG(void* pointer, long size);
	void ReadSG(void* pointer, long size);
	void sgInitialiseHub(long dont_save_lara);
	void sgSaveLevel();
}

void Inject_Savegame(bool replace);
