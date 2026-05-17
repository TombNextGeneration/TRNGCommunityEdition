#pragma once
#include "../types.h"

namespace tomb4
{
	extern uchar &CurrentSequence;
	extern uchar (&SequenceUsed)[6];
	extern uchar (&Sequences)[3];

	long SwitchTrigger(short item_number, short timer);
}

void Inject_Switch(bool replace);
