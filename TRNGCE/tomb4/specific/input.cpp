#include "input.h"

namespace tomb4
{
	long &linput = *reinterpret_cast<decltype(&linput)>(0x535780);
	long &input = *reinterpret_cast<decltype(&input)>(0x5355D8);
	long &dbinput = *reinterpret_cast<decltype(&dbinput)>(0x535784);
}
