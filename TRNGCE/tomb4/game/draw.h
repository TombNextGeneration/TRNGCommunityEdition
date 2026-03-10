#pragma once
#include "../types.h"

namespace tomb4
{
	extern STATIC_INFO (&static_objects)[NUMBER_STATIC_OBJECTS];
	extern ushort (&LightningRGB)[3];
	extern ushort (&LightningRGBs)[3];

	short* GetBoundsAccurate(ITEM_INFO* item);
	void DrawAnimatingItem(ITEM_INFO* item);
	short* GetBestFrame(ITEM_INFO* item);
}

void Inject_Draw(bool replace);
