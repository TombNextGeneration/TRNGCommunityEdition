#pragma once
#include "structures.h"

namespace trng {
	int GestioneKeyPad(int TipoKeyPad, WORD OcbCode, WORD Slot);
	void CambiaTasto(int *pTree, int IndiceTasto, int Valore, bool TestRestore);
	bool VerificaSwitchKeypad(void);
}

void LoadTombNextGenerationInject_TrngKeypad(bool replace);
