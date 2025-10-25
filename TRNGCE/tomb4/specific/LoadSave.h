#pragma once

namespace tomb4
{
	extern long &MusicVolume;
	extern long &SFXVolume;
	extern long &SoundQuality;

	long S_LoadSave(long load_or_save, long mono);
	long S_PauseMenu();
}

void Inject_Loadsave(bool replace);
