#pragma once
#include "../framework.h"
#include "MyConstants.h"
#include "structures.h"

namespace trng {
	typedef BOOL (__cdecl *TYPE_DebugPresente) (VOID);

#pragma pack(push, 1)
	// reocrd per memorizzare callback richieste dai plugin
	struct StrRecordCallBack {
		WORD CB_Tipo; // CB_... value
		WORD Flags; // CBT_.. (prima, dopo)
		void *pCall;
		WORD Numero;
	};

	struct StrPluginRec {
		char Nome[80];  //  nome SENZA ".dll"
		HMODULE hDllPlugin; // handle di libreria
		SYSTEMTIME Data; // data creazione (GMT)
		DWORD OffsetPatcher; // indirizzo tomb4 di Patch_GenericheAsm per plugin
		void * pDirectCall; // indirizzo in plugin per chiamare direttamente il suo codice a basso livello
		BYTE VersioneFile[4]; // 4 cifre di versione file 1.0.2.0
		BYTE VersioneProduct[4]; // 4 cifre di versione product 1.2.0.0
		DWORD OffCodeStart; // inizio codice allocato
		DWORD OffCodeEnd;  // fine codice allocato
		int PluginIdScript; // per triggers di triggergroup e cust_ e param_
		int PluginIdNgle;  // per trigger di floordata di livello tr4
		int TotRequiredCB;
		StrRecordCallBack VetRequiredCB[MAX_REQUIRED_CB];  // tutte le callback richieste dal plugin senza eccezione
		void * VetDirectCB[MAX_DIRECT_CB]; // indicizzata con DIRECT_CB queste sono senza numero e senza flag
	};

	// struttura Item per tomb3 size 0x84
	struct StrItemTr3 {
		int HeightFloor;		// 00
		int ContactFlags;		// 04
		DWORD MeshVisibilityMask; // 08
		WORD SlotID;			// 0C
		WORD StateIdCurrent;			// 0E
		WORD StateIdNext;			// 10
		WORD StateIdAI;				// 12
		WORD AnimationNow;		// 14
		WORD FrameNow;			// 16
		short Room;					// 18
		short ItemIndexNext;			// 1A
		short ItemIndexPrevious;  // 1C
		short SpeedH;			// 1E
		short SpeedV;			// 20
		short Health;				// 22
		WORD BoxZoneIndex;			// 24
		WORD Contatore;				// 26
		WORD Objectbuttons;	// 28
		WORD Intensity1;			// 2a
		WORD OcbCode;				// 2c
		BYTE IdSprite1;				// 2e
		BYTE IdSprite2;				// 2f
		WORD Trasparency;			// 30
		WORD Mistery1;				// 32
		WORD Reserved_34;		    // 34
		WORD Reserved_36;				// 36
		WORD Reserved_38;				// 38
		WORD Reserved_3A;				// 3A
		void *pZonaSavegame;		// 3C

		DWORD  CordX;					// 40
		int  CordY;					// 44
		DWORD  CordZ;					// 48
		short OrientationV;  // 4c
		short OrientationH;  // 4e
		short OrientationT;		// 50
		short OrientamentoSpec2;  //52
		BYTE MISTERO_3[10];		// 54
		DWORD Colore;			// 5e
		BYTE MISTERO_4[16];		// 62
		BYTE MisteroTr3[16];	// 72
		WORD FlagsMain;			// 82
	};

	// dimensione record 0x32
	struct StrSlotTomb3 {
		WORD  TotMesh;		// 0
		WORD  IndexFirstMesh;	// 2
		int   IndexFirstTree;	// 4
		int   IndexFirstFrame;  // 8
		void *pProcInitialise;	// 0C
		void *pProcControl;		// 10
		void *pProcFloor;		// 14
		void *pProcCeiling;		// 18
		void *pProcDrawEmitted; // 1C
		void *pProcCollision;   // 20
		WORD  IndexFirstAnim;   // 24 (era 26)
		short Vitality;			// 26 (era 28)
		WORD Sconosciuto2;		// 28 (era 2A)
		WORD ss_Unknown3;		// 2A    2C
		WORD FootStep;			// 2C      2E
		WORD  TestGuard;		// 2E       30
		WORD Flags;				// 30         32
	};

