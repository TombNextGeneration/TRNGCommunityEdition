#include "../../../inject.h"
#include "../../../tomb4/game/types.h"

namespace flep
{
	short (&quad_bike_slot_quadbike)[16] = *reinterpret_cast<decltype(&quad_bike_slot_quadbike)>(0x902118);
	short (&quad_bike_slot_vehicle_anim)[16] = *reinterpret_cast<decltype(&quad_bike_slot_vehicle_anim)>(0x900064);
	char (&quad_bike_index)[(long)tomb4::object_types::NUMBER_OBJECTS] = *reinterpret_cast<decltype(&quad_bike_index)>(0x900B60);

	long IsQuadBikeAssigned(long index)
	{
		return quad_bike_slot_quadbike[index] != -1 && quad_bike_slot_vehicle_anim[index] != -1;
	}
}

void Inject_VehiclesQuadbike(bool replace)
{
	ProcessInject(*(unsigned int*)0x90C148, (unsigned int)flep::IsQuadBikeAssigned, replace);
}
