#include "input.h"
#include "../../inject.h"

namespace tomb4
{
	long &linput = *reinterpret_cast<decltype(&linput)>(0x535780);
	long &input = *reinterpret_cast<decltype(&input)>(0x5355D8);
	long &dbinput = *reinterpret_cast<decltype(&dbinput)>(0x535784);
	long &joy_fire = *reinterpret_cast<decltype(&joy_fire)>(0x535774);
	long &joy_x = *reinterpret_cast<decltype(&joy_x)>(0x535778);
	long &joy_y = *reinterpret_cast<decltype(&joy_y)>(0x53577C);

	long S_UpdateInput()
	{
		__try { throw __func__; } __finally {}
	}

	long ReadJoystick(long& x, long& y)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Input(bool replace)
{
	ProcessInject(0x475A80, (unsigned int)tomb4::S_UpdateInput, false);
	ProcessInject(0x4759B0, (unsigned int)tomb4::ReadJoystick, false);
}
