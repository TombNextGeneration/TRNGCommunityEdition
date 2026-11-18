#pragma once
#include "../types.h"

namespace tomb4
{
	extern char &HorsemanShotgunDamage;
	extern char &HorsemanRevolverDamage;
	extern long &HorseDamage;
	extern long &HorsemanShieldDamage;
	extern short &HorseFootDamage;
	extern short &HorsemanAxeDamage;
	extern char &HorsemanFootDamage;

	void HorsemanControl(short item_number);
	void TriggerHorsemanRicochets(PHD_VECTOR* pos, long yrot, long num);
}

void Inject_Horse(bool replace);
