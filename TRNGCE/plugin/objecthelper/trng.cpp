#include "trng.h"
#include <cstdio>
#include "../../inject.h"
#include "../../tomb4/specific/winmain.h"

namespace plugin::objecthelper {
	// you'll use the "Trng" global variable to access to all trng data
	// In c++, you'll use the syntax:
	// Trng.pGlobTomb4->
	// and now it will appear the list of members to choose..
	// While in assembly you use it in this way:
	//  mov  eax, dword ptr [Trng]
	//  mov  ecx, dword ptr [eax+04h]  ; and now ECX points to the trng
	// data (pGlobTomb4)
	// see the "Trng Plugin tutorial" for more infos.
	trng::StrTrngInfos Trng = {-1};

	// FOR_YOU:
	// perform an (existing) flipeffect trigger with the given data
	bool PerformFlipeffect(char *pPluginName, int FlipNumber, int Arg1, int Arg2)
	{
		int TimerField;
		int PluginId;

		if (Arg2 == 0) {
			TimerField = Arg1;
		} else {
			TimerField = Arg1 | (Arg2 << 8);
		}
		if (pPluginName == NULL) {
			PluginId = 0;
		} else {
			PluginId = FindPluginID(pPluginName);
		}
		if (PluginId == -1)
			return false;

		Service(trng::SRV_PERFORM_FLIPEFFECT, PluginId, FlipNumber, TimerField);
		return true;
	}

	// FOR_YOU:
	// find the ID of loaded plugin giving the name "plugin_name.dll"
	// NOTE: you can use this procedure only AFTER that the CB_INIT_PROGRAM callback code has been performed.
	// returns the ID of plugin, or -1 if there is no loaded plugin with the supplied name
	int FindPluginID(char PluginName[])
	{
		int i;

		for (i = 0; i < Trng.TotPlugins; i++) {
			if (_stricmp(PluginName, Trng.pVetPluginNames[i]) == 0) {
				return i;
			}
		}

		SendToLog("ERROR: cann't locate plugin: \"%s\"", PluginName);

		return -1;
	}

	// send to load a text with (optional) variable arguments: use %d  for numbers, and %s for texts
	bool SendToLog(const char *szFormat, ...)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMain
		static char MyInternalBuffer[512];

		va_list pArgs;

		if (*pTombWind4 == 0)
			return false;

		va_start(pArgs, szFormat);
		vsprintf_s(MyInternalBuffer, szFormat, pArgs);
		va_end(pArgs);

		Service(trng::SRV_F_InviaLog, MyInternalBuffer);
		return true;
	}

	// FOR_YOU:
	// this is the procedure to call global trng services
	int Service(DWORD SRV_Type, ...)
	{
		va_list pArgs;
		int RetValue;

		va_start(pArgs, SRV_Type);

		RetValue = Trng.Service(Trng.IdMyPlugin, SRV_Type, pArgs);
		va_end(pArgs);
		return RetValue;
	}
}

void Inject_Plugin_Objecthelper_trng(void* module, bool replace)
{
	CopyAddressInject(module, 0x1000D10C, &plugin::objecthelper::Trng, sizeof(trng::StrTrngInfos));

	ModuleAddressProcessInject(module, 0x10005F10, (unsigned int)plugin::objecthelper::PerformFlipeffect, replace);
	ModuleAddressProcessInject(module, 0x10005EB0, (unsigned int)plugin::objecthelper::FindPluginID, replace);
	ModuleAddressProcessInject(module, 0x10005DD0, (unsigned int)plugin::objecthelper::SendToLog, replace);
	ModuleAddressProcessInject(module, 0x10005DB0, (unsigned int)plugin::objecthelper::Service, replace);
}
