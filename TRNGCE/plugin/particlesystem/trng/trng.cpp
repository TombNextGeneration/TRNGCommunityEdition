#include "trng.h"
#include "../../../inject.h"

namespace plugin::particlesystem {
	trng::StrTrngInfos Trng = { .IdMyPlugin = -1 };
}

void Inject_Plugin_Particlesystem_trng(void* module, bool replace)
{
	CopyInject(module, "Trng", &plugin::particlesystem::Trng, sizeof(trng::StrTrngInfos));
}
