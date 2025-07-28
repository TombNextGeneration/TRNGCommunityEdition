#include "LoadSave.h"

namespace tomb4
{
	long &MusicVolume = *reinterpret_cast<decltype(&MusicVolume)>(0x4B1710);
	long &SFXVolume = *reinterpret_cast<decltype(&SFXVolume)>(0x4B1714);
	long &SoundQuality = *reinterpret_cast<decltype(&SoundQuality)>(0x4B1718);
}
