#pragma once
#include "../types.h"

namespace tomb4
{
	extern LARA_INFO &lara;
	extern ITEM_INFO* &lara_item;
	extern short &DashTimer;

	void lara_col_swandive(ITEM_INFO* item, COLL_INFO* coll);
	void GetLaraCollisionInfo(ITEM_INFO* item, COLL_INFO* coll);
	void LaraDeflectEdgeJump(ITEM_INFO* item, COLL_INFO* coll);
	void lara_col_stop(ITEM_INFO* item, COLL_INFO* coll);
	long LaraHitCeiling(ITEM_INFO* item, COLL_INFO* coll);
	long LaraFallen(ITEM_INFO* item, COLL_INFO* coll);
	long TestLaraSlide(ITEM_INFO* item, COLL_INFO* coll);
}

void Inject_Lara(bool replace);
