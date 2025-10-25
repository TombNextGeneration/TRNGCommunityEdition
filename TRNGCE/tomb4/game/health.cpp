#include "health.h"

namespace tomb4
{
	long &health_bar_timer = *reinterpret_cast<decltype(&health_bar_timer)>(0x4BF558);
}
