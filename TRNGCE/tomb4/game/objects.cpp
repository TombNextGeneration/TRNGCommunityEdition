#include "objects.h"
#include "../../inject.h"

namespace tomb4
{
	OBJECT_INFO (&objects)[(long)object_types::NUMBER_OBJECTS] = *reinterpret_cast<decltype(&objects)>(0x52B720);

	void BridgeFlatFloor(ITEM_INFO* item, long x, long y, long z, long* height)
	{
		__try { throw __func__; } __finally {}
	}

	void BridgeFlatCeiling(ITEM_INFO* item, long x, long y, long z, long* height)
	{
		__try { throw __func__; } __finally {}
	}

	void BridgeTilt1Floor(ITEM_INFO* item, long x, long y, long z, long* height)
	{
		__try { throw __func__; } __finally {}
	}

	void BridgeTilt1Ceiling(ITEM_INFO* item, long x, long y, long z, long* height)
	{
		__try { throw __func__; } __finally {}
	}

	void BridgeTilt2Floor(ITEM_INFO* item, long x, long y, long z, long* height)
	{
		__try { throw __func__; } __finally {}
	}

	void BridgeTilt2Ceiling(ITEM_INFO* item, long x, long y, long z, long* height)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Objects(bool replace)
{
	ProcessInject(0x455340, (unsigned int)tomb4::BridgeFlatFloor, false);
	ProcessInject(0x455370, (unsigned int)tomb4::BridgeFlatCeiling, false);
	ProcessInject(0x4553D0, (unsigned int)tomb4::BridgeTilt1Floor, false);
	ProcessInject(0x455420, (unsigned int)tomb4::BridgeTilt1Ceiling, false);
	ProcessInject(0x455460, (unsigned int)tomb4::BridgeTilt2Floor, false);
	ProcessInject(0x4554B0, (unsigned int)tomb4::BridgeTilt2Ceiling, false);
}
