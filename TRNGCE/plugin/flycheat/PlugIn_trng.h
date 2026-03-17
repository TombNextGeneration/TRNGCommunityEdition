#pragma once
#include "constants_mine.h"

namespace plugin::flycheat {
	extern bool (&Transition)[COMMANDS];
	extern bool (&State)[COMMANDS];

	void FriendlyFish(void);
	void FriendlyBeetles(void);
}

void Inject_Plugin_FlyCheat(void* module, bool replace);
