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
	void sgSaveGame();
	long OpenSaveGame(uchar current_level, long saving);
	void SaveLaraData();
	void SaveHubData(long index);
	void sgRestoreGame();
	void RestoreLevelData(long FullSave);
	void RestoreLaraData(long FullSave);
}

void Inject_Savegame(bool replace);
