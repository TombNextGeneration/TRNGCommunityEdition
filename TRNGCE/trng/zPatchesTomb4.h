#pragma once
#include "structures.h"

namespace trng {
	extern DWORD &OffsetPosLara;
	extern StrBaseMemAllocata &BaseAlloc;
	extern int &LivelloOldNumber;

	void SalvaDimensioniMesh(WORD *VetPtrMesh[], int TotMesh);
	bool FreeMine(void *pMemory);
	void * MallocMine(DWORD Size, const char *pDescrizione);
	void InitSlot(void);
	void SetSlotMotorBoat(WORD SlotBoat, WORD SlotLaraBoat);
	void SetSlotRubberBoat(WORD SlotBoat, WORD SlotLaraBoat);
	void SetSlotMotorBikeLara(void);
	void InitSlotKayak(void);
	void InitSlotHydra(void);
	void InitSlotEnemySubMarine(void);
	bool EsisteDirectCB(int CB_Numero, WORD Flags);
	void RiassegnaAssignSlotNew(void);
	WORD ConvertiSlotAssigned(WORD SlotNow);
	bool IsNemicoEsploso(WORD SlotId);
	WORD ContaItemCreatiDaSalvare(void);
	short DaSalvare(StrItemTr4 *pItem);
	bool SlotSempreAttivo(WORD Slot);
	void SalvaItemCreati(void);
	void InizializzaAdrImmediati(void);
	void InitCustomize(void);
}

void LoadTombNextGenerationInject_ZPatchesTomb4(bool replace);
