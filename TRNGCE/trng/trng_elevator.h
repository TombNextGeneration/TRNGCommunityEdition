#pragma once
#include "../tomb4/types.h"
#include "structures.h"

namespace trng {
	void SetSlotElevator(void);
	void TwoBlockPlatformCeiling(tomb4::ITEM_INFO *item, long x, long y, long z, long *height);
	void TwoBlockPlatformFloor(tomb4::ITEM_INFO *item, long x, long y, long z, long *height);
	void ControlTwoBlockPlatform(short ItemIndex);
	void AggiornaPosY(int ItemIndex, int IncY);
	void PreparaElevator(void);
	void CalcolaInfoAnimDoor(StrScriptElevator *pElevatore);
	int GetNgleRoomIndice(int TombIndice);
	void GestionePortaAnimating(StrScriptElevator *pElevatore, bool TestApri);
	void ImpostaEventoNow(short GT_Evento, short Parameter);
}

void LoadTombNextGenerationInject_TrngElevator(bool replace);
