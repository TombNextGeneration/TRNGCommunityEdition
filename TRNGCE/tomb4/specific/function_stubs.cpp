#include "function_stubs.h"
#include <cstring>
#include "../../inject.h"

namespace tomb4
{
	static long &rand_1 = *reinterpret_cast<decltype(&rand_1)>(0x4B74D0);
	static long &rand_2 = *reinterpret_cast<decltype(&rand_2)>(0x4B74D4);
	static long &malloc_used = *reinterpret_cast<decltype(&malloc_used)>(0x7E70C0);

	long &malloc_free = *reinterpret_cast<decltype(&malloc_free)>(0x7E70C4);
	char* &malloc_ptr = *reinterpret_cast<decltype(&malloc_ptr)>(0x7E70AC);
	char* &malloc_buffer = *reinterpret_cast<decltype(&malloc_buffer)>(0x7E70D4);
	PHD_VECTOR &CamRot = *reinterpret_cast<decltype(&CamRot)>(0x7E70B0);

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

	void Log(ulong type, const char* s, ...)
	{
		__try { throw __func__; } __finally {}
	}

	void* game_malloc(long size, long type)
	{
		char* ptr;

		size = (size + 3) & -4;

		if (size > malloc_free)
		{
			Log(0, "OUT OF MEMORY");
			return 0;
		}
		else
		{
			ptr = malloc_ptr;
			malloc_free -= size;
			malloc_used += size;
			malloc_ptr += size;
			memset(ptr, 0, size);
			return ptr;
		}
	}

	void* game_malloc(long size)
	{
		return game_malloc(size, 0);
	}

	void S_CDLoop()
	{

	}
}

void Inject_FunctionStubs(bool replace)
{
	ProcessInject(0x48EB50, (unsigned int)tomb4::GetRandomControl, replace);
	ProcessInject(0x48EB90, (unsigned int)tomb4::SeedRandomControl, replace);
	ProcessInject(0x48EB70, (unsigned int)tomb4::GetRandomDraw, replace);
	ProcessInject(0x48EBA0, (unsigned int)tomb4::SeedRandomDraw, replace);
	ProcessInject(0x499EC0, (unsigned int)tomb4::Log, false);
//	ProcessInject(0x48EBF0, (unsigned int)tomb4::game_malloc, replace);
//	ProcessInject(0x425D20, (unsigned int)tomb4::S_CDLoop, replace);
}