	// strutture room per tr3 (size 0x50)
	struct Tipo_StrRoomTr3 {
		void *pStaticDataRoom;   // 00
		StrBaseDoors *pDoors; 		    // 04
		void *pCollsionSectors; // 08
		void *pLights;           // 0c
		StrMeshInfo *Ptr_StaticMesh;       // 10
		int  OriginZ;                 // 14
		int  Mistero1;              // 18
		int  OriginX;                 // 1C
		int  OrigYBottom;           // 20
		int  OrigYTop;              // 24
		WORD Z_SizeSectors;         // 28
		WORD X_SizeSectors;         // 2A
		DWORD ColorIntensityLight;  // 2C
		WORD TotLights;             // 30
		WORD TotStaticMesh;         // 32
		BYTE WaterIntensity;		// 34
		char FlipMapIndex;   // 35
		char MisteroFlip1;			// 36
		BYTE Mistero30;              // 37
		int  Mistero2;              // 38
		int  Mistero3;		        // 3C
		int  Mistero4;				// 40
		int  Mistero5; 			    // 44
		short FirstItemIndex;			// 48
		short FirstEffect;			// 4A
		short  AlternateRoom;			// 4C  -1 se non c'e' o e' stanza flippata?
		WORD  FlagsRoom;		     // 4E
	};

	// struttura singolo record animation
	struct StrAnimationTr3 {
		DWORD FrameOffset;		// 0x00
		BYTE  FrameRate;		// 0x04
		BYTE  FrameSize;		// 0x05
		WORD  StateId;			// 0x06
		WORD  Mistery1;			// 0x08
		WORD  Speed;			// 0x0A
		WORD  AccelLO;			// 0x0C
		WORD  AccelHI;			// 0x0e
		WORD  FrameStart;		// 0x10
		WORD  FrameEnd;			// 0x12
		WORD  NextAnimation;	// 0x14
		WORD  NextFrame;		// 0x16
		WORD  NumStateChanges;	// 0x18
		WORD  StateChangeOffset; // 0x1a
		WORD  NunAnimCommands;	// 0x1c
		WORD  AnimCommand;		// 0x1e
	};

	struct StrRobaTomb3 {
		int CordY;
		int StepY;
		DWORD StartTime;
		StrItemTr3* pLara;
		int *pTotItem3;
		StrSlotTomb3 *VetSlot3;
		StrItemTr3 *pVetItemTr3;
		Tipo_StrRoomTr3 *pVetRoomTr3;
		BYTE *pLevelNow;
		StrAnimationTr3 *pVetAnimations;
	};

	// lo uso solo per diagnostica per cui per ora me ne frego dei campi
	struct Tipo_StrRoomTr5 {
		BYTE VetValori[0xd0];
	};

	struct StrStringaTr5 {
		short OrgX;
		short OrgY;
		WORD Colore;
		char MexTesto[512];
	};

	struct StrRobaTomb5 {
		DWORD StartTime;
		StrItemTr4* pLara;
		int *pTotItem5;
		StrSlot *VetSlot5;
		StrItemTr4 *pVetItemTr5;
		Tipo_StrRoomTr5 *pVetRoomTr5;
		BYTE *pLevelNow;
		StrStateChange *pVetChangeState;
		StrAnimDispatch *pVetAnimDispatch;
		int CordY;
		int StepY;
		StrAnimationTr4 *pVetAnimations;
		int TotStringhe;
		StrStringaTr5 VetStringhe[MAX_STRINGE_TR5];
	};

	struct StrCodePatch {
		DWORD Inizio;
		DWORD Fine;
		int   NewValue;  // solo per patch parametrica
		DWORD ProcStart; // solo per patch rilocatrice
		DWORD ProcEnd;   // solo per patch rilocatore
		WORD IndexPlugin;  // indice a nome libreria che ha effettuato questa patch
		WORD FlagsTYPP;        // TYPP_  (Type Patch)
	};

	// patch parametrica
	// dati riassunivi a scopo informativo ma non saranno usati per calcolo conflitti
	struct StrArgPatch {
		int PluginId;
		DWORD OffsetFirst; // primo offset, della serie, dove si fa una modifica
		DWORD OffsetLast;  // ultimo offset della serie dove c'e' stata una modifica
		DWORD ValoreNew;  // nuovo valore che viene assegnato a tutta la serie
		WORD Size;  // 1 , 2, 4
		WORD Flags;  // TYPP_  (run time, parametrica e tipo dato)
	};

	struct StrReservedData {
		DWORD PluginID;
		DWORD StartOffset;
		DWORD EndOffset;  // inclusa nella zona contesa
	};

	struct StrMyDatabase {
		DWORD TotPlugins;
		StrPluginRec *pVetPlugins;
		int TotMemZones;
		StrRecordMemZone *pVetMemZone;
		int TotCodeZones;
		StrCodePatch *pVetCodePatch;
		int TotPatchArg;
		StrArgPatch *pVetPatchArg;
		int TotReservedData;
		StrReservedData *pVetReserved;
	};

