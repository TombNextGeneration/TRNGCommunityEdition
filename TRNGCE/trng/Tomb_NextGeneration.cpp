#include "Tomb_NextGeneration.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../inject.h"
#include "zPatchesTomb4.h"
#include "zRoomEditor.h"
#include "ListTr4Patch.h"
#include "plugin.h"
#include "../tomb4/specific/winmain.h"
#include "../tomb4/specific/dxshell.h"
#include "../tomb4/game/newinv.h"
#include "trng_weather.h"
#include "Oggetti.h"
#include "../tomb4/game/lara.h"
#include "../tomb4/game/objects.h"

namespace trng {
	StrGlobaliTomb4 &GlobTomb4 = *reinterpret_cast<decltype(&GlobTomb4)>(0x101C9578);
	StrGlobAddress &AdrGlobali = *reinterpret_cast<decltype(&AdrGlobali)>(0x10462630);
	StrMyGlob &MyGlobPrivate = *reinterpret_cast<decltype(&MyGlobPrivate)>(0x101B94E0);
	StrBaseCustomize &BaseCustomize = *reinterpret_cast<decltype(&BaseCustomize)>(0x104C54C8);
	StrGlobMisc &BaseGlobMisc = *reinterpret_cast<decltype(&BaseGlobMisc)>(0x103E27D0);
	char (&Dir_Trle)[256] = *reinterpret_cast<decltype(&Dir_Trle)>(0x101B93E0);
	int &TotAllocata = *reinterpret_cast<decltype(&TotAllocata)>(0x1054D384);
	bool &TestDebugLog = *reinterpret_cast<decltype(&TestDebugLog)>(0x1054D370);
	DWORD &DefValoreZero = *reinterpret_cast<decltype(&DefValoreZero)>(0x1054D37C); // usato per ptr_AdrDiagnotica
	// 1= Tomb4.exe,  2=winroomedit , 3=pc2tom.exe
	int &TipoExe = *reinterpret_cast<decltype(&TipoExe)>(0x101B93D8);
	int &TotCheckMemory = *reinterpret_cast<decltype(&TotCheckMemory)>(0x101B2914);
	StrBaseVarAll &BaseVariableTRNG = *reinterpret_cast<decltype(&BaseVariableTRNG)>(0x1054CFC8);
	StrPanelloSavegame &BasePanello = *reinterpret_cast<decltype(&BasePanello)>(0x1054CAF8);
	StrBaseScriptImages &BaseScriptImages = *reinterpret_cast<decltype(&BaseScriptImages)>(0x1054A700);
	StrBaseTriggerGroups &BaseTriggerGroups = *reinterpret_cast<decltype(&BaseTriggerGroups)>(0x104C7168);
	StrBaseCustomize &BaseCustomizeDefault = *reinterpret_cast<decltype(&BaseCustomizeDefault)>(0x104C3828);
	BaseScriptOrganizer &BaseOrganizer = *reinterpret_cast<decltype(&BaseOrganizer)>(0x1048E0A8);
	StrBaseGlobalTriggers &BaseGlobalTriggers = *reinterpret_cast<decltype(&BaseGlobalTriggers)>(0x10489A50);
	StrBaseScriptEnvCondition &BaseEnvConditions = *reinterpret_cast<decltype(&BaseEnvConditions)>(0x10462848);
	StrBaseEffects &BaseEffects = *reinterpret_cast<decltype(&BaseEffects)>(0x10460558);
	StrScriptLevel &ScriptLevelNow = *reinterpret_cast<decltype(&ScriptLevelNow)>(0x10460540);
	StrBaseDiagnostica &BaseDiagnostica = *reinterpret_cast<decltype(&BaseDiagnostica)>(0x1045FA58);
	StrDatiVariabili &DatiVariabili = *reinterpret_cast<decltype(&DatiVariabili)>(0x1045F868); //level o lara
	StrDatiVariabili &DatiVarLara = *reinterpret_cast<decltype(&DatiVarLara)>(0x1045F678); // solo lara
	BaseAnimScript &BaseAnimations = *reinterpret_cast<decltype(&BaseAnimations)>(0x1045A470);
	StrRecording &BaseDemo = *reinterpret_cast<decltype(&BaseDemo)>(0x10425000);  // to record or play demo
	StrDemo &DemoTitle = *reinterpret_cast<decltype(&DemoTitle)>(0x10424D80);
	StrDemo &DemoLevel = *reinterpret_cast<decltype(&DemoLevel)>(0x10424B00);
	StrBaseCutscene &BaseCutscene = *reinterpret_cast<decltype(&BaseCutscene)>(0x104245A8);  // data about cutscene and demos
	StrBaseSwapAnim &BaseSwapAnim = *reinterpret_cast<decltype(&BaseSwapAnim)>(0x104239E8);
	StrBaseMemSwapAnim &BaseMemSwapAnim = *reinterpret_cast<decltype(&BaseMemSwapAnim)>(0x10423850); // to save/reload from savegame the last swapping to restore situation
	StrBaseSpeechActor &BaseSpeechActor = *reinterpret_cast<decltype(&BaseSpeechActor)>(0x1041D830); // to store PARAM_ACTOR_SPEECH
	StrPluginNames (&VetPluginNgle)[MAX_PLUGINS_NGLE] = *reinterpret_cast<decltype(&VetPluginNgle)>(0x10418030);
	StrTablePluginIdFloor &PluginFloorTable = *reinterpret_cast<decltype(&PluginFloorTable)>(0x10408028); // to discover the owner for each trigger in floordata
	StrTableScriptPlugin &PluginScriptTable = *reinterpret_cast<decltype(&PluginScriptTable)>(0x103E2820); // to discover the id of script commands (triggergroup, customize an parameters)
	int (&VetMeshSwapSlot)[78] = *reinterpret_cast<decltype(&VetMeshSwapSlot)>(0x10159AF0);
	int (&VetStandardSwapMesh)[107] = *reinterpret_cast<decltype(&VetStandardSwapMesh)>(0x10159C28);
	int (&VetSlotMeshMoveables)[122] = *reinterpret_cast<decltype(&VetSlotMeshMoveables)>(0x10159DD4);
	TYPE_tombInviaLog &tombInviaLog = *reinterpret_cast<decltype(&tombInviaLog)>(0x1015999C);
	BYTE &FlagMicroCaratteri = *reinterpret_cast<decltype(&FlagMicroCaratteri)>(0x1054D37A);
	// usata per nome finestra setup, per quella principale lo si fa in modo immediato
	char (&MexNewWindowTitle)[256] = *reinterpret_cast<decltype(&MexNewWindowTitle)>(0x103DFC4C);
	char (&BufferLog)[8192] = *reinterpret_cast<decltype(&BufferLog)>(0x101B73D8);

