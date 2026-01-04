#pragma once
#include "../types.h"

namespace tomb4
{
	inline struct { STATIC_INFO (*&_)[NUMBER_STATIC_OBJECTS] = *reinterpret_cast<decltype(&_)>(0x4730B5); decltype(*_) operator()() { return *_; } } static_objects;
#define static_objects static_objects()
	extern ushort (&LightningRGB)[3];
	extern ushort (&LightningRGBs)[3];

	short* GetBoundsAccurate(ITEM_INFO* item);
	void DrawAnimatingItem(ITEM_INFO* item);
	short* GetBestFrame(ITEM_INFO* item);
}

void Inject_Draw(bool replace);
