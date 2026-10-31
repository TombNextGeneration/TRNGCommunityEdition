#pragma once
#include "../../trng/structures.h"

namespace plugin::classicinventory {
	extern trng::StrTrngInfos Trng;
}

void Inject_Plugin_ClassicInventory_trng(void* module, bool replace);