	// modifica i damage sulla base di elenco Enemy
	void ImpostaEnemyDamage(void)
	{
		__try { throw __func__; } __finally {}
	}

	// chiamata nel momento in  cui la libreria viene collegata
	// se restituisce false bisogna abortire il programma
	bool Inizializza(void)
	{
		static int VetInventory[115] = {
			0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
			0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2,
			0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC,
			0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
			0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0,
			0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA,
			0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4,
			0xF5, 0xF6, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
			0x100, 0x101, 0x128, 0x129, 0x12A, 0x12B, 0x12C, 0x12D,
			0x12E, 0x12F, 0x130, 0x131, 0x15D, 0x15E, 0x15F, 0x160, 0x161, 0x162,
			0x163, 0x164, 0x165, 0x166, 0x167, 0x169, 0x16A, 0x16B, 0x16C,
			0x16E, 0x16F, 0x170, 0x171, 0x172, 0x173, 0x174, -1
		};

		char BufProductTrngVersion[80];
		bool TestEsito;
		int i;
		char *pChar;

		TestEsito = true;
		strcpy_s(Dir_Trle, TrovaDirectoryCorrente());
		memset(&GlobTomb4, 0, sizeof(StrGlobaliTomb4));
		LinkGlobTomb4Structures();
		memset(&MyGlobPrivate, 0, sizeof(StrMyGlob));
		BaseAlloc.TotAllocata = 0;
		TotAllocata = 0;

		TestDebugLog = IsAttivoDebugger();

		srand((DWORD) time(NULL));

		pChar = TrovaVersioneFile("Tomb_NextGeneration.dll", BufProductTrngVersion);

		if (pChar == NULL) {
			MexVersione[0] = 0;
		} else {
			strcpy_s(MexVersione, pChar);
		}

		GlobTomb4.HardwareB.m_index = -1;
		GlobTomb4.HardwareB.Attivo = false;
		GlobTomb4.pDiagnostica->TestSospendiBreakCond = false;
		GlobTomb4.pAdrDiagnostica = &DefValoreZero;

		MyGlobPrivate.TestDebugVersione = false;

		// valori validi per qualunque exe chiamante

		for (i = 0; VetInventory[i] != -1; i++) {
			GlobTomb4.VetInventory[i] = VetInventory[i];
		}

		GlobTomb4.VetInventory[i] = -1;

		CalcolaVersione(&GlobTomb4.BaseVersione);

		TestBloccoTRY = 0;
		LastErroreLog[0] = 0;
		LastErrorDX[0] = 0;
		TestAttivatoCrash = false;
		GlobTomb4.TestSetCamera = false;

		// tomb4
		TipoExe = EXE_TOMB4;

		TotCheckMemory = 0;
		LastNGHeader.NWords = 0;
		LastNGHeader.Result = 0;
		LastNGHeader.pNGArray = NULL;
		LastNGHeader.SizeHeader = 0;
		LastNGHeader.StartOffset = 0;
		SalvaVettoriRemap.TestAttivo = false;

		// il plugin trng considerarlo caricato per qualunque exe
		InizializzaPluginTrng();

		//TOMB4

		// inizializza indirizzi tomb4 in puntatori variabili e procedure
		// Inizializza valori globali
		InizializzaTomb4();
		// aggiorna i blocchi con tutti i plugin caricati

		GlobTomb4.LastTombMexage[0] = 0;

		TestEsito = StartUpTomb4();
		if (TestEsito) {
			InviaErroreLog("The library has been successfully attached!", 0, false);
		} else {
			InviaErroreLog("ERROR: failed the attaching of Tomb_NextGeneration.dll", 0, false);
		}

		return TestEsito;
	}

