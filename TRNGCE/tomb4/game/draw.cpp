#include "draw.h"
#include "../../inject.h"

namespace tomb4
{
#undef static_objects
	STATIC_INFO (*&static_objects)[(long)static_types::NUMBER_STATIC_OBJECTS] = *reinterpret_cast<decltype(&static_objects)>(0x4730B5);
#define static_objects (*tomb4::static_objects)
	ushort (&LightningRGB)[3] = *reinterpret_cast<decltype(&LightningRGB)>(0x7FD1D8);
	ushort (&LightningRGBs)[3] = *reinterpret_cast<decltype(&LightningRGBs)>(0x7FE010);

	short* GetBoundsAccurate(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void DrawAnimatingItem(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Draw(bool replace)
{
	ProcessInject(0x4504E0, (unsigned int)tomb4::GetBoundsAccurate, false);
	ProcessInject(0x44F600, (unsigned int)tomb4::DrawAnimatingItem, false);
}
