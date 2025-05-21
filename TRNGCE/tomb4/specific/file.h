#pragma once
#include "../game/types.h"

namespace tomb4
{
	extern short* &mesh_base;
	extern CHANGE_STRUCT* &changes;
	extern RANGE_STRUCT* &ranges;
	extern short* &commands;
	extern short* &frames;

	bool LoadObjects();
}

void Inject_File(bool replace);