	// inserisce in globtomb4 i puntatori alle varie struture globali separate
	void LinkGlobTomb4Structures(void)
	{
		GlobTomb4.pBaseVariableTRNG = &BaseVariableTRNG;
		GlobTomb4.pBasePanello = &BasePanello;
		GlobTomb4.pBaseScriptImages = &BaseScriptImages;
		GlobTomb4.pBaseTriggerGroups = &BaseTriggerGroups;
		GlobTomb4.pBaseCustomize = &BaseCustomize;
		GlobTomb4.pBaseCustomizeDefault = &BaseCustomizeDefault;
		GlobTomb4.pBaseOrganizer = &BaseOrganizer;
		GlobTomb4.pBaseGlobalTriggers = &BaseGlobalTriggers;
		GlobTomb4.pBaseEnvConditions = &BaseEnvConditions;
		GlobTomb4.pAdr = &AdrGlobali;
		GlobTomb4.pBaseEffects = &BaseEffects;
		GlobTomb4.pScriptLevelNow = &ScriptLevelNow;
		GlobTomb4.pDiagnostica = &BaseDiagnostica;
		GlobTomb4.pDatiVariabili = &DatiVariabili; //level o lara
		GlobTomb4.pDatiVarLara = &DatiVarLara; // solo lara
		GlobTomb4.pBaseAnimations = &BaseAnimations;
		GlobTomb4.pBaseDemo = &BaseDemo;  // to record or play demo
		GlobTomb4.pDemoTitle = &DemoTitle;
		GlobTomb4.pDemoLevel = &DemoLevel;
		GlobTomb4.pBaseCutscene = &BaseCutscene;  // data about cutscene and demos
		GlobTomb4.pBaseSwapAnim = &BaseSwapAnim;
		GlobTomb4.pBaseMemSwapAnim = &BaseMemSwapAnim; // to save/reload from savegame the last swapping to restore situation
		GlobTomb4.pBaseSpeechActor = &BaseSpeechActor; // to store PARAM_ACTOR_SPEECH
		GlobTomb4.pVetPluginNgle = VetPluginNgle;
		GlobTomb4.pPluginFloorTable = &PluginFloorTable; // to discover the owner for each trigger in floordata
		GlobTomb4.pPluginScriptTable = &PluginScriptTable; // to discover the id of script commands (triggergroup, customize an parameters)
		GlobTomb4.pMisc = &BaseGlobMisc;

		GlobTomb4.pVetMemorySavegame = VetMemorySavegame; // records about savegame memory  (ngle)
		GlobTomb4.pVetItemMemory = VetItemMemory;     // records about item memory (ngle)
		GlobTomb4.pVetCodeMemory = VetCodeMemory;    // records about code memory (ngle)
		GlobTomb4.pVetSlotMemory = VetSlotMemory;      // records about slot memory (ngle)
		GlobTomb4.pVetMemoryAnimation = VetMemoryAnimation;  // records about animation memory (ngle)
		GlobTomb4.pVetMemoryInventory = VetMemoryInventory;  // record about inventory memory (ngle)

		GlobTomb4.pVetMeshSwapSlot = VetMeshSwapSlot;
		GlobTomb4.pVetStandardSwapMesh = VetStandardSwapMesh;
		GlobTomb4.pVetSlotMeshMoveables = VetSlotMeshMoveables;

		// check control for 1.3.0.0 version
		GlobTomb4.CheckValue1_3_0_0 = 0x01234567;
	}

