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
#define THREAD struct THREAD_ { volatile long active; volatile long ended; ulong handle; ulong address; }
	extern THREAD &LevelLoadingThread;
#undef THREAD

	bool LoadObjects();
}

void Inject_File(bool replace);
