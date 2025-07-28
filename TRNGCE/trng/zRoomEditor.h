#pragma once
#include "structures.h"

namespace trng {
	extern char (&MexVersione)[30];
	extern int &TestBloccoTRY;
	extern char (&LastErroreLog)[512];
	extern char (&LastErrorDX)[1024];
	extern bool &TestAttivatoCrash;
	extern StrExtractNG &LastNGHeader;
	extern StrSalvaVettoriRemap &SalvaVettoriRemap;
	extern StrNGConstants &MainBaseCostanti;

	char *TrovaDirectoryCorrente(void);
	char ** Split(char *pStringa, char Separatore, int* pTotPezzi, char *pBufferHost, char **pVetPtr, bool TestSoloPrimo);
	int InStr(DWORD Start, char *pTesto, const char *pFind);
	void CaricaNGConstants(WORD TipoLoading, StrNGConstants * pBaseCostanti, char *pNomeFile);
}

void LoadTombNextGenerationInject_ZRoomEditor(bool replace);