	struct StrBloccoCodice {
		DWORD Inizio;
		DWORD Fine;
		char *pNomePlugin;
	};

	struct StrBaseBlocchiCodice {
		int TotBlocchi;
		StrBloccoCodice VetBlocchi[400];
	};

	// questo contiene 0 se nesusno a riciesto call back first or after per il dato trigger
	// oppure contiene flag CBT_FIRST o CFT_AFTER
	// per controllare quelle replace usare la struttura StrCallGlobReplace
	struct StrCallGlob {
		WORD VetFlipeffects[1024];
		WORD VetActions[256];
		WORD VetConditions[256];
		WORD VetSlotControl[SLOT_NUMBER_OBJECTS];
		WORD VetSlotInitialise[SLOT_NUMBER_OBJECTS];
		WORD VetSlotCollision[SLOT_NUMBER_OBJECTS];
		WORD VetSlotDraw[SLOT_NUMBER_OBJECTS];
		WORD VetSlotFloor[SLOT_NUMBER_OBJECTS];
		WORD VetSlotCeiling[SLOT_NUMBER_OBJECTS];
		WORD VetSlotDrawExtra[SLOT_NUMBER_OBJECTS];
		WORD VetTrngAsmPatch[MAX_TRNG_ASM_PATCH];
		WORD VetStateIdControl[256];
		WORD VetStateIdCollision[256];
		WORD VetDirectCB[MAX_DIRECT_CB];
	};

	// qui se e' NULL non c'e' alcuna procedura replace per il dato trigger
	// in caso contrario il puntatore e' proprio l'indirizzo della callback
	struct StrCallGlobReplace {
		void * VetFlipeffects[1024];
		void * VetActions[256];
		void * VetConditions[256];
		void * VetSlotControl[SLOT_NUMBER_OBJECTS];
		void * VetSlotInitialise[SLOT_NUMBER_OBJECTS];
		void * VetSlotCollision[SLOT_NUMBER_OBJECTS];
		void * VetSlotDraw[SLOT_NUMBER_OBJECTS];
		void * VetSlotFloor[SLOT_NUMBER_OBJECTS];
		void * VetSlotCeiling[SLOT_NUMBER_OBJECTS];
		void * VetSlotDrawExtra[SLOT_NUMBER_OBJECTS];
		void * VetTrngAsmPatchAddr[MAX_TRNG_ASM_PATCH];
		WORD VetTrngAsmPatchFlags[MAX_TRNG_ASM_PATCH]; // flags (per FTB_ASM o meno)
		void * VetStateIdControl[256];
		void * VetStateIdCollision[256];
		void * VetDirectCB[MAX_DIRECT_CB];
		int    VetDirectCB_PluginId[MAX_DIRECT_CB];
	};

	struct StrMyGlob {
		StrRobaTomb3 RobaTomb3;
		StrRobaTomb5 RobaTomb5;
		WORD TotBlindSavegame;
		WORD SettingScriptDat; // copia di setting script.dat
		TYPE_DebugPresente  ProcIsDebuggerPresente;
		BYTE VetBlindSavegame[128];
		BYTE VetControlloKrypt[1034]; // usata per controlli debugger
		bool TestDebuggerPresente;
		WORD VetNascondiSetting[251]; // vettore tutto nullo tranne 111 dove
									  // c'e' copia di settings di script.dat
		TYPE_DebugPresente  ProcIsDebuggerPresente2;
		bool TestNG_NoScript;
		bool TestNG_NoTr4;
		int TotCtrlScript;
		BYTE VetCtrlScript[64];  // valori decriptati
		WORD TotControlloScriptDat;
		BYTE VetControlloScriptDat[64];
		char UltimoTr4Caricato[256];
		int TestFileCriptati;
		StrMyDatabase DataBase; // per patch di ogni tipo e callback e roba plugin
		bool TestPatchDinamiche; // attivato a true DOPO l'esecuzione di patch iniziali
		bool TestDebugVersione; // true se trng o qualunque plugin e' in modo debug
		StrBaseBlocchiCodice BaseCodici;
		StrCallGlob BaseVetCbFirstAfter; // per controllo rapido se c'e' quallche call back first o after per ognitrigger
		StrCallGlobReplace BaseVetCbReplace; // o NULL o punttore alla callback
		BYTE *pTomb4Mem;  // serie di byte di sezione codice di tomb4 originale
	};
#pragma pack(pop)
}
