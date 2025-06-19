#include "types.h"

namespace tomb4
{
	LARA_INFO &lara = *reinterpret_cast<decltype(&lara)>(0x80DEC0);
	ITEM_INFO* &lara_item = *reinterpret_cast<decltype(&lara_item)>(0x80E01C);
}
