#include "trng.h"
#include "../../inject.h"

namespace plugin::flycheat {
	trng::StrTrngInfos Trng = { .IdMyPlugin = -1 };
}

void Inject_Plugin_FlyCheat_trng(void* module, bool replace)
{
	CopyInject(module, "Trng", &plugin::flycheat::Trng, sizeof(trng::StrTrngInfos));
}
