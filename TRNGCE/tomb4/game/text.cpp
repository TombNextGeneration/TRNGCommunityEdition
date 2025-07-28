#include "text.h"

namespace tomb4
{
	long &font_height = *reinterpret_cast<decltype(&font_height)>(0x7F4F30);
	long &GnFrameCounter = *reinterpret_cast<decltype(&GnFrameCounter)>(0x7E70CC);
}
