#pragma once
#include "../types.h"

namespace tomb4
{
	extern LOCUST_STRUCT (&Locusts)[64];
	extern char &LocustDamage;

	void UpdateLocusts();
}

void Inject_Croc(bool replace);
