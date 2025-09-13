#pragma once
#include "structures.h"

namespace trng {
	extern StrAdrMemory (&VetMemorySavegame)[95];
	extern StrAdrMemory (&VetItemMemory)[41];
	extern StrAdrMemory (&VetCodeMemory)[25];
	extern StrAdrMemory (&VetSlotMemory)[20];
	extern StrAdrMemory (&VetMemoryAnimation)[20];
	extern StrAdrMemory (&VetMemoryInventory)[11];

	bool StartUpTomb4(void);
}

void LoadTombNextGenerationInject_ListTr4Patch(bool replace);
