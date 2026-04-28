#include "cmdline.h"

namespace tomb4
{
	bool &fmvs_disabled = *reinterpret_cast<decltype(&fmvs_disabled)>(0x4BFD59);
	bool &start_setup = *reinterpret_cast<decltype(&start_setup)>(0x4BFD58);
}
