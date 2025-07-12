#pragma once
#include "structures.h"

namespace trng {
	extern DWORD &OffsetPosLara;
	extern StrBaseMemAllocata &BaseAlloc;

	void * MallocMine(DWORD Size, const char *pDescrizione);
	bool FreeMine(void *pMemory);
	void SalvaDimensioniMesh(WORD *VetPtrMesh[], int TotMesh);
	void SetSlotMotorBoat(WORD SlotBoat, WORD SlotLaraBoat);
	void SetSlotRubberBoat(WORD SlotBoat, WORD SlotLaraBoat);
	void SetSlotMotorBikeLara(void);
	void InitSlotKayak(void);
	void InitSlotHydra(void);
	void InitSlotEnemySubMarine(void);
	bool EsisteDirectCB(int CB_Numero, WORD Flags);
	void RiassegnaAssignSlotNew(void);
	void InitSlot(void);
	bool IsNemicoEsploso(WORD SlotId);
	WORD ConvertiSlotAssigned(WORD SlotNow);
	bool SlotSempreAttivo(WORD Slot);
	short DaSalvare(StrItemTr4 *pItem);
	WORD ContaItemCreatiDaSalvare(void);
	void SalvaItemCreati(void);
}

void Inject_ZPatchesTomb4(bool replace);
