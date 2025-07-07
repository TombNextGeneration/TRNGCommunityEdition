#include "../inject.h"
#include "structures.h"
#include "MyStructures.h"

namespace trng {
	StrGlobaliTomb4 &GlobTomb4 = *reinterpret_cast<decltype(&GlobTomb4)>(0x101C9578);
	StrGlobAddress &AdrGlobali = *reinterpret_cast<decltype(&AdrGlobali)>(0x10462630);
	StrMyGlob &MyGlobPrivate = *reinterpret_cast<decltype(&MyGlobPrivate)>(0x101B94E0);
	StrBaseCustomize &BaseCustomize = *reinterpret_cast<decltype(&BaseCustomize)>(0x104C54C8);
	StrGlobMisc &BaseGlobMisc = *reinterpret_cast<decltype(&BaseGlobMisc)>(0x103E27D0);

	// modifica i damage sulla base di elenco Enemy
	void ImpostaEnemyDamage(void)
	{
		__try { throw __func__; } __finally {}
	}

	// chiamata nel momento in  cui la libreria viene collegata
	// se restituisce false bisogna abortire il programma
	bool Inizializza(void)
	{
		return false;
	}
}

void Inject_TombNextGeneration(bool replace)
{
	ProcessInject(0x10069407, (unsigned int)trng::ImpostaEnemyDamage, false);
}

void LoadTombNextGenerationInject_TombNextGeneration(bool replace)
{
	ProcessInject(0x100461EB, (unsigned int)trng::Inizializza, replace);
}
