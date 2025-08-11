#include "Tomb_NextGeneration.h"
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
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
#include "../tomb4/game/gameflow.h"

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
	StrFloatPatch (&VetFarWorld)[5] = *reinterpret_cast<decltype(&VetFarWorld)>(0x1015A420);
	int &NuovoFlagCapelli = *reinterpret_cast<decltype(&NuovoFlagCapelli)>(0x4A6E6C);
#define malloc ((void *(*)(size_t)) 0x10135531)

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
		StrParseNGField ParseField;
		int Indice;
		int i;
		int n;
		char *pChar;
		int ContaLivello;
		StrImportFile *pImpFile;
		const char *pNome;
		int IndiceStringa;
		int j;
		StrRecPluginScript *pPlugin;
		int TestIgnora;
		bool TestEraSetting; // per controllo crypt
		DWORD EndOffset, StartOffset, NuovaSize;
		WORD TagScript;
		WORD * pFirstImport;
		StrLastScriptDat ScriptDatNow;
		WORD TotWords;
		StrHeaderImportFile *pHeader;
		StrSoundSettings *pSound;
		FILE *pFile;
		int Tot;
		WORD FarView;
		bool TestExport;

		// prima caricare extrang strings (anche se solo in modo temporaneo)
		CaricaNGStringTemp();

		// inizializza dati di opzioni script
		GlobTomb4.ScriptOptions.DisablePatchMem = 0;
		MyGlobPrivate.TotControlloScriptDat = 0;
		GlobTomb4.ScriptOptions.MainFlags = 0;
		GlobTomb4.WorldFarView = -1;

		GlobTomb4.DefSettings.DefMaxFog = 40;
		GlobTomb4.DefSettings.DefMinFog = 12;

		GlobTomb4.SoundSettings.MusicQuality = SCRIPT_IGNORE;
		GlobTomb4.SoundSettings.VolumeMusic = -1;
		GlobTomb4.SoundSettings.VolumeSFX = -1;
		GlobTomb4.BaseImportedFiles.TotFiles = 0;
		MyGlobPrivate.SettingScriptDat = 0;

		for (i = 0; i < MAX_IMPORT_FILES * 10; i++) {
			GlobTomb4.BaseImportedFiles.VetID[i] = -1;
		}

		GlobTomb4.pDiagnostica->LogItem.ItemIndex = -1;
		GlobTomb4.pDiagnostica->LogItem.Flags = 0;
		GlobTomb4.pPluginScriptTable->TotPlugins = 0;

		pFirstImport = NULL;

		if (EsisteFile(NomeScriptDat) == false) {
			return false;
		}

		if (ExtractNGHeader(NomeScriptDat, &GlobTomb4.HeaderNG_Script) == false) {
			MyGlobPrivate.TestNG_NoScript = true;
			// impostare farview a 40
			FarView = 40;
			GlobTomb4.WorldFarView = FarView;
			ModificaWorldFarView(FarView, true);

			// modificre i valori di ripristino di farview
			// in modo che siano sempre reimpostrai i valori
			// previsti per worldfarview
			VetFarWorld[2].ValDefault = (float) (FarView * 1024);
			if (FarView < GlobTomb4.DefSettings.DefMaxFog)
				GlobTomb4.DefSettings.DefMaxFog = FarView;

			// --- fine imposta farview

			return false;
		}

		MyGlobPrivate.TestNG_NoScript = false;
		// scoprire data e dimensione di file script.dat
		// prima scoprire i dati di attuale script.dat
		TestExport = true;
		if (fopen_s(&pFile, NomeScriptDat, "rb") != 0)
			return false;

		ScriptDatNow.SizeFile = QuantoLungo(pFile);
		fclose(pFile);

		// adesso devo scoprire data
		GetDataDelFile(NomeScriptDat, &ScriptDatNow.DataLastWrite);

		i = 0;
		ContaLivello = 0;
		while (ParseNgField(GlobTomb4.HeaderNG_Script.pNGArray, i, &ParseField)) {

			// analizzare tipo di pacchetto
			switch (ParseField.Type) {
			case NGTAG_CONTROLLO_OPTIONS:
				MyGlobPrivate.TotControlloScriptDat = (WORD) ParseField.SizeData;
				memcpy(&MyGlobPrivate.VetControlloScriptDat, &ParseField.pData[0], ParseField.SizeData);
				break;

			case NGTAG_IMPORT_FILE:
				// elaborare file import.
				// se e' di tipo memoria salva il contentuto e tutto
				// se invece e' di tipo temproary lo estrae subito
				if (pFirstImport == NULL)
					pFirstImport = ParseField.pData;

				i = 0;
				pHeader = (StrHeaderImportFile*) &ParseField.pData[i];

				switch (pHeader->TipoImport) {
				case IMPORT_TEMPORARY:
					// salvare il file a meno che non sia gia' stato fatto
					pNome = GetFileTrle(pHeader->NomeFile);

					// se ci sono sotto cartelle nel percorso del file
					// le crea adesso
					CreaSottoCartelle(pHeader->NomeFile);
					// salvare file
					if (fopen_s(&pFile, pNome, "wb") != 0)
						break;
					fwrite(&pHeader->VetBytes[0], pHeader->SizeFile, 1, pFile);
					fclose(pFile);

					break;
				case IMPORT_MEMORY:
					// salvare l'intero contenuto
					Tot = GlobTomb4.BaseImportedFiles.TotFiles;
					if (Tot >= MAX_IMPORT_FILES)
						break;
					pImpFile = &GlobTomb4.BaseImportedFiles.VetFiles[Tot];

					pImpFile->Id = pHeader->Id;
					pImpFile->Size = pHeader->SizeFile;
					pImpFile->Tipo = pHeader->TipoFile;
					pImpFile->NumeroFile = pHeader->NumeroFile;

					GlobTomb4.BaseImportedFiles.VetID[pImpFile->Id] = Tot;

					// adesso allocare la memora necessaria e spostare i dati
					pImpFile->pData = (BYTE *) malloc(pHeader->SizeFile);
					memcpy(pImpFile->pData, &pHeader->VetBytes[0], pHeader->SizeFile);
					GlobTomb4.BaseImportedFiles.TotFiles++;

					break;
				}
				break;

			// aggiungere controllo aqnche per sezione livello per beccare in title il comando WindowTitle
			// per cmabiare il nome dlela finestra setup
			case NGTAG_SCRIPT_LEVEL:
				if (ContaLivello == 0) {
					ContaLivello++;
					// livello [Title]
					// adesso scandire tutti i mini tag presenti
					i = 0;

					while (ParseField.pData[i] & 0xff) {
						// prendere da byte alto prima word il codice tag sript
						// attuale
						TotWords = ParseField.pData[i] & 0xFF;

						TagScript = ParseField.pData[i++] >> 8;
						// calcola dove inizia prossimo tag, successivo
						// a tutti gli argomenti di questo tag
						Indice = i + TotWords;

						// qui mettere patch per script?

						switch (TagScript) {
						case ctn_WindowTitle:
							IndiceStringa = ParseField.pData[i];
							if (IndiceStringa != -1) {
								pChar = GetString(IndiceStringa);
								if (pChar)
									strcpy_s(MexNewWindowTitle, pChar);
							}
							break;
						}
						i = Indice;
					}
				}
				break;

			case NGTAG_SCRIPT_OPTIONS:
				// per ora mi interessa solo questo tag
				// adesso scandire tutti i mini tag presenti
				i = 0;

				while (ParseField.pData[i] & 0xFF) {
					// prendere da byte alto prima word il codice tag sript
					// attuale
					TotWords = ParseField.pData[i] & 0xFF;

					TagScript = ParseField.pData[i++] >> 8;
					Indice = i + TotWords;
					TestEraSetting = false;
					TestIgnora = 0;

					switch (TagScript) {
					case cnt_FlagsOption:
						// word attuale contiene i flag per opzioni

						GlobTomb4.ScriptOptions.MainFlags = ParseField.pData[i];
						break;

					case ctn_Settings:
						// opzione di comando script Settings=
						GlobTomb4.Settings = ParseField.pData[i];
						TestEraSetting = true;
						break;

					case cnt_Plugin:
						// salvare tutti i comandi Plugin=
						n = GlobTomb4.pPluginScriptTable->TotPlugins;
						pPlugin = &GlobTomb4.pPluginScriptTable->VetPlugins[n];

						pPlugin->PluginId = ParseField.pData[i++];
						// ora dovrei estrarre la stringa ma non so se e' gia' disponibile
						IndiceStringa = ParseField.pData[i++];

						pNome = GetString(IndiceStringa);
						if (pNome == NULL)
							pNome = "UKNOWN_MISSING_STRING";
						strcpy_s(pPlugin->Name, pNome);

						// ora ci sono flag MPS (dword)
						pPlugin->MainPluginSettings = *(int*) &ParseField.pData[i];
						if (pPlugin->MainPluginSettings == -1)
							pPlugin->MainPluginSettings = 0;

						i += 2;

						// ora ci sarebbe lista di word per disable code
						pPlugin->TotDisable = TotWords - i + 1;
						for (j = 0; j < pPlugin->TotDisable; j++) {
							pPlugin->VetDisable[j] = ParseField.pData[i++];
						}
						GlobTomb4.pPluginScriptTable->TotPlugins++;
						break;

					case cnt_WorldFarView:
						FarView = ParseField.pData[i];
						GlobTomb4.WorldFarView = FarView;

						ModificaWorldFarView(FarView, true);
						if (FarView != SCRIPT_IGNORE) {
							// modificre i valori di ripristino di farview
							// in modo che siano sempre reimpostrai i valori
							// previsti per worldfarview
							VetFarWorld[2].ValDefault = (float) (FarView * 1024);
							if (FarView < GlobTomb4.DefSettings.DefMaxFog)
								GlobTomb4.DefSettings.DefMaxFog = FarView;
						}
						break;
					case ctn_SoundSettings:
						// impostazioni per settings
						pSound = &GlobTomb4.SoundSettings;

						pSound->MusicQuality = ParseField.pData[i++];
						pSound->VolumeMusic = ParseField.pData[i++];
						pSound->VolumeSFX = ParseField.pData[i];
						break;

					case ctn_LogItem:
						// comando LogItem= Flags, Indice
						GlobTomb4.pDiagnostica->LogItem.Flags = ParseField.pData[i++];
						if (GlobTomb4.pDiagnostica->LogItem.Flags == SCRIPT_IGNORE)
							GlobTomb4.pDiagnostica->LogItem.Flags = 0;
						GlobTomb4.pDiagnostica->LogItem.ItemIndex = ParseField.pData[i];
						break;
					case cnt_DiagnosticType:
						GlobTomb4.pDiagnostica->FlagsDgx = ParseField.pData[i++];
						GlobTomb4.pDiagnostica->DgxExtra = ParseField.pData[i++];
						if (GlobTomb4.pDiagnostica->DgxExtra == SCRIPT_IGNORE)
							GlobTomb4.pDiagnostica->DgxExtra = 0;
						break;
					}

					if (TestEraSetting) {
						// salva una copia di setting script.dat
						MyGlobPrivate.SettingScriptDat = ParseField.pData[i];
					}
					// calcolare prossimo indice
					i = Indice;
				}
				break;
			}
			// puntare a chunk successivo
			i = ParseField.NextIndex;
		}

		if (pFirstImport) {
			// c'erano import file
			// ridurre la memoria allocata in modo da escludere
			// la parte degli import
			// dato che pFirstImport punta alla prima word effettiva
			// di tag, devo ridurre di 3 word, 2 per per la dimensione
			// e una per il tag ngtag
			pFirstImport -= 3;
			// ora azzerare i valori
			pFirstImport[0] = 0;
			pFirstImport[1] = 0;
			pFirstImport += 3;
			// adesso calcolare la nuova dimensione ridotta
			EndOffset = (DWORD ) pFirstImport;
			StartOffset = (DWORD) GlobTomb4.HeaderNG_Script.pNGArray;

			NuovaSize = EndOffset - StartOffset;
			GlobTomb4.HeaderNG_Script.pNGArray = (WORD *) ReallocMine(GlobTomb4.HeaderNG_Script.pNGArray, NuovaSize, "HeaderNG_Script.pNGArray in LeggeNGScriptDa");
		}

		return true;
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

	// questo e' un cariccamento solo temporaneo di stringhe ng allo scopo di poter
	// avere i testi dei comandi della sezione [Options] letti prima dell'avvio di tomb4

	void CaricaNGStringTemp(void)
	{
		const char *pNomeLingua;
		char *pNomeFile;
		StrListaFiles *pVetNomi;
		int TotNomi;
		int i;

		// fare diversi tentativi
		pNomeLingua = "english.dat";
		pNomeFile = GetFileTrle(pNomeLingua);
		if (EsisteFile(pNomeFile) == false) {
			pVetNomi = TrovaFiles(Dir_Trle, "*.dat", &TotNomi);
			for (i = 0; i < TotNomi; i++) {
				if (_stricmp(pVetNomi[i].Testo, "script.dat") != 0) {
					pNomeFile = GetFileTrle(pVetNomi[i].Testo);
					if (EsisteFile(pNomeFile) == true)
						break;
				}
			}
			if (i == TotNomi) {
				MessageBoxTomb("ERROR: cann't find <language>.dat file in current trle path", "Missing english.dat");
				return;
			}
		}

		LeggiNG_LanguageDat(pNomeFile);
	}

	void MessageBoxTomb(const char *pMessaggio, const char *pTitolo)
	{
		MessageBox(NULL, pMessaggio, pTitolo, MB_APPLMODAL);
	}

	// verifica se in pNomeFile file contiene l'extra ng header
	//  ed estrae l'extra ng header dal file pNomeFile
	// il risultato dell'estrazione viene scritto nella struttura puntatata
	// da pExtractNG
	// in pExtractNG.Result viene inserito l'esito dell'operazione:
	// Result = 0   -> Non c'e' un header ng
	// Result = -1  -> l'header ng e' corrotto
	// Result - -2  -> errore aprendo il file
	// Result = 1  -> Header ng e' presente ed e' stato estratto
	//		nella struttura puntata da pExtractNG saranno impostati tutti i valori
	//
	// nota: se la funzione restituisce (true) la funzione chiamante
	// dovra' al termine di tutte le operazioni, liberare la memoria
	// contenuta nel campo pExtractNG->pArray
	// nota: una copia viene salvata nella variabile globale
	// LastNGHeader
	bool ExtractNGHeader(char *pNomeFile, StrExtractNG* pExtractNG)
	{
		DWORD SizeFile;
		FILE *pFile;
		StrEndNgHeader EndNgHeader;
		DWORD IndexBegin;
		WORD *pArray;
		int TotItems;
		WORD FirstCheckWord;
		WORD *pArray2;

		memset(pExtractNG, 0, sizeof(StrExtractNG));

		if (fopen_s(&pFile, pNomeFile, "rb") != 0) {
			// cann't open file
			pExtractNG->Result = -2;
			memcpy(&LastNGHeader, pExtractNG, sizeof(StrExtractNG));
			return false;
		}

		SizeFile = QuantoLungo(pFile);
		// trovare punto di inizio di header finale ng
		IndexBegin = SizeFile - sizeof(StrEndNgHeader);
		fseek(pFile, IndexBegin, SEEK_SET);
		fread(&EndNgHeader, sizeof(StrEndNgHeader), 1, pFile);
		if (EndNgHeader.EndCheck != NG_LONG_CHECK) {
			// il file non possiede un header ng
			fclose(pFile);
			pExtractNG->Result = 0;
			memcpy(&LastNGHeader, pExtractNG, sizeof(StrExtractNG));
			return false;
		}
		pExtractNG->SizeHeader = EndNgHeader.SizeNgHeader;
		// allocare vettore WORD in grado di osptiare tutti i dati
		TotItems = (EndNgHeader.SizeNgHeader - 2 - sizeof(EndNgHeader)) / 2;
		pArray = (WORD *) MallocMine(TotItems * 2, "pArray in ExtractNGHeader");
		if (pArray == NULL) {
			fclose(pFile);
			pExtractNG->Result = -1;
			memcpy(&LastNGHeader, pExtractNG, sizeof(StrExtractNG));

			return false;
		}
		// liberare eventuale memoria precedente
		if (pExtractNG->pNGArray != NULL) {
			FreeMine(pExtractNG->pNGArray);
			pExtractNG->pNGArray = NULL;
		}
		pExtractNG->pNGArray = pArray;

		pExtractNG->NWords = TotItems;

		// localizza inizio di header ng
		IndexBegin = SizeFile - EndNgHeader.SizeNgHeader;
		pExtractNG->StartOffset = IndexBegin;

		fseek(pFile, IndexBegin, SEEK_SET);
		// prima legge word di controllo iniziale
		fread(&FirstCheckWord, 2, 1, pFile);
		// adesso carica vettore con i dati
		fread(pArray, 2, TotItems, pFile);
		fclose(pFile);

		// verificare che prima word all'inizio dell'header contenga
		// valore corrispondente a coppia di caratteri "NG"
		if (FirstCheckWord != NG_SHORT_CHECK) {
			pExtractNG->Result = -1;
			FreeMine(pArray);
			pExtractNG->pNGArray = NULL;
			memcpy(&LastNGHeader, pExtractNG, sizeof(StrExtractNG));
			return false;
		}
		pExtractNG->Result = 1;
		// liberare eventuale blocco precedente
		if (LastNGHeader.pNGArray != NULL) {
			FreeMine(LastNGHeader.pNGArray);
			LastNGHeader.pNGArray = NULL;
		}
		memcpy(&LastNGHeader, pExtractNG, sizeof(StrExtractNG));
		// ora cambiare in lastngheader il puntatore a memoria
		// altrimenti si condivide anche la fine di quella memoria
		pArray2 = (WORD *) MallocMine(TotItems * 2, "pArray in ExtractNGHeader");

		LastNGHeader.pNGArray = pArray2;
		memcpy(pArray2, pArray, TotItems * 2);

		return true;
	}

	// nome: QuantoLungo
	// input: FILE tempfile
	// output: long dimfile
	// scopo: Trova dimensione in byte di file di input. Dopo l'oprazione imposta
	// scopo: puntatore all'inizio del file.
	long QuantoLungo(FILE *tempfile)
	{
		long tempdim;

		fseek(tempfile, 0, SEEK_END);
		tempdim = ftell(tempfile);
		fseek(tempfile, 0, SEEK_SET);
		return tempdim;
	}

	// scandisce lista campi ng:
	// input:
	//      pNGArray = puntatore a word array dell'intero ng header
	//		CurrentIndex = Indice che punta a campo attuale da scandire
	//      pParseNGField = puntatatore a struttura StrParseNGField da
	//			riempire con i risultati del parsing (vedi sotto)
	// output:
	//		scrive i seguenti dati nei campi di struttura puntata da pParseNGField:
	//		DWORD NextIndex;  // Index where start next chunk
	//		word *pData;      // pointer to data memory for currentIndex field
	//		DWORD StartDataIndex // index of first word for currentindex field
	//		DWORD SizeData;   // size of data (in bytes) pointed by pData
	//		WORD  Type;       // Type of CurrentIndex chunk
	//
	// valore ritornato dalla funzione (bool):
	//		false = CurrentIndex punta a fine seguenza header
	//				il parsing deve essere interrotto, i dati scritti
	//				in pParseNGField non sono significativi
	//		true = il campo currentIndex e' valido e i dati estratti
	//				sono stati scritti nella struttura pParseNGField
	//

	bool ParseNgField(WORD *pNgArray, DWORD CurrentIndex, StrParseNGField* pParseNGField)
	{
		DWORD Word1, NumberOfWords;
		int i;
		DWORD ExtraWords;

		i = CurrentIndex;

		if (pNgArray[i] & 0x8000) {
			// size e' DWORD
			Word1 = pNgArray[i++] & 0x7fff;
			NumberOfWords = Word1 * 65536 + pNgArray[i++];
			ExtraWords = 3;
		} else {
			// size e' WORD
			NumberOfWords = pNgArray[i++];
			ExtraWords = 2;
		}

		if (NumberOfWords == NGTAG_END_SEQUENCE)
			return false;

		pParseNGField->NextIndex = CurrentIndex + NumberOfWords;
		pParseNGField->Type = pNgArray[i++];
		pParseNGField->pData = &pNgArray[i];
		pParseNGField->StartDataIndex = i;
		pParseNGField->SizeData = (NumberOfWords - ExtraWords) * 2;

		return true;
	}

	// restituisce puntaotre a stringa ng con valore indice
	// se non la trova restituisce messaggio d'errore "ERROR Missing Extra String %d"
	char *GetStringaNG(int Indice)
	{
		static char BufMissing[80];

		int i;

		Indice &= 0x7fff;

		// stringa NG
		for (i = 0; i < GlobTomb4.TotExtraStrings; i++) {
			if (GlobTomb4.VetExtraStrings[i].Indice == Indice) {
				return GlobTomb4.VetExtraStrings[i].pTesto;

			}
		}

		if (Indice == 666)
			return NULL;

		sprintf_s(BufferLog, "ERROR: cann't locate extra ng string with index = %d", Indice);
		InviaLog(BufferLog);

		sprintf_s(BufMissing, "ERROR Missing Extra String %d", Indice);
		return BufMissing;
	}

	// modifica tutti i valori di tomb4 dove e' presente un riferimento
	// a worldfarview usando come valore
	// se TestHardware=true modifica tutto, sia valori hard che soft
	// nel caso invece sia soft ignora quelli hard e modifica quelli soft
	void ModificaWorldFarView(WORD NumBlocchi, bool TestHardware)
	{
		__try { throw __func__; } __finally {}
	}

	// riceve un percorso come "help\bin\readme.txt
	// e (se mancanti) crea le sottocartelle  "help" e poi "help\bin"

	void CreaSottoCartelle(char *pNomeFile)
	{
		// dividiere il percorso secondo separatori dicartelle

		char **pVetParti;
		int TotParti;
		char NomeDir[256];
		int i;

		pVetParti = Split(pNomeFile, '\\', &TotParti, NULL, NULL, false);

		if (TotParti < 2)
			return;

		for (i = 0; i < TotParti - 1; i++) {
			sprintf_s(NomeDir, "%s\\%s", Dir_Trle, pVetParti[i]);
			if (EsisteDirectory(NomeDir) == false) {
				// creare questa directory
				CreaDirectory(NomeDir);
			}
		}
	}

	bool EsisteDirectory(char *NomeDir)
	{
		return EsisteFile(NomeDir);
	}

	bool CreaDirectory(char *NomeDir)
	{
		if (_mkdir(NomeDir) == -1)
			return false;
		return true;
	}

	// restituisce puntatore carattere di stringa di valore IndiceStringa
	// nel formato usato da script.dat, ossia, se c'e' bit 0x8000 attivo
	// e' una stringa NG, altrimenti e' una stringa standard
	char * GetString(int IndiceStringa)
	{
		static char MexNotFound[17] = "STRING NOT FOUND";

		char *pChar;
		int i;
		WORD Indice;
		WORD *pIndiceStringheDat;
		char *pStringheScriptDat;

		pIndiceStringheDat = tomb4::gfStringOffset;
		pStringheScriptDat = tomb4::gfStringWad;

		if (IndiceStringa & STRING_NG) {
			Indice = IndiceStringa & MASK_STRING_INDEX;

			// stringa NG
			for (i = 0; i < GlobTomb4.TotExtraStrings; i++) {
				if (GlobTomb4.VetExtraStrings[i].Indice == Indice) {
					pChar = GlobTomb4.VetExtraStrings[i].pTesto;

					return pChar;
				}
			}
			// non e' stata trovata stringa

			sprintf_s(BufferLog, "ERROR: cann't locate extra ng string with index = %d", IndiceStringa & MASK_STRING_INDEX);
			InviaLog(BufferLog);

			return NULL;
		}

		// stringa e' di tipo standard
		if (pIndiceStringheDat == NULL || pStringheScriptDat == NULL) {
			sprintf_s(BufferLog, "ERROR: cann't locate standard string with index = %d (standard strings have not yet been loaded)", IndiceStringa);
			InviaLog(BufferLog);
			return NULL;
		}
		Indice = pIndiceStringheDat[IndiceStringa];
		pChar = &pStringheScriptDat[Indice];
		return pChar;
	}

	// chiamata nello stesso momento in cui in tomb4 si carica il file language.dat
	// Questa funzione carica i dati ng script per livello attuale
	void LeggiNG_ScriptForLevel(void)
	{
		__try { throw __func__; } __finally {}
	}

	void SalvaTagFmv(BYTE ValoreFmv)
	{
		GlobTomb4.BaseFMV.VetFmv[GlobTomb4.BaseFMV.TotFmv] = ValoreFmv;
		GlobTomb4.BaseFMV.TotFmv++;
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
	ProcessInject(0x1004318A, (unsigned int)trng::LeggeNGScriptDat, replace);
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
	ProcessInject(0x100430A8, (unsigned int)trng::CaricaNGStringTemp, replace);
	ProcessInject(0x10037B09, (unsigned int)trng::MessageBoxTomb, replace);
	ProcessInject(0x10037B9A, (unsigned int)trng::ExtractNGHeader, replace);
//	ProcessInject(0x1003780E, (unsigned int)trng::QuantoLungo, replace);
	ProcessInject(0x10068E37, (unsigned int)trng::ParseNgField, replace);
	ProcessInject(0x1007BF63, (unsigned int)trng::GetStringaNG, replace);
	ProcessInject(0x10068F1A, (unsigned int)trng::ModificaWorldFarView, false);
	ProcessInject(0x10042BEC, (unsigned int)trng::CreaSottoCartelle, replace);
	ProcessInject(0x10038336, (unsigned int)trng::EsisteDirectory, replace);
	ProcessInject(0x10038347, (unsigned int)trng::CreaDirectory, replace);
	ProcessInject(0x10041EF5, (unsigned int)trng::GetString, replace);
	ProcessInject(0x1006CA83, (unsigned int)trng::LeggiNG_ScriptForLevel, false);
	ProcessInject(0x100469BD, (unsigned int)trng::SalvaTagFmv, replace);
}
