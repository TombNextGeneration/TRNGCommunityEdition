#include "laramisc.h"
#include "../../inject.h"
#include "lara.h"
#include "control.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	COLL_INFO* &lara_coll = *reinterpret_cast<decltype(&lara_coll)>(0x4AB9B0);

	void LaraControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseLaraLoad(short item_number)
	{
		lara.item_number = item_number;
		lara_item = &items[item_number];
		trng::AdrGlobali.pLara = (trng::StrItemTr4*)lara_item;
	}

	void AnimateLara(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Laramisc(bool replace)
{
	ProcessInject(0x42FDD0, (unsigned int)tomb4::LaraControl, false);
	ProcessInject(0x430A20, (unsigned int)tomb4::InitialiseLaraLoad, replace);
	ProcessInject(0x4306D0, (unsigned int)tomb4::AnimateLara, false);
}
