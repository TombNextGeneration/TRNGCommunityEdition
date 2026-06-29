#include "vehicles.h"
#include "../../inject.h"
#include "minecart.h"
#include "quadbike.h"
#include "../../tomb4/game/savegame.h"
#include "types.h"
#include "sub.h"

namespace flep
{
	void SaveVehicle(tomb4::ITEM_INFO* item)
	{
		if (IsMineCartAssigned() && item->object_number == mine_cart_slot_minecart)
			tomb4::WriteSG(item->data, sizeof(CARTINFO));
		else
		{
			for (int i = 0; i < 16; i++)
			{
				if (IsQuadBikeAssigned(i) && quad_bike_index[quad_bike_slot_quadbike[i]] == i && item->object_number == quad_bike_slot_quadbike[i])
				{
					tomb4::WriteSG(item->data, sizeof(QUADINFO));
					break;
				}

				if (IsSubAssignedToItem(i, item))
				{
					tomb4::WriteSG(item->data, sizeof(SUBINFO));
					break;
				}
			}
		}
	}
}

// NOLINTBEGIN(clang-analyzer-core.FixedAddressDereference)
void Inject_Vehicles(bool replace)
{
	ProcessInject(*(unsigned int*)0x90C164, (unsigned int)flep::SaveVehicle, replace);
}
// NOLINTEND(clang-analyzer-core.FixedAddressDereference)
