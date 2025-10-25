#include "input.h"
#include "../../inject.h"

namespace tomb4
{
	long &linput = *reinterpret_cast<decltype(&linput)>(0x535780);
	long &input = *reinterpret_cast<decltype(&input)>(0x5355D8);
	long &dbinput = *reinterpret_cast<decltype(&dbinput)>(0x535784);

	long S_UpdateInput()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Input(bool replace)
{
	ProcessInject(0x475A80, (unsigned int)tomb4::S_UpdateInput, false);
}
