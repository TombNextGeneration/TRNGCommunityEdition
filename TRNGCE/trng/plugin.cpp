#include "plugin.h"
#include "../inject.h"
#include "../tomb4/specific/winmain.h"
#include "Tomb_NextGeneration.h"

namespace trng {
	// scandisce file ng_constant incluso in risorse
	// per scoprire i flipeffect, action e condition usati da trng
	// e poi scrive questi valori in database
	// imposta anche first e last param e cust
	void InizializzaPluginTrng(void)
	{
		__try { throw __func__; } __finally {}
	}

	// se TestMsgBox=true visusaliza anche messagebox se e' possibile
	void InviaErroreLog(const char *pMessage, DWORD PluginID, bool TestMsgBox)
	{
		if (TestMsgBox) {
			// vedere se si puo' mandare message box
			TryMessageBox(pMessage, PluginID);
		} else {
			InviaLog(pMessage);
		}
	}

	// se modo non e' esclusivo visualizza message box, altrimenti restituisce false
	// in ogni caso manda il messaggio sul log
	bool TryMessageBox(const char *pMessage, DWORD ID_Plugin)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMai

		InviaLog(pMessage);
		if (*pTombWind4 == 0 || ScopreModoFullScreen() == false) {
			Tomb4MessageBox(pMessage, MyGlobPrivate.DataBase.pVetPlugins[ID_Plugin].Nome);
			return true;
		}
		return false;
	}

	void Tomb4MessageBox(const char *pMessaggio, char *pTitolo)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMai

		MessageBox(*pTombWind4, pMessaggio, pTitolo, MB_APPLMODAL);
	}
}

void LoadTombNextGenerationInject_Plugin(bool replace)
{
	ProcessInject(0x10034C21, (unsigned int)trng::InizializzaPluginTrng, false);
	ProcessInject(0x1002B8F0, (unsigned int)trng::InviaErroreLog, replace);
	ProcessInject(0x1002B863, (unsigned int)trng::TryMessageBox, replace);
	ProcessInject(0x1002B845, (unsigned int)trng::Tomb4MessageBox, replace);
}
