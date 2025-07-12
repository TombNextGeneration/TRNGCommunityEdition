#include "../types.h"

namespace tomb4
{
	ROPE_STRUCT (&RopeList)[5] = *reinterpret_cast<decltype(&RopeList)>(0x7FB3A0);
	PENDULUM &CurrentPendulum = *reinterpret_cast<decltype(&CurrentPendulum)>(0x7FD080);
}
