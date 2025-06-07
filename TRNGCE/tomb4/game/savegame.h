#pragma once

namespace tomb4
{
	void WriteSG(void* pointer, long size);
	void ReadSG(void* pointer, long size);
	void SaveLevelData(long FullSave);
}

void Inject_Savegame(bool replace);
