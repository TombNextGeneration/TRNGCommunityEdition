#include "../../inject.h"

namespace tomb4
{
	static long &rand_1 = *reinterpret_cast<decltype(&rand_1)>(0x4B74D0);
	static long &rand_2 = *reinterpret_cast<decltype(&rand_2)>(0x4B74D4);

	long GetRandomControl()
	{
		rand_1 = 0x41C64E6D * rand_1 + 12345;
		return (rand_1 >> 10) & 0x7FFF;
	}

	void SeedRandomControl(long seed)
	{
		rand_1 = seed;
	}

	long GetRandomDraw()
	{
		rand_2 = 0x41C64E6D * rand_2 + 12345;
		return (rand_2 >> 10) & 0x7FFF;
	}

	void SeedRandomDraw(long seed)
	{
		rand_2 = seed;
	}
}

void Inject_FunctionStubs(bool replace)
{
	ProcessInject(0x48EB50, (unsigned int)tomb4::GetRandomControl, replace);
	ProcessInject(0x48EB90, (unsigned int)tomb4::SeedRandomControl, replace);
	ProcessInject(0x48EB70, (unsigned int)tomb4::GetRandomDraw, replace);
	ProcessInject(0x48EBA0, (unsigned int)tomb4::SeedRandomDraw, replace);
}
