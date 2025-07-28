#pragma once
#include "structures.h"
#include "../tomb4/types.h"

namespace trng {
	void ProcMyBridgeFloor(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY);
	void ProcMyBridgeCeiling(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY);
	void TightRopeCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll);
	void InitialiseTightRope(short item_number);
	void InitialiseGuardian(short item_number);
	void GuardianControl(short item_number);
	void ParallelBarCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll);
	void ControlBubble(short fx_number);
	void InitializeFishGenerator(short IndiceGeneratore);
	void TriggerFish(short ItemIndex);
	void TorpedoControl(short item_number);
	void DiverControl(short item_number);
	void CreaFinestraAvviso(void);
	bool IsModoWindowed(void);
	void CreaBlackWindow(void);
	long FAR PASCAL WindowBlackProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void DisattivaAnimWindow(void);
	void NascondiTaskBar(void);
}

void LoadTombNextGenerationInject_Oggetti(bool replace);
