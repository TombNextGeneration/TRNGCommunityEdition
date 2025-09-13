#pragma once
#include "structures.h"

namespace trng {
	void InizializzaPluginTrng(void);
	void InviaErroreLog(const char *pMessage, DWORD PluginID, bool TestMsgBox);
	bool TryMessageBox(const char *pMessage, DWORD ID_Plugin);
	void Tomb4MessageBox(const char *pMessaggio, char *pTitolo);
}

void LoadTombNextGenerationInject_Plugin(bool replace);
