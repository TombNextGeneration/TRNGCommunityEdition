#pragma once
#include "../tomb4/types.h"

namespace trng {
	void SetSlotElevator(void);
	void TwoBlockPlatformCeiling(tomb4::ITEM_INFO *item, long x, long y, long z, long *height);
	void TwoBlockPlatformFloor(tomb4::ITEM_INFO *item, long x, long y, long z, long *height);
	void ControlTwoBlockPlatform(short ItemIndex);
}

void Inject_TrngElevator(bool replace);
