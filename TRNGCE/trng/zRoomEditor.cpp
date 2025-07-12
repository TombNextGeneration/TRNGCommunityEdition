#include "../inject.h"
#include "structures.h"

namespace trng {
	char (&MexVersione)[30] = *reinterpret_cast<decltype(&MexVersione)>(0x106A4BD0);
	int &TestBloccoTRY = *reinterpret_cast<decltype(&TestBloccoTRY)>(0x106A463C);
	char (&LastErroreLog)[512] = *reinterpret_cast<decltype(&LastErroreLog)>(0x106A49AC);
	char (&LastErrorDX)[1024] = *reinterpret_cast<decltype(&LastErrorDX)>(0x106A41EC);
	bool &TestAttivatoCrash = *reinterpret_cast<decltype(&TestAttivatoCrash)>(0x106A0788);
	StrExtractNG &LastNGHeader = *reinterpret_cast<decltype(&LastNGHeader)>(0x106A3AA0);
	StrSalvaVettoriRemap &SalvaVettoriRemap = *reinterpret_cast<decltype(&SalvaVettoriRemap)>(0x106A0790);

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
}

void LoadTombNextGenerationInject_ZRoomEditor(bool replace)
{
	ProcessInject(0x100E8792, (unsigned int)trng::TrovaDirectoryCorrente, replace);
	ProcessInject(0x100E905D, (unsigned int)trng::Split, replace);
}
