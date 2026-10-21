#include "PlugIn_trng.h"
#include "../../inject.h"
#include "trng.h"
#include "../../tomb4/game/croc.h"
#include "../../tomb4/game/scarab.h"

namespace plugin::flycheat {
	bool (&Transition)[COMMANDS] = *reinterpret_cast<decltype(&Transition)>(0x1000A318);
	bool (&State)[COMMANDS] = *reinterpret_cast<decltype(&State)>(0x1000A330);

	void FriendlyFish(void)
	{
		short Health;

		Health = Trng.pGlobTomb4->pAdr->pLara->Health;
		if (State[COMMAND_AGGRESSIVENESS])
			Trng.pGlobTomb4->pAdr->pLara->Health = 0;
		tomb4::UpdateLocusts();
		if (State[COMMAND_AGGRESSIVENESS])
			Trng.pGlobTomb4->pAdr->pLara->Health = Health;
	}

	void FriendlyBeetles(void)
	{
		short Health;

		Health = Trng.pGlobTomb4->pAdr->pLara->Health;
		if (State[COMMAND_AGGRESSIVENESS])
			Trng.pGlobTomb4->pAdr->pLara->Health = 0;
		tomb4::UpdateScarabs();
		if (State[COMMAND_AGGRESSIVENESS])
			Trng.pGlobTomb4->pAdr->pLara->Health = Health;
	}
}

__declspec(naked) static void** Inject_Plugin_FlyCheat_Transition() { __asm lea eax, [plugin::flycheat::Transition] __asm ret }
__declspec(naked) static void** Inject_Plugin_FlyCheat_State() { __asm lea eax, [plugin::flycheat::State] __asm ret }

void Inject_Plugin_FlyCheat(void* module, bool replace)
{
	ModuleAddressReferenceInject(Inject_Plugin_FlyCheat_Transition(), module);
	ModuleAddressReferenceInject(Inject_Plugin_FlyCheat_State(), module);

	ModuleAddressProcessInject(module, 0x10001150, (unsigned int)plugin::flycheat::FriendlyFish, replace);
	ModuleAddressProcessInject(module, 0x10001100, (unsigned int)plugin::flycheat::FriendlyBeetles, replace);
}
