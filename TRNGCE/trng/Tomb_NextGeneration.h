#pragma once
#include "structures.h"
#include "MyStructures.h"

namespace trng {
	extern StrGlobaliTomb4 &GlobTomb4;
	extern StrGlobAddress &AdrGlobali;
	extern StrMyGlob &MyGlobPrivate;

	void ImpostaEnemyDamage(void);
}

void Inject_TombNextGeneration(bool replace);
