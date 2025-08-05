#pragma once
#include <stdio.h>
#include "structures.h"
#include "MyStructures.h"
#include "DefTomb4Funct.h"

namespace trng {
	extern StrGlobaliTomb4 &GlobTomb4;
	extern StrGlobAddress &AdrGlobali;
	extern StrMyGlob &MyGlobPrivate;
	extern StrBaseCustomize &BaseCustomize;
	extern StrGlobMisc &BaseGlobMisc;
	extern char (&Dir_Trle)[256];
	extern int &TotAllocata;
	extern bool &TestDebugLog;
	extern DWORD &DefValoreZero;
	extern int &TipoExe;
	extern int &TotCheckMemory;
	extern StrBaseVarAll &BaseVariableTRNG;
	extern StrPanelloSavegame &BasePanello;
	extern StrBaseScriptImages &BaseScriptImages;
	extern StrBaseTriggerGroups &BaseTriggerGroups;
	extern StrBaseCustomize &BaseCustomizeDefault;
	extern BaseScriptOrganizer &BaseOrganizer;
	extern StrBaseGlobalTriggers &BaseGlobalTriggers;
	extern StrBaseScriptEnvCondition &BaseEnvConditions;
	extern StrBaseEffects &BaseEffects;
	extern StrScriptLevel &ScriptLevelNow;
	extern StrBaseDiagnostica &BaseDiagnostica;
	extern StrDatiVariabili &DatiVariabili;
	extern StrDatiVariabili &DatiVarLara;
	extern BaseAnimScript &BaseAnimations;
	extern StrRecording &BaseDemo;
	extern StrDemo &DemoTitle;
	extern StrDemo &DemoLevel;
	extern StrBaseCutscene &BaseCutscene;
	extern StrBaseSwapAnim &BaseSwapAnim;
	extern StrBaseMemSwapAnim &BaseMemSwapAnim;
	extern StrBaseSpeechActor &BaseSpeechActor;
	extern StrPluginNames (&VetPluginNgle)[MAX_PLUGINS_NGLE];
	extern StrTablePluginIdFloor &PluginFloorTable;
	extern StrTableScriptPlugin &PluginScriptTable;
	extern int (&VetMeshSwapSlot)[78];
	extern int (&VetStandardSwapMesh)[107];
	extern int (&VetSlotMeshMoveables)[122];
	extern TYPE_tombInviaLog &tombInviaLog;
	extern BYTE &FlagMicroCaratteri;
	extern char (&MexNewWindowTitle)[256];
	extern char (&BufferLog)[8192];
	extern StrFloatPatch (&VetFarWorld)[5];

	void ImpostaEnemyDamage(void);
	bool Inizializza(void);
	void LinkGlobTomb4Structures(void);
	bool IsAttivoDebugger(void);
	char *TrovaVersioneFile(const char *NomeFile, char *pBufProductVersion);
	void CalcolaVersione(StrVersionHeader *pBaseVer);
	void InizializzaTomb4(void);
	bool InviaLog(const char *pMessaggio);
	void GestioneDgxErrori(const char *pMex);
	bool ScopreModoFullScreen(void);
	void InitStringOffsets(void);
	void AnalisiWideScreen(void);
	BYTE *CaricaTomb4Mem(void);
	void Controllo1FileMancanti(void);
	bool EsisteFile(const char *NomeFile);
	void InitPrintTextColors(void);
	void InitBarDefault(void);
	void CustDefToCustNow(void);
	bool LeggeNGScriptDat(char NomeScriptDat[]);
	void InitDgxErrors(void);
	void ImpostaCostantiNascoste(void);
	void InitRemapItemGroup(void);
	void VerifyImagesPix(void);
	StrListaFiles *TrovaFiles(const char DirSource[], const char Maschera[], int *pTotFiles);
	void LeggeMieSettingRegister(void);
	void VerificaAttivazioneSoftFullScreen(void);
	void VerificaAttivazioneNoWaitingRefresh(void);
	void RestyleWindow(void);
	void InitFmvLog(const char *pMex, bool TestCancellaLog);
	void CaricaNGStringTemp(void);
	void MessageBoxTomb(const char *pMessaggio, const char *pTitolo);
	bool ExtractNGHeader(char *pNomeFile, StrExtractNG* pExtractNG);
	long QuantoLungo(FILE *tempfile);
	bool ParseNgField(WORD *pNgArray, DWORD CurrentIndex, StrParseNGField* pParseNGField);
	char *GetStringaNG(int Indice);
	void ModificaWorldFarView(WORD NumBlocchi, bool TestHardware);
	void CreaSottoCartelle(char *pNomeFile);
	bool EsisteDirectory(char *NomeDir);
	bool CreaDirectory(char *NomeDir);
	char * GetString(int IndiceStringa);
}

void LoadTombNextGenerationInject_TombNextGeneration(bool replace);
