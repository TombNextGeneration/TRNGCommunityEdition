#pragma once
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

	void ImpostaEnemyDamage(void);
	void LinkGlobTomb4Structures(void);
	bool IsAttivoDebugger(void);
	char *TrovaVersioneFile(const char *NomeFile, char *pBufProductVersion);
	void CalcolaVersione(StrVersionHeader *pBaseVer);
	void InizializzaTomb4(void);
	bool Inizializza(void);
	void GestioneDgxErrori(const char *pMex);
	bool InviaLog(const char *pMessaggio);
	bool ScopreModoFullScreen(void);
}

void Inject_TombNextGeneration(bool replace);
void LoadTombNextGenerationInject_TombNextGeneration(bool replace);
