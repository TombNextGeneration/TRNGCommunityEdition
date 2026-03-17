#pragma once
#include "../../../trng/structures.h"

namespace plugin::particlesystem {
	extern trng::StrTrngInfos Trng;
}

void Inject_Plugin_Particlesystem_trng(void* module, bool replace);
