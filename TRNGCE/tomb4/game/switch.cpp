#include "types.h"

namespace tomb4
{
	uchar &CurrentSequence = *reinterpret_cast<decltype(&CurrentSequence)>(0x7F55E0);
	uchar (&SequenceUsed)[6] = *reinterpret_cast<decltype(&SequenceUsed)>(0x7F55E8);
	uchar (&Sequences)[3] = *reinterpret_cast<decltype(&Sequences)>(0x7F561C);
}
