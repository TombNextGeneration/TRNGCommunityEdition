#include "Tomb_NextGeneration.h"
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <math.h>
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
	TYPE_convert_obj_to_invobj &convert_obj_to_invobj = *reinterpret_cast<decltype(&convert_obj_to_invobj)>(0x1015993C);
	POINT (&VetSizeInner)[6] = *reinterpret_cast<decltype(&VetSizeInner)>(0x1015A3F0);
	short (&VetOriginali)[6] = *reinterpret_cast<decltype(&VetOriginali)>(0x10159AB4);
	short (&VetDetectorBig)[6] = *reinterpret_cast<decltype(&VetDetectorBig)>(0x10159AC0);
	short (&VetDetectorLittle)[6] = *reinterpret_cast<decltype(&VetDetectorLittle)>(0x10159ACC);
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
		StrParseNGField ParseField;
		StrRecordParamLgtn *pLightning;
		StrCircle *pCircle;
		StrStaticMIP *pMip;
		StrSpeechActor *pSpeech;
		WORD PluginId;
		CALL_PARAMETER pCallParam;
		StrMyInputBox *pInputBox;
		short PluginIndex;
		StrMyRect *pMyRect;
		int Index;
		CALL_CUSTOMIZE pCallCustomize;
		CALL_ASSIGN_SLOT pCallAssignSlot;
		DWORD *pDword;
		char MyBufInterno[256];
		StrSwapAnim *pSwap;
		int Indice, TotAnim;
		StrParamWText *pWText;
		StrBaseWindowsFonts *pBaseFonts;
		StrDemo *pDemo;
		StrParamTriangle *pTria;
		StrQuad *pQuad;
		StrShowSprite *pShowSprite;
		int TotDiari;
		StrScaleItem *pScale;
		WORD *pWord;
		StrRecordAssSlot *pAssign;
		DWORD TotItems;
		StrRecordSwitch *pSwitch;
		StrBaseFog *pFog;
		StrListaFiles *VetFiles;
		int TotFiles;
		StrPanelloSavegame *pPanel;
		StrCombine *pCombine;
		StrBaseDiario *pDiario;
		StrWindowsFont *pFont;
		StrScriptImage *pSImage;
		StrParamPrintText *pPrint;
		StrTestPositionCmd *pTestPosition;
		WORD Numero;
		StrSetCamera *pCamera;
		int IndiceStringa;
		StrScriptOrganizer *pScriptOrg;
		StrItemGroup *pItemGroup;
		int k, j;
		StrRotateItem *pRotate;
		StrColorRGB *pColor;
		int NInvItems;
		StrTexSequence *pTexSeq;
		WORD Rosso, Verde, Blu;
		WORD TagScript;
		StrScriptTrigger *pTrigger;
		StrGlobalTrigger *pGlob;
		int n;
		int Tot;
		const char *pChar;
		int TotMirror;
		WORD AddFlags;
		RecordMirror *pMirror;
		StrTriggerGroup *pGroup;
		int TotGroups;
		StrAddEffect *pEffect;
		int TotEffetti;
		BYTE ContaLivello;
		DWORD *pScriptMainFlags;
		StrScriptStandBy *pStand;
		DWORD ValScriptFlag;
		WORD IndiceSlot;
		StrScriptEnvMultCondition *pEnvScript;
		WORD TipoOggetto;
		WORD TotWords;
		short MinFog, MaxFog;
		WORD NumeroWord;
		StrColoraItem *pColora;
		StrDamage *pDamage;
		StrKeyPadScript *pScriptKeyPad;
		StrRecordEnemyScript *pEnemy;
		StrAnimScript *pAnimation;
		StrAnimObjScript *pAnimObj;
		StrMoveAdvance *pMove;
		StrMoveParameters *pMoveItem;
		StrDetector *pDetector;
		StrBaseTurbo *pTurbo;
		int TestIgnora;
		int i;
		BYTE *pByte;
		BYTE ValByte;
		short NumeroShort;
		StrLaraHp *pHp, *pOldHp;
		StrSingleShotResumTG *pSingleShotTG;
		StrProgressiveAction *pAzione;
		int TotRandom;
		DWORD Tempo;
		CALL_VOID pCallBack;
		int TotMip;
		StrElevator *pAscensore;
		StrScriptElevator *pElevatore;

		// mescola meglio i numeri casuali
		TotRandom = GetTickCount64() & 0x7f;
		TotRandom++;
		for (i = 0; i < TotRandom; i++) {
			Tempo = rand();
		}

		sprintf_s(BufferLog, "Parsing script.dat NG header for (new) level number %d", *GlobTomb4.pAdr->pLevelNow);
		InviaLog(BufferLog);

		// chiamare callback per plugin
		for (i = 1; i < (int) MyGlobPrivate.DataBase.TotPlugins; i++) {
			pCallBack = (CALL_VOID) MyGlobPrivate.DataBase.pVetPlugins[i].VetDirectCB[CB_INIT_LOAD_NEW_LEVEL];

			if (pCallBack != NULL) {
				pCallBack();
			}
		}
		LiberaCutsceneCamera();
		GlobTomb4.BaseLaraPosScript.TestPresent = false;

		GlobTomb4.pBaseCutscene->TotBasicCollision = 0;
		GlobTomb4.pBaseCutscene->LeadingActorIndex = -1;
		GlobTomb4.pBaseCutscene->ExtraActorIndex = -1;

		GlobTomb4.pBaseMemSwapAnim->TotMemSwap = 0;

		GlobTomb4.BaseSalvaFloor.InsideCondition = 0;
		GlobTomb4.pDemoNow = NULL;

		GlobTomb4.pPluginFloorTable->TotTable = 0;

		for (i = 0; i < MAX_ACTOR_SPEECHING; i++) {
			GlobTomb4.pBaseSpeechActor->VetPlay[i].TestAttivo = false;
		}

		GlobTomb4.BaseFlipMesh.TotFlipMesh = 0;
		GlobTomb4.BaseImages.TestPopUp = false;

		GlobTomb4.pAdr->pVetFlagsInventoryItems = (WORD *) tomb4::options_table; // pVetFlagsInventoryItems
		InizializzaAdaptiveFarView();
		pPanel = GlobTomb4.pBasePanello;

		pSingleShotTG = &GlobTomb4.BaseTG_SingleShotResumed;

		pSingleShotTG->TotTGResumed = 0;

		// salvare i dati di cust_keep_lara_hp di livello precendete
		pHp = &GlobTomb4.pBaseCustomize->BaseHpLara;
		pOldHp = &GlobTomb4.BaseOldHpLara;

		pOldHp->LastHpValue = pHp->LastHpValue;
		pOldHp->TotTargetLevels = pHp->TotTargetLevels;

		for (i = 0; i < pHp->TotTargetLevels; i++) {
			pOldHp->VetTargetLevels[i] = pHp->VetTargetLevels[i];
		}

		memset(GlobTomb4.pDemoLevel, 0, sizeof(StrDemo));

		// liberare eventuali dati presenti di immagini
		LiberaImmagine(&GlobTomb4.BaseImages.Effetto.EffectImage);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageBackGround);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageLittle);
		LiberaImmagine(&GlobTomb4.BaseImages.Temp);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageMonoScreen);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageBinocular);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageLaserSight);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageBinocCompass);
		LiberaImmagine(&GlobTomb4.BaseImages.ImageBinocSextant);

		InviaLog("Reset Image for background");
		memset(&GlobTomb4.BaseImgMonoScreen, 0, sizeof(StrBaseImgMonoScreen));
		InviaLog("Reset Image for binoculars");
		memset(&GlobTomb4.BaseImgBinocular, 0, sizeof(StrBaseImgBackGround));
		InviaLog("Reset Image for LastSight");
		memset(&GlobTomb4.BaseImgLaserSight, 0, sizeof(StrBaseImgBackGround));
		InviaLog("Reset Image for LoadLevel");
		memset(&GlobTomb4.BaseImgLoadingLevel , 0, sizeof(StrBaseImgBackGround));

		GlobTomb4.GlobBinoculars.ValoreZoomProgresso = 0x40; // ripristina valore originare per zoom binocolo

		GlobTomb4.TotBigNumbers = 0;
		GlobTomb4.pAdr->pSetting_Volumetric = (BYTE *) &tomb4::App.Volumetric;
		GlobTomb4.LevelFarView = -1;

		pAzione = &GlobTomb4.VetProgressiveActions[0];
		for (i = 0; i < GlobTomb4.TotProgressiveActions; i++) {
			if (pAzione->ActionType == AZ_PRINT_WINDOWS_STRING) {
				FreeMine((void*) pAzione->VetArgDword[1]);
				pAzione->VetArgDword[1] = 0;
			}
			pAzione->ActionType = 0;
			pAzione++;
		}
		GlobTomb4.TotProgressiveActions = 0;

		GlobTomb4.BaseRollBoats.TotRollBoats = 0;

		pScriptMainFlags = &tomb4::Gameflow->bitfield;
		ValScriptFlag = *pScriptMainFlags;
		pPanel->TestPresente = false;

		// ---------- INIZIALIZZA DATI DEFAULT PER LIVELLO ATTUALE ---------
		// azzera conbine items ai valori standard
		GlobTomb4.pAdr->pVetNewCombine[23].pProcedura = NULL;
		pWord = (WORD *) tomb4::options_table; // pVetFlagsInventoryItems
		memcpy(pWord, &GlobTomb4.VetSalvaFlagItems[0], 120 * 2);
		GlobTomb4.TotCombinabili = 0;

		GlobTomb4.pScriptLevelNow->AssignSlot.IndiceAnimRubberBoat = -1;
		GlobTomb4.pScriptLevelNow->AssignSlot.IndiceRubberBoat = -1;
		GlobTomb4.pScriptLevelNow->AssignSlot.IndiceAnimMotorBoat = -1;
		GlobTomb4.pScriptLevelNow->AssignSlot.IndiceMotorBoat = -1;
		GlobTomb4.pScriptLevelNow->LevelFlags = 0;
		GlobTomb4.pBaseAnimations->TotAnimazioni = 0;
		GlobTomb4.BaseAnimObj.TotAnimObj = 0;
		GlobTomb4.BaseStaticMIP.TotStaticMIP = 0;
		GlobTomb4.BaseMirror.TotMirror = 0;
		GlobTomb4.TotDisabledMirrors = 0;
		GlobTomb4.BaseElevator.TotElelevators = 0;
		GlobTomb4.BaseKeyPad.ScriptSettings.ClickSound = 369;
		GlobTomb4.BaseKeyPad.ScriptSettings.IndexFirstAnim = 197;
		GlobTomb4.BaseKeyPad.ScriptSettings.FrameFirstAnim = 28;
		GlobTomb4.BaseKeyPad.ScriptSettings.IndexAfterAnim = SCRIPT_IGNORE;
		GlobTomb4.TestFogRange = false;

		GlobTomb4.BaseAssignSlot.TotNewAssign = 0;
		// inizializza dati per standby
		GlobTomb4.BaseStandBy.TestPresente = false;
		GlobTomb4.BaseStandBy.TestIniziato = false;

		// inizializza nome di default pe rfinestra tomb
		pChar = "Tomb Raider - The Last Revelation";
		strcpy_s(GlobTomb4.WindowNome, pChar);

		if (ScopreModoFullScreen() == false && GlobTomb4.TestSoftFullScreen == false) {

			SetWindowText(*GlobTomb4.pAdr->pWindowHandle, pChar);
		}

		GlobTomb4.pBaseEffects->TotEffects = 0;
		for (i = 0; i < MAX_ADD_EFFECTS * 10; i++) {
			GlobTomb4.pBaseEffects->VetID[i] = -1;
		}

		GlobTomb4.BaseDetector.TestAttivo = false;
		GlobTomb4.BaseDetector.LastFrame = 0;
		GlobTomb4.BaseDetector.TestMostra = false;
		GlobTomb4.BaseTexSequence.TotSequenze = 0;
		for (i = 0; i < MAX_TEX_SEQUENCE * 10; i++) {
			GlobTomb4.BaseTexSequence.VetID[i] = -1;
		}

		GlobTomb4.BaseTestPosition.TotTestPositions = 0;
		for (i = 0; i < MAX_TEST_POSITION * 10; i++) {
			GlobTomb4.BaseTestPosition.VetId[i] = -1;
		}

		GlobTomb4.BaseParamLightning.TotParamLgtn = 0;
		for (i = 0; i < MAX_PARAM_LIGHTNING * 10; i++) {
			GlobTomb4.BaseParamLightning.VetId[i] = -1;
		}

		GlobTomb4.pBaseSpeechActor->TotSpeechActor = 0;
		for (i = 0; i < MAX_SPEECH_PARAM * 10; i++) {
			GlobTomb4.pBaseSpeechActor->VetId[i] = -1;
		}

		GlobTomb4.BaseParamWText.TotParamWText = 0;
		for (i = 0; i < MAX_PARAM_WTEXT * 10; i++) {
			GlobTomb4.BaseParamWText.VetIds[i] = -1;
		}
		GlobTomb4.BaseParamMyRects.TotMyRect = 0;
		for (i = 0; i < MAX_MY_RECT * 10; i++) {
			GlobTomb4.BaseParamMyRects.VetId[i] = -1;
		}

		GlobTomb4.BaseInputBoxes.TotInputBox = 0;
		for (i = 0; i < MAX_INPUT_BOX * 10; i++) {
			GlobTomb4.BaseInputBoxes.VetId[i] = -1;
		}

		GlobTomb4.pBaseSwapAnim->TotSwapAnim = 0;
		for (i = 0; i < MAX_SWAP_ANIM * 10; i++) {
			GlobTomb4.pBaseSwapAnim->VetId[i] = -1;
		}

		// e poi inizializzare vettore attuale
		GlobTomb4.BaseDiari.TotDiari = 0;

		GlobTomb4.pBaseScriptImages->TotScriptImages = 0;
		for (i = 0; i < MAX_IMAGES * 10; i++) {
			GlobTomb4.pBaseScriptImages->VetID[i] = -1;
		}

		GlobTomb4.BaseEquipItem.TotEquip = 0;
		GlobTomb4.pBaseEnvConditions->TotScriptEnvCondition = 0;
		for (i = 0; i < MAX_ENV_SCRIPT_CONDITIONS * 10; i++) {
			GlobTomb4.pBaseEnvConditions->VetID[i] = -1;
		}

		GlobTomb4.pBaseTriggerGroups->TotTriggerGroups = 0;
		for (i = 0; i < MAX_TRIGGER_GROUPS * 10; i++) {
			GlobTomb4.pBaseTriggerGroups->VetID[i] = -1;
		}

		GlobTomb4.BaseStandBy.TotStandBY = 0;
		for (i = 0; i < MAX_STANDBY * 10; i++) {
			GlobTomb4.BaseStandBy.VetID[i] = -1;
		}

		GlobTomb4.BaseSwitch.TotSwitch = 0;
		for (i = 0; i < MAX_SWITCH * 10; i++) {
			GlobTomb4.BaseSwitch.VetID[i] = -1;
		}

		GlobTomb4.pBaseGlobalTriggers->TotTriggers = 0;
		for (i = 0; i < MAX_GLOBAL_TRIGGERS * 10; i++) {
			GlobTomb4.pBaseGlobalTriggers->VetID[i] = -1;
		}
		GlobTomb4.pBaseOrganizer->TotOrganizer = 0;
		for (i = 0; i < MAX_ORGANIZERS * 10; i++) {
			GlobTomb4.pBaseOrganizer->VetID[i] = -1;
		}

		GlobTomb4.BaseItemGroup.TotGroups = 0;
		for (i = 0; i < MAX_ITEM_GROUPS * 10; i++) {
			GlobTomb4.BaseItemGroup.VetID[i] = -1;
		}

		GlobTomb4.BaseColoriRGB.TotColori = 0;
		for (i = 0; i < MAX_COLORI_RGB * 10; i++) {
			GlobTomb4.BaseColoriRGB.VetID[i] =-1;
		}

		GlobTomb4.BaseShowSprites.TotShowSprites = 0;
		for (i = 0; i < MAX_SHOW_SPRITES * 10; i++) {
			GlobTomb4.BaseShowSprites.VetIdShowSprites[i] = -1;
		}

		GlobTomb4.BaseTriangles.TotTriangles = 0;

		for (i = 0; i < MAX_TRIANGLES * 10; i++) {
			GlobTomb4.BaseTriangles.VetIdTriangles[i] = -1;
		}

		GlobTomb4.BaseQuads.TotQuads = 0;
		for (i = 0; i < MAX_QUADS * 10; i++) {
			GlobTomb4.BaseQuads.VetIdQuads[i] = -1;
		}

		GlobTomb4.BaseCircles.TotCircles = 0;
		for (i = 0; i < MAX_CIRCLES * 10; i++) {
			GlobTomb4.BaseCircles.VetIdCircle[i] = -1;
		}

		GlobTomb4.BaseMoveAdvance.TotMoveAdvance = 0;
		for (i = 0; i < MAX_MOVE_ADVANCE * 10; i++) {
			GlobTomb4.BaseMoveAdvance.VetID[i] = -1;
		}

		GlobTomb4.BaseColoraItem.TotColoraItem = 0;
		for (i = 0; i < MAX_COLORA_ITEM * 10; i++) {
			GlobTomb4.BaseColoraItem.VetID[i] = -1;
		}

		GlobTomb4.BaseMoveItem.TotMove = 0;
		for (i = 0; i < MAX_MOVE_PARAM * 10; i++) {
			GlobTomb4.BaseMoveItem.VetID[i] = -1;
		}

		GlobTomb4.BaseParamPrint.TotPrintText = 0;
		for (i = 0; i < MAX_PARAM_PRINT_TEXT * 10; i++) {
			GlobTomb4.BaseParamPrint.VetID[i] = -1;
		}

		GlobTomb4.BaseRotateItem.TotRotate = 0;
		for (i = 0; i < MAX_ROTATE_PARAM * 10; i++) {
			GlobTomb4.BaseRotateItem.VetID[i] = -1;
		}

		GlobTomb4.BaseSetCamera.TotSetCamera = 0;
		for (i = 0; i < MAX_SET_CAMERA * 10; i++) {
			GlobTomb4.BaseSetCamera.VetID[i] = -1;
		}

		GlobTomb4.BaseScaleParam.TotScale = 0;
		for (i = 0; i < MAX_SCALE_ITEM * 10; i++) {
			GlobTomb4.BaseScaleParam.VetIdScale[i] = -1;
		}

		// inizializzare dati per salvaraggio immagine interna in savegames
		InitScreenShot();

		// se si sta eseguendo senza ng (ossia con vecchi file e per level manager)
		// allora attivare cattura e salvataggio screenshot
		if (MyGlobPrivate.TestNG_NoScript == true) {
			GlobTomb4.ScreenShot.TestSalvaMiniShot = true;
		}
		// se c'e' attivo flag per attivare feature trlm
		// attivare salvaaggio immagini screenshot
		if (GlobTomb4.ScriptOptions.MainFlags & ngfm_Enable_Trlm_Options) {
			GlobTomb4.ScreenShot.TestSalvaMiniShot = true;
		}

		// liberare font precedenti
		LiberaAllFonts();

		// inizializzare vetfonts
		GlobTomb4.BaseFonts.TotFonts = 0;
		for (i = 0; i < MAX_FONTS * 10; i++) {
			GlobTomb4.BaseFonts.VetID[i] = -1;
		}

		AddFlags = 0;

		SetItemDetector(TD_AMULETO);
		RipristinaTurbo();

		CustDefToCustNow();
		// ripristinare tutti i valori standard di indici slot

		RipristinaIndiciSlot();
		// ripristinare distanza view per world e fog
		RipristinaWorldFarView();
		InizializzaBaseFog();
		RipristinaLevelSettings();
		// ripristina valori per print string sulla base di default
		RipristinaDefaultPrintString();

		RipristinaDamageSettings();
		RipristinaEnemy();

		// ------------------ FINE INIZIALIZZAZIONE ------------------------
		NInvItems = 0;

		sprintf_s(BufferLog, "WorldFarView = %d sectors", GlobTomb4.WorldFarView);
		InviaLog(BufferLog);

		// verificare che era stato trovato header per script
		if (GlobTomb4.HeaderNG_Script.Result != 1) {
			if (MyGlobPrivate.TestNG_NoScript == true) {
				if (*GlobTomb4.pAdr->pLevelNow != 0) {
					// se manca l'header ng in script dat attivare didefault il turbo per livelli level maanger
					pTurbo = &GlobTomb4.BaseTurbo;

					pTurbo->Flags = TRB_OPTIMIZE_SORTING;

					InviaLog("Enabled Turbo mode");
				}
			}
			return;
		}
		// ----- se e' attiva diagnostica e edgx_swap_view ---
		//creare una camera fittizia
		if ((GlobTomb4.ScriptOptions.MainFlags & ngfm_Diagnostica) != 0 && (GlobTomb4.pDiagnostica->DgxExtra & EDGX_SWAP_VIEW) != 0) {

			n = GlobTomb4.BaseSetCamera.TotSetCamera;

			pCamera = &GlobTomb4.BaseSetCamera.VetSetCamera[n];
			pCamera->IdCamera = MAX_SET_CAMERA - 1;
			GlobTomb4.BaseSetCamera.VetID[pCamera->IdCamera] = n;
			// ora leggere altri parametri dopo l'id
			pCamera->Flags = FSCAM_DISABLE_COMBAT_CAM;

			pCamera->Distance = GlobTomb4.pBaseCustomize->CameraCust.ChaseDistance;

			pCamera->VOrient = GlobTomb4.pBaseCustomize->CameraCust.ChaseHeight;

			pCamera->HOrient = GlobTomb4.pBaseCustomize->CameraCust.ChaseHOrient;

			pCamera->Speed = GlobTomb4.pBaseCustomize->CameraCust.Speed;

			GlobTomb4.BaseSetCamera.TotSetCamera++;
		}

		// ---- fine gestione swap_view
		i = 0;
		ContaLivello = 0;
		// qui bisognebre impostare  a "1" contalivello se title e' assente
		if ((ValScriptFlag & 0x04) == 0)
			ContaLivello++;

		while (ParseNgField(GlobTomb4.HeaderNG_Script.pNGArray, i, &ParseField)) {

			// analizzare tipo di pacchetto
			switch (ParseField.Type) {
			case NGTAG_SCRIPT_LEVEL:
				// per ora mi interessa solo questo tag

				// vedere se siamo nel livello attuale
				if (ContaLivello == *GlobTomb4.pAdr->pLevelNow) {
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
						TestIgnora = 0;
						// qui mettere patch per script?
						if (TestIgnora == 0) {

							switch (TagScript) {
							case cnt_FlagsLevel:
								GlobTomb4.pScriptLevelNow->LevelFlags = ParseField.pData[i];
								// se richiesta modifica di volumetric fx
								// attuarla adesso
								if (GlobTomb4.pScriptLevelNow->LevelFlags & fngl_VolumetricFX_Enable) {
									*GlobTomb4.pAdr->pSetting_Volumetric = 1;

									RestoreHardwareFogSempre();
								}
								if (GlobTomb4.pScriptLevelNow->LevelFlags & fngl_VolumetricFX_Disable)
									*GlobTomb4.pAdr->pSetting_Volumetric = 0;

								break;

							case cnt_Enemy:
								// prima word e' slot index
								if (GlobTomb4.BaseEnemys.TotEnemy >= MAX_ENEMY_SCRIPT) {
									sprintf_s(BufferLog, "ERROR: too much Enemy= script command for current level section. Max amout of enemy commands is %d", MAX_ENEMY_SCRIPT);
									InviaLog(BufferLog);
									break;
								}
								pEnemy = &GlobTomb4.BaseEnemys.VetEnemy[GlobTomb4.BaseEnemys.TotEnemy];
								GlobTomb4.BaseEnemys.TotEnemy++;
								// slot
								pEnemy->SlotId = ParseField.pData[i++];
								// Hp
								pEnemy->Health = ParseField.pData[i++];

								// NEF flags
								pEnemy->FlagsNEF = ParseField.pData[i++];
								if (pEnemy->FlagsNEF == SCRIPT_IGNORE)
									pEnemy->FlagsNEF = 0;

								// TEF flags
								pEnemy->TombFlags = ParseField.pData[i++];
								// valore extra
								pEnemy->Extra = ParseField.pData[i++];
								if (pEnemy->Extra == -1)
									pEnemy->Extra = 0;

								// e adesso array
								// copiare tutte le word successive
								k = 0;
								pEnemy->TotDamage = Indice - i;

								for (j = i; j < Indice; j++) {
									pEnemy->VetDamage[k++] = ParseField.pData[j];
								}

								break;
							case cnt_DefaultWindowsFont:
								pBaseFonts = &GlobTomb4.BaseFonts;

								j = ParseField.pData[i++];  // ID WindowsFont
								k = ParseField.pData[i++];  // flags DWF_...
								if (k == -1)
									k = 0;
								pBaseFonts->FlagDWF = k;

								pBaseFonts->LineSpacing = ParseField.pData[i++];
								if (pBaseFonts->LineSpacing == -1)
									pBaseFonts->LineSpacing = 0;

								for (k = 0; k < POFF_COUNTER; k++) {
									pBaseFonts->VetOffsetPosY[k] = ParseField.pData[i++];
									if (pBaseFonts->VetOffsetPosY[k] == -1)
										pBaseFonts->VetOffsetPosY[k] = 0;
								}

								ImpostaDefaultWindowsFont(j);
								break;

							case cnt_Demo:
								// Syntax: Demo= DemoFlags (DEMF_...), Parameter, InfoText ,
								//					WaitingTime, DemoIndex array
								if (*GlobTomb4.pAdr->pLevelNow == 0) {
									// demo title
									pDemo = GlobTomb4.pDemoTitle;
									GlobTomb4.pDemoNow = pDemo;

									if (pDemo->CtrlSign == 0x615274F1)
										break;
									// segnalare il caricamento
									pDemo->CtrlSign = 0x615274F1;
								} else {
									// demo level
									pDemo = GlobTomb4.pDemoLevel;
									GlobTomb4.pDemoNow = pDemo;
								}
								pDemo->LastIdPlayed = -1;

								pDemo->Flags = ParseField.pData[i++];
								if (pDemo->Flags == SCRIPT_IGNORE)
									pDemo->Flags = 0;

								pDemo->Parameter = ParseField.pData[i++];
								pDemo->StringInfoTextIndex = ParseField.pData[i++];
								pDemo->StringDemoLegendIndex = ParseField.pData[i++];
								pDemo->WaitingTime = ParseField.pData[i++];

								pDemo->TotDemoIDs = Indice - i;
								for (k = 0; k < pDemo->TotDemoIDs; k++) {
									pDemo->VetDemoIDs[k] = ParseField.pData[i++];
									// azzerare le uscite (ossia il numero di volte gia eseguito per un demo
									pDemo->VetDemoPlayed[k] = 0;
								}

								// se e' livello title e c''e flag random, mescolare indici
								if (*GlobTomb4.pAdr->pLevelNow == 0 && (pDemo->Flags & DEMF_RANDOM) != 0 && pDemo->TotDemoIDs > 1) {
									for (k = 0; k < pDemo->TotDemoIDs; k++) {

										j = Casuale(pDemo->TotDemoIDs);
										if (j != k) {
											NumeroWord = pDemo->VetDemoIDs[k];
											pDemo->VetDemoIDs[k] = pDemo->VetDemoIDs[j];
											pDemo->VetDemoIDs[j] = NumeroWord;
										}
									}
								}

								break;

							case cnt_AssignSlot:
								// ora si devono impostare gli indici per oggetti speciali
								// a seconda del loro codice
								// prima word lo slot tomb4 dove piazzare
								// seconda word il codice di nuovo oggetto
								IndiceSlot = ParseField.pData[i++];
								TipoOggetto = ParseField.pData[i++];
								PluginId = ParseField.pData[i];

								// annullare questo indice slot in tomb4
								AnnullaIndiceSlot(IndiceSlot);

								if (PluginId != 0) {
									// appartiene ad un plugin: inviarlo alla callback
									// fare anche conversione di pluginid
									PluginIndex = GetPluginIndex(PluginId, PLUG_FROM_SCRIPT);
									if (PluginIndex == -1)
										break;

									pCallAssignSlot = (CALL_ASSIGN_SLOT) MyGlobPrivate.DataBase.pVetPlugins[PluginIndex].VetDirectCB[CB_ASSIGN_SLOT_MINE];
									if (pCallAssignSlot != NULL) {
										//  (WORD Slot, WORD OBJ_TYPE);
										pCallAssignSlot(IndiceSlot, TipoOggetto);
									}
									break;

								}

								switch (TipoOggetto) {
								case OBJ_RUBBER_BOAT:
									GlobTomb4.pScriptLevelNow->AssignSlot.IndiceRubberBoat = IndiceSlot;
									break;
								case OBJ_RUBBER_BOAT_ANIM:
									GlobTomb4.pScriptLevelNow->AssignSlot.IndiceAnimRubberBoat = IndiceSlot;
									break;
								case OBJ_MOTOR_BOAT_ANIM:
									GlobTomb4.pScriptLevelNow->AssignSlot.IndiceAnimMotorBoat = IndiceSlot;
									break;
								case OBJ_MOTOR_BOAT:
									GlobTomb4.pScriptLevelNow->AssignSlot.IndiceMotorBoat = IndiceSlot;
									break;
								default:
									// nuovo formato
									// uesto e' un altro slot per lo scambio
									j = GlobTomb4.BaseAssignSlot.TotNewAssign;
									if (j >= MAX_ASSIGN_SLOT) {
										sprintf_s(BufferLog, "ERROR: too much AssignSlot commands in same [Level] section. Max number = %d", MAX_ASSIGN_SLOT);
										InviaLog(BufferLog);
										break;
									}
									pAssign = &GlobTomb4.BaseAssignSlot.VetNewAssign[j];

									pAssign->MioSlot = IndiceSlot;
									pAssign->TipoSlot = TipoOggetto;
									GlobTomb4.BaseAssignSlot.TotNewAssign++;
									break;
								}
								break;
							case cnt_LevelFarView:
								// una sola word seguente con il numero di blocchi
								ModificaWorldFarView(ParseField.pData[i], false);
								if (ParseField.pData[i] != SCRIPT_IGNORE) {
									// inserire vcalore anche in adaptive far view
									GlobTomb4.BaseAdaptiveFar.BlocchiFar = ParseField.pData[i];
									GlobTomb4.BaseAdaptiveFar.MaxFarView = ParseField.pData[i];
									GlobTomb4.LevelFarView = ParseField.pData[i];
									GlobTomb4.BaseFog.NowFogBulbDistance = ParseField.pData[i];
								}
								break;
							case ctn_WindowTitle:
								// questo lo posso eseguire subito
								IndiceStringa = ParseField.pData[i];
								if (IndiceStringa != -1) {
									pChar = GetString(IndiceStringa);
									strcpy_s(GlobTomb4.WindowNome, pChar);

									if (ScopreModoFullScreen() == false) {
										SetWindowText(*GlobTomb4.pAdr->pWindowHandle, pChar);
									}
								}
								break;

							case ctn_Turbo:
								// trovato comando turbo
								pTurbo = &GlobTomb4.BaseTurbo;

								pTurbo->Flags = ParseField.pData[i++];

								// copiare i valori extra
								if (ParseField.pData[i] != SCRIPT_IGNORE)
									GlobTomb4.BaseAdaptiveFar.FPStoKeep = ParseField.pData[i];

								// ora applicare i vari flag
								if (pTurbo->Flags & TRB_HIGH_PRIORITY) {
									pTurbo->TestPriorita = true;
									pTurbo->IndicePriorita = High_BELOW_NORMAL;
								}
								if (pTurbo->Flags & TRB_ASYNC_FRAMES)
									pTurbo->TestAsync = true;

								break;
							case ctn_SavegamePanel:
								pPanel->TestPresente = true;
								pPanel->FlagsSPF = ParseField.pData[i++];
								if (pPanel->FlagsSPF == SCRIPT_IGNORE)
									pPanel->FlagsSPF = 0;
								// image background
								pPanel->MioDiario.IdImage = ParseField.pData[i++];
								if (pPanel->FlagsSPF & SPF_PRELOAD_BKG_IMAGE) {
									if (AggiungiImmaginePreload(pPanel->MioDiario.IdImage) == false) {
										pPanel->TestPresente = false;
										break;
									}
								}

								pPanel->TotSave = ParseField.pData[i++];
								if (pPanel->TotSave == SCRIPT_IGNORE)
									pPanel->TotSave = 15;

								if (pPanel->TotSave > 100)
									pPanel->TotSave = 100;

								pPanel->TotVisibili = ParseField.pData[i++];
								if (pPanel->TotVisibili == SCRIPT_IGNORE) {
									pPanel->TotVisibili = 15;
								}
								if (pPanel->TotVisibili > pPanel->TotSave)
									pPanel->TotVisibili = pPanel->TotSave;

								pPanel->TipoLayout = ParseField.pData[i++];

								pPanel->IndiceStringa = ParseField.pData[i++];

								// ora ci sono i windows font
								// fare come ho fatto in Diary
								// prendere dati di WindowsFont per titolo
								// ------ WIndows Font per List savegame -------
								NumeroWord = ParseField.pData[i++];
								if (NumeroWord == SCRIPT_IGNORE) {
									InviaLog("ERROR: illegal Id for IdListWindowsFont of SavegamePanel command");
									break;
								}
								j = GlobTomb4.BaseFonts.VetID[NumeroWord];
								if (j == -1) {
									InviaLog("ERROR: illegal Id for IdListWindowsFont of SavegamePanel command");
									break;
								}
								pFont = &GlobTomb4.BaseFonts.VetFonts[j];

								pPanel->MioDiario.FontText = *pFont;

								// ------ WIndows Font per Info savegame -------
								NumeroWord = ParseField.pData[i++];
								if (NumeroWord == SCRIPT_IGNORE) {
									InviaLog("ERROR: illegal Id for IdInfoWindowsFont of SavegamePanel command");
									break;
								}
								j = GlobTomb4.BaseFonts.VetID[NumeroWord];
								if (j == -1) {
									InviaLog("ERROR: illegal Id for IdInfoWindowsFont of SavegamePanel command");
									break;
								}
								pFont = &GlobTomb4.BaseFonts.VetFonts[j];

								pPanel->MioDiario.FontInfoSave = *pFont;

								// ------ WIndows Font per Info savegame -------
								NumeroWord = ParseField.pData[i++];
								if (NumeroWord == SCRIPT_IGNORE) {
									InviaLog("ERROR: illegal Id for IdTitleWindowsFont of SavegamePanel command");
									break;
								}
								j = GlobTomb4.BaseFonts.VetID[NumeroWord];
								if (j == -1) {
									InviaLog("ERROR: illegal Id for IdTitleWindowsFont of SavegamePanel command");
									break;
								}
								pFont = &GlobTomb4.BaseFonts.VetFonts[j];

								pPanel->MioDiario.FontTitle = *pFont;
								break;

							case cnt_StandBy:
								TotItems = GlobTomb4.BaseStandBy.TotStandBY;
								if (TotItems >= MAX_STANDBY) {
									sprintf_s(BufferLog, "ERROR: too much StandBy command in current levelsection. Max value=%d", MAX_STANDBY);
									InviaLog(BufferLog);
									break;
								}
								pStand = &GlobTomb4.BaseStandBy.VetStandBy[TotItems];
								pStand->IdStandBY = ParseField.pData[i++];
								GlobTomb4.BaseStandBy.VetID[pStand->IdStandBY] = (short) TotItems;

								pStand->TipoStandby = ParseField.pData[i++];
								pStand->LimiteCicli = ParseField.pData[i++] * FRAME_SECONDO;

								pStand->Flags = ParseField.pData[i++];
								if (pStand->Flags == SCRIPT_IGNORE)
									pStand->Flags = 0;

								pStand->FirstText = ParseField.pData[i++];
								pStand->NumTexts = ParseField.pData[i++];
								if (pStand->FirstText == -1)
									pStand->NumTexts = 0;


								pStand->AudioTrack = ParseField.pData[i++];
								pStand->VerticalOrient = ParseField.pData[i++];
								if (pStand->VerticalOrient == -1)
									pStand->VerticalOrient = -2730; // default valore

								pStand->OrientSpeed = ParseField.pData[i++];
								pStand->Distanza = ParseField.pData[i++];
								pStand->IdTriggerGroupStart = ParseField.pData[i++];
								pStand->IdTriggerGroupEnd = ParseField.pData[i];
								// se questo standby ha Id = 1 metterlo
								// come default
								if (pStand->IdStandBY == 1) {
									ImpostaStandBy1(GlobTomb4.BaseStandBy.TotStandBY);

								}
								GlobTomb4.BaseStandBy.TotStandBY++;

								break;

							case ctn_Diary:

								TotDiari = GlobTomb4.BaseDiari.TotDiari;

								if (TotDiari >= MAX_DIARI) {
									sprintf_s(BufferLog, "ERROR: too much Diary commands in current level section. Max value=%d", MAX_DIARI);
									InviaLog(BufferLog);
									break;
								}
								pDiario = &GlobTomb4.BaseDiari.VetBaseDiario[TotDiari];
								pDiario->ID_Diario = ParseField.pData[i++];

								IndiceSlot = ParseField.pData[i++];

								if (IndiceSlot != SCRIPT_IGNORE)
									pDiario->SlotDiario = IndiceSlot;
								// flags LDF
								NumeroWord = ParseField.pData[i++];

								if (NumeroWord == SCRIPT_IGNORE)
									NumeroWord = 0;

								// e' un nuovo diario, azzerare le stringhe
								pDiario->TotStringhe = 0;
								pDiario->FlagsLDF = NumeroWord;

								pDiario->IdImage = ParseField.pData[i++];

								pDiario->FlagsPL = ParseField.pData[i++];
								if (pDiario->FlagsPL == SCRIPT_IGNORE)
									pDiario->FlagsPL = PL_CENTRAL_IMAGE;

								NumeroShort = ParseField.pData[i++];

								if (NumeroShort != -1) {
									// salvare prima stringa
									pDiario->VetStringhe[pDiario->TotStringhe] = NumeroShort;
									pDiario->TotStringhe++;
								}

								// prendere dati di WindowsFont per titolo
								NumeroWord = ParseField.pData[i++];
								if (NumeroWord == SCRIPT_IGNORE) {
									InviaLog("ERROR: illegal Id for TitleWFontId of Diary command");
									break;
								}
								j = GlobTomb4.BaseFonts.VetID[NumeroWord];
								if (j == -1) {
									InviaLog("ERROR: illegal Id for TitleWFontId of Diary command");
									break;
								}
								pFont = &GlobTomb4.BaseFonts.VetFonts[j];

								pDiario->FontTitle = *pFont;

								// prendere dati di WindowsFont per testo
								NumeroWord = ParseField.pData[i++];
								if (NumeroWord == SCRIPT_IGNORE) {
									InviaLog("ERROR: illegal Id for CommonTextWFontId of Diary command");
									break;
								}
								j = GlobTomb4.BaseFonts.VetID[NumeroWord];
								if (j == -1) {
									InviaLog("ERROR: illegal Id for CommonTextWFontId of Diary command");
									break;
								}
								pFont = &GlobTomb4.BaseFonts.VetFonts[j];

								pDiario->FontText = *pFont;

								GlobTomb4.BaseDiari.TotDiari++;

								break;

							case cnt_Snow:
								if (ParseField.pData[i]) {

									AddFlags |= fngl_Snow;
									if (ParseField.pData[i] == SNOW_ALL_OUTSIDE) {
										AddFlags |= fngl_Snow_All;
									}
								}
								break;
							case cnt_Rain:
								if (ParseField.pData[i]) {
									AddFlags |= fngl_Rain;
									if (ParseField.pData[i] == RAIN_ALL_OUTSIDE) {
										AddFlags |= fngl_Rain_All;
									}
								}
								break;

							case cnt_FogRange:
								// due word seguenti
								MinFog = ParseField.pData[i++];
								MaxFog = ParseField.pData[i++];
								pFog = &GlobTomb4.BaseFog;
								GlobTomb4.TestFogRange = true;

								if (MinFog == -1)
									MinFog = 12;

								if (MaxFog == -1) {
									MaxFog = 20;
									if (GlobTomb4.LevelFarView != -1) {
										MaxFog = GlobTomb4.LevelFarView;
									} else {
										if (GlobTomb4.WorldFarView != -1) {
											MaxFog = GlobTomb4.WorldFarView;
										}
									}

								}

								pFog->DefMinScript = MinFog;
								pFog->DefMaxScript = MaxFog;

								pFog->NowStartFog = MinFog;
								pFog->NowEndFog = MaxFog;

								break;
							case ctn_MirrorEffect:
								// prima word e' numero di stanza da dove
								// si vede mirror
								TotMirror = GlobTomb4.BaseMirror.TotMirror;
								if (TotMirror >= MAX_MIRRORS) {

									InviaLog("ERROR too much mirror effects for current level. Max number is 100");

									break;
								}
								pMirror = &GlobTomb4.BaseMirror.VetMirror[TotMirror];

								pMirror->MirrorRoom = ParseField.pData[i++];
								// stanza nascosta dietro specchio
								pMirror->HiddenRoom = ParseField.pData[i++];
								// Tipo di mirror
								pMirror->MirrorType = ParseField.pData[i++];
								// adesso c'e' l'opzionale array degli animating
								k = 0;
								pMirror->TotAnimating = Indice - i;

								for (j = i; j < Indice; j++) {
									if (ParseField.pData[j] == SCRIPT_IGNORE) {
										pMirror->TotAnimating = k;
										break;
									}
									pMirror->VetAnimMain[k++] = ParseField.pData[j];
								}
								// attivare sempre il mirror all'inizio
								pMirror->TestAttivo = 1;

								GlobTomb4.BaseMirror.TotMirror = TotMirror + 1;

								break;

							case ctn_KeyPad:
								pScriptKeyPad = &GlobTomb4.BaseKeyPad.ScriptSettings;
								// prima word: indice animazione iniziale
								pScriptKeyPad->IndexFirstAnim = ParseField.pData[i++];
								/// frame iniziale
								pScriptKeyPad->FrameFirstAnim = ParseField.pData[i++];
								// animazione finale
								pScriptKeyPad->IndexAfterAnim = ParseField.pData[i++];
								// suono per click
								pScriptKeyPad->ClickSound = ParseField.pData[i++];
								break;

							case ctn_Elevator:
								// allocare un nuovo record
								j = GlobTomb4.BaseElevator.TotElelevators;

								if (j >= MAX_ELEVATORS) {

									InviaLog("ERROR: too much elevators for current level");

									break;
								}
								GlobTomb4.BaseElevator.TotElelevators++;
								pElevatore = &GlobTomb4.BaseElevator.VetScriptElevators[j];
								pAscensore = &GlobTomb4.BaseElevator.VetAscensori[j];

								// primo valore e' indice elevatore
								pElevatore->IndiceElevatore = ParseField.pData[i++];
								// distanza tra floors
								pElevatore->ClickDistance = ParseField.pData[i++];
								// numero di piani
								pElevatore->TotFloors = ParseField.pData[i++];
								// flag elevatore
								pElevatore->Flags = ParseField.pData[i++];
								if (pElevatore->Flags == SCRIPT_IGNORE)
									pElevatore->Flags = 0;

								pElevatore->TotDoors = 0;
								// indexfirstdoor
								pElevatore->IndexFirstDoor = ParseField.pData[i++];
								// indice keypad
								pElevatore->KeyPadIndex = ParseField.pData[i++];
								// velocita'
								pElevatore->Speed = ParseField.pData[i++];
								if (pElevatore->Speed == SCRIPT_IGNORE)
									pElevatore->Speed = 20;

								// ora lista (opzionale) di item collegati ad ascensore
								k = 0;
								pElevatore->TotFrameItems = Indice - i;

								for (j = i; j < Indice; j++) {
									if (ParseField.pData[j] == SCRIPT_IGNORE) {
										pElevatore->TotFrameItems = k;
										break;
									}
									pElevatore->VetFrameItems[k++] = ParseField.pData[j];
								}

								break;

							case ctn_Detector:
								pDetector = &GlobTomb4.BaseDetector;
								pDetector->TestAttivo = true;
								pDetector->Flags = ParseField.pData[i++];
								if (pDetector->Flags == SCRIPT_IGNORE)
									pDetector->Flags = 0;
								pDetector->ScalaMetrica = ParseField.pData[i++];
								if (pDetector->ScalaMetrica == SCRIPT_IGNORE)
									pDetector->ScalaMetrica = 2;
								pDetector->RangeMetri = ParseField.pData[i++];
								// ora elenco item
								k = 0;
								pDetector->TotIndici = Indice - i;

								for (j = i; j < Indice; j++) {

									pDetector->VetIndici[k++] = ParseField.pData[j];

								}
								if (pDetector->TotIndici == 0) {

									InviaLog("ERROR in detector: no item index is present");

									pDetector->TestAttivo = false;
								}
								pDetector->TestMostra = false;
								pDetector->Indice = pDetector->VetIndici[0];
								if (pDetector->TestAttivo == true) {
									SetItemDetector(TD_LITTLE_DETECTOR);
								}

								if (pDetector->Flags & DTF_ENGAGE_INVENTORY) {
									pDetector->Flags |= DTF_REQUIRED_ITEM;
								}
								break;
							case ctn_Customize:
								n = ParseField.pData[i++];  // prima word CUST_ tipo

								PluginId = ParseField.pData[i++]; // id di plugin (0 = trng)

								if (n == CUST_SET_INV_ITEM) {
									NInvItems++;
									// se e' il primo
									// azzerare i dati inseriti da eventuale
									// default di title
									if (NInvItems == 1) {
										GlobTomb4.pBaseCustomize->BaseInvItems.TotInvItems = 0;
									}
								}
								if (PluginId > 0) {
									// qui fare call back per customize di plugin
									// fare anche conversione di pluginid
									PluginIndex = GetPluginIndex(PluginId, PLUG_FROM_SCRIPT);
									if (PluginIndex == -1)
										break;

									pCallCustomize = (CALL_CUSTOMIZE) MyGlobPrivate.DataBase.pVetPlugins[PluginIndex].VetDirectCB[CB_CUSTOMIZE_MINE];
									// cbCustomizeMine(WORD CustomizeValue, int NumberOfItems, short *pItemArray)
									pCallCustomize(n, Indice - i, (short *) &ParseField.pData[i]);
								} else {
									EseguiCustomize(n, (short *) &ParseField.pData[i], Indice - i);
								}
								break;
							case ctn_Parameters:
								// prima devo scroprire che tipo di parameters list
								// e'
								n = ParseField.pData[i++];
								PluginId = ParseField.pData[i++];

								if (PluginId > 0) {
									// chiamare callback di plugin per gestire parameter
									PluginIndex = GetPluginIndex(PluginId, PLUG_FROM_SCRIPT);
									if (PluginIndex == -1)
										break;

									pCallParam = (CALL_PARAMETER) MyGlobPrivate.DataBase.pVetPlugins[PluginIndex].VetDirectCB[CB_PARAMETER_MINE];
									if (pCallParam == NULL) {
										sprintf_s(BufferLog, "ERROR: plugin %s has not set the callback for its Parameters= script commands", MyGlobPrivate.DataBase.pVetPlugins[PluginIndex].Nome);
										InviaLog(BufferLog);
										break;
									}
									// (WORD ParameterValue, int NumberOfItems, short *pItemArray);
									pCallParam(n, Indice - i, (short *) &ParseField.pData[i]);
									break;

								}

								// il primo parametro e' sempre un PARAM_...
								// che definisce il tipo di lista
								switch (n) {

								case PARAM_ACTOR_SPEECH:
									n = GlobTomb4.pBaseSpeechActor->TotSpeechActor;
									if (n >= MAX_SPEECH_PARAM) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_ACTOR_SPEECH commands in current level section: %d", MAX_SPEECH_PARAM);
										InviaLog(BufferLog);
										break;
									}

									pSpeech = &GlobTomb4.pBaseSpeechActor->VetSpeechActor[n];
									pSpeech->IdSpeech = ParseField.pData[i++];

									if (pSpeech->IdSpeech > MAX_SPEECH_PARAM * 10) {
										sprintf_s(BufferLog, "ERROR: too big ID value (%d) for PARAM_ACTOR_SPEECH command in current level section", pSpeech->IdSpeech);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.pBaseSpeechActor->VetId[pSpeech->IdSpeech] = n;

									pSpeech->Flags = ParseField.pData[i++];
									if (pSpeech->Flags == SCRIPT_IGNORE)
										pSpeech->Flags = 0;

									pSpeech->Parameter = ParseField.pData[i++];

									pSpeech->FrameRate = ParseField.pData[i++];
									if (pSpeech->FrameRate == -1)
										pSpeech->FrameRate = 5;

									pSpeech->SpeechSlot = ParseField.pData[i++];

									pSpeech->HeadSlotMesh = ParseField.pData[i++];

									pSpeech->FirstSpeechMesh = ParseField.pData[i++];

									pSpeech->TotSpeechMesh = ParseField.pData[i++];

									pSpeech->TotCommands = Indice - i;

									for (j = 0; j < pSpeech->TotCommands; j++) {
										pSpeech->VetCommands[j] = ParseField.pData[i++];
									}
									GlobTomb4.pBaseSpeechActor->TotSpeechActor++;
									break;


								case PARAM_MOVE_ITEM:
									n = GlobTomb4.BaseMoveItem.TotMove;
									if (n >= MAX_MOVE_PARAM) {
										sprintf_s(BufferLog,"WARNING: too much Parameters PARAM_MOVE_ITEM command in current level section: %d", n);
										InviaLog(BufferLog);
										break;
									}

									pMoveItem = &GlobTomb4.BaseMoveItem.VetMove[n];
									pMoveItem->IdMove = ParseField.pData[i++];
									if (pMoveItem->IdMove >= MAX_MOVE_PARAM * 10) {
										sprintf_s(BufferLog, "ERROR: Too big ID value (%d) for PARAM_MOVE_ITEM command in current level section", pMoveItem->IdMove);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseMoveItem.VetID[pMoveItem->IdMove] = n;
									pMoveItem->Flags = ParseField.pData[i++];
									if (pMoveItem->Flags == SCRIPT_IGNORE)
										pMoveItem->Flags = 0;
									pMoveItem->ItemIndex = ParseField.pData[i++];
									pMoveItem->Direzione = ParseField.pData[i++];
									pMoveItem->Distanza = ParseField.pData[i++];
									pMoveItem->Speed = ParseField.pData[i++];
									if (pMoveItem->Speed == SCRIPT_IGNORE)
										pMoveItem->Speed = 0;

									pMoveItem->SuonoMovimento = ParseField.pData[i++];
									pMoveItem->SuonoFinale = ParseField.pData[i++];
									pMoveItem->Extra = ParseField.pData[i++];
									if (pMoveItem->Extra == -1)
										pMoveItem->Extra = 0;

									GlobTomb4.BaseMoveItem.TotMove++;
									break;
								case PARAM_BIG_NUMBERS:
									n = GlobTomb4.TotBigNumbers;
									TotItems = TotWords - 1;

									for (j = 0; j < (int) TotItems; j++) {
										GlobTomb4.VetBigNumbers[n++] = ParseField.pData[i++];
									}
									GlobTomb4.TotBigNumbers = n;
									break;
								case PARAM_SHOW_SPRITE:
									n = GlobTomb4.BaseShowSprites.TotShowSprites;
									if (n >= MAX_SHOW_SPRITES) {
										sprintf_s(BufferLog,"ERROR: too much Parameters=PARAM_SHOW_SPRITE commands in current level section. The max number was %d", n);
										InviaLog(BufferLog);
										break;
									}

									pShowSprite = &GlobTomb4.BaseShowSprites.VetShowSprites[n];
									pShowSprite->IdShowSprite = ParseField.pData[i++];
									sprintf_s(MyBufInterno, "Parameters=PARAM_SHOW_SPRITE, %d", pShowSprite->IdShowSprite);

									if (pShowSprite->IdShowSprite >= MAX_SHOW_SPRITES * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for PARAM_SHOW_SPRITE command in current level section", pShowSprite->IdShowSprite);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseShowSprites.VetIdShowSprites[pShowSprite->IdShowSprite] = n;

									pShowSprite->Flags = ParseField.pData[i++];
									if (pShowSprite->Flags == SCRIPT_IGNORE)
										pShowSprite->Flags = 0;

									pShowSprite->Posizione.left = ParseField.pData[i++];
									pShowSprite->Posizione.top = ParseField.pData[i++];
									pShowSprite->Posizione.right = ParseField.pData[i++];
									pShowSprite->Posizione.bottom = ParseField.pData[i++];

									pShowSprite->SlotSprite = ParseField.pData[i++];
									pShowSprite->IndiceSprite = ParseField.pData[i++];
									// se c'e' colore trovarlo adesso
									n = ParseField.pData[i++];

									// trovare coloregb
									if (n == SCRIPT_IGNORE) {
										pShowSprite->Colore = 0;
									} else {
										pShowSprite->Colore = GetColoreId(n, 0x808080, false, MyBufInterno);
									}

									pShowSprite->GridX = ParseField.pData[i++];
									pShowSprite->GridY = ParseField.pData[i++];
									pShowSprite->ExtraValue = ParseField.pData[i];

									GlobTomb4.BaseShowSprites.TotShowSprites++;
									break;

								case PARAM_SCALE_ITEM:
									n = GlobTomb4.BaseScaleParam.TotScale;
									if (n >= MAX_SCALE_ITEM) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_SCALE_ITEM command in current level section. The max value is %d", n);
										InviaLog(BufferLog);
										break;
									}
									pScale = &GlobTomb4.BaseScaleParam.VetScaleItem[n];
									pScale->IdScale = ParseField.pData[i++];
									if (pScale->IdScale >= MAX_SCALE_ITEM * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_SCALE_ITEM command in current level section", pScale->IdScale);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseScaleParam.VetIdScale[pScale->IdScale] = n;
									pScale->ItemIndex = ParseField.pData[i++];
									pScale->Flags = ParseField.pData[i++];
									if (pScale->Flags == SCRIPT_IGNORE)
										pScale->Flags = 0;
									pScale->BeginPerc = ParseField.pData[i++];
									pScale->FinalPerc = ParseField.pData[i++];
									pScale->IncPerc = ParseField.pData[i++];
									GlobTomb4.BaseScaleParam.TotScale++;
									break;

								case PARAM_COLOR_ITEM:
									n = GlobTomb4.BaseColoraItem.TotColoraItem;
									if (n >= MAX_COLORA_ITEM) {
										sprintf_s(BufferLog,"WARNING: too much Parameters=PARAM_COLOR_ITEM command in current level section: %d", n);
										InviaLog(BufferLog);
										break;
									}
									pColora = &GlobTomb4.BaseColoraItem.VetColoraItem[n];
									pColora->IdColItem  = ParseField.pData[i++];
									if (pColora->IdColItem >= MAX_COLORA_ITEM * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_COLORA_ITEM command in current level section", pColora->IdColItem);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseColoraItem.VetID[pColora->IdColItem] = n;
									GlobTomb4.BaseColoraItem.TotColoraItem++;

									pColora->Flags = ParseField.pData[i++];
									pColora->ItemIndex = ParseField.pData[i++];
									pColora->IdColore1 = ParseField.pData[i++];
									pColora->IdColore2 = ParseField.pData[i++];
									pColora->Speed = ParseField.pData[i];
									break;

								case PARAM_CIRCLE:
									n = GlobTomb4.BaseCircles.TotCircles;
									if (n >= MAX_CIRCLES) {
										sprintf_s(BufferLog,"WARNING: too much Parameters=PARAM_CIRCLE commands in same level section: %d", MAX_CIRCLES);
										InviaLog(BufferLog);
										break;
									}

									pCircle = &GlobTomb4.BaseCircles.VetCircle[n];
									pCircle->IdParam = ParseField.pData[i++];
									if (pCircle->IdParam >= MAX_CIRCLES * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_CIRCLES command in current level section", pCircle->IdParam);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseCircles.VetIdCircle[pCircle->IdParam] = n;

									pCircle->CenterX = ParseField.pData[i++];
									pCircle->CenterY = ParseField.pData[i++];
									pCircle->Radius = ParseField.pData[i];
									GlobTomb4.BaseCircles.TotCircles++;
									break;

								case PARAM_QUADRILATERAL:
									n = GlobTomb4.BaseQuads.TotQuads;
									if (n >= MAX_QUADS) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_QUADRILATERAL commands in same level section: %d", MAX_QUADS);
										InviaLog(BufferLog);
										break;
									}

									pQuad = &GlobTomb4.BaseQuads.VetQuads[n];
									pQuad->IdParam = ParseField.pData[i++];
									if (pQuad->IdParam >= MAX_QUADS * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_QUADS command in current level section", pQuad->IdParam);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseQuads.VetIdQuads[pQuad->IdParam] = n;

									pQuad->Tria1.A.x = (float) ParseField.pData[i++];
									pQuad->Tria1.A.y = (float) ParseField.pData[i++];

									pQuad->Tria1.B.x = (float) ParseField.pData[i++];
									pQuad->Tria1.B.y = (float) ParseField.pData[i++];

									pQuad->Tria1.C.x = (float) ParseField.pData[i++];
									pQuad->Tria1.C.y = (float) ParseField.pData[i++];

									pQuad->Tria2.A.x = pQuad->Tria1.C.x;
									pQuad->Tria2.A.y = pQuad->Tria1.C.y;

									pQuad->Tria2.B.x = (float) ParseField.pData[i++];
									pQuad->Tria2.B.y = (float) ParseField.pData[i++];

									pQuad->Tria2.C.x = pQuad->Tria1.A.x;
									pQuad->Tria2.C.y = pQuad->Tria1.A.y;

									GlobTomb4.BaseQuads.TotQuads++;
									break;

								case PARAM_TRIANGLE:
									n = GlobTomb4.BaseTriangles.TotTriangles;
									if (n >= MAX_TRIANGLES) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_TRIANGLES commands in same level section: %d", MAX_TRIANGLES);
										InviaLog(BufferLog);
										break;
									}

									pTria = &GlobTomb4.BaseTriangles.VetTriangles[n];
									pTria->IdParam = ParseField.pData[i++];
									if (pTria->IdParam >= MAX_TRIANGLES * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_TRIANGLES command in current level section", pTria->IdParam);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseTriangles.VetIdTriangles[pTria->IdParam] = n;

									pTria->Tria.A.x = (float) ParseField.pData[i++];
									pTria->Tria.A.y = (float) ParseField.pData[i++];

									pTria->Tria.B.x = (float) ParseField.pData[i++];
									pTria->Tria.B.y = (float) ParseField.pData[i++];

									pTria->Tria.C.x = (float) ParseField.pData[i++];
									pTria->Tria.C.y = (float) ParseField.pData[i++];

									GlobTomb4.BaseTriangles.TotTriangles++;
									break;

								case PARAM_MOVE_ADV_ITEM:
									// advanced move
									n = GlobTomb4.BaseMoveAdvance.TotMoveAdvance;
									if (n >= MAX_MOVE_ADVANCE) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_MOVE_ADV_ITEM command in current level section: %d", n);
										InviaLog(BufferLog);
										break;
									}
									pMove = &GlobTomb4.BaseMoveAdvance.VetMove[n];
									pMove->IdMove = ParseField.pData[i++];
									if (pMove->IdMove >= MAX_MOVE_ADVANCE * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_MOVE_ADVANCE command in current level section", pMove->IdMove);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseMoveAdvance.VetID[pMove->IdMove] = n;
									pMove->Flags = ParseField.pData[i++];
									if (pMove->Flags == SCRIPT_IGNORE)
										pMove->Flags = 0;
									pMove->Direction = ParseField.pData[i++];
									pMove->Distance = ParseField.pData[i++];
									pMove->Speed = ParseField.pData[i++];
									pMove->SoundStart = ParseField.pData[i++];
									pMove->SoundMoving = ParseField.pData[i++];
									pMove->SoundFInal = ParseField.pData[i++];
									pMove->IndiceTriggerGroup = ParseField.pData[i++];
									GlobTomb4.BaseMoveAdvance.TotMoveAdvance++;
									break;

								case PARAM_ROTATE_ITEM:
									n = GlobTomb4.BaseRotateItem.TotRotate;
									if (n >= MAX_ROTATE_PARAM) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_ROTATE_ITEM command in current level section: %d", n);
										InviaLog(BufferLog);
										break;
									}

									pRotate = &GlobTomb4.BaseRotateItem.VetRotate[n];
									pRotate->IdMove = ParseField.pData[i++];
									if (pRotate->IdMove >= MAX_ROTATE_PARAM * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_ROTATE_PARAM command in current level section", pRotate->IdMove);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseRotateItem.VetID[pRotate->IdMove] = n;
									pRotate->Flags = ParseField.pData[i++];
									if (pRotate->Flags == SCRIPT_IGNORE)
										pRotate->Flags = 0;
									pRotate->ItemIndex = ParseField.pData[i++];
									pRotate->DirezioneH = ParseField.pData[i++];
									pRotate->AngoloH = ParseField.pData[i++];
									pRotate->SpeedH = ParseField.pData[i++];

									pRotate->DirezioneV = ParseField.pData[i++];
									pRotate->AngoloV = ParseField.pData[i++];
									pRotate->SpeedV = ParseField.pData[i++];

									pRotate->SoundMoving = ParseField.pData[i++];
									pRotate->SoundFinal = ParseField.pData[i++];
									GlobTomb4.BaseRotateItem.TotRotate++;
									break;
								case PARAM_SET_CAMERA:
									n = GlobTomb4.BaseSetCamera.TotSetCamera;
									if (n >= MAX_SET_CAMERA) {
										sprintf_s(BufferLog, "WARNING: too much Parameters PARAM_SET_CAMERA command in current level section: %d", n);
										InviaLog(BufferLog);
										break;
									}
									pCamera = &GlobTomb4.BaseSetCamera.VetSetCamera[n];
									pCamera->IdCamera = ParseField.pData[i++];
									if (pCamera->IdCamera >= MAX_SET_CAMERA * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_SET_CAMERA command in current level section", pCamera->IdCamera);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseSetCamera.VetID[pCamera->IdCamera] = n;
									// ora leggere altri parametri dopo l'id
									pCamera->Flags = ParseField.pData[i++];
									if (pCamera->Flags == SCRIPT_IGNORE)
										pCamera->Flags = 0;
									pCamera->Distance = ParseField.pData[i++];

									if (pCamera->Distance == -1) {
										pCamera->Distance = GlobTomb4.pBaseCustomize->CameraCust.ChaseDistance;
									}

									pCamera->VOrient = ParseField.pData[i++];

									if (pCamera->VOrient == -1) {
										pCamera->VOrient = GlobTomb4.pBaseCustomize->CameraCust.ChaseHeight;
									}
									pCamera->HOrient = ParseField.pData[i++];
									if (pCamera->HOrient == -1) {
										pCamera->HOrient = GlobTomb4.pBaseCustomize->CameraCust.ChaseHOrient;
									}
									pCamera->Speed = ParseField.pData[i++];
									if (pCamera->Speed == SCRIPT_IGNORE) {
										pCamera->Speed = GlobTomb4.pBaseCustomize->CameraCust.Speed;
									}
									GlobTomb4.BaseSetCamera.TotSetCamera++;
									break;


								case PARAM_PRINT_TEXT:
									n = GlobTomb4.BaseParamPrint.TotPrintText;
									if (n >= MAX_PARAM_PRINT_TEXT) {
										sprintf_s(BufferLog, "WARNING: too much Parameters PARAM_PRINT_TEXT command in current level section: %d", n);
										InviaLog(BufferLog);
										break;
									}
									pPrint = &GlobTomb4.BaseParamPrint.VetPrint[n];
									pPrint->IdPrint  = ParseField.pData[i++];
									if (pPrint->IdPrint >= MAX_PARAM_PRINT_TEXT * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for MAX_PARAM_PRINT_TEXT command in current level section", pPrint->IdPrint);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseParamPrint.VetID[pPrint->IdPrint] = n;
									// ora leggere tre word successive
									// come fossero quelli di comando TextFormat
									ScansioneTextFormat(&pPrint->Formatting, &ParseField.pData[i]);
									i += 3;
									pPrint->DurateTime = ParseField.pData[i++];
									pPrint->OrgX = ParseField.pData[i++];
									pPrint->OrgY = ParseField.pData[i];

									GlobTomb4.BaseParamPrint.TotPrintText++;
									break;
								case PARAM_SWAP_ANIMATIONS:
									n = GlobTomb4.pBaseSwapAnim->TotSwapAnim;
									if (n >= MAX_SWAP_ANIM) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_SWAP_ANIMATIONS  commands in current level section: %d", PARAM_SWAP_ANIMATIONS);
										InviaLog(BufferLog);
										break;
									}

									pSwap = &GlobTomb4.pBaseSwapAnim->VetSwapAnim[n];
									pSwap->Id = ParseField.pData[i++];
									if (pSwap->Id >= MAX_SWAP_ANIM * 10) {
										sprintf_s(BufferLog, "WARNING: too big ID value (%d) for Parameters=PARAM_SWAP_ANIMATIONS  command in current level section", pSwap->Id);
										InviaLog(BufferLog);
										break;

									}

									GlobTomb4.pBaseSwapAnim->VetId[pSwap->Id] = n;

									pSwap->FirstSourceAnim = ParseField.pData[i++];
									pSwap->FirstTargetAnim = ParseField.pData[i++];
									pSwap->NumberOfAim = ParseField.pData[i++];
									GlobTomb4.pBaseSwapAnim->TotSwapAnim++;
									break;
								case PARAM_INPUT_BOX:
									n = GlobTomb4.BaseInputBoxes.TotInputBox;

									if (n >= MAX_INPUT_BOX) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_INPUT_BOX  commands in current level section: %d", MAX_INPUT_BOX);
										InviaLog(BufferLog);
										break;
									}
									pInputBox = &GlobTomb4.BaseInputBoxes.VetInputBox[n];
									pInputBox->IdInputBox = ParseField.pData[i++];
									if (pInputBox->IdInputBox >= MAX_INPUT_BOX * 10) {
										sprintf_s(BufferLog, "WARNING: Too big ID value (%d) for Parameters=PARAM_INPUT_BOX command in current level section", pInputBox->IdInputBox  );
										InviaLog(BufferLog);
										break;
									}

									GlobTomb4.BaseInputBoxes.VetId[pInputBox->IdInputBox] = n;

									// InputBoxId, BckImageId, WFontId, MaxChars, SfxSound, Flags (FIB_ values)
									pInputBox->IdImage = ParseField.pData[i++];
									pInputBox->IdWFont = ParseField.pData[i++];
									pInputBox->MaxChars = ParseField.pData[i++];
									if (pInputBox->MaxChars == SCRIPT_IGNORE)
										pInputBox->MaxChars = 10;
									pInputBox->SfxSound = ParseField.pData[i++];
									if (pInputBox->SfxSound == -1)
										pInputBox->SfxSound = 109;
									pInputBox->RIB_Flags = ParseField.pData[i++];
									if (pInputBox->RIB_Flags == SCRIPT_IGNORE) {
										pInputBox->RIB_Flags = RIB_BLINK_CARET | RIB_SOUND_ON_KEY | RIB_ONLY_CAPS;
									}
									pInputBox->ExtraParam = ParseField.pData[i];
									GlobTomb4.BaseInputBoxes.TotInputBox++;
									break;

								case PARAM_RECT:
									n = GlobTomb4.BaseParamMyRects.TotMyRect;
									if (n >= MAX_MY_RECT) {
										sprintf_s(BufferLog, "WARNING: too much Parameters=PARAM_RECT  commands in current level section: %d", MAX_MY_RECT);
										InviaLog(BufferLog);
										break;
									}

									pMyRect = &GlobTomb4.BaseParamMyRects.VetMyRect[n];
									pMyRect->Id = ParseField.pData[i++];
									if (pMyRect->Id  >= MAX_MY_RECT * 10) {
										sprintf_s(BufferLog, "WARNING: Too big ID value (%d) for Parameters=PARAM_RECT command in current level section", pMyRect->Id );
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseParamMyRects.VetId[pMyRect->Id] = n;

									pMyRect->OrgX = ParseField.pData[i++];
									pMyRect->OrgY = ParseField.pData[i++];
									pMyRect->SizeX = ParseField.pData[i++];
									pMyRect->SizeY = ParseField.pData[i++];
									pMyRect->ForeColor = ParseField.pData[i++];
									pMyRect->BackColor = ParseField.pData[i];

									GlobTomb4.BaseParamMyRects.TotMyRect++;
									break;

								case PARAM_WTEXT:
									//  IdParameter, Flags, WindowsFontId, TimeDurate, Left, Top, Right, Bottom
									n = GlobTomb4.BaseParamWText.TotParamWText;
									if (n >= MAX_PARAM_WTEXT) {
										sprintf_s(BufferLog, "WARNING: too much Parameters PARAM_WTEXT commands in current level section: %d", MAX_PARAM_WTEXT);
										InviaLog(BufferLog);
										break;
									}
									pWText = &GlobTomb4.BaseParamWText.VetParamWText[n];
									pWText->IdParam = ParseField.pData[i++];
									if (pWText->IdParam >= MAX_PARAM_WTEXT * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for PARAM_WTEXT command in current level section", pWText->IdParam);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseParamWText.VetIds[pWText->IdParam] = n;

									pWText->Flags = ParseField.pData[i++];
									if (pWText->Flags == SCRIPT_IGNORE)
										pWText->Flags = 0;

									pWText->WindowsFontId = ParseField.pData[i++];

									pWText->Durate = ParseField.pData[i++];

									pWText->MyRect.left = ParseField.pData[i++];
									pWText->MyRect.top  = ParseField.pData[i++];
									pWText->MyRect.right = ParseField.pData[i++];
									pWText->MyRect.bottom = ParseField.pData[i++];

									GlobTomb4.BaseParamWText.TotParamWText++;
									break;

								case PARAM_LIGHTNING:
									n = GlobTomb4.BaseParamLightning.TotParamLgtn;

									if (n >= MAX_PARAM_LIGHTNING) {
										sprintf_s(BufferLog, "WARNING: too much Parameters PARAM_LIGHTNING commands in current level section: %d", n);
										break;
									}
									pLightning = &GlobTomb4.BaseParamLightning.VetRecordLgtn[n];
									pLightning->IdParamLgtn = ParseField.pData[i++];
									if (pLightning->IdParamLgtn >= MAX_PARAM_LIGHTNING * 10) {
										sprintf_s(BufferLog, "Too big ID value (%d) for PARAM_LIGHTNING command in current level section", pLightning->IdParamLgtn);
										InviaLog(BufferLog);
										break;
									}
									GlobTomb4.BaseParamLightning.VetId[pLightning->IdParamLgtn] = n;
									// ora leggere i parametri
									pLightning->Flags = ParseField.pData[i++];
									if (pLightning->Flags == -1)
										pLightning->Flags = 0;

									pLightning->IndexSource = ParseField.pData[i++];

									pLightning->IndexTarget = ParseField.pData[i++];
									// trovare
									Index = ParseField.pData[i++];
									pLightning->Color = TrovaColoreRGB(Index);

									pLightning->Intensity = ParseField.pData[i++];
									if (pLightning->Intensity == -1)
										pLightning->Intensity = 0x20;

									pLightning->SoundEffect = ParseField.pData[i++];

									pLightning->Size = ParseField.pData[i++];
									if (pLightning->Size == -1)
										pLightning->Size = 0x18;

									pLightning->ParticleDurate = ParseField.pData[i++];
									if (pLightning->ParticleDurate == -1)
										pLightning->ParticleDurate = 0x18;

									pLightning->IntervalMask = ParseField.pData[i++];
									if (pLightning->IntervalMask < 1)
										pLightning->IntervalMask = 1;

									pLightning->Arg1 = ParseField.pData[i++];
									if (pLightning->Arg1 == -1)
										pLightning->Arg1 = 1;

									pLightning->Arg3 = ParseField.pData[i];
									if (pLightning->Arg3 == -1)
										pLightning->Arg3 = 5;

									GlobTomb4.BaseParamLightning.TotParamLgtn++;
									break;

								default:

									sprintf_s(BufferLog, "ERROR: found a parameter list with unknown type: %d", n);
									InviaLog(BufferLog);
									break;

								}
								break;
							case ctn_WindowsFont:
								n = GlobTomb4.BaseFonts.TotFonts;
								if (n >= MAX_FONTS) {
									sprintf_s(BufferLog, "WARNING: too much WindowsFont= command. Max=%d", MAX_FONTS);
									InviaLog(BufferLog);
									break;
								}
								pFont = &GlobTomb4.BaseFonts.VetFonts[n];
								pFont->IdFont = ParseField.pData[i++];
								sprintf_s(MyBufInterno, "WindowsFont= %d", pFont->IdFont);
								if (pFont->IdFont >= MAX_FONTS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for WindowsFont command in current level section", pFont->IdFont);
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.BaseFonts.VetID[pFont->IdFont] = n;
								// indice nome font
								j = ParseField.pData[i++];
								pChar = GetString(j);
								// scompattare formato "%d:%s"
								pChar = ScompattaNomeFont(pChar, &pFont->CharSet);
								strcpy_s(pFont->NomeFont, pChar);

								pFont->FlagsWFF = ParseField.pData[i++];
								if (pFont->FlagsWFF == SCRIPT_IGNORE) {
									pFont->FlagsWFF = 0;
								}
								pFont->SizeFont = ParseField.pData[i++];

								// colore rgb
								j = ParseField.pData[i++];
								pFont->ColoreText = GetColoreId(j, 0xFFFFFF, true, MyBufInterno);
								j = ParseField.pData[i++];
								if (j != SCRIPT_IGNORE)
									pFont->ColoreShadow = GetColoreId(j, 0x00000, true, MyBufInterno);
								GlobTomb4.BaseFonts.TotFonts++;
								break;
							case ctn_TestPosition:
								Tot = GlobTomb4.BaseTestPosition.TotTestPositions;
								if (Tot >= MAX_TEST_POSITION) {
									sprintf_s(BufferLog, "WARNING: too much TestPosition script command in this level section. Max is %d", Tot);
									InviaLog(BufferLog);
									break;
								}
								pTestPosition = &GlobTomb4.BaseTestPosition.VetTestPosition[Tot];
								pTestPosition->IdTestPosition = ParseField.pData[i++];
								if (pTestPosition->IdTestPosition >= MAX_TEST_POSITION * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for TestPosition command in current level section", pTestPosition->IdTestPosition);
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.BaseTestPosition.VetId[pTestPosition->IdTestPosition] = Tot;
								// flags
								pTestPosition->Flags = ParseField.pData[i++];
								if (pTestPosition->Flags == SCRIPT_IGNORE)
									pTestPosition->Flags = 0;

								// slot
								pTestPosition->Slot = ParseField.pData[i++];
								// x range
								pTestPosition->DatiPosition.Distance.MinX = ParseField.pData[i++];
								pTestPosition->DatiPosition.Distance.MaxX = ParseField.pData[i++];
								// y range
								pTestPosition->DatiPosition.Distance.MinY = ParseField.pData[i++];
								pTestPosition->DatiPosition.Distance.MaxY = ParseField.pData[i++];
								// z range
								pTestPosition->DatiPosition.Distance.MinZ = ParseField.pData[i++];
								pTestPosition->DatiPosition.Distance.MaxZ = ParseField.pData[i++];

								// diff orient horizzontal
								pTestPosition->DatiPosition.Orienting.OrientHMin = ParseField.pData[i++];
								pTestPosition->DatiPosition.Orienting.OrientHMax = ParseField.pData[i++];
								// diff orient vertiale
								pTestPosition->DatiPosition.Orienting.OrientVMin = ParseField.pData[i++];
								pTestPosition->DatiPosition.Orienting.OrientVMax = ParseField.pData[i++];
								// diff orient rotate
								pTestPosition->DatiPosition.Orienting.OrientRMin = ParseField.pData[i++];
								pTestPosition->DatiPosition.Orienting.OrientRMax = ParseField.pData[i];

								GlobTomb4.BaseTestPosition.TotTestPositions++;
								break;

							case ctn_ColorRGB:
								Tot = GlobTomb4.BaseColoriRGB.TotColori;
								if (Tot >= MAX_COLORI_RGB) {
									sprintf_s(BufferLog, "WARNING: Too much ColorRGB script command in this level section. Max is %d", Tot);
									InviaLog(BufferLog);
									break;
								}
								pColor = &GlobTomb4.BaseColoriRGB.VetColori[Tot];
								pColor->IdColor = ParseField.pData[i++];
								if (pColor->IdColor >= MAX_COLORI_RGB * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for ColorRGB command in current level section", pColor->IdColor );
									InviaLog(BufferLog);
									break;
								}
								// salvare id
								GlobTomb4.BaseColoriRGB.VetID[pColor->IdColor] = Tot;

								Rosso = ParseField.pData[i++];
								Verde = ParseField.pData[i++];
								Blu = ParseField.pData[i++];

								pColor->Colore = Blu;
								pColor->Colore |= (Verde << 8);
								pColor->Colore |= (Rosso << 16);

								GlobTomb4.BaseColoriRGB.TotColori++;
								break;

							case ctn_TriggerGroup:
							case cnt_TriggerGroupWord:
								// ATTENZIONE: se e' TagScript == cnt_TriggerGroupWord, tutti gli argomenti sono word
								// se invece e' cnt_TriggerGroup, la prima e' una word (id del triggergroup)
								// e le altre saranno dword
								TotGroups = GlobTomb4.pBaseTriggerGroups->TotTriggerGroups;
								if (TotGroups >= MAX_TRIGGER_GROUPS) {
									sprintf_s(BufferLog, "ERROR: too much TriggerGroup command in current level. Max = %d", MAX_TRIGGER_GROUPS);
									InviaLog(BufferLog);
									break;
								}
								pGroup = &GlobTomb4.pBaseTriggerGroups->VetTriggerGroups[TotGroups];

								pGroup->IdGroup = ParseField.pData[i++];
								if (pGroup->IdGroup >= MAX_TRIGGER_GROUPS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for TriggerGroup command in current level section", pGroup->IdGroup);
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.pBaseTriggerGroups->VetID[pGroup->IdGroup] = TotGroups;

								// ora leggere sequence di trigger
								// ogni trigger ci sono tre valori
								k = Indice - i;
								if (TagScript == ctn_TriggerGroup) {
									pGroup->TotTriggers = k / 6;  // calcola numero di word presenti per ogni trigger
								}else {
									// dimensione word solo 3 word per ogni trigger
									pGroup->TotTriggers = k / 3;
								}
								pDword = (DWORD *) &ParseField.pData[i];
								pWord = &ParseField.pData[i];

								i = 0;
								for (j = 0; j < pGroup->TotTriggers; j++) {
									pTrigger = &pGroup->VetTriggers[j];

									if (TagScript == ctn_TriggerGroup) {
										// tipo Dword
										pTrigger->PluginId = (WORD) (pDword[i] >> 16);
										pTrigger->Flags = (WORD) pDword[i++];
										pTrigger->Object = (WORD) pDword[i++];
										pTrigger->Timer = (WORD) pDword[i++];
									} else {

										// tipo word
										pTrigger->PluginId = 0;
										pTrigger->Flags = pWord[i++];
										pTrigger->Object = pWord[i++];
										pTrigger->Timer = pWord[i++];

									}

									// ora se manca nei flag qualunque
									// tgroup per quale indice usare
									// allora impostare troup per uso
									// di indice del trigger (se pero' e' flipeffect dovrebbe essere evitato)
									if ((pTrigger->Flags & TGROUP_FLIPEFFECT) == 0) {
										// non e' flipeffect
										if ((pTrigger->Flags & (TGROUP_USE_FOUND_ITEM_INDEX + TGROUP_USE_OWNER_ANIM_ITEM_INDEX + TGROUP_USE_EXECUTOR_ITEM_INDEX + TGROUP_USE_ITEM_USED_BY_LARA_INDEX)) == 0) {

											pTrigger->Flags |= TGROUP_USE_TRIGGER_ITEM_INDEX;
										}
									}

									// ggestione single shot resumed
									if (pTrigger->Flags & TGROUP_SINGLE_SHOT_RESUMED) {
										// memorizzare questo id
										// a meno che non sia gia' presente il groupid
										for (k = 0; k < pSingleShotTG->TotTGResumed; k++) {
											if (pSingleShotTG->VetTGResumed[k] == pGroup->IdGroup)
												break;
										}

										if (k == pSingleShotTG->TotTGResumed) {
											// non c'era: memorizzarlo ora
											pSingleShotTG->VetTGResumed[k] = pGroup->IdGroup;
											pSingleShotTG->TotTGResumed++;

										}
									}
								}
								GlobTomb4.pBaseTriggerGroups->TotTriggerGroups++;
								break;

							case ctn_MultEnvCondition:
								// MultEnvCondition=:Word:Word:Word:Array

								n = GlobTomb4.pBaseEnvConditions->TotScriptEnvCondition;
								if (n >= MAX_ENV_SCRIPT_CONDITIONS) {

									sprintf_s(BufferLog, "ERROR: too many MultEnvCondition commands (max %d for level)", MAX_ENV_SCRIPT_CONDITIONS);
									break;
								}
								pEnvScript = &GlobTomb4.pBaseEnvConditions->VetScriptEndCondition[n];
								GlobTomb4.pBaseEnvConditions->TotScriptEnvCondition++;

								pEnvScript->IdEnvScript = ParseField.pData[i++];

								if (pEnvScript->IdEnvScript >= MAX_ENV_SCRIPT_CONDITIONS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for MultEnvCondition command in current level section", pEnvScript->IdEnvScript );
									InviaLog(BufferLog);
									break;
								}
								// salvare id
								GlobTomb4.pBaseEnvConditions->VetID[pEnvScript->IdEnvScript] = n;
								n = 0;
								pEnvScript->VetEnvCondition[n].EnvCondition = ParseField.pData[i++];
								pEnvScript->VetEnvCondition[n].DistanceEnv = ParseField.pData[i++];
								pEnvScript->VetEnvCondition[n].Extra = ParseField.pData[i++];

								// ora prendere l'elenco (successivo)
								n++;
								Tot = Indice - i;

								for (j = 0; j < Tot; j += 3) {
									pEnvScript->VetEnvCondition[n].EnvCondition = ParseField.pData[i + j];
									pEnvScript->VetEnvCondition[n].DistanceEnv = ParseField.pData[i + j + 1];
									pEnvScript->VetEnvCondition[n].Extra = ParseField.pData[i + j + 2];
									n++;
								}
								pEnvScript->TotEnvCondition = n;
								break;
							case ctn_ItemGroup:
								Tot = GlobTomb4.BaseItemGroup.TotGroups;
								if (Tot >= MAX_ITEM_GROUPS) {
									InviaLog("ERROR: too many ItemGroup commands for current level");
									break;
								}

								pItemGroup = &GlobTomb4.BaseItemGroup.VetItemGroup[Tot];
								pItemGroup->IdGroup = ParseField.pData[i++];
								if (pItemGroup->IdGroup >= MAX_ITEM_GROUPS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for ItemGroup command in current level section", pItemGroup->IdGroup );
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.BaseItemGroup.VetID[pItemGroup->IdGroup] = Tot;

								n = Indice - i;
								Tot = 0;
								for (j = 0; j < n; j++) {
									pItemGroup->VetIndici[Tot++] = ParseField.pData[i++];
								}
								pItemGroup->TotIndici = Tot;

								GlobTomb4.BaseItemGroup.TotGroups++;
								break;

							case ctn_Organizer:
								n = GlobTomb4.pBaseOrganizer->TotOrganizer;
								if (n >= MAX_ORGANIZERS) {
									InviaLog("ERROR: too many Organizer command for current level (max 500 for level)");
									break;
								}
								pScriptOrg = &GlobTomb4.pBaseOrganizer->VetOrganizer[n];

								pScriptOrg->Id = ParseField.pData[i++];
								if (pScriptOrg->Id >= MAX_ORGANIZERS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for Organizer command in current level section", pScriptOrg->Id);
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.pBaseOrganizer->VetID[pScriptOrg->Id] = n;

								pScriptOrg->Flags = ParseField.pData[i++];
								if (pScriptOrg->Flags == SCRIPT_IGNORE)
									pScriptOrg->Flags = 0;

								pScriptOrg->Parameter = ParseField.pData[i++];
								if (pScriptOrg->Parameter == SCRIPT_IGNORE)
									pScriptOrg->Parameter = 0;

								// adesso ci sono le coppie da eseguire
								Tot = (Indice - i) / 2;
								if (Tot > MAX_ORGANIZE_COPPIE)
									Tot = MAX_ORGANIZE_COPPIE;

								pScriptOrg->TotCoppie = Tot;

								for (j = 0; j < pScriptOrg->TotCoppie; j++) {
									pScriptOrg->VetCoppie[j].Secondi = ParseField.pData[i++];
									pScriptOrg->VetCoppie[j].IdGroup = ParseField.pData[i++];

								}
								GlobTomb4.pBaseOrganizer->TotOrganizer++;

								break;

							case ctn_GlobalTrigger:
								n = GlobTomb4.pBaseGlobalTriggers->TotTriggers;
								if (n >= MAX_GLOBAL_TRIGGERS) {
									sprintf_s(BufferLog, "ERROR: too many GlobalTrigger commands (max %d for level)", MAX_GLOBAL_TRIGGERS);
									InviaLog(BufferLog);
									break;
								}
								pGlob = &GlobTomb4.pBaseGlobalTriggers->VetTriggers[n];
								pGlob->Id = ParseField.pData[i++];
								if (pGlob->Id >= MAX_ORGANIZERS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for GlobalTrigger command in current level section", pGlob->Id);
									InviaLog(BufferLog);
									break;
								}
								// salva id e indice
								GlobTomb4.pBaseGlobalTriggers->VetID[pGlob->Id] = n;

								pGlob->Flags = ParseField.pData[i++];
								if (pGlob->Flags == SCRIPT_IGNORE)
									pGlob->Flags = 0;

								pGlob->GlobalTrigger = ParseField.pData[i++];
								// questo e' una dword
								pGlob->ParamWords.WordBassa = ParseField.pData[i++];
								pGlob->ParamWords.WordAlta = ParseField.pData[i++];

								pGlob->IndiceConditionGroup = ParseField.pData[i++];
								pGlob->IndicePerformGroup = ParseField.pData[i++];
								pGlob->IndiceFalseGroup = ParseField.pData[i++];
								GlobTomb4.pBaseGlobalTriggers->TotTriggers++;
								break;
							case cnt_LaraStartPos:
								GlobTomb4.BaseLaraPosScript.TestPresent = true;
								GlobTomb4.BaseLaraPosScript.Room = ParseField.pData[i++];
								GlobTomb4.BaseLaraPosScript.OCB = ParseField.pData[i];
								break;
							case ctn_Equipment:
								n = GlobTomb4.BaseEquipItem.TotEquip;
								if (n >= MAX_EQUIP_ITEM) {
									InviaLog("ERROR: too many Equipment commands (max 100 for level)");
									break;
								}
								GlobTomb4.BaseEquipItem.VetEquip[n].Slot = ParseField.pData[i++];
								GlobTomb4.BaseEquipItem.VetEquip[n].Quantita = ParseField.pData[i];
								GlobTomb4.BaseEquipItem.TotEquip++;
								break;
							case cnt_CombineItems:
								// trovare il primo record libero per
								// ospitare combine
								pCombine = &GlobTomb4.pAdr->pVetNewCombine[0];

								while (pCombine->pProcedura != NULL)
									pCombine++;

								pCombine->PrimoItem = convert_obj_to_invobj(ParseField.pData[i++]);
								pCombine->SecondoItem = convert_obj_to_invobj(ParseField.pData[i++]);
								pCombine->ItemFinale = convert_obj_to_invobj(ParseField.pData[i]);

								// ora convertire i valori slot
								// negli indici relativi a vetitems
								// se qualcuno manca ignorare ilcomando
								if (pCombine->PrimoItem == 25 || pCombine->SecondoItem == 25 || pCombine->ItemFinale == 25)
									break;

								pCombine->pProcedura = &MiaCombineItems;
								// salvare item che prima non avevano
								// flag di combine
								AggiungiCombinabile(pCombine->PrimoItem);
								AggiungiCombinabile(pCombine->SecondoItem);

								// ok, ora attivare i flag corretti
								GlobTomb4.pAdr->pVetFlagsInventoryItems[pCombine->PrimoItem] |= 8;
								GlobTomb4.pAdr->pVetFlagsInventoryItems[pCombine->SecondoItem] |= 8;
								GlobTomb4.pAdr->pVetFlagsInventoryItems[pCombine->ItemFinale] |= 0x10;

								pCombine++;
								pCombine->pProcedura = NULL;
								break;

							case cnt_Switch:
								n = GlobTomb4.BaseSwitch.TotSwitch;
								if (n >= MAX_SWITCH) {
									InviaLog("ERROR: reached max number of Switch= script command for current level");
									break;
								}
								pSwitch = &GlobTomb4.BaseSwitch.VetSwitch[n];
								pSwitch->IdSwitch = ParseField.pData[i++];
								if (pSwitch->IdSwitch >= MAX_SWITCH * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for Switch command in current level section", pSwitch->IdSwitch );
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.BaseSwitch.VetID[pSwitch->IdSwitch] = n;

								pSwitch->Variable = ParseField.pData[i++];
								if (pSwitch->Variable == SCRIPT_IGNORE)
									pSwitch->Variable = 0x0200;

								pSwitch->Flags = ParseField.pData[i++];
								if (pSwitch->Flags == SCRIPT_IGNORE)
									pSwitch->Flags = 0;

								// ora copiare la lista di indici

								// ora eventuali extra parametri
								k = 0;
								pSwitch->TotIndici = Indice - i;

								for (j = i; j < Indice; j++) {
									pSwitch->VetIndici[k++] = ParseField.pData[j];
								}
								GlobTomb4.BaseSwitch.TotSwitch++;
								break;

							case ctn_Image:

								n = GlobTomb4.pBaseScriptImages->TotScriptImages;
								if (n >= MAX_IMAGES) {
									InviaLog("ERROR: reached max number of Image= script command for current level");
									break;
								}

								pSImage = &GlobTomb4.pBaseScriptImages->VetImages[n];

								pSImage->IdCommand = ParseField.pData[i++];
								if (pSImage->IdCommand >= MAX_IMAGES * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for Image command in current level section", pSImage->IdCommand);
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.pBaseScriptImages->VetID[pSImage->IdCommand] = n;

								pSImage->NumeroImage = ParseField.pData[i++];
								pSImage->Flags = ParseField.pData[i++];
								if (pSImage->Flags == SCRIPT_IGNORE) {
									pSImage->Flags = 0;
								}

								pSImage->EffectTime = ParseField.pData[i++];
								if (pSImage->EffectTime == SCRIPT_IGNORE) {
									pSImage->EffectTime = 30;
								}
								pSImage->AudioTrack = ParseField.pData[i++];
								pSImage->RectZona.left = ParseField.pData[i++];
								pSImage->RectZona.top = ParseField.pData[i++];
								pSImage->RectZona.right = ParseField.pData[i++];
								pSImage->RectZona.bottom = ParseField.pData[i++];

								// se questa immagine e' di tipo preload
								// ed e' diversa dalle altre gia' caricate
								// caricarla adesso
								if (pSImage->Flags & IF_PRELOAD) {
									if (AggiungiImmaginePreload(pSImage->NumeroImage) == false)
										break;

								}
								GlobTomb4.pBaseScriptImages->TotScriptImages++;
								break;

							case ctn_TextureSequence:
								n = GlobTomb4.BaseTexSequence.TotSequenze;
								if (n >= MAX_TEX_SEQUENCE) {
									InviaLog("ERROR: reached max number for TextureSequence in current level");
									break;
								}

								pTexSeq = &GlobTomb4.BaseTexSequence.VetSequenze[n];

								pTexSeq->IdSequenza = ParseField.pData[i++];
								if (pTexSeq->IdSequenza >= MAX_TEX_SEQUENCE * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for TextureSequence command in current level section", pTexSeq->IdSequenza );
									InviaLog(BufferLog);
									break;
								}
								GlobTomb4.BaseTexSequence.VetID[pTexSeq->IdSequenza] = n;

								pTexSeq->FPS = ParseField.pData[i++];
								if (pTexSeq->FPS == SCRIPT_IGNORE)
									pTexSeq->FPS = 30;
								if (pTexSeq->FPS < 1 || pTexSeq->FPS > 30)
									pTexSeq->FPS = 30;

								// calcolare il valore di frame di ritardo
								pTexSeq->FrameDelay = FRAME_SECONDO / pTexSeq->FPS;

								pTexSeq->Flags = ParseField.pData[i++];
								if (pTexSeq->Flags == SCRIPT_IGNORE)
									pTexSeq->Flags = 0;
								if (pTexSeq->Flags & SEQ_LOOP_INVERSE)
									pTexSeq->Flags |= SEQ_LOOP;

								// ora c'e' la sequenza di valori
								// che fra l'altro sono nybble

								n = Indice - i;
								if (n == 0) {
									pTexSeq->TotFrames = 0;
								} else {
									pByte = (BYTE*) &ParseField.pData[i];

									pTexSeq->TotFrames = pByte[0];
									pByte++;
									k = 0;
									for (j = 0; j < pTexSeq->TotFrames; j++) {
										ValByte = pByte[j];
										// per ogni word quattro valori
										pTexSeq->VetFrames[k++] = ValByte & 0x0f;
										pTexSeq->VetFrames[k++] = (ValByte & 0xf0) >> 4;

									}
									GlobTomb4.BaseTexSequence.TotSequenze++;
								}

								break;

							case ctn_AddEffect:
								TotEffetti = GlobTomb4.pBaseEffects->TotEffects;
								if (TotEffetti >= MAX_ADD_EFFECTS) {

									sprintf_s(BufferLog, "ERROR: reached max number for AddEffect= commands (%d)", MAX_ADD_EFFECTS);
									InviaLog(BufferLog);
									break;
								}
								pEffect = &GlobTomb4.pBaseEffects->VetEffects[TotEffetti];
								pEffect->Id = ParseField.pData[i++];
								if (pEffect->Id >= MAX_ADD_EFFECTS * 10) {
									sprintf_s(BufferLog, "Too big ID value (%d) for AddEffect command in current level section", pEffect->Id);
									InviaLog(BufferLog);
									break;
								}
								pEffect->Type = ParseField.pData[i++];
								pEffect->Flags = ParseField.pData[i++];
								if (pEffect->Flags == SCRIPT_IGNORE)
									pEffect->Flags = 0;
								pEffect->Joint = ParseField.pData[i++];
								pEffect->DispX = ParseField.pData[i++];
								pEffect->DispY = ParseField.pData[i++];
								pEffect->DispZ = ParseField.pData[i++];
								pEffect->DurateEmit = ParseField.pData[i++];
								pEffect->DuratePause = ParseField.pData[i++];
								// salvare indice relativo a ID
								GlobTomb4.pBaseEffects->VetID[pEffect->Id] = TotEffetti;

								// ora eventuali extra parametri
								k = 0;
								pEffect->TotExtra = Indice - i;

								for (j = i; j < Indice; j++) {
									pEffect->VetExtra[k++] = ParseField.pData[j];
								}
								GlobTomb4.pBaseEffects->TotEffects++;

								break;

							case cnt_StaticMIP:
								TotMip = GlobTomb4.BaseStaticMIP.TotStaticMIP;
								if (TotMip >= MAX_STATIC_MIP) {
									sprintf_s(BufferLog, "ERROR: Too many StaticMIP= script command in current level (%d)", TotMip);
									InviaLog(BufferLog);
									break;
								}

								pMip = &GlobTomb4.BaseStaticMIP.VetStaticMIP[TotMip];

								pMip->Slot = ParseField.pData[i++];
								pMip->DistanceB = ParseField.pData[i++];
								pMip->SlotB = ParseField.pData[i++];
								pMip->DistanceC = ParseField.pData[i++];
								pMip->SlotC = ParseField.pData[i];

								GlobTomb4.BaseStaticMIP.TotStaticMIP++;
								break;

							case cnt_Animation:
							case cnt_AnimationObj:
								if (TagScript == cnt_Animation) {
									TotAnim = GlobTomb4.pBaseAnimations->TotAnimazioni;
									if (TotAnim >= MAX_ANIM_SCRIPT) {
										sprintf_s(BufferLog, "ERROR: Too much Animation= script command in current [Level] section (%d)", MAX_ANIM_SCRIPT);
										InviaLog(BufferLog);
										break;
									}
									pAnimation = &GlobTomb4.pBaseAnimations->VetAnimations[TotAnim];

								} else {
									// questo e' AnimationObj
									// ci sono due campi prima

									TotAnim = GlobTomb4.BaseAnimObj.TotAnimObj;
									if (TotAnim >= MAX_ANIM_OBJ_SCRIPT) {
										sprintf_s(BufferLog, "Too much AnimationObj= script command in current [Level] section (%d)", MAX_ANIM_OBJ_SCRIPT);
										InviaLog(BufferLog);
										break;
									}
									pAnimObj = &GlobTomb4.BaseAnimObj.VetAnimObj[TotAnim];
									pAnimObj->Slot = ParseField.pData[i++];
									pAnimObj->ActionType = ParseField.pData[i++];

									pAnimation = &pAnimObj->Animation;

								}
								pAnimation->AnimIndex = ParseField.pData[i++];
								pAnimation->Key1 = ParseField.pData[i++];
								pAnimation->Key2 = ParseField.pData[i++];
								pAnimation->Flags = ParseField.pData[i++];
								if (pAnimation->Flags == SCRIPT_IGNORE)
									pAnimation->Flags = 0;

								pAnimation->Environment = ParseField.pData[i++];
								if (pAnimation->Environment == SCRIPT_IGNORE)
									pAnimation->Environment = 0;
								pAnimation->DistanceEnv = ParseField.pData[i++];
								pAnimation->Extra = ParseField.pData[i++];

								// e adesso array
								// copiare tutte le word successive
								k = 0;
								pAnimation->TotStateId = Indice - i;

								for (j = i; j < Indice; j++) {
									pAnimation->VetStateId[k++] = ParseField.pData[j];
								}
								// aumentare numero anim prese
								if (TagScript == cnt_Animation) {
									GlobTomb4.pBaseAnimations->TotAnimazioni++;
								} else {
									GlobTomb4.BaseAnimObj.TotAnimObj++;
								}
								break;

							case cnt_TextFormat:
								// tre word seguenti
								// prima word: colore
								ScansioneTextFormat(&GlobTomb4.PrintString, &ParseField.pData[i]);
								FlagMicroCaratteri = GlobTomb4.PrintString.DefALLFlagsMicro;

								break;
							case cnt_Damage:
								// prima word dei flag
								Numero = ParseField.pData[i++];

								if (Numero & DMG_COLD_WATER)
									pDamage = &GlobTomb4.DamageColdWater;
								else
									pDamage = &GlobTomb4.DamageRoom;

								pDamage->Flags = Numero;

								pDamage->SecondiMorte = ParseField.pData[i++];
								pDamage->SecondiRicrescita = ParseField.pData[i++];

								// ora c'e' dword per colore
								pDword = (DWORD *) &ParseField.pData[i];
								pDamage->Colore = *pDword;
								pDamage->Colore |= 0xff000000;
								i += 2;
								// ora c'e' indice stringa
								pDamage->IndiceStringa = ParseField.pData[i++];
								// ora c'e' percentuale di beep
								pDamage->PercentualeBeep = ParseField.pData[i];
								if (pDamage->PercentualeBeep == SCRIPT_IGNORE)
									pDamage->PercentualeBeep = 15;

								CalcolaQuotaTickPerDamage(pDamage);
								break;

							}
						}
						// calcolare prossimo indice
						i = Indice;
					}
				}
				ContaLivello++;
				break;
			}

			// puntare a chunk successivo
			i = ParseField.NextIndex;
		}

		GlobTomb4.pScriptLevelNow->LevelFlags |= AddFlags;
		// se c'e' flag pe rattivare feature richieste da trlm2009
		// e mancava un comando turbo in questo header, allora attivarlo
		// adesso

		if (GlobTomb4.ScriptOptions.MainFlags & ngfm_Enable_Trlm_Options) {
			// richiesta di attivare feature: attivare turbo
			if (*GlobTomb4.pAdr->pLevelNow != 0 && GlobTomb4.BaseTurbo.Flags == 0) {
				// se manca l'header ng in script dat attivare didefault il turbo per livelli level maanger
				pTurbo = &GlobTomb4.BaseTurbo;

				pTurbo->Flags = TRB_OPTIMIZE_SORTING;

				InviaLog("Enabled Turbo mode");
			}
		}

		// ora ricreare i nomi delle tracce audio usando l'attuale tipo di extensione
		RicreaNomiWav(GlobTomb4.pBaseCustomize->BassDll.TipoEstensione);
		PreparaBarCust();

		if (GlobTomb4.pBaseCustomize->ScreenShotInner.TestAddInnerShot == true) {
			// trovata customize per aggiungere inner screenshot
			GlobTomb4.ScreenShot.TestSalvaMiniShot = true;
			// impostare dimensione
			i = GlobTomb4.pBaseCustomize->ScreenShotInner.FlagQSF & 0x0f;

			if (i >= 6) {
				i = 0;
			}

			GlobTomb4.ScreenShot.ShotSizeX = VetSizeInner[i].x;
			GlobTomb4.ScreenShot.ShotSizeY = VetSizeInner[i].y;
			if (GlobTomb4.pBaseCustomize->ScreenShotInner.FlagQSF & QSF_TRUE_COLOR) {
				GlobTomb4.ScreenShot.TestRGB = true;
			} else {
				GlobTomb4.ScreenShot.TestRGB = false;
			}
		}

		// se c'e' il precahce per filmati, accederealla cartella fmvs

		if (GlobTomb4.pBaseCustomize->FlagsFMV & FMV_PRE_CACHE) {
			InviaLog("Precaching of FMVs folder");
			VetFiles = TrovaFiles(GetFileTrle("fmvs"), "fmv*", &TotFiles);
		}

		// applicare le impostazioni di basefog
		ModificaFogEnd();
		ModificaFogStart();
		ModificaHardwareFog();
		ModificaFogBulbDistance();
	}

	void SalvaTagFmv(BYTE ValoreFmv)
	{
		GlobTomb4.BaseFMV.VetFmv[GlobTomb4.BaseFMV.TotFmv] = ValoreFmv;
		GlobTomb4.BaseFMV.TotFmv++;
	}

	// riprstina fixed camera usata, e riattiva camera standard per seguire lara
	void LiberaCutsceneCamera(void)
	{
		StrAdrCamera *pCam;
		StrCutsceneCamera *pCut;

		pCut = &GlobTomb4.pBaseCutscene->BaseCamera;

		pCut->TestAttiva = false;
		if (pCut->TestAllocata == false)
			return;
		GlobTomb4.TestDisableFeatures &= ~DF_GUARDA;
		// ripristinare dati originali
		*pCut->pCamera = pCut->Original;
		pCut->TestAllocata = false;

		pCam = &GlobTomb4.pAdr->Camera;

		*pCam->pModeCameraNext = 0;
		*pCam->pIndexCameraNext = -1;
		*pCam->pTargetCameraNext = NULL;
		*pCam->pSecondsTimerCamera = 0;
	}

	void InizializzaAdaptiveFarView(void)
	{
		StrAdaptiveFarView *pFar;
		int i;

		pFar = &GlobTomb4.BaseAdaptiveFar;

		pFar->BlocchiFar = 20;

		pFar->MaxFarView = 20;
		pFar->FPStoKeep = 29.0f;

		pFar->Incremento = 0;
		pFar->LastTime = 0;
		for (i = 0; i < 3; i++) {
			pFar->VetLastFps[i] = 30.0;
		}
	}

	// libera tutte le risorse allocate per immagine di pRecord
	// nota: il controllo se immagine era con preload deve essere fatto prima.
	// questa funzione libera anche immagini con preload
	void LiberaImmagine(StrRecordImage *pRecord)
	{
		if (pRecord->TestUsata == false)
			return;

		sprintf_s(BufferLog, "FreeImage(): image%d.bmp", pRecord->NImage);
		InviaLog(BufferLog);

		// prima rimettere il bitmap oriignale nel memhdc
		SelectObject(pRecord->MemHdc, pRecord->hOldBitMap);
		if (pRecord->TestPreload == false) {
			DeleteObject(pRecord->hBitMap);
			pRecord->hBitMap = NULL;
		}

		// adesso si puo' eliminare hdc
		DeleteDC(pRecord->MemHdc);
		pRecord->MemHdc = NULL;
		pRecord->TestUsata = false;
		pRecord->NImage = -1;
	}

	// inizializza dati per cattura screenshot
	void InitScreenShot(void)
	{
		StrMiniShot *pShot;

		pShot = &GlobTomb4.ScreenShot;

		pShot->LastTimeScreenShot = 0;
		pShot->ShotSizeX = 320;
		pShot->ShotSizeY = 240;
		pShot->TestRGB = true;
		pShot->TestSalvaMiniShot = false;
	}

	void LiberaAllFonts(void)
	{
		StrWindowsFont *pFont;
		int i;

		for (i = 0; i < GlobTomb4.BaseFonts.TotFonts; i++) {
			pFont = &GlobTomb4.BaseFonts.VetFonts[i];

			if (pFont->hFont) {
				SelectObject(pFont->HdcConFont, pFont->hFontOld);
				DeleteObject(pFont->hFont);
				pFont->hFont = NULL;
			}
		}
	}

	// imposta in base item inventario
	// i valori per rotazione distaznza, topy ecc per visione in
	// inventario o su schermo
	// #define TD_AMULETO 0    (usa dati di amuleto di horus)
	// #define TD_BIG_DETECTOR 1  (usa dati per mostrare detector su schermo)
	// #define TD_LITTLE_DETECTOR 2  (dati per detector in inventario)
	void SetItemDetector(int TipoDetector)
	{
		short *pSrc;
		tomb4::INVOBJ *pInv;

		pInv = &tomb4::inventry_objects_list[(long)tomb4::invobj_types::INV_QUEST1_ITEM];
		switch (TipoDetector) {
		case TD_AMULETO:
		default:
			pSrc = VetOriginali;
			break;
		case TD_BIG_DETECTOR:
			pSrc = VetDetectorBig;
			break;
		case TD_LITTLE_DETECTOR:
			pSrc = VetDetectorLittle;
			break;
		}

		pInv->yoff = pSrc[0];
		pInv->scale1 = pSrc[1];
		pInv->yrot = pSrc[2];
		pInv->xrot = pSrc[3];
		pInv->zrot = pSrc[4];
		pInv->flags = pSrc[5];
	}

	// inizializza (disattiva tutto) per turbo
	void RipristinaTurbo(void)
	{
		StrBaseTurbo *pTurbo;

		pTurbo = &GlobTomb4.BaseTurbo;

		if (pTurbo->TestPriorita == false)
			return;
		pTurbo->Flags = 0;
		pTurbo->IndicePriorita = -1;
		pTurbo->TestAsync = false;
		pTurbo->TestPriorita = false;
		pTurbo->TotArg = 0;
		RestorePriorita();
	}

	// imposta nuova priorita' per thread di gioco
	bool SetPriority(int Livello)
	{
		DWORD ClasseP, ThreadP;

		if (Livello2Priority(Livello, &ClasseP, &ThreadP) == false)
			return false;

		if (SetPriorityClass(GlobTomb4.pAdr->BaseHandles.hProcess, ClasseP) == FALSE) {

			sprintf_s(BufferLog, "ERROR calling SetPriorityClass() Class=%d", ClasseP);
			InviaLog(BufferLog);

			return false;
		}

		if (SetThreadPriority(GlobTomb4.pAdr->BaseHandles.hThread, ThreadP) == FALSE) {

			sprintf_s(BufferLog, "ERROR: failed calling SetThreadPriority() with Priority_thread = %d ", ThreadP);
			InviaLog(BufferLog);

			return false;
		}

		sprintf_s(BufferLog, "Changed Priority to %d", Livello);
		InviaLog(BufferLog);

		return true;
	}

	// converte indicepriority in coppia di valori per classe e thread
	bool Livello2Priority(int IndicePriority, DWORD *pClasse, DWORD *pThread)
	{
		static DWORD VetClassePriority[14] = {IDLE_PRIORITY_CLASS,
					  IDLE_PRIORITY_CLASS,
					  IDLE_PRIORITY_CLASS,
					  IDLE_PRIORITY_CLASS,
					  NORMAL_PRIORITY_CLASS,
					  NORMAL_PRIORITY_CLASS,
					  NORMAL_PRIORITY_CLASS,
					  NORMAL_PRIORITY_CLASS,
					  NORMAL_PRIORITY_CLASS,
					  HIGH_PRIORITY_CLASS,
					  HIGH_PRIORITY_CLASS,
					  HIGH_PRIORITY_CLASS,
					  HIGH_PRIORITY_CLASS,
					  REALTIME_PRIORITY_CLASS};
		static DWORD VetThreadPriority[14] = {(DWORD) THREAD_PRIORITY_IDLE,
					  (DWORD) THREAD_PRIORITY_LOWEST,
					  (DWORD) THREAD_PRIORITY_BELOW_NORMAL,
					  THREAD_PRIORITY_NORMAL,
					  (DWORD) THREAD_PRIORITY_LOWEST,
					  (DWORD) THREAD_PRIORITY_BELOW_NORMAL,
					  THREAD_PRIORITY_NORMAL,
					  THREAD_PRIORITY_ABOVE_NORMAL,
					  THREAD_PRIORITY_HIGHEST,
					  (DWORD) THREAD_PRIORITY_BELOW_NORMAL,
					  THREAD_PRIORITY_NORMAL,
					  THREAD_PRIORITY_ABOVE_NORMAL,
					  THREAD_PRIORITY_TIME_CRITICAL,
					  (DWORD) THREAD_PRIORITY_IDLE};

		if (IndicePriority <= NONE_PRIORITY || IndicePriority >= OVERFLOW_PRIORITY)
			return false;

		*pClasse = VetClassePriority[IndicePriority - 1];
		*pThread = VetThreadPriority[IndicePriority - 1];

		return true;
	}

	// rimette in locazioni di tomb4 tutti i valori standard per slot id
	void RipristinaIndiciSlot(void)
	{
		__try { throw __func__; } __finally {}
	}

	// ripristina tutti i valori di default per calcolo distanza di world e fog
	void RipristinaWorldFarView(void)
	{
		__try { throw __func__; } __finally {}
	}

	// reimposta valori standard per fog range
	void InizializzaBaseFog(void)
	{
		__try { throw __func__; } __finally {}
	}

	// ripristina settings per livello corrente
	void RipristinaLevelSettings(void)
	{
		if (GlobTomb4.DefSettings.DefVolumetricFX) {
			// assicuarsi che sia attiva fog a livello hardware
			RestoreHardwareFogSempre();
		}
		*GlobTomb4.pAdr->pSetting_Volumetric = GlobTomb4.DefSettings.DefVolumetricFX;
	}

	// a differenza di RestoreFog() questa funziona abilita SEMPRE la fog
	// a livello hardware, mentre l'altra funzione agiva in coppia
	// con DisabilitaFog
	void RestoreHardwareFogSempre(void)
	{
		tomb4::App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, 1);
	}

	void RipristinaDefaultPrintString(void)
	{
		StrPrintString *pTextFormat;

		pTextFormat = &GlobTomb4.PrintString;

		pTextFormat->BlinkSpeed = pTextFormat->DefBlinkSpeed;
		pTextFormat->Colore = pTextFormat->DefColore;
		pTextFormat->Flags = pTextFormat->DefFlags;
		pTextFormat->Posizione = pTextFormat->DefPosition;
		pTextFormat->FlagsMicro = pTextFormat->DefFlagsMicro;
		FlagMicroCaratteri = pTextFormat->DefALLFlagsMicro;
	}

	// all'inizio di livello, e un attimo prima di leggere personalizzazioni
	// nello script.dat con comando Damage=, imposta valori di default
	// per cold room e generiche damage room
	void RipristinaDamageSettings(void)
	{
		StrDamage *pDamage;

		// settings per acqua fredda
		pDamage = &GlobTomb4.DamageColdWater;
		pDamage->Colore = 0xfff924f1; // rosa
		pDamage->Flags = DMG_INDIRECT_BAR + DMG_SLOW_DISAPPEARING + DMG_ALERT_BEEP + DMG_COLD_WATER;
		pDamage->IndiceStringa = -1;
		pDamage->SecondiMorte = 10;
		pDamage->DamValue = 10000;
		pDamage->FlagProgresso = FPD_NONE;
		pDamage->Percentuale = 100;
		pDamage->SecondiRicrescita = 5;
		pDamage->PercentualeBeep = 20;
		CalcolaQuotaTickPerDamage(pDamage);

		// settings per generica room damage
		pDamage = &GlobTomb4.DamageRoom;
		pDamage->Colore = 0xFFF6F923; // giallo
		pDamage->Flags = DMG_INDIRECT_BAR + DMG_SLOW_DISAPPEARING + DMG_ALERT_BEEP;
		pDamage->IndiceStringa = -1;
		pDamage->SecondiMorte = 16;
		pDamage->SecondiRicrescita = 6;
		pDamage->PercentualeBeep = 20;
		pDamage->DamValue = 10000;
		pDamage->FlagProgresso = FPD_NONE;
		pDamage->Percentuale = 100;
		CalcolaQuotaTickPerDamage(pDamage);
	}

	// sulla base di SecondiMorte imposta quote di tick per ridurre barra o vita
	// impsota valore QuotaRiduzione e quotaricrescita
	void CalcolaQuotaTickPerDamage(StrDamage *pRec)
	{
		int QuotaTick;

		// prima calcolare quota ricrescita

		pRec->QuotaRicrescita = 10000 / (FRAME_SECONDO * pRec->SecondiRicrescita);

		if (pRec->QuotaRicrescita == 0)
			pRec->QuotaRicrescita = 1;

		pRec->QuotaRiduzioneRapida = 1000 / (FRAME_SECONDO * 3);

		if (pRec->SecondiMorte <= 0) {
			pRec->QuotaRiduzione = 10000;
			return;
		}

		QuotaTick = 10000 / (FRAME_SECONDO * pRec->SecondiMorte);
		if (QuotaTick > 10000)
			QuotaTick = 10000;
		if (QuotaTick == 0)
			QuotaTick = 1;

		pRec->QuotaRiduzione = QuotaTick;
	}

	// ripristina modifiche per danno di creeture a lara e azzera
	// totEnemy
	// VetDamage
	void RipristinaEnemy(void)
	{
		__try { throw __func__; } __finally {}
	}

	// chiamata quando viene trovato comando script che forza ad usare per tutti i caratteri
	// un certo font di windows
	void ImpostaDefaultWindowsFont(short IDWindowsFont)
	{
		StrBaseWindowsFonts *pBaseFonts;
		int i;
		int Variazione;
		float fVariazione, fAltezza;

		i = GlobTomb4.BaseFonts.VetID[IDWindowsFont];

		if (i == -1) {
			sprintf_s(BufferLog, "ERROR: missing ID (%d) for WindowsFont= command, pointed by SetDefaultWindowsFont= command", IDWindowsFont);
			InviaLog(BufferLog);
			return;
		}

		pBaseFonts = &GlobTomb4.BaseFonts;
		// se era gia' impoostato a true era gia' stato creato il font
		if (pBaseFonts->TestUsaWindowsFont == true)
			return;

		// ora questo codice dovrfebbe essere eseguito una volta sola
		// ora proviamo a vedere se si deve anche modificare AltezzaRigaCaratteri in percentuale
		Variazione = GlobTomb4.BaseFonts.LineSpacing;
		if (Variazione) {
			// questi sono centesimi
			// meglio fare tutto con float
			fVariazione = (float) Variazione;
			fAltezza = (float) *GlobTomb4.pAdr->pRowCharHeight;

			fAltezza = (fAltezza / 100.0f) * fVariazione;

			*GlobTomb4.pAdr->pRowCharHeight = Float2Int(fAltezza);

		}

		pBaseFonts->TestUsaWindowsFont = true;
		pBaseFonts->DefWindowsFont = pBaseFonts->VetFonts[i];

		// ora creare font
		pBaseFonts->DefWindowsFont.hFont = CreaWindowsFontForCB(&pBaseFonts->DefWindowsFont, false);
	}

	// converte da float a int con arrotondamento all'intero piu' vicino
	int Float2Int(float x)
	{
		return lroundf(x);
	}

	// crea il corrispettivo di Cord che era costruito per schermo SchermoRef
	// col nuovo valore di schermo attuale SizeSchermo
	float RapportoFloatSchermo(int SizeSchermo, float SchermoRef, float Cord)
	{
		float Alfa;

		SalvaDimensioneSchermo();

		Alfa = (float) SizeSchermo;
		Alfa = Alfa / SchermoRef;

		Alfa = Alfa * Cord;
		return Alfa;
	}

	// restituisce un numero casuale compreso tra 0 e Massimo-1
	int Casuale(int Massimo)
	{
		int Numero;

		Numero = rand();
		if (Numero >= Massimo) {
			Numero = Numero % Massimo;
		}

		return Numero;
	}

	// inserisce in tutte le locazioni di tomb4 dove appriva costante per
	// slot IndiceSlot con un valore nullo
	void AnnullaIndiceSlot(WORD IndiceSlot)
	{
		__try { throw __func__; } __finally {}
	}

	// questa funzione, usando le varie tabelle di script, trng e tr4
	// dovrebbe consentire tutte le conversioni con indice a plugin di tomb4
	// #define PLUG_FROM_SCRIPT 1   // quelli memorizzati per comandi script customize e parameter
	// #define PLUG_FROM_NGLE 2    // quelli memorizzati nel floor data preso da file .tr4
	int GetPluginIndex(int PluginId, int FromPlug)
	{
		int i;
		StrPluginRec *pRec;
		const char *pSource;

		if (PluginId == 0)
			return 0;

		switch (FromPlug) {
		case PLUG_FROM_SCRIPT:
		default:
			pSource = "script";
			break;
		case PLUG_FROM_NGLE:
			pSource = "ngle/tr4";
			break;
		}

		for (i = 1; i < (int) MyGlobPrivate.DataBase.TotPlugins; i++) {
			pRec = &MyGlobPrivate.DataBase.pVetPlugins[i];

			switch (FromPlug) {
			case PLUG_FROM_SCRIPT:
				if (pRec->PluginIdScript == PluginId)
					return i;
				break;
			case PLUG_FROM_NGLE:
				if (pRec->PluginIdNgle == PluginId)
					return i;
				break;
			}
		}

		// e' strano che non ,l'abbia trovato
		sprintf_s(BufferLog, "ERROR: cannot find the plugin library linked with %s Plugin ID %d", pSource, PluginId);
		InviaLog(BufferLog);

		return -1;
	}

	bool AggiungiImmaginePreload(int NImage)
	{
		int j;
		char NomeImmagine[512];
		bool TestCrypt;
		char NomeCryptImmagine[512];

		if (NImage == -1)
			return false;

		// controllare se era gia' stata caricata
		for (j = 0; j < GlobTomb4.BasePreloadImages.TotPreload; j++) {
			if (GlobTomb4.BasePreloadImages.VetPreload[j].ImageId == NImage)
				break;
		}

		TestCrypt = false;

		if (j == GlobTomb4.BasePreloadImages.TotPreload) {
			// non era ancora stata caricata
			sprintf_s(NomeImmagine, "Pix\\image%d.bmp", NImage);
			if (EsisteFile(NomeImmagine) == false) {
				sprintf_s(NomeImmagine, "image%d.bmp", NImage);
			}

			if (EsisteFile(NomeImmagine)==false) {
				sprintf_s(BufferLog, "ERROR cann't find file: %s", NomeImmagine);
				InviaLog(BufferLog);
				return false;
			}

			GlobTomb4.BasePreloadImages.VetPreload[j].hBitMap = LoadImage(NULL, NomeImmagine, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			GlobTomb4.BasePreloadImages.VetPreload[j].ImageId = NImage;
			GlobTomb4.BasePreloadImages.TotPreload++;

			if (TestCrypt) {
				memset(NomeCryptImmagine, 0, 511);
				memset(NomeImmagine, 0, 511);
			}
		}
		return true;
	}

	// oopia in basestandby il record script standby con indice
	void ImpostaStandBy1(int Indice)
	{
		StrBaseStandBy *pBStand;
		StrScriptStandBy *pStand;

		pBStand = &GlobTomb4.BaseStandBy;
		pStand = &GlobTomb4.BaseStandBy.VetStandBy[Indice];

		pBStand->TestPresente = true;
		pBStand->AudioTrack = pStand->AudioTrack;
		pBStand->IdNow = pStand->IdStandBY;
		pBStand->Distanza = pStand->Distanza;
		pBStand->Flags = pStand->Flags;
		pBStand->IdTriggerGroupEnd = pStand->IdTriggerGroupEnd;
		pBStand->IdTriggerGroupStart = pStand->IdTriggerGroupStart;
		pBStand->IndicePrimaStringa = pStand->FirstText;
		pBStand->LimiteCicli = pStand->LimiteCicli;
		pBStand->OrientSpeed = pStand->OrientSpeed;
		pBStand->TestFlipEffect = false;
		pBStand->TestIniziato = false;
		pBStand->TipoStandby = pStand->TipoStandby;
		pBStand->TotStringhe = pStand->NumTexts;
		pBStand->VerticalOrient = pStand->VerticalOrient;
	}

	// chiamata direttamente da scansione di dati script per livello attuale
	// riceve tutti i comandi script Customize= all'inizio del livello
	// VetArg[] e TotArg sono gli argomenti
	// se il livello e' title sostituisce anche i valori di default
	void EseguiCustomize(int CustTipo, short *VArg, int TotArg)
	{
		static short SlotDoors[16] = {322, 323, 324, 325, 326, 327, 328, 329, 330,
			331, 332, 333, 335, 340, 347, -1};
		static short SlotAnimatings[33] = {427, 428, 429, 430, 431, 432, 433, 434,
			435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448,
			449, 450, 451, 452, 453, 454, 455, 456, 457, 458, -1};
		static short SlotFakeWalls[20] = {117, 118, 119, 120, 121, 139, 149, 150,
			151, 152, 153, 336, 337, 338, 156, 157, 158, 159, 160, -1};
		static short SlotPanels[9] = {472, 473, 474, 475, 476, 477, 478, 479, -1};
		static short SlotVehicles[3] = {32, 31, -1};

		StrBaseCustomize *pCust;
		StrBaseCustomize *pDef;
		StrCustBinocular *pBin;
		bool TestTitle;
		StrScriptImage TempImage;
		StrBaseImgBackGround *pBack;
		StrScriptImage *pSImage;
		int j;
		int i;
		StrRollBoatScript *pRollBoat;
		WORD ValWord;
		StrDatiXRain *pRain;
		StrCustFlare *pFlare;
		StrBaseAnimMorte *pMorte;
		StrDartCustomize *pDart;
		DWORD Valore;
		WORD Flags;
		WORD Slot;
		StrBaseHarpoon *pHarp;
		int n;
		StrBarraCust *pBar;
		StrCustLightItems *pLight;
		StrCustLightItems *pLightDef;
		short VetArg[256];

		for (i = 0; i < 256; i++)
			VetArg[i] = -1;

		for (i = 0; i < TotArg; i++) {
			VetArg[i] = VArg[i];
		}

		pCust = GlobTomb4.pBaseCustomize;
		pDef = GlobTomb4.pBaseCustomizeDefault;

		if (*GlobTomb4.pAdr->pLevelNow == 0)
			TestTitle = true;
		else
			TestTitle = false;

		switch (CustTipo) {
		case CUST_DISABLE_SCREAMING_HEAD:
			pCust->TestDisabilitaDoppiaTesta = true;
			if (TestTitle)
				pDef->TestDisabilitaDoppiaTesta = true;
			break;
		case CUST_SET_SECRET_NUMBER:
			pCust->SecretsAmount = VetArg[0];
			if (TestTitle)
				pDef->SecretsAmount = VetArg[0];
			break;
		case CUST_SET_JEEP_KEY_SLOT:
			pCust->SlotChiaveJeep = VetArg[0];
			if (TestTitle)
				pDef->SlotChiaveJeep = VetArg[0];
			break;
		case CUST_SET_CREDITS_LEVEL:
			pCust->CreditsLevel = VetArg[0];
			if (TestTitle)
				pDef->CreditsLevel = VetArg[0];
			break;
		case CUST_WATERFALL_SPEED:
			pCust->WaterfallSpeed = (char) VetArg[0];
			if (TestTitle)
				pDef->WaterfallSpeed = (char) VetArg[0];
			break;
		case CUST_TITLE_FMV:
			pCust->TitleFmv = VetArg[0];
			if (VetArg[1] == 1)
				pCust->TitleTestMultiply = true;

			if (TestTitle) {
				pDef->TitleFmv = VetArg[0];
				pDef->TitleTestMultiply = pCust->TitleTestMultiply;
			}
			break;
		case CUST_DISABLE_PUSH_AWAY_ANIMATION:
			pCust->TestDisablePushAway = true;
			if (TestTitle) {
				pDef->TestDisablePushAway = true;
			}
			break;
		case CUST_BINOCULARS:
			// dati customize per binocolo
			//  Customize=CUST_BINOCULARS, FLAGS (BINF_...), Parameter, CompassImage,
			//         CompassRectAndFlags, SextantImage, SextantRectAndFlags,
			//                LightnessRectAndFlags, DistanceRectAndFlags, LightSwitchRectAndFlags
			pBin = &pCust->CustBinoculars;

			pBin->TestPresente = true;
			i = 0;

			pBin->Flags = VetArg[i++];
			pBin->Parameter = VetArg[i++];
			pBin->CompassImage = VetArg[i++];
			pBin->CompassRect = VetArg[i++];
			pBin->SextantImage = VetArg[i++];
			pBin->SextantRect = VetArg[i++];
			pBin->LightnessRect = VetArg[i++];
			pBin->ZoomRect = VetArg[i++];
			pBin->LighSwitchRect = VetArg[i++];
			pBin->FontId = VetArg[i++];

			if (TestTitle) {
				pDef->CustBinoculars = *pBin;
			}
			// allocare immagini richieste
			if (pBin->Flags & BINF_COMPASS) {
				if (pBin->CompassRect & BINT_STRIP)
					AggiungiImmaginePreload(pBin->CompassImage);
			}

			if (pBin->Flags & BINF_SEXTANT) {
				if (pBin->SextantRect & BINT_STRIP)
					AggiungiImmaginePreload(pBin->SextantImage);
			}

			break;

		case CUST_BACKGROUND:
			// BackGroundType (BKGDT_...), Flags (BKGDF_...), Parameter, ImageId
			n = VetArg[0];  // type of background

			// localizzare image asscoiata, a meno che non ci sia flag 	BKGDF_KEEP_GAME_SCREEN
			Flags = VetArg[1];
			if (Flags == SCRIPT_IGNORE)
				Flags = 0;

			if ((Flags & BKGDF_KEEP_GAME_SCREEN) == 0 || (Flags & BKGDF_SEMI_TRANSPARENT) != 0) {
				i = VetArg[3];
				if (i == -1) {
					InviaLog("ERROR missing image id in CUSTOMIZE=CUST_BACKGROUND command");

					break;
				}
				i = GlobTomb4.pBaseScriptImages->VetID[i];
				if (i == -1) {
					sprintf_s(BufferLog, "ERROR cann't locate image with id %d in CUSTOMIZE=CUST_BACKGROUND command", VetArg[0]);
					InviaLog(BufferLog);
					break;
				}
				pSImage = &GlobTomb4.pBaseScriptImages->VetImages[i];
			} else {
				pSImage = &TempImage;
				pSImage->AudioTrack = -1;
				pSImage->Flags = 0;
				pSImage->NumeroImage = -1;
			}

			switch (n) {
			case BKGDT_INVENTORY:

				GlobTomb4.BaseImgMonoScreen.TestBackGround = true;
				if (pSImage->Flags & IF_PLAY_AUDIO_TRACK) {
					GlobTomb4.BaseImgMonoScreen.Cd_Track = pSImage->AudioTrack;
					if (pSImage->Flags & IF_LOOP_AUDIO_TRACK) {
						GlobTomb4.BaseImgMonoScreen.TestLoop = true;
					} else {
						GlobTomb4.BaseImgMonoScreen.TestLoop = false;
					}

				} else {
					GlobTomb4.BaseImgMonoScreen.Cd_Track = -1;
				}
				if (pSImage->Flags & IF_TRANSPARENCE) {
					GlobTomb4.BaseImgMonoScreen.TestTrasparente = true;
				} else {
					GlobTomb4.BaseImgMonoScreen.TestTrasparente = false;
				}
				GlobTomb4.BaseImgMonoScreen.Flags = VetArg[1];
				if (GlobTomb4.BaseImgMonoScreen.Flags == SCRIPT_IGNORE) {
					GlobTomb4.BaseImgMonoScreen.Flags = 0;
				}
				GlobTomb4.BaseImgMonoScreen.Parameter = VetArg[2];
				if (GlobTomb4.BaseImgMonoScreen.Parameter == -1) {
					GlobTomb4.BaseImgMonoScreen.Parameter = 0;
				}

				GlobTomb4.BaseImgMonoScreen.TestImageMonoscreen = false;
				GlobTomb4.BaseImgMonoScreen.NumeroImage = pSImage->NumeroImage;
				break;
			case BKGDT_LOADING_LEVEL:
			case BKGDT_TITLE:
			case BKGDT_BINOCULAR:
			case BKGDT_LASER_SIGHT:

				switch (n) {
					case BKGDT_LOADING_LEVEL:
					default:
						InviaLog("Found BKGDT_LOADING_LEVEL");
						pBack = &GlobTomb4.BaseImgLoadingLevel;
						if (pBack->TestAllocatedImage == true && ((pBack->Flags & BKGDF_KEEP_GAME_SCREEN) == 0 || (pBack->Flags & BKGDF_SEMI_TRANSPARENT) != 0)) {
							// era gia' allocato
							sprintf_s(BufferLog, "There was an already allocated image for loading level (image%d.bmp)", pBack->ImageNumber);
							InviaLog(BufferLog);
							if (pBack->ImageNumber != pSImage->NumeroImage) {
								InviaLog("Image was different than that we have to use");
								// liberare immagine precedente
								LiberaImmagine(&GlobTomb4.BaseImages.ImageLoadLevel);
								pBack->TestAllocatedImage = false;
								pBack->ImageNumber = 0;
							}
						}
						break;
					case BKGDT_TITLE:
						InviaLog("Found BKGDT_TITLE");
						pBack = &GlobTomb4.BaseImgTitle;
						break;
					case BKGDT_BINOCULAR:
						InviaLog("Found BKGDT_BINOCULAR");
						pBack = &GlobTomb4.BaseImgBinocular;
						break;
					case BKGDT_LASER_SIGHT:
						InviaLog("Found BKGDT_LASER_SIGHT");
						pBack = &GlobTomb4.BaseImgLaserSight;
						break;
				}

				pBack->Flags = VetArg[1];
				if (pBack->Flags == SCRIPT_IGNORE)
					pBack->Flags = 0;

				pBack->Parameter = VetArg[2];
				if (pBack->Parameter == -1)
					pBack->Parameter = 0;

				pBack->ImageNumber = pSImage->NumeroImage;

				pBack->TestEnabled = true;

				if (pSImage->Flags & IF_TRANSPARENCE) {
					pBack->TestTransparent = true;
				} else {
					pBack->TestTransparent = false;
				}

				break;

			default:
				sprintf_s(BufferLog, "ERROR: unknown background type (%d) in Customize=CUST_BACKGROUND command", n);
				InviaLog(BufferLog);
				break;
			}
			break;

		case CUST_FIX_BUGS:
			pCust->BugsToFix |= VetArg[0];
			if (TestTitle) {
				pDef->BugsToFix |= VetArg[0];
			}
			break;

		case CUST_SHATTER_SPECIFIC:
			pCust->BaseShatterSpecific.TotSpecific = TotArg;
			for (i = 0; i < TotArg; i++) {
				pCust->BaseShatterSpecific.VetSpecific[i] = VetArg[i];
			}
			if (TestTitle) {
				pDef->BaseShatterSpecific.TotSpecific = TotArg;
				for (i = 0; i < TotArg; i++) {
					pDef->BaseShatterSpecific.VetSpecific[i] = VetArg[i];
				}
			}
			break;
		case CUST_SLOT_FLAGS:
			i = pCust->BaseSlotFlags.TotSlotFlags;

			pCust->BaseSlotFlags.VetSlotFlags[i].Slot = VetArg[0];
			pCust->BaseSlotFlags.VetSlotFlags[i].Flags = VetArg[1];
			pCust->BaseSlotFlags.TotSlotFlags++;

			if (TestTitle) {
				pDef->BaseSlotFlags.VetSlotFlags[i].Slot = VetArg[0];
				pDef->BaseSlotFlags.VetSlotFlags[i].Flags = VetArg[1];
				pDef->BaseSlotFlags.TotSlotFlags++;
			}
			break;

		case CUST_SFX:
			i = VetArg[0];
			if (i < 0)
				break;
			pCust->VetCustSFX[i] = VetArg[1];
			if (TestTitle)
				pDef->VetCustSFX[i] = VetArg[1];
			break;

		case CUST_ROLLING_BOAT:
			// aggiungere i dati di questo rollboat in zona per script
			// poi solo prima di iniziare giocfolivello trovare gli item
			// corrispondenti.
			i = pCust->BaseRollScript.TotRollBoatScript;
			if (i >= MAX_ROLL_BOAT_SCRIPT)
				break;
			pRollBoat = &pCust->BaseRollScript.VetRollBoatsScript[i];

			pRollBoat->Slot = VetArg[0];
			pRollBoat->Flags = VetArg[1];
			if (VetArg[1] == -1)
				pRollBoat->Flags = 0;
			pRollBoat->SpeedSwing = VetArg[2];
			pRollBoat->SpeedPitch = VetArg[3];
			pRollBoat->SoundSfx = VetArg[4];

			pCust->BaseRollScript.TotRollBoatScript++;
			break;

		case CUST_DISABLE_FORCING_ANIM_96:
			pCust->TestDisableAnim96 = true;
			if (TestTitle)
				pDef->TestDisableAnim96 = true;
			break;
		case CUST_SET_TEXT_COLOR:
			i = VetArg[0];
			if (i >= 0 && i < TT_MAX_TEXT_TYPES) {
				pCust->VetTTColors[i] = (BYTE) VetArg[1];
				if (TestTitle)
					pDef->VetTTColors[i] = (BYTE) VetArg[1];
			}
			break;
		case CUST_SHATTER_RANGE:
			// imposta numeri slot per shatter
			Slot = pDef->ShatterInizio;
			if (TotArg >= 1 && VetArg[0] != -1)
				Slot = (WORD) VetArg[0];

			pCust->ShatterInizio = Slot;
			if (TestTitle)
				pDef->ShatterInizio = Slot;

			Slot = pDef->ShatterFine;
			if (TotArg >= 2 && VetArg[1] != -1)
				Slot = (WORD) VetArg[1];

			pCust->ShatterFine = Slot;
			if (TestTitle)
				pDef->ShatterFine = Slot;
			break;
		case CUST_LOOK_TRASPARENT:
			if (VetArg[0] == 0)
				pCust->TestNoTransparencyLara = true;
			if (TestTitle)
				pDef->TestNoTransparencyLara = pCust->TestNoTransparencyLara;
			break;

		case CUST_SET_OLD_CD_TRIGGER:
			if (VetArg[0] == 1)
				pCust->TestOldCDTrigger = true;
			if (TestTitle)
				pDef->TestOldCDTrigger = pCust->TestOldCDTrigger;
			break;
		case CUST_ESCAPE_FLY_CAMERA:
			if (VetArg[0] == 1)
				pCust->TestEscapeFlyCamera = true;
			if (VetArg[1] != -1)
				pCust->TastoEsciFlyCamera = VetArg[1];

			if (TestTitle) {
				pDef->TestEscapeFlyCamera = pCust->TestEscapeFlyCamera;
				pDef->TastoEsciFlyCamera = pCust->TastoEsciFlyCamera;
			}
			break;
		case CUST_PAUSE_FLY_CAMERA:
			if (VetArg[0] == 1)
				pCust->TestPauseFlyCamera = true;
			if (VetArg[1] != -1)
				pCust->TastoPauseFlyCamera = VetArg[1];

			if (TestTitle) {
				pDef->TestPauseFlyCamera = pCust->TestPauseFlyCamera;
				pDef->TastoPauseFlyCamera = pCust->TastoPauseFlyCamera;
			}
			break;
		case CUST_CAMERA:
			if (VetArg[0] != -1)
				pCust->CameraCust.Flags = VetArg[0];
			if (VetArg[1] != -1)
				pCust->CameraCust.ChaseDistance = VetArg[1];
			if (VetArg[2] != -1)
				pCust->CameraCust.ChaseHeight = VetArg[2];
			if (VetArg[3] != -1)
				pCust->CameraCust.ChaseHOrient = VetArg[3];
			if (VetArg[4] != -1)
				pCust->CameraCust.CombatDistance = VetArg[4];
			if (VetArg[5] != -1)
				pCust->CameraCust.CombatHeight = VetArg[5];
			if (VetArg[6] != -1)
				pCust->CameraCust.LookDistance = VetArg[6];
			if (VetArg[7] != -1)
				pCust->CameraCust.LookHeight = VetArg[7];
			if (VetArg[8] != -1)
				pCust->CameraCust.Speed = VetArg[8];

			if (TestTitle)
				pDef->CameraCust = pCust->CameraCust;
			break;

		case CUST_KEEP_DEAD_ENEMIES:
			if (VetArg[0] == 1)
				pCust->TestKeepNemiciMorti = true;
			if (TestTitle)
				pDef->TestKeepNemiciMorti = pCust->TestKeepNemiciMorti;
			break;

		case CUST_CD_SINGLE_PLAYBACK:
			if (VetArg[0] != -1)
				pCust->TipoCDM = VetArg[0];
			if (TestTitle)
				pDef->TipoCDM = pCust->TipoCDM;
			break;
		case CUST_BAR:
			if (VetArg[0] == -1)
				break;

			i = VetArg[0];
			pBar = &pCust->VetBar[i];
			// flagbar
			if (VetArg[1] != -1) {
				pBar->Flags = VetArg[1];
			}

			pBar->OrgX = VetArg[2];   // orgx
			pBar->OrgY = VetArg[3];   // orgy

			if (VetArg[4] != -1) {
				pBar->SizeX = VetArg[4];
			}

			if (VetArg[5] != -1) {
				pBar->SizeY = (BYTE) VetArg[5];
			}

			// idcolor1
			if (VetArg[6] != -1) {
				pBar->Color1 = TrovaColoreRGB(VetArg[6]);
			} else {
				pBar->Color1 = GlobTomb4.VetBarDefault[i].DefColor1;
			}
			// idcolor2
			if (VetArg[7] != -1) {
				pBar->Color2 = TrovaColoreRGB(VetArg[7]);
			} else {
				pBar->Color2 = GlobTomb4.VetBarDefault[i].DefColor2;
			}

			pBar->Extra = VetArg[8];
			if (pBar->Flags & FBAR_SOUND_BAR_ANIM) {
				if (pBar->Extra == -1) {
					pBar->ExtraLong = 0xFF808080;
				} else {
					pBar->ExtraLong = TrovaColoreRGB(pBar->Extra);
				}
			}

			if (pBar->Flags & FBAR_USED_FOR_BOAT_FUEL) {
				pBar->ExtraLong = (WORD) pBar->Extra;
			}

			if (TestTitle) {
				// copiare tutto
				memcpy(&pDef->VetBar[i], pBar, sizeof(StrBarraCust));
			}
			break;

		case CUST_ADD_DEATH_ANIMATION:
			// nota a differenza di altri cust questo non usa title
			// come default
			pMorte = &GlobTomb4.pBaseCustomize->BaseAddAnimMorte;

			n = pMorte->TotCustAnimMorte;

			if (n >= MAX_ANIM_MORTE) {
				sprintf_s(BufferLog, "ERROR: too much adding of new death animations in current level section. Max = %d", MAX_ANIM_MORTE);
				InviaLog(BufferLog);
				break;
			}
			if (VetArg[0] == -1)
				break;
			pMorte->VetAnimMorte[n].Slot = VetArg[0];
			if (VetArg[1] == -1)
				break;
			pMorte->VetAnimMorte[n].AnimIndex = VetArg[1];

			pMorte->TotCustAnimMorte++;

			break;
		case CUST_KEEP_LARA_HP:
			i = pCust->BaseHpLara.TotTargetLevels;
			pCust->BaseHpLara.VetTargetLevels[i] = VetArg[0];
			pCust->BaseHpLara.TotTargetLevels++;
			if (TestTitle) {
				i = pDef->BaseHpLara.TotTargetLevels;
				pDef->BaseHpLara.VetTargetLevels[i] = VetArg[0];
				pDef->BaseHpLara.TotTargetLevels++;
			}
			break;

		case CUST_DISABLE_MISSING_SOUNDS:
			// se e' presente allora disabiitare
			pCust->TestDisableMissingSounds = true;
			if (TestTitle)
				pDef->TestDisableMissingSounds = pCust->TestDisableMissingSounds;
			break;
		case CUST_FLARE:
			pFlare = &pCust->BaseFlare;

			if (VetArg[0] != -1)
				pFlare->Flags = VetArg[0];
			if (VetArg[1] != -1) {
				pFlare->Durata = VetArg[1] * FRAME_SECONDO;
				// aggiornare anche gli altri valori
				pFlare->Valore810 = pFlare->Durata - 90;
				pFlare->Valore876 = pFlare->Durata - 24;
			}
			if (VetArg[2] != -1)
				pFlare->Rosso = VetArg[2];
			if (VetArg[3] != -1)
				pFlare->Verde = VetArg[3];
			if (VetArg[4] != -1)
				pFlare->Blu = VetArg[4];
			if (VetArg[5] != -1)
				pFlare->Intensita = VetArg[5];
			if (TestTitle)
				pDef->BaseFlare = *pFlare;
			break;

		case CUST_INNER_SCREENSHOT:
			// se e' presente allora abilitare aggiunta di screenshot

			pCust->ScreenShotInner.TestAddInnerShot = true;
			if (VetArg[0] != -1) {
				pCust->ScreenShotInner.FlagQSF = VetArg[0];

			} else {
				pCust->ScreenShotInner.FlagQSF = 1; // 320x240 256 colori
			}

			if (TestTitle)
				pDef->ScreenShotInner = pCust->ScreenShotInner;
			break;

		case CUST_TEXT_ON_FLY_SCREEN:
			if (VetArg[0] == 1)
				pCust->TestPrintOnFlyby = true;
			if (TestTitle)
				pDef->TestPrintOnFlyby = pCust->TestPrintOnFlyby;
			break;
		case CUST_FMV_CUTSCENE:
			if (VetArg[0] != -1)
				pCust->FlagsFMV = VetArg[0];
			if (TestTitle)
				pDef->FlagsFMV = pCust->FlagsFMV;
			break;

		case CUST_NO_TIME_IN_SAVELIST:
			if (VetArg[0] == 1)
				pCust->TestNoTimeInSaveList = true;
			if (TestTitle)
				pDef->TestNoTimeInSaveList = pCust->TestNoTimeInSaveList;
			break;
		case CUST_SAVE_LOCUST:
			if (VetArg[0] == 1)
				pCust->TestSaveLocust = true;
			if (TestTitle)
				pDef->TestSaveLocust = pCust->TestSaveLocust;

			break;
		case CUST_TR5_UNDERWATER_COLLISIONS:
			pCust->TestTr5Collisions = true;
			if (TestTitle)
				pDef->TestTr5Collisions = true;
			break;
		case CUST_DARTS:
			i = pCust->BaseDartCustomization.TotCust;
			if (i >= MAX_DART_CUST) {
				sprintf_s(BufferLog, "ERROR: too much Customize=CUST script command in same level section (max=%d)", MAX_DART_CUST);
				InviaLog(BufferLog);
				break;
			}
			pDart = &pCust->BaseDartCustomization.VetCust[i];
			i = 0;
			pDart->IdCustomize = VetArg[i++];
			pDart->Flags = VetArg[i++];
			if (pDart->Flags == SCRIPT_IGNORE)
				pDart->Flags = 0;
			pDart->IdAddEffect = VetArg[i++];
			pDart->Speed = VetArg[i++];
			if (pDart->Speed == -1)
				pDart->Speed = 0x100;
			pDart->EmittingTimer = VetArg[i++];
			if (pDart->EmittingTimer == -1)
				pDart->EmittingTimer = 0x18;
			// rgb colore 1
			pDart->ColorMain = 0xff783c14;
			pDart->ColorSecondary = 0xff000000;

			n = VetArg[i++];
			if (n != -1) {
				Valore = TrovaColoreRGB(n);
				pDart->ColorMain = Valore | 0xFF000000;
			}
			// colore secondario
			n = VetArg[i++];
			if (n != -1) {
				Valore = TrovaColoreRGB(n);
				pDart->ColorSecondary = Valore | 0xFF000000;
			}

			pDart->IdTriggerGroup = VetArg[i];

			pCust->BaseDartCustomization.TotCust++;

			if (TestTitle) {
				// copiare questo record anche in default
				n = pDef->BaseDartCustomization.TotCust;
				if (n >= MAX_DART_CUST) {
					InviaLog("ERROR: Too much Customize=CUST_DARTS commands in [Title] section");
				} else {
					pDef->BaseDartCustomization.VetCust[n] = *pDart;
					pDef->BaseDartCustomization.TotCust++;
				}
			}

			break;

		case CUST_SCREENSHOT_CAPTURE:
			pCust->BaseCatturaShot.Secondi = VetArg[0];
			pCust->BaseCatturaShot.FrameGap = VetArg[1];
			pCust->BaseCatturaShot.QaulitaImage = VetArg[2];
			pCust->BaseCatturaShot.TestInCorso = false;
			if (TestTitle) {
				memcpy(&pDef->BaseCatturaShot, &pCust->BaseCatturaShot, sizeof(StrCatturaShot));
			}
			break;

		case CUST_SET_STILL_COLLISION:
			pCust->BaseStillCollision.Flags = VetArg[0];
			pCust->BaseStillCollision.Flags |= COLL_ENABLED;

			if (VetArg[1] != -1)
				pCust->BaseStillCollision.LowerHeight = VetArg[1];

			// ora aggungere i moveable dei flag
			Flags = pCust->BaseStillCollision.Flags;

			if (Flags & COLL_DOORS) {
				i = 0;
				while (SlotDoors[i] != -1) {
					j = SlotDoors[i];
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 1;
					i++;
				}
			}

			if (Flags & COLL_ANIMATINGS) {
				i = 0;
				while (SlotAnimatings[i] != -1) {
					j = SlotAnimatings[i];
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 1;
					i++;
				}
			}

			if (Flags & COLL_PANELS) {
				i = 0;
				while (SlotPanels[i] != -1) {
					j = SlotPanels[i];
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 1;
					i++;
				}
			}

			if (Flags & COLL_VEHICLES) {
				i = 0;
				while (SlotVehicles[i] != -1) {
					j = SlotVehicles[i];
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 1;
					i++;
				}
			}

			if (Flags & COLL_FAKE_WALLS) {
				i = 0;
				while (SlotFakeWalls[i] != -1) {
					j = SlotFakeWalls[i];
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 1;
					i++;
				}
			}
			// ora calcolare gli eventuali extra item.
			for (i = 2; i < TotArg; i++) {
				if (VetArg[i] == -1)
					break;
				j = VetArg[i];
				// se il numero e' negativo togliere questo slot
				if (j < 0) {
					j = -j;
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 0;

				} else {
					// aggiungerlo
					pCust->BaseStillCollision.VetSlotStillCollisions[j] = 1;
				}
			}
			if (TestTitle) {
				memcpy(&pDef->BaseStillCollision, &pCust->BaseStillCollision, sizeof(StrStillCollision));
			}
			break;

		case CUST_HARPOON:
			// HarpoonFlags (HRP_...), TopBorder,
			//			DistanceFromCam, Orient_X, Orient_Y, Orient_Z
			pHarp = &pCust->BaseHarpoon;

			pHarp->TestArpione = true;
			// flags
			if (VetArg[0] != -1)
				pHarp->ArpioneFlags = VetArg[0];
			// topborder
			if (VetArg[1] != -1)
				pHarp->TopY = VetArg[1];
			// Distance
			if (VetArg[2] != -1)
				pHarp->Distance = VetArg[2];
			// OrientX
			if (VetArg[3] != -1)
				pHarp->OrientX = VetArg[3];
			// orienty
			if (VetArg[4] != -1)
				pHarp->OrientY = VetArg[4];
			// orientz
			if (VetArg[5] != -1)
				pHarp->OrientZ = VetArg[5];
			// hspeed
			pHarp->HSpeed = VetArg[6];
			// gravity
			if (VetArg[7] != -1)
				pHarp->Gravity = VetArg[7];

			if (TestTitle) {
				memcpy(&pDef->BaseHarpoon, pHarp, sizeof(StrBaseHarpoon));
			}
			break;

		case CUST_LIGHT_OBJECT:
			if (VetArg[0] == -1)
				break;
			Slot = VetArg[0];
			switch (Slot) {
			case 394:
				// AMBER_LIGHT
				pLight = &pCust->AmberLight;
				pLightDef = &pDef->AmberLight;
				break;
			case 395:
				// WHITE_LIGHT
				pLight = &pCust->WhiteLight;
				pLightDef = &pDef->WhiteLight;
				break;
			case 396:
				// BLINKING_LIGHT
				pLight = &pCust->BlinkingLight;
				pLightDef = &pDef->BlinkingLight;
				break;
			default:
				InviaLog("Unknown light slot in  Customize=CUST_LIGHT command");

				return;
			}

			if (VetArg[1] != -1)
				pLight->Rosso = VetArg[1];
			if (VetArg[2] != -1)
				pLight->Verde = VetArg[2];
			if (VetArg[3] != -1)
				pLight->Blue = VetArg[3];
			if (VetArg[4] != -1)
				pLight->Intensita = VetArg[4];
			if (VetArg[5] != -1)
				pLight->Time = VetArg[5];

			if (TestTitle)
				*pLightDef = *pLight;
			break;

		case CUST_FIX_WATER_FOG_BUG:
			if (VetArg[0] != -1) {
				if (VetArg[0] == 1) {
					pCust->TestFixWaterFogBug = true;
				} else {
					pCust->TestFixWaterFogBug = false;
				}

				if (TestTitle) {
					pDef->TestFixWaterFogBug = pCust->TestFixWaterFogBug;
				}
			}

			break;

		case CUST_PARALLEL_BARS:
			if (VetArg[0] != -1)
				pCust->ParallelBarFlags = VetArg[0];
			if (VetArg[1] != -1)
				pCust->ParalledSpeedSlide = VetArg[1];

			if (VetArg[2] != -1)
				pCust->ParallelMaxTurns = VetArg[2];

			if (TestTitle) {
				pDef->ParallelBarFlags = pCust->ParallelBarFlags;
				pDef->ParalledSpeedSlide = pCust->ParalledSpeedSlide;
				pDef->ParallelMaxTurns = pCust->ParallelMaxTurns;
			}
			break;

		case CUST_HAIR_TYPE:
			if (VetArg[0] != -1) {
				pCust->HairType = VetArg[0];

				if (TestTitle)
					pDef->HairType = pCust->HairType;
			}
			break;

		case CUST_SPEED_MOVING:

			pCust->SpeedMoving = VetArg[0];
			if (TestTitle)
				pDef->SpeedMoving = VetArg[0];
			break;

		case CUST_ROLLINGBALL_PUSHING:

			// Distance
			if (VetArg[0] == -1) {
				pCust->RollingBallPush.Distance = pDef->RollingBallPush.Distance;
			} else {
				pCust->RollingBallPush.Distance = VetArg[0];

			}
			if (VetArg[1] == -1) {
				pCust->RollingBallPush.Animation = pDef->RollingBallPush.Animation;
			} else {
				pCust->RollingBallPush.Animation = VetArg[1];

			}
			if (VetArg[2] == -1) {
				pCust->RollingBallPush.AnimFallito = pDef->RollingBallPush.AnimFallito;
			} else {
				pCust->RollingBallPush.AnimFallito = VetArg[2];

			}
			if (VetArg[3] == -1) {
				pCust->RollingBallPush.FrameStartPush = pDef->RollingBallPush.FrameStartPush;
			} else {
				pCust->RollingBallPush.FrameStartPush = VetArg[3];

			}
			if (VetArg[4] == -1) {
				pCust->RollingBallPush.FrameStartActivation = pDef->RollingBallPush.FrameStartActivation;
			} else {
				pCust->RollingBallPush.FrameStartActivation = VetArg[4];

			}

			if (VetArg[5] == -1) {
				pCust->RollingBallPush.FrameInvulnerabile = pDef->RollingBallPush.FrameInvulnerabile;
			} else {
				pCust->RollingBallPush.FrameInvulnerabile = VetArg[5];

			}
			if (VetArg[6] != -1) {
				pCust->RollingBallPush.SpeedPushing = VetArg[6];
			}
			if (TestTitle == true) {
				// usarli come default
				memcpy(&pDef->RollingBallPush, &pCust->RollingBallPush, sizeof(StrRollingPush));
			}
			break;
		case CUST_NEW_SOUND_ENGINE:

			if (VetArg[0] != -1) {
				GlobTomb4.pBaseCustomize->BassDll.Flags = VetArg[0];
			}
			if (VetArg[1] != -1) {
				// indice estensione

				GlobTomb4.pBaseCustomize->BassDll.TipoEstensione = VetArg[1];
			}
			if (VetArg[2] != -1) {
				// fade out lungo
				GlobTomb4.pBaseCustomize->BassDll.TimeFadeOut = VetArg[2];
			}
			if (VetArg[3] != -1) {
				// fade out corto
				GlobTomb4.pBaseCustomize->BassDll.TimeFadeOutCorto = VetArg[3];
			}
			if (TestTitle == true) {
				memcpy(&GlobTomb4.pBaseCustomizeDefault->BassDll, &GlobTomb4.pBaseCustomize->BassDll, sizeof(StrBassDll));
			}
			break;

		case CUST_AMMO:
			// formato
			 // Customize=CUST_AMMO,
			// SlotOfAmmo, Ammo flags (AMMO_....),
			// Damage, ShotsForBox, ShotsWithWeapon, Extra, IdTriggerGroupWhenHitEnemy, DamageForExplosion, Speed, Gravity, IdAddEffectToAmmo, IdTriggerGroupAtEnd

			InitAmmoCust(VetArg[0], &VetArg[1], TestTitle);
			break;
		case CUST_WEAPON:
			InitWeaponCust(VetArg[0], &VetArg[1], TestTitle);
			break;
		case CUST_SHOW_AMMO_COUNTER:
			pCust->ShowAmmoCounter.TestShowAmmoCounter = true;

			ScansioneTextFormat(&pCust->ShowAmmoCounter.TexAmmoCounter, (WORD *) &VetArg[0]);

			if (VetArg[4] != -1) {
				pCust->ShowAmmoCounter.Flags = VetArg[4];
			}
			if (TestTitle) {
				memcpy(&pDef->ShowAmmoCounter, &pCust->ShowAmmoCounter, sizeof(StrShowAmmoCounter));
			}
			break;
		case CUST_STATIC_TRANSPARENCY:
			if (VetArg[0] != -1) {
				pCust->TrasparenzaGlass = (255 * VetArg[0]) / 100;
			}
			if (VetArg[1] != -1) {
				pCust->TrasparenzaIce = (255 * VetArg[1]) / 100;
			}
			if (TestTitle) {
				pDef->TrasparenzaGlass = pCust->TrasparenzaGlass;
				pDef->TrasparenzaIce = pCust->TrasparenzaIce;
			}
			break;
		case CUST_SET_STATIC_DAMAGE:
			if (VetArg[0] != -1)
				pCust->DamageStatic = VetArg[0];
			if (VetArg[1] != -1)
				pCust->PoisonStatic = VetArg[1];

			if (TestTitle) {
				pDef->DamageStatic = pCust->DamageStatic;
				pDef->PoisonStatic = pCust->PoisonStatic;
			}
			break;

		case CUST_BIKE_VS_ENEMIES:
			// per ogni valore controllare se lo slot era gia' presente
			// se si, allora sostituire quel valore
			for (i = 0; i < TotArg; i++) {
				ValWord = VetArg[i] & HIT_MASK_SLOT;
				// vedere se era gia' definito
				for (j = 0; j < pCust->BaseSlotCollideVehicles.TotSlotCollide; j++) {
					if ((pCust->BaseSlotCollideVehicles.VetSlotCollide[j] & HIT_MASK_SLOT) == ValWord)
						break;
				}

				if (j == pCust->BaseSlotCollideVehicles.TotSlotCollide) {
					pCust->BaseSlotCollideVehicles.TotSlotCollide++;
				}

				pCust->BaseSlotCollideVehicles.VetSlotCollide[j] = VetArg[i];
			}

			if (TestTitle) {
				for (i = 0; i < pCust->BaseSlotCollideVehicles.TotSlotCollide; i++) {
					pDef->BaseSlotCollideVehicles.VetSlotCollide[i] = pCust->BaseSlotCollideVehicles.VetSlotCollide[i];
				}
				pDef->BaseSlotCollideVehicles.TotSlotCollide = pCust->BaseSlotCollideVehicles.TotSlotCollide;
			}
			break;

		case CUST_SET_INV_ITEM:
			i = pCust->BaseInvItems.TotInvItems;

			pCust->BaseInvItems.VetInvItems[i] = VetArg[0];
			pCust->BaseInvItems.TotInvItems++;

			if (TestTitle) {
				// aggiungerlo in default, sperando che non sia gia' presente
				for (i = 0; i < pDef->BaseInvItems.TotInvItems; i++) {
					if (pDef->BaseInvItems.VetInvItems[i] == VetArg[0])
						break;
				}
				if (i == pDef->BaseInvItems.TotInvItems) {
					pDef->BaseInvItems.VetInvItems[i] = VetArg[0];
					pDef->BaseInvItems.TotInvItems++;
				}
			}
			break;

		case CUST_RAIN:
			pRain = &GlobTomb4.DatiRain;
			// flags
			if (VetArg[0] != -1)
				pRain->Flags = VetArg[0];
			// DropSize
			if (VetArg[1] != -1)
				pRain->Rain_Float_2 = VetArg[1];
			// SPlashAmount
			if (VetArg[2] != -1)
				pRain->SplashRain = VetArg[2];
			// MaxRain
			if (VetArg[3] != -1)
				pRain->Max_Rain = VetArg[3];
			// MinRain
			if (VetArg[4] != -1)
				pRain->Min_Rain = VetArg[4];
			// float1
			if (VetArg[5] != -1)
				pRain->Rain_Float_1 = VetArg[5];
			// float4
			if (VetArg[6] != -1)
				pRain->Rain_Float_4 = VetArg[6];
			// float8
			if (VetArg[7] != -1)
				pRain->Rain_Float_8 = VetArg[7];
			// float16
			if (VetArg[8] != -1)
				pRain->Rain_Float_16 = VetArg[8];
			// sound sfx o altro
			if (pRain->Flags & FR_PLAY_SFX) {
				pRain->SoundSFX = VetArg[9];
			}

			break;
		default:

			sprintf_s(BufferLog, "WARNING: unknown cust type %d", CustTipo);
			InviaLog(BufferLog);
			break;
		}
	}

	DWORD TrovaColoreRGB(int IdColor)
	{
		int i;

		i = GlobTomb4.BaseColoriRGB.VetID[IdColor];
		if (i == -1) {
			sprintf_s(BufferLog, "ERROR: not found ColorRgb=%d", IdColor);
			InviaLog(BufferLog);
			return 0x0000FF00;
		}

		return GlobTomb4.BaseColoriRGB.VetColori[i].Colore;
	}

	// inizializza ammo aappena letto da script
	// InitAmmoCust(VetArg[0], &VetArg[1], TestTitle);

	void InitAmmoCust(short SlotArma, short VetArg[], bool TestTitle)
	{
		StrCustAmmo *pAmmo;
		StrCustAmmo *pDef;
		short n;
		bool TestFucile;

		TestFucile = false;

		switch (SlotArma) {

		case 350: // PISTOLS_AMMO_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoPistols;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoPistols;
			break;
		case 352:  // UZI_AMMO_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoUZI;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoUZI;
			break;
		case 354: // SHOTGUN_AMMO1_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoFucileNormale;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoFucileNormale;
			TestFucile = true;
			break;
		case 355: // SHOTGUN_AMMO2_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoFucilePotenziate;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoFucilePotenziate;
			TestFucile = true;
			break;
		case 357:  // CROSSBOW_AMMO1_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoBalestraNormali;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoBalestraNormali;
			break;
		case 358:  // CROSSBOW_AMMO2_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoBalestraVelenose;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoBalestraVelenose;

			break;
		case 359: // CROSSBOW_AMMO3_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoBalestraEsplosive;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoBalestraEsplosive;
			break;
		case 362:  // GRENADE_GUN_AMMO1_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoGranateNormali;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoGranateNormali;
			break;
		case 363:  // GRENADE_GUN_AMMO2_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoGranateEsplosive;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoGranateEsplosive;
			break;
		case 364: // GRENADE_GUN_AMMO3_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoGranateLuminose;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoGranateLuminose;
			break;
		case 367:  // SIXSHOOTER_AMMO_ITEM:
			pAmmo = &GlobTomb4.pBaseCustomize->AmmoRevolver;
			pDef = &GlobTomb4.pBaseCustomizeDefault->AmmoRevolver;
			break;
		default:
			sprintf_s(BufferLog, "ERROR: unknown ammo slot for Customize command. Unknown slot %d", SlotArma);
			InviaLog(BufferLog);
			return;
		}

		// vetarg (escludendo i primi due campi) e':
		// 0: Ammo flags (AMMO_....)
		if (VetArg[0] != -1)
			pAmmo->Flags = VetArg[0];

		// 1:Damage
		if (VetArg[1] != -1)
			pAmmo->DamageNormale = VetArg[1];

		// 2: ShotsForBox,
		if (VetArg[2] != -1) {
			n = VetArg[2];
			if (n < 0) {
				n = -1;
			} else {
				if (TestFucile == true)
					n *= 6;
			}
			pAmmo->Pickup = n;
		}

		// 3:ShotsWithWeapon
		if (VetArg[3] != -1) {
			n = VetArg[3];
			if (n < 0) {
				n = -1;
			} else {
				if (TestFucile == true)
					n *= 6;
			}
			pAmmo->PickupRegalo = n;
		}

		// 4:Extra
		if (VetArg[4] != -1)
			pAmmo->Extra = VetArg[4];

		// 5:IdTriggerGroupWhenHitEnemy
		pAmmo->IdTriggerHitEnemy = VetArg[5];

		// 6:DamageForExplosion
		if (VetArg[6] != -1)
			pAmmo->DamageEsplosivo = VetArg[6];

		// 7:Speed
		if (VetArg[7] != -1)
			pAmmo->Speed = VetArg[7];

		// 8:Gravity
		if (VetArg[8] != -1)
			pAmmo->Gravity = VetArg[8];

		// 9:IdAddEffectToAmmo
		pAmmo->IdAddEffect = VetArg[9];

		// 10: IdTriggerGroupAtEnd
		pAmmo->IdTriggerAtEnd = VetArg[10];

		// se e' titolo impostarlo come valori di default
		if (TestTitle) {
			memcpy(pDef, pAmmo, sizeof(StrCustAmmo));
		}
	}

	// salva i dati cust_weap appena letti da script
	void InitWeaponCust(short SlotArma, short VetArg[], bool TestTitle)
	{
		StrCustWeapon *pWeap;
		StrCustWeapon *pDef;

		switch (SlotArma) {
		case 349: // PISTOLS_ITEM
			pWeap = &GlobTomb4.pBaseCustomize->WeaponPistols;
			pDef = &GlobTomb4.pBaseCustomizeDefault->WeaponPistols;
			break;
		case 351:  // UZI_ITEM
			pWeap = &GlobTomb4.pBaseCustomize->WeaponUzi;
			pDef = &GlobTomb4.pBaseCustomizeDefault->WeaponUzi;
			break;
		case 353: // SHOTGUN_ITEM
			pWeap = &GlobTomb4.pBaseCustomize->WeaponFucile;
			pDef = &GlobTomb4.pBaseCustomizeDefault->WeaponFucile;
			break;
		case 356: // CROSSBOW_ITEM
			pWeap = &GlobTomb4.pBaseCustomize->WeaponBalestra;
			pDef = &GlobTomb4.pBaseCustomizeDefault->WeaponBalestra;
			break;
		case 361: // GRENADE_GUN_ITEM
			pWeap = &GlobTomb4.pBaseCustomize->WeaponLanciaGranate;
			pDef = &GlobTomb4.pBaseCustomizeDefault->WeaponLanciaGranate;
			break;
		case 366:  // SIXSHOOTER_ITEM (revolver)
			pWeap = &GlobTomb4.pBaseCustomize->WeaponRevolver;
			pDef = &GlobTomb4.pBaseCustomizeDefault->WeaponRevolver;
			break;
		default:
			return;
		}

		// argomenti:
		// 0: Weapon flags (WEAP_..)
		if (VetArg[0] != -1)
			pWeap->Flags = VetArg[0];

		// 1: SoundForShot
		if (VetArg[1] != -1)
			pWeap->SoundShot = VetArg[1];

		// 2: FramesForRecharge
		if (VetArg[2] != -1)
			pWeap->FramesRicarica = (BYTE) VetArg[2];

		// 3: DurateFlash
		if (VetArg[3] != -1)
			pWeap->SizeShell = (BYTE) VetArg[3];

		// 4: Extra
		if (VetArg[4] != -1)
			pWeap->Extra = VetArg[4];

		// 5: MaxDistanceForAiming
		if (VetArg[5] != -1)
			pWeap->DistanceAiming = VetArg[5] * 1024;

		// 6: FrameToTakeWeapon
		if (VetArg[6] != -1)
			pWeap->FrameToTakeWeapon = (BYTE) VetArg[6];

		// 7: FrameToLetWeapon
		if (VetArg[7] != -1)
			pWeap->FrameToLetWeapon = (BYTE) VetArg[7];

		// 8: Random dispersione
		if (VetArg[8] != -1)
			pWeap->Dispersion = VetArg[8];

		// 9: VPositionOfWeapon
		if (VetArg[9] != -1)
			pWeap->VPositionOfWeapon = VetArg[9];

		// 10: Unknown,
		if (VetArg[10] != -1)
			pWeap->Unknow = VetArg[10];

		// 11: FrameCounter
		if (VetArg[11] != -1)
			pWeap->FrameCounter = (BYTE) VetArg[11];

		// 12: FrameMinRange
		if (VetArg[12] != -1)
			pWeap->FrameMinRange = (BYTE) VetArg[12];

		// 13: FrameMaxRange
		if (VetArg[13] != -1)
			pWeap->FrameMaxRange = (BYTE) VetArg[13];

		// 14: OrigX
		if (VetArg[14] != -1)
			pWeap->OrigX = VetArg[14];

		// 15: OrigY
		if (VetArg[15] != -1)
			pWeap->OrigY = VetArg[15];

		// 16: OrigZ
		if (VetArg[16] != -1)
			pWeap->OrigZ = VetArg[16];

		// 17: OrigOrient
		if (VetArg[17] != -1)
			pWeap->Orient = VetArg[17];

		if (TestTitle) {
			memcpy(pDef, pWeap, sizeof(StrCustWeapon));
		}
	}

	// riceve i soliti parametri per testo (uguali a quelli di TextFormat=
	// e li salva in struttura pText
	void ScansioneTextFormat(StrPrintString *pText, WORD VetScript[])
	{
		WORD Numero;
		int i;

		i = 0;
		Numero = VetScript[i++];
		if (Numero == SCRIPT_IGNORE)
			Numero = FC_WHITE;
		pText->Colore = Numero;

		// seconda word: flag FT_ sia per posizione che per
		// eventuale blink
		Numero = VetScript[i++];
		if (Numero == SCRIPT_IGNORE)
			Numero = 1; // corrisponde a  FT_BOTTOM_CENTER;

		pText->Flags = Numero & 0xF000;
		pText->FlagsMicro = (Numero & 0x0FF0) >> 4;
		pText->Posizione = Numero & 0x000F;

		// terza word: velocita' blink
		Numero = VetScript[i++];
		if (Numero == SCRIPT_IGNORE)
			Numero = 0x10;

		pText->BlinkSpeed = (BYTE) Numero;

		// quarta word: SC_... size globale
		Numero = VetScript[i++];

		if (Numero == SCRIPT_IGNORE)
			Numero = SC_NORMAL;

		// attenzione questo e' un valroe da elaborare
		switch (Numero) {
		case SC_NORMAL:
			Numero = 0;
			break;
		case SC_HALF_WIDTH:
			Numero = FT_HALF_SIZEX;
			break;
		case SC_HALF_HEIGHT:
			Numero = FT_HALF_SIZEY;
			break;
		case SC_HALF_SIZE:
			Numero = FT_HALF_SIZEX + FT_HALF_SIZEY;
			break;
		case SC_DOUBLE_WIDTH:
			Numero = FT_DOUBLE_SIZEX;
			break;
		case SC_DOUBLE_HEIGHT:
			Numero = FT_DOUBLE_SIZEY;
			break;
		case SC_DOUBLE_SIZE:
			Numero = FT_DOUBLE_SIZEX + FT_DOUBLE_SIZEY;
			break;
		default:
			Numero = 0;
			break;
		}
		pText->DefALLFlagsMicro = (BYTE) Numero;
	}

	// note: TestInverti = true, quando il colore sara' usato in funzioni windows dove rosso e blu sono invertiti

	COLORREF GetColoreId(short IdColorRgb, COLORREF ColoreDef, bool TestInverti, char *pMexComando)
	{
		// cerca di localizzare colore presente in colorrgb id
		// se non lo trova resittuisce colore di default ColoreDef
		int Indice;
		COLORREF NewColor;
		StrSingleColors *pDest;

		if (IdColorRgb < 0) {
			sprintf_s(BufferLog, "ERROR it has not been set the ID for ColorRbg in the script command %s", pMexComando);
			InviaLog(BufferLog);
			return ColoreDef;
		}
		Indice = GlobTomb4.BaseColoriRGB.VetID[IdColorRgb];

		if (Indice == -1) {
			sprintf_s(BufferLog, "INTERNAL ERROR: not found the ColorRgb command with id = %d", IdColorRgb);
			InviaLog(BufferLog);
			return ColoreDef;
		}
		if (TestInverti) {
			pDest = (StrSingleColors *) &NewColor;

			pDest->Blue = GlobTomb4.BaseColoriRGB.VetColori[Indice].Single.Red;
			pDest->Green = GlobTomb4.BaseColoriRGB.VetColori[Indice].Single.Green;
			pDest->Red = GlobTomb4.BaseColoriRGB.VetColori[Indice].Single.Blue;
			pDest->Unused = 0;
			return NewColor;
		}

		return GlobTomb4.BaseColoriRGB.VetColori[Indice].Colore;
	}

	// pChar= ScompattaNomeFont(pChar, &pFont->CharSet);
	// riceve nome font che puo' avere il formato "32:Arial"
	// dove il primo numero sarebbe il charset
	const char * ScompattaNomeFont(const char NomeFont[], int *pCharSet)
	{
		DWORD i;
		const char *pChar;
		char BufNum[80];

		*pCharSet = 0;

		pChar = NomeFont;

		for (i = 0; i < strlen(NomeFont); i++) {
			BufNum[i] = NomeFont[i];
			if (NomeFont[i] == ':') {
				pChar = &NomeFont[i + 1];
				BufNum[i] = 0;

				if (PrendiNumero(BufNum, pCharSet) == false)
					*pCharSet = 0;
				break;
			}
		}

		return pChar;
	}

	// procedura usata per combinare o separare i miei oggetti
	// l'indice di record combine e' contenuto in variabile globale GlobIndiceCombine
	void MiaCombineItems(bool TestSepara)
	{
		int Primo, Secondo, Finale;
		StrCombine *pCombine;

		pCombine = &GlobTomb4.pAdr->pVetNewCombine[GlobIndiceCombine];

		Primo = GlobTomb4.pAdr->pVetStructInventoryItems[pCombine->PrimoItem].Slot;
		Secondo = GlobTomb4.pAdr->pVetStructInventoryItems[pCombine->SecondoItem].Slot;
		Finale = GlobTomb4.pAdr->pVetStructInventoryItems[pCombine->ItemFinale].Slot;

		if (TestSepara) {
			// separare
			GestionePickups(Primo, INV_INCREMENTA, 0);
			GestionePickups(Secondo, INV_INCREMENTA, 0);
			GestionePickups(Finale, INV_DECREMENTA, 0);
		} else {
			// combinare
			GestionePickups(Primo, INV_DECREMENTA, 0);
			GestionePickups(Secondo, INV_DECREMENTA, 0);
			GestionePickups(Finale, INV_INCREMENTA, 0);
		}
	}

	// legge o imposta valore per un oggetto inventario: pickups, armi, munizioni ecc
	// Slot e' numero di slot
	// operazione e' costante INV_ (inventario)
	// valore contiene l'argomento da usare per qualche operazione
	// se operazione e' INV_READ restituisce il numero di elmenti

	WORD GestionePickups(WORD Slot, int Operazione, short Valore)
	{
		__try { throw __func__; } __finally {}
	}

	// verifica se item attuale in precedenza non aveva status combinabile
	// se non aveva il flag, lo aggiunge adesso
	void AggiungiCombinabile(WORD ItemIndex)
	{
		int i;

		// se era gia' stato memorizzato uscire subito
		for (i = 0; i < GlobTomb4.TotCombinabili; i++) {
			if (ItemIndex == GlobTomb4.VetCombinabili[i])
				return;
		}

		if (GlobTomb4.pAdr->pVetFlagsInventoryItems[ItemIndex] & 0x08)
			return;

		// ok, salvarlo
		i = GlobTomb4.TotCombinabili;
		GlobTomb4.VetCombinabili[i] = ItemIndex;
		GlobTomb4.TotCombinabili++;
	}

	// riscrive l'intera lista di nomi wav in modo da avere estensione
	// corretta sulla base di tipoextwav
	void RicreaNomiWav(int TipoExtWav)
	{
		__try { throw __func__; } __finally {}
	}

	void ModificaFogEnd(void)
	{
		StrBaseFog *pFog;

		pFog = &GlobTomb4.BaseFog;

		pFog->FloatFogEnd = (float) pFog->NowEndFog;

		pFog->FloatFogEnd = pFog->FloatFogEnd * 1024.0f;

		SetFogEnd();
	}

	// modiifca con directx il valore per FOG_END prelevandolo
	// da valore globale in BaseFog.FloatFogEnd
	void SetFogEnd(void)
	{
		tomb4::DXAttempt(tomb4::App.dx.lpD3DDevice->SetLightState(D3DLIGHTSTATE_FOGEND, *(DWORD *) &GlobTomb4.BaseFog.FloatFogEnd));
	}

	// inserisce valore pFog->NowDistanceFog nella variabile tomb4,
	// convertendolo in float e moltiplicandolo * 1024
	// imposta anche floatstartfog di basefog
	void ModificaFogStart(void)
	{
		StrBaseFog *pFog;

		pFog = &GlobTomb4.BaseFog;

		pFog->FloatFogStart = (float) pFog->NowStartFog * 1024.0f;

		*GlobTomb4.pAdr->pStartFog = pFog->FloatFogStart;
	}

	// chiama directx per attivare o diattivare hardware fog usando
	// valore in BaseFog.TestHardwareFog

	void ModificaHardwareFog(void)
	{
		tomb4::DXAttempt(tomb4::App.dx.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, GlobTomb4.BaseFog.TestHardFogEnabled));
	}

	// imposta in variabile globale tomb4 il valore float per la max distanza
	// per fogbulbs
	// legge l'input da BaseFog.NowFogBulbDistance
	void ModificaFogBulbDistance(void)
	{
		__try { throw __func__; } __finally {}
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
	ProcessInject(0x1006CA83, (unsigned int)trng::LeggiNG_ScriptForLevel, replace);
	ProcessInject(0x100469BD, (unsigned int)trng::SalvaTagFmv, replace);
	ProcessInject(0x1003B591, (unsigned int)trng::LiberaCutsceneCamera, replace);
	ProcessInject(0x1006C37F, (unsigned int)trng::InizializzaAdaptiveFarView, replace);
	ProcessInject(0x10039931, (unsigned int)trng::LiberaImmagine, replace);
	ProcessInject(0x1006C4C4, (unsigned int)trng::InitScreenShot, replace);
	ProcessInject(0x1006CA1A, (unsigned int)trng::LiberaAllFonts, replace);
	ProcessInject(0x10056B43, (unsigned int)trng::SetItemDetector, replace);
	ProcessInject(0x1006C334, (unsigned int)trng::RipristinaTurbo, replace);
	ProcessInject(0x10039B5B, (unsigned int)trng::SetPriority, replace);
	ProcessInject(0x10039B2C, (unsigned int)trng::Livello2Priority, replace);
	ProcessInject(0x10038CEF, (unsigned int)trng::RipristinaIndiciSlot, false);
	ProcessInject(0x10041BDF, (unsigned int)trng::RipristinaWorldFarView, false);
	ProcessInject(0x100690DB, (unsigned int)trng::InizializzaBaseFog, false);
	ProcessInject(0x10069151, (unsigned int)trng::RipristinaLevelSettings, replace);
	ProcessInject(0x1005CB53, (unsigned int)trng::RestoreHardwareFogSempre, replace);
	ProcessInject(0x10069179, (unsigned int)trng::RipristinaDefaultPrintString, replace);
	ProcessInject(0x10069270, (unsigned int)trng::RipristinaDamageSettings, replace);
	ProcessInject(0x100691D5, (unsigned int)trng::CalcolaQuotaTickPerDamage, replace);
	ProcessInject(0x10069342, (unsigned int)trng::RipristinaEnemy, false);
	ProcessInject(0x1006C882, (unsigned int)trng::ImpostaDefaultWindowsFont, replace);
	ProcessInject(0x10038468, (unsigned int)trng::Float2Int, replace);
	ProcessInject(0x100757AC, (unsigned int)trng::RapportoFloatSchermo, replace);
	ProcessInject(0x10037AE4, (unsigned int)trng::Casuale, replace);
	ProcessInject(0x10038D71, (unsigned int)trng::AnnullaIndiceSlot, false);
	ProcessInject(0x10038810, (unsigned int)trng::GetPluginIndex, replace);
	ProcessInject(0x1006C4FE, (unsigned int)trng::AggiungiImmaginePreload, replace);
	ProcessInject(0x1005E62D, (unsigned int)trng::ImpostaStandBy1, replace);
	ProcessInject(0x10069D3B, (unsigned int)trng::EseguiCustomize, replace);
	ProcessInject(0x1007CDA2, (unsigned int)trng::TrovaColoreRGB, replace);
	ProcessInject(0x100698CA, (unsigned int)trng::InitAmmoCust, replace);
	ProcessInject(0x100695C5, (unsigned int)trng::InitWeaponCust, replace);
	ProcessInject(0x1006C19B, (unsigned int)trng::ScansioneTextFormat, replace);
	ProcessInject(0x1006C3E9, (unsigned int)trng::GetColoreId, replace);
	ProcessInject(0x1006C983, (unsigned int)trng::ScompattaNomeFont, replace);
	ProcessInject(0x1006C6FB, (unsigned int)trng::MiaCombineItems, replace);
	ProcessInject(0x1003A063, (unsigned int)trng::GestionePickups, false);
	ProcessInject(0x1006C7F5, (unsigned int)trng::AggiungiCombinabile, replace);
	ProcessInject(0x10069C5A, (unsigned int)trng::RicreaNomiWav, false);
	ProcessInject(0x10069039, (unsigned int)trng::ModificaFogEnd, replace);
	ProcessInject(0x10068FCB, (unsigned int)trng::SetFogEnd, replace);
	ProcessInject(0x10069074, (unsigned int)trng::ModificaFogStart, replace);
	ProcessInject(0x100690B1, (unsigned int)trng::ModificaHardwareFog, replace);
	ProcessInject(0x10068FEF, (unsigned int)trng::ModificaFogBulbDistance, false);
}
