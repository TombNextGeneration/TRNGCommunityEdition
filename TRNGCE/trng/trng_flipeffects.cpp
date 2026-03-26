#include "trng_flipeffects.h"
#include "../inject.h"
#define malloc ((void *(*)(size_t)) 0x10135531)
#define realloc ((void *(*)(void *, size_t)) 0x101353F9)
#define free ((void (*)(void *)) 0x101355BD)

namespace trng {
	// qui c'e' tutto (e solo) il codice relativo all'esecuzione di flipeffect standards
	// ossia senza callback e diverse engine
	// questo e' un codice da esport
	int PerformTRNGFlipEffect(int FlipNumber, WORD Timer, WORD Flags)
	{
		__try { throw __func__; } __finally {}
	}
}

void LoadTombNextGenerationInject_TrngFlipeffects(bool replace)
{
	ProcessInject(0x1009D2C7, (unsigned int)trng::PerformTRNGFlipEffect, false);
}