	// controlla (in chiaro) se e' presente il debugger
	bool IsAttivoDebugger(void)
	{
		FARPROC AdrGetProc;
		HMODULE ModuleHandle;
		TYPE_DebugPresente ProcIsDebuggerPresent;

		ModuleHandle = GetModuleHandle("kernel32.dll");
		if (ModuleHandle == NULL)
			return false;

		AdrGetProc = GetProcAddress(ModuleHandle, "IsDebuggerPresent");
		if (AdrGetProc == NULL)
			return false;

		ProcIsDebuggerPresent = (TYPE_DebugPresente) AdrGetProc;

		if (ProcIsDebuggerPresent())
			return true;
		return false;
	}

	// estrae dall'eseguibile NomeFile la stringa che descrive la versione sia  FileVersion
	// che ProductVersion
	// se non  c'e' versione restituisce NULL
	char *TrovaVersioneFile(const char *NomeFile, char *pBufProductVersion)
	{
		__try { throw __func__; } __finally {}
	}

	// inserisce in globtomb4 i numeri di versione di questa dll
	// in modo da poterli salvare in tutti gli header ng
	// char MexVersione[] = "1.1.9.8";
	void CalcolaVersione(StrVersionHeader *pBaseVer)
	{
		char **pVetParti;
		int TotParti;
		int i;
		int Numero;

		pVetParti = Split(MexVersione, '.', &TotParti, NULL, NULL, false);
		for (i = 0; i < 4; i++) {
			pBaseVer->VetVersione[i] = 0;
		}

		for (i = 0; i < TotParti; i++) {
			// convertire numero

			if (sscanf_s(pVetParti[i], "%d", &Numero) != 1)
				return;

			pBaseVer->VetVersione[i] = (WORD) Numero;
		}
	}

