#pragma once

namespace flep
{
	extern short &mine_cart_slot_minecart;
	extern short &mine_cart_slot_vehicle_anim;
	extern short &mine_cart_slot_mapper;

	long IsMineCartAssigned(void);
}

void Inject_VehiclesMinecart(bool replace);
