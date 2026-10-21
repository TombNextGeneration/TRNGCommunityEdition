#include "trng.h"
#include "../../../inject.h"

namespace plugin::particlesystem {
	// you'll use the "Trng" global variable to access to all trng data
	// In c++, you'll use the syntax:
	// Trng.pGlobTomb4->
	// and now it will appear the list of members to choose..
	// While in assembly you use it in this way:
	//  mov  eax, dword ptr [Trng]
	//  mov  ecx, dword ptr [eax+04h]  ; and now ECX points to the trng
	// data (pGlobTomb4)
	// see the "Trng Plugin tutorial" for more infos.
	trng::StrTrngInfos Trng = { -1 };
}

void Inject_Plugin_Particlesystem_trng(void* module, bool replace)
{
	CopyInject(module, "Trng", &plugin::particlesystem::Trng, sizeof(trng::StrTrngInfos));
}
