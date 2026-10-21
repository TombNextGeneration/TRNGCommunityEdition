#pragma once
#include "../../trng/structures.h"
#include "constants_mine.h"
#include "../../tomb4/types.h"
#include "structures_mine.h"
#include "../../trng/DefTomb4Funct.h"

namespace plugin::objecthelper {
	extern int (&PluginFunctionQueryHandle)[tomb4::NUMBER_OBJECTS];
	extern DWORD (&PluginQuerySupport)[tomb4::NUMBER_OBJECTS];
	extern StrResult &Result;
	extern trng::CALL_FLIPEFFECT_MINE (&PluginPointer)[PLUGINS];
	extern char *(&PluginName)[PLUGINS];

	void HeadshotEnemy(trng::StrItemTr4 *item);
	void MakeQuery(WORD Slot, DWORD Query);
	void PerformNewFlipeffect(int Handle, int Flipeffect, DWORD Timer);
	void PerformGeneralFlipeffect(int Handle, int Flipeffect, WORD Timer, WORD Extra);
	int HighestBitSet(DWORD Value);
	void HitEnemy(trng::StrItemTr4 *item);
}

void Inject_Plugin_Objecthelper(void* module, bool replace);
