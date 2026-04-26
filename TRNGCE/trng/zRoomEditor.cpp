#include "zRoomEditor.h"
#include <cstdlib>
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
	DWORD &RetValue = *reinterpret_cast<decltype(&RetValue)>(0x106A3BB4);

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

	// estrae dal testo complessivo Testo la sezione NomeParte
	// Per esempio se NomeParte = "TEXT" estrarra il testo contenuto
	// in <TEXT> <END_TEXT>
	// ATTENZIONE: il testo restituito da questa funzione e' stato allocato
	// dinamicamente con malloc() per cui andrebbe rilasciato quando non
	// viene piu' utilizzato
	// nota: Se TestRimuovi = true la porzione estratta viene eliminata
	// dal testo sorgente (*Testo),
	// se invece e' false viene lasciata
	char *EstraeParteTesto(char *Testo, const char *NomeParte, bool TestRimuovi)
	{
		DWORD j;
		int Indice;
		char StartSection[80];
		char EndSection[80];
		DWORD z;
		char *pResult;
		DWORD SizeTesto;
		DWORD Inizio, Fine;

		sprintf_s(StartSection, "<%s>", NomeParte);
		Indice = InStr(0, Testo, StartSection);

		if (Indice < 0)
			return NULL;
		j = Indice;
		Inizio = j;

		j += strlen(StartSection);
		// trovare parte finale
		sprintf_s(EndSection, "<END_%s>", NomeParte);
		z = InStr(j, Testo, EndSection);
		if (z < 0) {
			return NULL;
		}
		Fine = z + strlen(EndSection);

		SizeTesto = z - j;

		pResult = (char*) malloc(SizeTesto + 2);
		if (pResult == NULL)
			return NULL;
		memcpy(pResult, &Testo[j], SizeTesto);
		pResult[SizeTesto] = 0;

		if (TestRimuovi == true) {
			if (Testo[Fine] == 0x0a)
				Fine++;

			memmove(&Testo[Inizio], &Testo[Fine], strlen(&Testo[Fine]) + 1);
		}

		return pResult;
	}

	// funzione usata per leggere dati testuali di media manager
	// cerca in testo il tag pNomeTag. se lo trova restituisce il puntatore
	// agli argomenti del tag ed elimina l'intera accoppiata #NomeTag#=Argomenti
	// da pTesto
	// se non lo trova restituisce NULL
	char *EstraeDatiTag(char *pTesto, const char *pNomeTag)
	{
		static char BufArgomenti[512];

		DWORD i, j;
		char *pChar;
		DWORD n, z;

		i = InStr(0, pTesto, pNomeTag);
		if (i == (DWORD) -1)
			return NULL;
		j = i + strlen(pNomeTag);

		pChar = PrendiLinea(pTesto, &j);

		if (pChar == NULL)
			return NULL;
		if (pChar[0] == 0) {
			BufArgomenti[0] = '~';
			BufArgomenti[1] = 0;
		} else {
			strcpy_s(BufArgomenti, pChar);
		}
		// ora togliere tutto il blocco di testo di questo tag.
		n = strlen(pTesto);
		for (z = i; z < n - strlen(BufArgomenti); z++) {
			pTesto[z] = pTesto[z + strlen(BufArgomenti)];
		}
		pTesto[z] = 0;

		return BufArgomenti;
	}

	// cerca a partire da *pIndice e aggiorna il indice a posizione immediatamente
	// seguente l'ultimo codice di ritorno a capo incontrato
	char *PrendiLinea(char *pBufLinea, DWORD *pIndice)
	{
		static char StrArgomenti[256];

		DWORD Indice;
		DWORD i, j;
		char Car;
		DWORD z;

		Indice = *pIndice;
		z = 0;
		StrArgomenti[0] = 0;
		for (j = Indice; j < strlen(pBufLinea); j++) {
			Car = pBufLinea[j];
			if (Car == '\n' || Car == '\r')
				break;
			StrArgomenti[z++] = Car;

		}
		StrArgomenti[z] = 0;

		// superare tutti gli eventuali caratteri di fine linea
		for (i = j; i < strlen(pBufLinea); i++) {
			Car = pBufLinea[i];
			if (Car != '\n' && Car != '\r')
				break;
		}

		*pIndice = i;
		return StrArgomenti;
	}

	// verifica che testo in StrNumero sia corretto in decimale o esadecimale
	// Se lo e' lo converte e restituisce il valore, se non lo e' restituisc
	// false e imposta TestErrore = true
	int GetArgNumerico(char *StrNumero, bool *TestErrore)
	{
		char *pChar;
		int Valore;

		pChar = Trim(StrNumero);

		if (*pChar == '$') {

			pChar++;

			if (sscanf_s(pChar, "%x", &Valore) != 1) {
				*TestErrore = true;
				Valore = 0;
			} else {
				*TestErrore = false;
			}
		} else {

			if (sscanf_s(pChar, "%d", &Valore) != 1) {
				*TestErrore = true;
				Valore = 0;
			} else {
				*TestErrore = false;
			}
		}

		return Valore;
	}

	// elimina spazi dai lati della stringa
	char *Trim(char *pStringa)
	{
		static char BufStringa[512];

		int i;
		int Fine;
		int Inizio;
		int j;

		// trovare primo carattere diverso da spazio
		for (i = 0; i < (int) strlen(pStringa); i++) {
			if (pStringa[i] != ' ')
				break;
		}

		Inizio = i;

		for (i = strlen(pStringa) - 1; i >= 0; i--) {
			if (pStringa[i] != ' ')
				break;
		}

		Fine = i;
		if (Fine < Inizio) {
			BufStringa[0] = 0;
			return BufStringa;
		}

		j = 0;
		for (i = Inizio; i <= Fine; i++) {
			BufStringa[j++] = pStringa[i];
		}
		BufStringa[j] = 0;

		return BufStringa;
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
	ProcessInject(0x100E9398, (unsigned int)trng::EstraeParteTesto, replace);
	ProcessInject(0x100E92A0, (unsigned int)trng::EstraeDatiTag, replace);
	ProcessInject(0x100E91CE, (unsigned int)trng::PrendiLinea, replace);
	ProcessInject(0x100E9503, (unsigned int)trng::GetArgNumerico, replace);
	ProcessInject(0x100E8AE3, (unsigned int)trng::Trim, replace);
}
