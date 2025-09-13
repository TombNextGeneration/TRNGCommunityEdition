#include "senet.h"

namespace tomb4
{
	short (&senet_item)[6] = *reinterpret_cast<decltype(&senet_item)>(0x4BF2D8);
	char (&senet_piece)[6] = *reinterpret_cast<decltype(&senet_piece)>(0x7FE038);
	char (&senet_board)[17] = *reinterpret_cast<decltype(&senet_board)>(0x7FE220);
	char &last_throw = *reinterpret_cast<decltype(&last_throw)>(0x4BF2E4);
	long &SenetTargetX = *reinterpret_cast<decltype(&SenetTargetX)>(0x7FE0E4);
	long &SenetTargetZ = *reinterpret_cast<decltype(&SenetTargetZ)>(0x7FE0E8);
	char &piece_moving = *reinterpret_cast<decltype(&piece_moving)>(0x4ACBF8);
}
