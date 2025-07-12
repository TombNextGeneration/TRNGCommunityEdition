#pragma once
#include "structures.h"

namespace trng {
	void InizializzaPluginTrng(void);
	void Tomb4MessageBox(const char *pMessaggio, char *pTitolo);
	bool TryMessageBox(const char *pMessage, DWORD ID_Plugin);
	void InviaErroreLog(const char *pMessage, DWORD PluginID, bool TestMsgBox);
}

void LoadTombNextGenerationInject_Plugin(bool replace);
