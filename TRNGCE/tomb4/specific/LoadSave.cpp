#include "LoadSave.h"
#include "../../inject.h"

namespace tomb4
{
	long &MusicVolume = *reinterpret_cast<decltype(&MusicVolume)>(0x4B1710);
	long &SFXVolume = *reinterpret_cast<decltype(&SFXVolume)>(0x4B1714);
	long &SoundQuality = *reinterpret_cast<decltype(&SoundQuality)>(0x4B1718);
	long &ControlMethod = *reinterpret_cast<decltype(&ControlMethod)>(0x5B7360);

	long S_LoadSave(long load_or_save, long mono)
	{
		__try { throw __func__; } __finally {}
	}

	long S_PauseMenu()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Loadsave(bool replace)
{
	ProcessInject(0x47AE70, (unsigned int)tomb4::S_LoadSave, false);
	ProcessInject(0x47ADB0, (unsigned int)tomb4::S_PauseMenu, false);
}
