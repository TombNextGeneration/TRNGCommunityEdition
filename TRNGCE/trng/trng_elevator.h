#pragma once
#include "../tomb4/types.h"

namespace trng {
	void ControlTwoBlockPlatform(short ItemIndex);
	void TwoBlockPlatformFloor(tomb4::ITEM_INFO *item, long x, long y, long z, long *height);
	void TwoBlockPlatformCeiling(tomb4::ITEM_INFO *item, long x, long y, long z, long *height);
	void SetSlotElevator(void);
}

void Inject_TrngElevator(bool replace);
