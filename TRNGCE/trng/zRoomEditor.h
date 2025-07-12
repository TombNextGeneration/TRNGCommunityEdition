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

	char *TrovaDirectoryCorrente(void);
	char ** Split(char *pStringa, char Separatore, int* pTotPezzi, char *pBufferHost, char **pVetPtr, bool TestSoloPrimo);
}

void LoadTombNextGenerationInject_ZRoomEditor(bool replace);
