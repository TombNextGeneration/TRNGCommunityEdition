#pragma once
#include "structures.h"

namespace trng {
	void InizializzaPluginTrng(void);
	void InviaErroreLog(const char *pMessage, DWORD PluginID, bool TestMsgBox);
	bool TryMessageBox(const char *pMessage, DWORD ID_Plugin);
	void Tomb4MessageBox(const char *pMessaggio, char *pTitolo);
	void DeleteParamCommand(int ParamType, int IdParam, bool TestSempre, bool TestSottoCommandi);
	bool LogOnDebug(const char *szFormat, ...);
	void DeleteColorRgb(int IdColorRgb, bool TestSempre);
	void DeleteTriggerGroup(int IdTriggerGroup, bool TestSempre);
	void DeleteAddEffect(int IdEffect, bool TestSempre);
	int WINAPI Servo(DWORD ID_Plugin, DWORD SRV_Value, va_list pArgs);
	int Service(DWORD SRV_Type, ...);
}

void LoadTombNextGenerationInject_Plugin(bool replace);
