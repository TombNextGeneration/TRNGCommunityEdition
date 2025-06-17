#include "../../../inject.h"
#include "../../../tomb4/game/types.h"

namespace flep
{
	short &mine_cart_slot_minecart = *reinterpret_cast<decltype(&mine_cart_slot_minecart)>(0x900878);
	short &mine_cart_slot_vehicle_anim = *reinterpret_cast<decltype(&mine_cart_slot_vehicle_anim)>(0x902464);
	short &mine_cart_slot_mapper = *reinterpret_cast<decltype(&mine_cart_slot_mapper)>(0x90220C);

	long IsMineCartAssigned(void)
	{
		return mine_cart_slot_minecart != -1 && mine_cart_slot_vehicle_anim != -1 && mine_cart_slot_mapper != -1;
	}
}

void Inject_VehiclesMinecart(bool replace)
{
	ProcessInject(*(unsigned int*)0x90C0F4, (unsigned int)flep::IsMineCartAssigned, replace);
}
