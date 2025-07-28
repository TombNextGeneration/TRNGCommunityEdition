#include "zRoomEditor.h"
#include "../inject.h"

namespace trng {
	char (&MexVersione)[30] = *reinterpret_cast<decltype(&MexVersione)>(0x106A4BD0);
	int &TestBloccoTRY = *reinterpret_cast<decltype(&TestBloccoTRY)>(0x106A463C);
	char (&LastErroreLog)[512] = *reinterpret_cast<decltype(&LastErroreLog)>(0x106A49AC);
	char (&LastErrorDX)[1024] = *reinterpret_cast<decltype(&LastErrorDX)>(0x106A41EC);
	bool &TestAttivatoCrash = *reinterpret_cast<decltype(&TestAttivatoCrash)>(0x106A0788);
	StrExtractNG &LastNGHeader = *reinterpret_cast<decltype(&LastNGHeader)>(0x106A3AA0);
	StrSalvaVettoriRemap &SalvaVettoriRemap = *reinterpret_cast<decltype(&SalvaVettoriRemap)>(0x106A0790);
	StrNGConstants &MainBaseCostanti = *reinterpret_cast<decltype(&MainBaseCostanti)>(0x106CF2D0);

	char *TrovaDirectoryCorrente(void)
	{
		static char MiaDirectory[256];

		GetCurrentDirectory(255, MiaDirectory);
		return MiaDirectory;
	}

	// restituisce un vettore di puntatori stringhe alle parti di pStringa
	// divise dal (singolo) carattere Separatore
	// imposta in pTotPezzi il numero di elementi trovati
	// nota: se pBufferHost e' diverso da NULL, verra' usato questo buffere
	// per salvare le singole stringhe
	// Stesso discorso per pVetPtr che se non e' null ospitera' un vettore
	// di puntatori carattere
	// se TestSoloPrimo = true, si ferma nel dividere al primo separatore
	// ignorando quelli eventalmente successivi
	// nota e' previsto che non possano esserci piu di 50 elementi finali
	// l'intera pStringa non deve essere piu' lunga di 1023 caratteri
	char ** Split(char *pStringa, char Separatore, int* pTotPezzi, char *pBufferHost, char **pVetPtr, bool TestSoloPrimo)
	{
		static char * pVettore[50];
		static char Buffer[1024];

		DWORD		i;
		int  IndiceOld;
		int		TotItem;
		char *pTemp;
		DWORD  MaxLen;
		char *pOut;
		char **pVetPointer;

		pOut = Buffer;

		pVetPointer = pVettore;

		IndiceOld = 0;
		strcpy_s(Buffer, pStringa);
		TotItem = 0;
		MaxLen = strlen(pOut);

		for (i = 0; i < MaxLen; i++) {
			if (pOut[i] == Separatore) {
				// salvare il precedente
				pVetPointer[TotItem++] = &pOut[IndiceOld];
				pOut[i] = 0;
				IndiceOld = i + 1;
				if (TestSoloPrimo)
					break;
			}
		}

		// salvare ultimo indiceold a meno che non sia nullo
		pTemp = &pOut[IndiceOld];
		if (strlen(pTemp) > 0) {
			pVetPointer[TotItem++] = pTemp;
		}

		*pTotPezzi = TotItem;
		return pVetPointer;
	}

	// simula comportamento di InStr di visual basic, con la differenza
	// che la ricerca parte da indice 0 e se non trova nulla restituisce -1
	// invece che 0
	int InStr(DWORD Start, char *pTesto, const char *pFind)
	{
		DWORD i;
		DWORD n;
		DWORD j;
		DWORD TotCar;
		char BufSingle[2000];

		n = strlen(pFind);
		if (n > strlen(pTesto))
			return -1;

		TotCar = strlen(pTesto) - n + 1;

		for (i = Start; i < TotCar; i++) {
			for (j = 0; j < n; j++)
				BufSingle[j] = pTesto[i + j];
			BufSingle[j] = 0;

			if (_stricmp(BufSingle, pFind) == 0)
				return i;
		}
		return -1;
	}

	// carica l'intero file ng_constants.txt in memoria
	// TipoLoading e' una costant LNGC_...
	// se TestMain = true carfica da risorse il file principale
	// se testmain = false carica "my_ng_constants.txt"
	// e aggiorna in modo dinamico le voci trovate
	void CaricaNGConstants(WORD TipoLoading, StrNGConstants * pBaseCostanti, char *pNomeFile)
	{
		__try { throw __func__; } __finally {}
	}
}

void LoadTombNextGenerationInject_ZRoomEditor(bool replace)
{
	ProcessInject(0x100E8792, (unsigned int)trng::TrovaDirectoryCorrente, replace);
	ProcessInject(0x100E905D, (unsigned int)trng::Split, replace);
	ProcessInject(0x100E88E4, (unsigned int)trng::InStr, replace);
	ProcessInject(0x100EC199, (unsigned int)trng::CaricaNGConstants, false);
}
