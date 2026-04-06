#pragma once

namespace tomb4
{
	extern long &MusicVolume;
	extern long &SFXVolume;
	extern long &SoundQuality;
	extern long &ControlMethod;

	long S_LoadSave(long load_or_save, long mono);
	long S_PauseMenu();
	void S_DrawHealthBar(long pos, long flash_state);
	void DoBar(long x, long y, long width, long height, long pos, long clr1, long clr2);
	void DoSlider(long x, long y, long width, long height, long pos, long clr1, long clr2, long clr3);
}

void Inject_Loadsave(bool replace);
