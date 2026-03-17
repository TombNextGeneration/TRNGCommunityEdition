#include "cmdline.h"

namespace tomb4
{
	bool &fmvs_disabled = *reinterpret_cast<decltype(&fmvs_disabled)>(0x4BFD59);
}
