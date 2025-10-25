#pragma once
#include "../types.h"

namespace tomb4
{
	extern OBJECT_INFO (&objects)[(long)object_types::NUMBER_OBJECTS];

	void BridgeFlatFloor(ITEM_INFO* item, long x, long y, long z, long* height);
	void BridgeFlatCeiling(ITEM_INFO* item, long x, long y, long z, long* height);
	void BridgeTilt1Floor(ITEM_INFO* item, long x, long y, long z, long* height);
	void BridgeTilt1Ceiling(ITEM_INFO* item, long x, long y, long z, long* height);
	void BridgeTilt2Floor(ITEM_INFO* item, long x, long y, long z, long* height);
	void BridgeTilt2Ceiling(ITEM_INFO* item, long x, long y, long z, long* height);
	void AnimateWaterfalls();
}

void Inject_Objects(bool replace);
