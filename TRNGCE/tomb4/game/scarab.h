#pragma once
#include "../types.h"

namespace tomb4
{
	extern SCARAB_STRUCT (&Scarabs)[128];

	void UpdateScarabs();
}

void Inject_Scarab(bool replace);
