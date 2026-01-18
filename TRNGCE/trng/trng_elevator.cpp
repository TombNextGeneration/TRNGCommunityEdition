#include "trng_elevator.h"
#include "../inject.h"
#include "structures.h"
#include "Tomb_NextGeneration.h"

namespace trng {
	// when there are elevator= command in the script, the twoblockplatform object will be redirected
	// to our custom procedure to transform it in the trng elevator
	// #callback#
	void SetSlotElevator(void)
	{
		StrSlot *pSlotNow;

		if (GlobTomb4.BaseElevator.TotElelevators > 0) {
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[150];
			pSlotNow->pProcCeiling = &TwoBlockPlatformCeiling;
			pSlotNow->pProcFloor = &TwoBlockPlatformFloor;
			pSlotNow->pProcControl = &ControlTwoBlockPlatform;
		}
	}

	// sostituisce TwoBlockPlatformCeiling:
	//	;esp+14= LONG* (puntatore a long)  nuova cordy
	//	;esp+10=long  cordz
	//	;esp+C=long   cordy
	//	;esp+8=long    cordx
	//	;esp+4 = ITEM_INFO* di piattaforma
	void TwoBlockPlatformCeiling(tomb4::ITEM_INFO *item, long x, long y, long z, long *height)
	{
		__try { throw __func__; } __finally {}
	}

	// sostituisce TwoBlockPlatformFloor
	void TwoBlockPlatformFloor(tomb4::ITEM_INFO *item, long x, long y, long z, long *height)
	{
		__try { throw __func__; } __finally {}
	}

	// nuova gestione di twoblockplatform quando ci sono ascensori
	void ControlTwoBlockPlatform(short ItemIndex)
	{
		__try { throw __func__; } __finally {}
	}

	// aggiorna posizione di ItemIndex (relativo ad ascensore) aggiungedo a coordinata y
	// il valore IncY
	// aggiorna anche numero di room in modo corretto
	void AggiornaPosY(int ItemIndex, int IncY)
	{
		StrItemTr4 *pItem;
		int CordY;

		pItem = &GlobTomb4.pAdr->pVetItems[ItemIndex];
		CordY = pItem->CordY + IncY;

		AggiornaPosizioneItem(ItemIndex, pItem->CordX, CordY, pItem->CordZ, -0x200);
	}
}

void LoadTombNextGenerationInject_TrngElevator(bool replace)
{
	ProcessInject(0x100989A4, (unsigned int)trng::SetSlotElevator, replace);
	ProcessInject(0x10097457, (unsigned int)trng::TwoBlockPlatformCeiling, false);
	ProcessInject(0x100973F2, (unsigned int)trng::TwoBlockPlatformFloor, false);
	ProcessInject(0x10096116, (unsigned int)trng::ControlTwoBlockPlatform, false);
	ProcessInject(0x10095E65, (unsigned int)trng::AggiornaPosY, replace);
}