	void InizializzaTomb4(void)
	{
		char NomeFile[256];
		char *pLinea;
		WORD *pWord;

		InitRainSnow();
		InizializzaAdrImmediati();

		InitStringOffsets();
		AnalisiWideScreen();
		// poi toglierla
		// vedere se tomb4 e' stato lanciato in modalita' setup
		GlobTomb4.TestSetup = false;
		pLinea = GetCommandLine();
		if (InStr(0, pLinea, "-setup") >= 0)
			GlobTomb4.TestSetup = true;

		// qui consentire a utente di entrare in setup
		if (GlobTomb4.TestSetup == false) {
			CreaFinestraAvviso();
		}

		GlobTomb4.TestTr4ConHeaderNG = false;
		GlobTomb4.TestSavegameConHeaderNG = false;
		GlobTomb4.BaseFMV.OperazioneAltEnter = OAE_NORMALE;
		GlobTomb4.pVetSalvaSizeMesh = NULL;
		GlobTomb4.TotProgressiveActions = 0;
		GlobTomb4.pDiagnostica->TestPremutoF7 = false;
		GlobTomb4.SavegameLastName[0] = 0;
		GlobTomb4.SavegameLastNumber = -1;
		GlobTomb4.PrintString.DefPosition = STRING_BOTTOM_CENTER;
		GlobTomb4.PrintString.DefBlinkSpeed = 0x10;
		GlobTomb4.PrintString.DefFlagsMicro = 0;
		GlobTomb4.PrintString.DefALLFlagsMicro = 0;
		GlobTomb4.PrintString.DefFlags = FTS_ALIGN_CENTER;
		GlobTomb4.PrintString.DefColore = FC_WHITE;
		GlobTomb4.BaseSfxPlayed.TotSuonati = 0;
		GlobTomb4.ScrollingEndIndex = -1;
		GlobTomb4.ScrollingLastIndex = -1;
		GlobTomb4.TestFirstTime = false;
		GlobTomb4.BaseFMV.IndiceUltimoFMVAttivato = -1;
		GlobTomb4.pDiagnostica->FlagsDgx = SCRIPT_IGNORE; // tutto
		GlobTomb4.pDiagnostica->DgxExtra = 0; // nullo
		GlobTomb4.TestFirstLoadTitle = true;
		GlobTomb4.BaseImages.HdcTomb = NULL;
		LivelloOldNumber = 0;
		GlobTomb4.TestDebuggerInProgress = IsAttivoDebugger();

		// carica file memoria di tomb4 originale.
		MyGlobPrivate.pTomb4Mem = CaricaTomb4Mem();

		// primo controllo
		Controllo1FileMancanti();

		InitPrintTextColors();
		InitBarDefault();

		// imposta valori di default sia in normale customize che valori
		// di default
		InitCustomize();
		FlagMicroCaratteri = GlobTomb4.PrintString.DefALLFlagsMicro;

		sprintf_s(NomeFile, "%s\\%s", Dir_Trle, "script.dat");
		MexNewWindowTitle[0] = 0;

		// qui c'e' un controllo su trng.set basato su somma indici pari
		LeggeNGScriptDat(NomeFile);

		InitDgxErrors();
		GlobTomb4.TestNoDamageRollingBallIndex = -1;

		// se lo script NON ha alcun header ng attivare crs
		if (MyGlobPrivate.TestNG_NoScript == true) {
			GlobTomb4.ScriptOptions.MainFlags |= ngfm_CRS;
		}

		// se c'e' flag speciali di abilitazioni feature volute da trlm2009
		// attivarle ora
		if (GlobTomb4.ScriptOptions.MainFlags & ngfm_Enable_Trlm_Options) {
			GlobTomb4.ScriptOptions.MainFlags |= ngfm_CRS;
		}

		if ((GlobTomb4.ScriptOptions.MainFlags & ngfm_CRS) == 0) {
			GlobTomb4.MyPrefTomb.Flags = FPT_NO_RESUME_CRASH;
		}

		ImpostaCostantiNascoste();

		InitRemapItemGroup();

		VerifyImagesPix();
		LeggeMieSettingRegister();
		VerificaAttivazioneSoftFullScreen();
		VerificaAttivazioneNoWaitingRefresh();
			// crea una finestra nera senza, bordi o caption
		// in modo da non vedere il desktop quando tra poco si ridurra lo schermo
		// da eseguire quando c'e' fullscreen (servira' per i filmati o per soft_full_screen)
		if (GlobTomb4.TestWindowedModeRegister == false && GlobTomb4.TestSetup == false) {
			CreaBlackWindow();
		}

		if (GlobTomb4.TestSoftFullScreen == true && GlobTomb4.TestSetup == false) {
			RestyleWindow();
		}
		// se e' atttivo diagnostica caricare
		// le costanti con i nomi dei trigger
		if ((GlobTomb4.ScriptOptions.MainFlags & ngfm_Diagnostica) != 0) {

			CaricaNGConstants(LNGC_MAIN, &MainBaseCostanti, NULL);
		}

		// salvare i valori originali di flags

		pWord = (WORD *) tomb4::options_table; // pVetFlagsInventoryItems
		memcpy(&GlobTomb4.VetSalvaFlagItems[0], pWord, 120 * 2);

		// inizializza (elimina) log fmv
		InitFmvLog("START TOMB4", true);

		if (MyGlobPrivate.TestNG_NoScript == true) {
			strcat_s(GlobTomb4.BaseMissing.MexMissing, "WARNING: Missing Header NG in \"script.dat\" file. (The script.dat is an old version)\r\n");
			GlobTomb4.BaseMissing.TestAvvisi = true;
		}
	}

	bool InviaLog(const char *pMessaggio)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMai

		// se c'e' debugger attivo invia il messaggio nel finestra di output

		if (TestDebugLog) {
			OutputDebugString(pMessaggio);
			OutputDebugString("\r\n");
		}

