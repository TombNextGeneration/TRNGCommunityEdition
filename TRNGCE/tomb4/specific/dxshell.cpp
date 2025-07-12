#include "../types.h"

namespace tomb4
{
	DXPTR* &G_dxptr = *reinterpret_cast<decltype(&G_dxptr)>(0x754468);
}
