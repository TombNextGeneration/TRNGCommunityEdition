#pragma once
#include "../types.h"

namespace tomb4
{
	extern char (&LibraryTab)[8];

	long OnTwoBlockPlatform(ITEM_INFO* item, long x, long z);
	void LaraBurn();
	void OpenTrapDoor(ITEM_INFO* item);
	void RollingBallCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll);
}

void Inject_Traps(bool replace);
