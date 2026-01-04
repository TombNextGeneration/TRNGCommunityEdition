#pragma once
#include "structures.h"

namespace trng {
	int PerformTRNGFlipEffect(int FlipNumber, WORD Timer, WORD Flags);
}

void LoadTombNextGenerationInject_TrngFlipeffects(bool replace);
