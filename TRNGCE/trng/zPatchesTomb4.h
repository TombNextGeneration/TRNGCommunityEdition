#pragma once
#include "structures.h"

namespace trng {
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
}

void Inject_ZPatchesTomb4(bool replace);
