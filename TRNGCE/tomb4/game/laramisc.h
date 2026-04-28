#pragma once
#include "../types.h"

namespace tomb4
{
	extern COLL_INFO* &lara_coll;

	void LaraControl(short item_number);
	void InitialiseLaraLoad(short item_number);
}

void Inject_Laramisc(bool replace);
