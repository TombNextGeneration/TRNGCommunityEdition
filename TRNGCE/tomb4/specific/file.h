#pragma once
#include "../types.h"

namespace tomb4
{
	extern short* &mesh_base;
	extern CHANGE_STRUCT* &changes;
	extern RANGE_STRUCT* &ranges;
	extern short* &commands;
	extern short* &frames;
	extern long &number_cameras;
	extern short &nAIObjects;
	inline struct { volatile long active; volatile long ended; ulong handle; ulong address; } &LevelLoadingThread = *reinterpret_cast<decltype(&LevelLoadingThread)>(0x4A6D38);

	bool LoadObjects();
	bool LoadCinematic();
}

void Inject_File(bool replace);
