#include "Plugin_ClassicInventory.h"
#include "../../inject.h"

namespace plugin::classicinventory {
	bool picked_up_object(int slot)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Plugin_ClassicInventory(void* module, bool replace)
{
	ModuleProcessInject(module, "picked_up_object", (unsigned int)plugin::classicinventory::picked_up_object, false);
}
