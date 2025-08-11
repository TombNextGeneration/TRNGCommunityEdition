#include "Oggetti.h"
#include "../inject.h"
#include "Tomb_NextGeneration.h"

namespace trng {
	// usa sottoprocedura SubBridgeTilt(pBridge, CordX, CordZ)
	void ProcMyBridgeFloor(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY)
	{
		__try { throw __func__; } __finally {}
	}

	void ProcMyBridgeCeiling(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY)
	{
		__try { throw __func__; } __finally {}
	}

	void TightRopeCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseTightRope(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseGuardian(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void GuardianControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	// ------- codici barra parallela ---------------------------------------
	// procedura collisione di tomb5 originale per gestire giravolte
	// di lara intorno alla parallelbar
	void ParallelBarCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll)
	{
		__try { throw __func__; } __finally {}
	}

	// procedura redirezionata per bubble per poter lanciare singolo
	// oggetto come arpione
	void ControlBubble(short fx_number)
	{
		__try { throw __func__; } __finally {}
	}

	// ****************** FUNZIONI PER FISH ************************************
	// riposiziona l'emitter in modo che sia in una posizione centrale
	void InitializeFishGenerator(short IndiceGeneratore)
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerFish(short ItemIndex)
	{
		__try { throw __func__; } __finally {}
	}

	void TorpedoControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void DiverControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	// visualizzare una piccola finestra al centro dello schermo
	// solo per informare di prmeere tasto ctrl
	void CreaFinestraAvviso(void)
	{
		__try { throw __func__; } __finally {}
	}

	bool IsModoWindowed(void)
	{
		__try { throw __func__; } __finally {}
	}

	// questa finestra va fatta:
	// 1) se siamo in modalita' fullscreen fare schermo nero sotto
	void CreaBlackWindow(void)
	{
		HINSTANCE TombInstance;
		WNDCLASS wc;

		wc = {0};

		// trovare handle di instanza

		TombInstance = GetModuleHandle(NULL);

		// ok, ora fare tutto il necessario

		// Set up and register window class

		wc.lpfnWndProc = WindowBlackProc;
		wc.hInstance = TombInstance;
		wc.lpszClassName = BLACK_FIELD;
		if (!RegisterClass(&wc))
			return;

		GlobTomb4.BaseFMV.WindowBlack = CreateWindowEx(0, BLACK_FIELD, "", WS_POPUP, 0, 0, GlobTomb4.BaseWideScreen.SizeX, GlobTomb4.BaseWideScreen.SizeY, NULL, NULL, TombInstance, 0);

		if (GlobTomb4.BaseFMV.WindowBlack == NULL) {
			UnregisterClass(BLACK_FIELD, TombInstance);
			return;
		}

		DisattivaAnimWindow();
		ShowWindow(GlobTomb4.BaseFMV.WindowBlack, SW_NORMAL);
		NascondiTaskBar();
	}

	long FAR PASCAL WindowBlackProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		__try { throw __func__; } __finally {}
	}

	// disattiva l'animazione delle finestre per evitare lo schifotto
	// della finestra che si modifica quando avvio fmv in modo full screen
	void DisattivaAnimWindow(void)
	{
		__try { throw __func__; } __finally {}
	}

	void NascondiTaskBar(void)
	{
		__try { throw __func__; } __finally {}
	}
}

void LoadTombNextGenerationInject_Oggetti(bool replace)
{
	ProcessInject(0x1001194A, (unsigned int)trng::ProcMyBridgeFloor, false);
	ProcessInject(0x10011C6A, (unsigned int)trng::ProcMyBridgeCeiling, false);
	ProcessInject(0x1001C94C, (unsigned int)trng::TightRopeCollision, false);
	ProcessInject(0x1001C8EC, (unsigned int)trng::InitialiseTightRope, false);
	ProcessInject(0x1001D5E8, (unsigned int)trng::InitialiseGuardian, false);
	ProcessInject(0x1001D822, (unsigned int)trng::GuardianControl, false);
	ProcessInject(0x1001BF31, (unsigned int)trng::ParallelBarCollision, false);
	ProcessInject(0x10014BE3, (unsigned int)trng::ControlBubble, false);
	ProcessInject(0x10012116, (unsigned int)trng::InitializeFishGenerator, false);
	ProcessInject(0x100122A7, (unsigned int)trng::TriggerFish, false);
	ProcessInject(0x1001FE63, (unsigned int)trng::TorpedoControl, false);
	ProcessInject(0x1001548E, (unsigned int)trng::DiverControl, false);
	ProcessInject(0x10025267, (unsigned int)trng::CreaFinestraAvviso, false);
	ProcessInject(0x10025FE9, (unsigned int)trng::IsModoWindowed, false);
	ProcessInject(0x1002504C, (unsigned int)trng::CreaBlackWindow, replace);
	ProcessInject(0x10024EC9, (unsigned int)trng::WindowBlackProc, false);
	ProcessInject(0x10024FCE, (unsigned int)trng::DisattivaAnimWindow, false);
	ProcessInject(0x10024E6E, (unsigned int)trng::NascondiTaskBar, false);
}
