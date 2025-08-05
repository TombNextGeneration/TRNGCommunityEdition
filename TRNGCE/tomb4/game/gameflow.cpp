#include "gameflow.h"

namespace tomb4
{
	uchar &gfCurrentLevel = *reinterpret_cast<decltype(&gfCurrentLevel)>(0x7FD170);
	ushort &gfLevelFlags = *reinterpret_cast<decltype(&gfLevelFlags)>(0x7FD140);
	uchar &gfGameMode = *reinterpret_cast<decltype(&gfGameMode)>(0x4AD439);
	CVECTOR &gfLayer1Col = *reinterpret_cast<decltype(&gfLayer1Col)>(0x7FD144);
	CVECTOR &gfLayer2Col = *reinterpret_cast<decltype(&gfLayer2Col)>(0x7FD13C);
	char &gfLayer1Vel = *reinterpret_cast<decltype(&gfLayer1Vel)>(0x7FD132);
	char &gfLayer2Vel = *reinterpret_cast<decltype(&gfLayer2Vel)>(0x7FD131);
	uchar &gfLevelComplete = *reinterpret_cast<decltype(&gfLevelComplete)>(0x7FD190);
	ushort* &gfStringOffset = *reinterpret_cast<decltype(&gfStringOffset)>(0x7FD154);
	char* &gfStringWad = *reinterpret_cast<decltype(&gfStringWad)>(0x7FD198);
}
