#include "ListTr4Patch.h"
#include "../inject.h"

namespace trng {
	StrAdrMemory (&VetMemorySavegame)[95] = *reinterpret_cast<decltype(&VetMemorySavegame)>(0x1014D010);
	StrAdrMemory (&VetItemMemory)[41] = *reinterpret_cast<decltype(&VetItemMemory)>(0x1014CDE0);
	StrAdrMemory (&VetCodeMemory)[25] = *reinterpret_cast<decltype(&VetCodeMemory)>(0x1014CC40);
	StrAdrMemory (&VetSlotMemory)[20] = *reinterpret_cast<decltype(&VetSlotMemory)>(0x1014CD28);
	StrAdrMemory (&VetMemoryAnimation)[20] = *reinterpret_cast<decltype(&VetMemoryAnimation)>(0x1014CF58);
	StrAdrMemory (&VetMemoryInventory)[11] = *reinterpret_cast<decltype(&VetMemoryInventory)>(0x1014D368);

	// se restituisce false bisogna abortire il programma
	bool StartUpTomb4(void)
	{
		__try { throw __func__; } __finally {}
	}
}

void LoadTombNextGenerationInject_ListTr4Patch(bool replace)
{
	ProcessInject(0x1000EB71, (unsigned int)trng::StartUpTomb4, false);
}
