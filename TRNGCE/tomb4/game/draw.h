#pragma once
#include "types.h"

namespace tomb4
{
	extern STATIC_INFO (*&static_objects)[(long)static_types::NUMBER_STATIC_OBJECTS];
#define static_objects (*static_objects)

	short* GetBoundsAccurate(ITEM_INFO* item);
	void DrawAnimatingItem(ITEM_INFO* item);
}

void Inject_Draw(bool replace);
