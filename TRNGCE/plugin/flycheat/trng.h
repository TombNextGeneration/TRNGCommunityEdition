#pragma once
#include "../../trng/structures.h"

namespace plugin::flycheat {
	extern trng::StrTrngInfos Trng;
}

void Inject_Plugin_FlyCheat_trng(void* module, bool replace);
