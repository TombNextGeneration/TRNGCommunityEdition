#pragma once
#include "../game/types.h"

namespace tomb4
{
	extern long &malloc_free;
	extern char* &malloc_ptr;

	long GetRandomControl();
	void SeedRandomControl(long seed);
	long GetRandomDraw();
	void SeedRandomDraw(long seed);
	void Log(ulong type, const char* s, ...);
	void* game_malloc(long size, long type = 0);
}

void Inject_FunctionStubs(bool replace);
