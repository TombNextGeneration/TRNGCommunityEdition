#include "dxshell.h"

namespace tomb4
{
	DXPTR* &G_dxptr = *reinterpret_cast<decltype(&G_dxptr)>(0x754468);
	char (&keymap)[256] = *reinterpret_cast<decltype(&keymap)>(0x754260);
}
