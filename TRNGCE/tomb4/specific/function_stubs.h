#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &malloc_free;
	extern char* &malloc_ptr;
	extern char* &malloc_buffer;

	long GetRandomControl();
	void SeedRandomControl(long seed);
	long GetRandomDraw();
	void SeedRandomDraw(long seed);
	void Log(ulong type, const char* s, ...);
	void* game_malloc(long size, long type = 0);
}

void Inject_FunctionStubs(bool replace);
