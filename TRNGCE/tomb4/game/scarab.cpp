#include "scarab.h"
#include "../../inject.h"

namespace tomb4
{
	SCARAB_STRUCT (&Scarabs)[128] = *reinterpret_cast<decltype(&Scarabs)>(0x80EBE0);

	void UpdateScarabs()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Scarab(bool replace)
{
	ProcessInject(0x40E2F0, (unsigned int)tomb4::UpdateScarabs, false);
}