		if (*pTombWind4 == 0)
			return false;
		if ((GlobTomb4.ScriptOptions.MainFlags & ngfm_Diagnostica) != 0 && (GlobTomb4.pDiagnostica->FlagsDgx & DGX_ERRORS) != 0) {
			GestioneDgxErrori(pMessaggio);
		}
		tombInviaLog(1, pMessaggio);
		return true;
	}

	void GestioneDgxErrori(const char *pMex)
	{
		__try { throw __func__; } __finally {}
	}

	bool ScopreModoFullScreen(void)
	{
		if (tomb4::G_dxptr == NULL)
			return false;

		if (tomb4::G_dxptr->Flags & 0x02)
			return false;
		return true;
	}

	// MainMenuOffsets, NewGameTitle, LoadGameTitle, NewGameList, LoadGameList, OptionSettings,OptionCmdList, PauseScreen,
	// StatList, InventoryItemName, ExamineText

	void InitStringOffsets(void)
	{
		__try { throw __func__; } __finally {}
	}

	// verifica se schermo  attuale e' di tipo widescreen
	void AnalisiWideScreen(void)
	{
		StrWideScreen *pWide;
		float SizeX, SizeY;

		pWide = &GlobTomb4.BaseWideScreen;

		pWide->SizeX = GetSystemMetrics(SM_CXSCREEN);
		pWide->SizeY = GetSystemMetrics(SM_CYSCREEN);

		SizeX = (float) pWide->SizeX;
		SizeY = (float) pWide->SizeY;

		GlobTomb4.BaseWideScreen.RapportoSchermo = SizeX / SizeY;
	}

	BYTE *CaricaTomb4Mem(void)
	{
		__try { throw __func__; } __finally {}
	}

	// primo controllo per presenza di esistenza di file script.dat english/other.dat
	void Controllo1FileMancanti(void)
	{
		static const char *VetLingue[8] = {"english.dat", "german.dat", "french.dat", "italian.dat",
			"spanish.dat", "us.dat", "japan.dat", NULL};
		static const char *VetStandard[3] = {"load.bmp", "data\\uklogo.pak", NULL};

		StrBaseMissing *pLog;
		int i;

		pLog = &GlobTomb4.BaseMissing;
		memset(pLog, 0, sizeof(StrBaseMissing));

		if (EsisteFile("script.dat") == false) {
			strcat_s(pLog->MexMissing, "CRITICAL ERROR: Missing \"SCRIPT.DAT\" file\r\n");
			pLog->TestErrori = true;
		} else {
			// lo script.dat c'e'
			pLog->TestScriptPresenti = true;

			// vedere se c'e' almeno un file .dat di lingue
			// prima cercare i file language clasici
			i = 0;
			while (VetLingue[i]) {
				if (EsisteFile(VetLingue[i]) == true)
					break;
				i++;
			}
			if (VetLingue[i] == NULL) {
				pLog->TestAvvisi = true;
				strcat_s(pLog->MexMissing, "WARNING: not found any standard language.dat (english.dat, german.dat ect)\r\n");
			}
		}

		i = 0;
		while (VetStandard[i]) {
			if (EsisteFile(VetStandard[i]) == false) {
				pLog->TestErrori = true;
				sprintf_s(BufferLog, "CRITICAL ERROR: missing \"%s\" file\r\n", VetStandard[i]);
				strcat_s(pLog->MexMissing, BufferLog);
			}

			i++;
		}

		if (pLog->TestErrori) {
			MessageBox(NULL, pLog->MexMissing, "TRNG Diagnostic", MB_APPLMODAL);
		}
	}

	// nome: EsisteFile
	// input: char *NomeFile
	// scopo: Verifica se file con nome NomeFile, esiste
	// output: long TRUE=Esiste / FALSE = non esiste
	bool EsisteFile(const char *NomeFile)
	{
		struct stat stbuffer;

		if (NomeFile[0] == 0)
			return false;

		if (stat(NomeFile, &stbuffer) != 0)
			return false;
		return true;
	}

	void InitPrintTextColors(void)
	{
		//                          0   BIANCO_MOD  BIANCO      ROSSO       BLU        METAL_CHIA   GOLD        METAL_SCU  giallo
		static DWORD VetColors[9] = {0, 0x00ffffff, 0x00ffffff, 0x000000ff, 0x00ff0000, 0x00808080, 0x0000A0A0, 0x00404040, 0x0000FFFF};

		int i;

		for (i = 1; i < 9; i++) {
			GlobTomb4.VetTextColors[i] = (COLORREF) VetColors[i];
		}
		GlobTomb4.ColorWhiteStep = -15;
		GlobTomb4.ColorGradientNow = 255;
	}

	// inserisci in globtomb4 tutti i dati standard per barre di progressione
	// di tomb4
	void InitBarDefault(void)
	{
		__try { throw __func__; } __finally {}
	}

	// inizializza a valori di default tuto cio che puo' essere customizzato
	void CustDefToCustNow(void)
	{
		// copia l'intera struttura di default in quella di valori customize
		// attuali
		memcpy(GlobTomb4.pBaseCustomize, GlobTomb4.pBaseCustomizeDefault, sizeof(StrBaseCustomize));
	}

	bool LeggeNGScriptDat(char NomeScriptDat[])
	{
		__try { throw __func__; } __finally {}
	}

	void InitDgxErrors(void)
	{
		GlobTomb4.BaseDgxErrors.TotNew = 0;
		GlobTomb4.BaseDgxErrors.TotOld = 0;
	}

	// imposta alcuni valori costanti in variabili globali di tomb4
	// in modo da renderli meno riconoscibili nel codice
	void ImpostaCostantiNascoste(void)
	{
		// salva indirizzo di indiceveicoloattivo
		GlobTomb4.pVehicleIndex = &tomb4::lara.vehicle;

		// salva indirizzo di slot default sprites

		GlobTomb4.pSlotDefaultSprite = (StrSlot *) &tomb4::objects[(int) tomb4::object_types::DEFAULT_SPRITES];

		// salva valore di costant eper slot usato per detector
		// valore 252 0xFC

		GlobTomb4.BaseDetector.SlotDetector = (WORD) tomb4::object_types::QUEST_ITEM1;
	}

	// inizializza vettore di conversione tra azione e flipeffect che usano
	// itemgroup per eseguire azioni specifiche
	void InitRemapItemGroup(void)
	{
		short *pVet;
		int i;
		short NumAction;

		pVet = GlobTomb4.BaseItemGroup.VetRemapFlipActions;

		for (i = 0; i < 256; i++) {
			pVet[i] = -1;
		}

		// ora inserire i valori di conversione rispetto a flipeffect
		// NOTA: potrei avere problemi se il numero di flipeffect e' oltre 255
		NumAction = 29;
		for (i = 137; i <= 144; i++) {
			pVet[i] = NumAction++;
		}

		pVet[145] = 43;
		pVet[146] = 44;
	}

	// controlla se in cartella PIX ci sono immagini in formato standard ma
	// di tipo jpg

	void VerifyImagesPix(void)
	{
		StrListaFiles *VetNomi;
		int TotNomi;

		VetNomi = TrovaFiles("pix", "image*.jpg", &TotNomi);
		if (TotNomi == 0)
			return;
		MessageBox(NULL, "WARNING: some image in PIX folder is in jpg format. You should convert them in .bmp format using the CONVERTER.exe utility otherwise they will be not showed in game", "TRNG Warning", 0);
	}

	// funziona come trovafiles di visual basic
	// l'unica limitazione e' che arriva al massimo a 256 files
	// poi si ferma
	// altra limitazione e' che il nome (solo il nome non l'intero percorso)
	// e' al masismo di 63 caratteri piu' lo zero, se e' piu' lungo lo ignora

	StrListaFiles *TrovaFiles(const char DirSource[], const char Maschera[], int *pTotFiles)
	{
		static StrListaFiles VetFiles[256];

		char *pNome;
		char NewPath[256];
		WIN32_FIND_DATA InfoFile;
		HANDLE Ricerca;

		// se ultimo carattere e' '\' eliminarlo

		*pTotFiles = 0;
		sprintf_s(NewPath, "%s\\%s", DirSource, Maschera);

		Ricerca = FindFirstFile(NewPath, &InfoFile);
		if (Ricerca == INVALID_HANDLE_VALUE)
			return NULL;
		do {
			// tutte le directory passarle nuovamente a ScanDirectory
			// tutti i file passarli a ScanFile
			pNome = InfoFile.cFileName;
			// creare nuovo percorso

			if ((InfoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {

				// e' un file
				if (strlen(pNome) < 80) {
					// memorizzarlo

					strcpy_s(VetFiles[*pTotFiles].Testo, pNome);
					(*pTotFiles)++;
					if (*pTotFiles >= 256)
						break;
				}
			}
		} while (FindNextFile(Ricerca, &InfoFile) == TRUE);

		FindClose(Ricerca);

		return &VetFiles[0];
	}

	void LeggeMieSettingRegister(void)
	{
		__try { throw __func__; } __finally {}
	}

	// scopre se va attivata modalita' softfullscreen
	// questo avviene SOLO se oltre alla setting SET_FORCE_SOFT_FULL_SCREEN dello script
	// c'e' anche settato l'exclusive full screen nel registro
	// oltre a questo NON attivarlo se siamo in modalita' setup
	void VerificaAttivazioneSoftFullScreen(void)
	{
		GlobTomb4.TestWindowedModeRegister = IsModoWindowed();
		GlobTomb4.TestSoftFullScreen = false;

		if (GlobTomb4.TestSetup)
			return;

		if (GlobTomb4.TestWindowedModeRegister == true)
			return;

		if ((GlobTomb4.Settings & SET_FORCE_SOFT_FULL_SCREEN) == 0 && (GlobTomb4.EmergencySettings & ES_SOFT_FULL_SCREEN) == 0)
			return;
		// se era attivo nello script, oppure nel registro attivare testsoftfull screen
		// impostare che si sta usando un windowed mode
		GlobTomb4.TestSoftFullScreen = true;
	}

	void VerificaAttivazioneNoWaitingRefresh(void)
	{
		__try { throw __func__; } __finally {}
	}

	// se e' attiva la modalita'  SOFT_FULL_SCREEN
	// modifica con una patch lo style della finestra per togliere
	// bordo e caption
	void RestyleWindow(void)
	{
		__try { throw __func__; } __finally {}
	}

	void InitFmvLog(const char *pMex, bool TestCancellaLog)
	{

	}
}

void LoadTombNextGenerationInject_TombNextGeneration(bool replace)
{
	ProcessInject(0x10069407, (unsigned int)trng::ImpostaEnemyDamage, false);
	ProcessInject(0x100461EB, (unsigned int)trng::Inizializza, replace);
	ProcessInject(0x10044B59, (unsigned int)trng::LinkGlobTomb4Structures, replace);
	ProcessInject(0x100637E3, (unsigned int)trng::IsAttivoDebugger, replace);
	ProcessInject(0x10042C85, (unsigned int)trng::TrovaVersioneFile, false);
	ProcessInject(0x10045F85, (unsigned int)trng::CalcolaVersione, replace);
	ProcessInject(0x10044D11, (unsigned int)trng::InizializzaTomb4, replace);
	ProcessInject(0x100385DE, (unsigned int)trng::InviaLog, replace);
	ProcessInject(0x100384A4, (unsigned int)trng::GestioneDgxErrori, false);
	ProcessInject(0x10081306, (unsigned int)trng::ScopreModoFullScreen, replace);
	ProcessInject(0x10044805, (unsigned int)trng::InitStringOffsets, false);
	ProcessInject(0x10043D84, (unsigned int)trng::AnalisiWideScreen, replace);
	ProcessInject(0x10044CD0, (unsigned int)trng::CaricaTomb4Mem, false);
	ProcessInject(0x1004461E, (unsigned int)trng::Controllo1FileMancanti, replace);
	ProcessInject(0x10038304, (unsigned int)trng::EsisteFile, replace);
	ProcessInject(0x100447BD, (unsigned int)trng::InitPrintTextColors, replace);
	ProcessInject(0x10044360, (unsigned int)trng::InitBarDefault, false);
	ProcessInject(0x1006C17C, (unsigned int)trng::CustDefToCustNow, replace);
	ProcessInject(0x1004318A, (unsigned int)trng::LeggeNGScriptDat, false);
	ProcessInject(0x1004485D, (unsigned int)trng::InitDgxErrors, replace);
	ProcessInject(0x10043C84, (unsigned int)trng::ImpostaCostantiNascoste, replace);
	ProcessInject(0x100440ED, (unsigned int)trng::InitRemapItemGroup, replace);
	ProcessInject(0x1004453A, (unsigned int)trng::VerifyImagesPix, replace);
	ProcessInject(0x100386FF, (unsigned int)trng::TrovaFiles, replace);
	ProcessInject(0x10044AC9, (unsigned int)trng::LeggeMieSettingRegister, false);
	ProcessInject(0x100448A8, (unsigned int)trng::VerificaAttivazioneSoftFullScreen, replace);
	ProcessInject(0x10044B02, (unsigned int)trng::VerificaAttivazioneNoWaitingRefresh, false);
	ProcessInject(0x100445F6, (unsigned int)trng::RestyleWindow, false);
	ProcessInject(0x1006581A, (unsigned int)trng::InitFmvLog, replace);
}
