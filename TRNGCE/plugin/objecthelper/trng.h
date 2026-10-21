#pragma once
#include "../../trng/structures.h"

namespace plugin::objecthelper {
	extern trng::StrTrngInfos Trng;

	bool PerformFlipeffect(char *pPluginName, int FlipNumber, int Arg1, int Arg2);
	int FindPluginID(char PluginName[]);
	bool SendToLog(const char *szFormat, ...);
	int Service(DWORD SRV_Type, ...);
}

void Inject_Plugin_Objecthelper_trng(void* module, bool replace);
