#pragma once

namespace plugin::classicinventory {
	bool picked_up_object(int slot);
}

void Inject_Plugin_ClassicInventory(void* module, bool replace);
