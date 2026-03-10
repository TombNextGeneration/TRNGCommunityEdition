#include "PlugIn_trng.h"

namespace flep {
	BYTE (&pPatchMap)[0x1000] = *reinterpret_cast<decltype(&pPatchMap)>(0x812000);
}
