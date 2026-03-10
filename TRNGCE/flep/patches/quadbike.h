#pragma once
#include "../../tomb4/types.h"

namespace flep
{
	extern short (&quad_bike_slot_quadbike)[16];
	extern short (&quad_bike_slot_vehicle_anim)[16];
	extern char (&quad_bike_index)[tomb4::NUMBER_OBJECTS];

	long IsQuadBikeAssigned(long index);
}

void Inject_Quadbike(bool replace);
