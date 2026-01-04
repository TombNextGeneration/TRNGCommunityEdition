#include "zRoomEditor.h"
#include "../inject.h"
#include "Tomb_NextGeneration.h"
#include "RoomEditor.h"

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

	char *GetFileTrle(const char *pNomeFile)
	{
		static char NomeTrle[256];

		sprintf_s(NomeTrle, "%s\\%s", Dir_Trle, pNomeFile);
		return NomeTrle;
	}

	// restituisce solo nome del file, senza cartella e senza estensione
	char *SoloNomeSenzaExt(char FileName[])
	{
		static char BufferTemp[256];

		int i;

		strcpy_s(BufferTemp, SoloNome(FileName));
		for (i = strlen(BufferTemp) - 1; i >= 0; i--) {
			if (BufferTemp[i] == '.') {
				BufferTemp[i] = 0;
				break;
			}
		}

		return BufferTemp;
	}

	char * SoloNome(char FileName[])
	{
		// restituisce solo il nome del file
		int i;

		for (i = strlen(FileName) - 1; i >= 0; i--) {
			if (FileName[i] == '\\')
				break;
		}
		if (i > 0 && FileName[i] == '\\') {
			return &FileName[i + 1];
		}
		return FileName;
	}

	// restituisce la data dell'ultima modifica di pNomeFile
	void GetDataDelFile(char *pNomeFile, FILETIME *pFileTime)
	{
		HANDLE InFile;

		InFile = CreateFile(pNomeFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (InFile == INVALID_HANDLE_VALUE)
			return;
		GetFileTime(InFile, NULL, NULL, pFileTime);
		CloseHandle(InFile);
	}

	// trasorma stringa numerica in numero. se non e' numero resituisce false
	bool PrendiNumero(char *pTesto, int *pValore)
	{
		if (sscanf_s(pTesto, "%d", pValore) != 1)
			return false;
		else
			return true;
	}

	// usato solo per debug di comandi script in modalita' tomb4
	// restituisce un testo descrittivo del trigger esportato pTrigger
	char *GetTestoScriptTrigger(StrScriptTrigger *pTrigger)
	{
		static const char * VetMexCmd[11] = {"<undefined>", "GOTO", "EXIT", "TCMD_SET_TIMER", "TCMD_SET_FULL_TIMER",
									"TCMD_SET_EXTRA_TIMER", "TCMD_SET_EXTRA_CONDITION", "TCMD_SET_OBJECT",
									"TCMD_LOG", "TCMD_PAUSE", "TCMD_TIMER_FIELD"};
		static char Buffer[300];
		static char MiniBuf[80];

		int i, j;
		int TipoCampoTrigger;  // SEZ_...
		int NumeroCampo;
		int Valore;
		int Indice;
		const char *pMexTipo;
		const char *pArg3;
		int z;
		StrNGConstants * pBaseCostanti;
		StrRecordSezione *pSezione;

		pBaseCostanti = &MainBaseCostanti;

		pMexTipo = "UNKNOWN";

		if ((pTrigger->Flags & TGROUP_COMMAND) == TGROUP_COMMAND) {
			switch (pTrigger->Object) {
			case TCMD_EXIT:
				// e' TCMD_EXIT e llora il terzo valore e' vero o false
				if (pTrigger->Timer == 0) {
					pArg3 = "FALSE";
				} else {
					pArg3 = "TRUE";
				}
				break;
			default:
				sprintf_s(MiniBuf, "%d ($%04X)", pTrigger->Timer, pTrigger->Timer);
				pArg3 = MiniBuf;
				break;
			}
			z = pTrigger->Object;
			if (z >= TCMD_MAX_ID)
				z = 0;

			sprintf_s(Buffer, "COMMAND: %s %s", VetMexCmd[z], pArg3);
			return Buffer;
		}

		TipoCampoTrigger = SEZ_TOT;
		NumeroCampo = 0;
		Valore = 0;

		if (pTrigger->Flags & TGROUP_FLIPEFFECT) {
			pMexTipo = "FLIPEFFECT";

			TipoCampoTrigger = SEZ_TRIGGERWHAT;
			NumeroCampo = 9;
			Valore = pTrigger->Object & 0x3ff;

			sprintf_s(MiniBuf, "<&> = %d  (E) = %d", pTrigger->Timer & 0xff, (pTrigger->Timer & 0x7f00) >> 8);
		}

		if (pTrigger->Flags & TGROUP_ACTION) {
			pMexTipo = "ACTION";
			TipoCampoTrigger = SEZ_TRIGGERWHAT;
			NumeroCampo = 11;
			Valore = pTrigger->Timer & 0xff;
			Indice = pTrigger->Object & 0x3ff;

			sprintf_s(MiniBuf, "NgleIndex=%d (E) = %d", Indice, (pTrigger->Timer & 0x7f00) >> 8);
		}


		if (pTrigger->Flags & TGROUP_CONDITION_TRIGGER) {
			pMexTipo = "CONDITION";
			TipoCampoTrigger = SEZ_TRIGGERTYPE;
			NumeroCampo = 12;
			Valore = pTrigger->Timer & 0xff;
			sprintf_s(MiniBuf, "<#> = %d (E) = %d", pTrigger->Object & 0x3ff, (pTrigger->Timer & 0x7f00) >> 8);
		}

		if (pTrigger->PluginId > 0) {

			sprintf_s(Buffer, "%s trigger of plugin with ScriptID=%d  <%s>", pMexTipo, pTrigger->PluginId, MiniBuf);

			return Buffer;
		}

		for (i = 0; i < pBaseCostanti->TotSezioni; i++) {
			pSezione = &pBaseCostanti->pVetSezioni[i];

			if (pSezione->TipoSezione == TipoCampoTrigger && pSezione->NumeroSezione == NumeroCampo) {

				// ok, ora cercare il numero specifico nella lista
				for (j = 0; j < pSezione->TotValori; j++) {
					if (pSezione->pVetValori[j].Numero == Valore) {
						// trovato
						// ora calcolare anche gli argomenti

						sprintf_s(Buffer, "%s trigger: \"%s\" <%s>", pMexTipo, pSezione->pVetValori[j].pDescrizione, MiniBuf);
						return Buffer;
					}
				}
			}
		}
		return MiniBuf;
	}
}

void LoadTombNextGenerationInject_ZRoomEditor(bool replace)
{
	ProcessInject(0x100E8792, (unsigned int)trng::TrovaDirectoryCorrente, replace);
	ProcessInject(0x100E905D, (unsigned int)trng::Split, replace);
	ProcessInject(0x100E88E4, (unsigned int)trng::InStr, replace);
	ProcessInject(0x100EC199, (unsigned int)trng::CaricaNGConstants, false);
	ProcessInject(0x100E87AC, (unsigned int)trng::GetFileTrle, replace);
	ProcessInject(0x100E9626, (unsigned int)trng::SoloNomeSenzaExt, replace);
	ProcessInject(0x100E95C6, (unsigned int)trng::SoloNome, replace);
	ProcessInject(0x100FBCEA, (unsigned int)trng::GetDataDelFile, replace);
	ProcessInject(0x10114BF2, (unsigned int)trng::PrendiNumero, replace);
	ProcessInject(0x100E8D4E, (unsigned int)trng::GetTestoScriptTrigger, replace);
}
