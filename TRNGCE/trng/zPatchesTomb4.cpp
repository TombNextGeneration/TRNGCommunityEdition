#include "zPatchesTomb4.h"
#include "../inject.h"
#include "Tomb_NextGeneration.h"
#include "../tomb4/game/control.h"
#include "DefTomb4Funct.h"
#include "MyStructures.h"
#include "trng_elevator.h"
#include "../tomb4/game/collide.h"
#include "Oggetti.h"
#include "../tomb4/game/objects.h"
#include "../tomb4/game/draw.h"
#include "../tomb4/game/savegame.h"
#include "../tomb4/game/lara.h"
#include "../tomb4/specific/dxshell.h"
#include "../tomb4/game/sound.h"
#include "../tomb4/specific/input.h"
#include "../tomb4/specific/3dmath.h"
#include "../tomb4/game/text.h"
#include "../tomb4/specific/winmain.h"
#include "../tomb4/game/gameflow.h"
#include "../tomb4/game/spotcam.h"
#include "../tomb4/specific/LoadSave.h"
#include "../tomb4/game/camera.h"
#include "../tomb4/specific/file.h"
#include "../tomb4/game/newinv.h"
#include "../tomb4/game/lara2gun.h"
#include "../tomb4/game/scarab.h"
#include "../tomb4/game/effects.h"
#include "../tomb4/game/tomb4fx.h"
#include "../tomb4/specific/audio.h"
#include "zRoomEditor.h"
#include "../tomb4/game/laraskin.h"
#include "../tomb4/game/sphere.h"
#include "../tomb4/game/box.h"
#include "../tomb4/game/delstuff.h"
#include "../tomb4/specific/function_stubs.h"
#include "../tomb4/game/bike.h"
#include "../tomb4/game/effect2.h"
#define malloc ((void *(*)(size_t)) 0x10135531)
#define realloc ((void *(*)(void *, size_t)) 0x101353F9)
#define free ((void (*)(void *)) 0x101355BD)

namespace trng {
	DWORD &OffsetPosLara = *reinterpret_cast<decltype(&OffsetPosLara)>(0x10679E5C);
	StrBaseMemAllocata &BaseAlloc = *reinterpret_cast<decltype(&BaseAlloc)>(0x10658848);
	int &LivelloOldNumber = *reinterpret_cast<decltype(&LivelloOldNumber)>(0x10679F50); // usato per passarlo a callback cbInitLevel
	int &GlobIndiceCombine = *reinterpret_cast<decltype(&GlobIndiceCombine)>(0x10679E68);
	// chiamata quando si entra in inventario
	int &TestLoadedGame = *reinterpret_cast<decltype(&TestLoadedGame)>(0x10657B68);
	WORD &RetSlotAss = *reinterpret_cast<decltype(&RetSlotAss)>(0x10657B6A);
	int &SlotSceltoInventario = *reinterpret_cast<decltype(&SlotSceltoInventario)>(0x10657F7C);
	int &TestEsitoBow = *reinterpret_cast<decltype(&TestEsitoBow)>(0x10679E3C);
	int &ExitMyFunction = *reinterpret_cast<decltype(&ExitMyFunction)>(0x10679F60);
	int &SalvaSlot = *reinterpret_cast<decltype(&SalvaSlot)>(0x10679F70);
	int &SalvaIndexItem = *reinterpret_cast<decltype(&SalvaIndexItem)>(0x10679F68);
	int &SalvaStrItem = *reinterpret_cast<decltype(&SalvaStrItem)>(0x10679F74);
	int &SalvaCall = *reinterpret_cast<decltype(&SalvaCall)>(0x10679F6C);
	DWORD &MyOutResult = *reinterpret_cast<decltype(&MyOutResult)>(0x10679F2C);
	StrSalvaOldDebug (&VetSalvaOldDebug)[30] = *reinterpret_cast<decltype(&VetSalvaOldDebug)>(0x106699EC);
	DWORD &LastReturnDX = *reinterpret_cast<decltype(&LastReturnDX)>(0x10679BF4);
	DWORD &ColorSlide = *reinterpret_cast<decltype(&ColorSlide)>(0x106699BC);

	// chiamata in fase caricamento di tr4 quando ancora
	// le mesh sono uguali a quelle in file tr4
	// salva il numero di vertici per ogni singola mesh
	// salva in GlobTomb4.pVetSalvaSizeMesh[]
	void SalvaDimensioniMesh(WORD *VetPtrMesh[], int TotMesh)
	{
		int i;
		WORD *pPunta;
		const char *pMex;

		// allocare memoria necessaria
		//a ttenzione questo viene chiamato ad ogni livello
		// per cui dovrei prima liberar eprecedente memoria

		if (GlobTomb4.pVetSalvaSizeMesh != NULL)
			FreeMine(GlobTomb4.pVetSalvaSizeMesh);

		GlobTomb4.pVetSalvaSizeMesh = (WORD *) MallocMine(TotMesh * 2, "pVetSalvaSizeMesh in SalvaDimensioniMesh()");

		for (i = 0; i < TotMesh; i++) {
			pPunta = VetPtrMesh[i];
			if (pPunta[5] > 255)
				pMex = "\t**** MAGGIORE DI 255 *******";
			else
				pMex = "";

			//tot vertici e' all'offset 10 0x0A quindi la 5a word
			GlobTomb4.pVetSalvaSizeMesh[i] = pPunta[5];
		}
	}

	// libera memoria con cattura eccezioni
	bool FreeMine(void *pMemory)
	{
		__try { throw __func__; } __finally {}
	}

	void * MallocMine(DWORD Size, const char *pDescrizione)
	{
		__try { throw __func__; } __finally {}
	}

	// gli slot sono stati appena impostati con le procedure e altri valori
	// come quelli di resistenza ecc
	// ora si puo' cambiarli in questa funzione
	void InitSlot(void)
	{
		StrIndiciAssign *pAssign;
		int i, j;
		WORD FlagSlot;
		CALL_VOID CallInitObjects;
		WORD NewFlags;
		StrPluginRec *pRec;
		WORD IndiceSlot;
		StrRecordEnemyScript *pEnemy;
		StrSlot *pSlotNow;
		StrSlot *pSlotSrc;

		GlobTomb4.pAdr->VetMeshPointer = (StrMeshTr4 **) tomb4::meshes;
		// se c'e' von croy salva mesh con mano libera e quella di pugnale
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[39];

		GlobTomb4.pAdr->pVonCroyMeshFreeHand = NULL;
		GlobTomb4.pAdr->pVonCroyMeskKnifeHand = NULL;

		if (pSlotNow->Flags & 0x001) {
			i = pSlotNow->IndexFirstMesh;
			GlobTomb4.pAdr->pVonCroyMeshFreeHand = GlobTomb4.pAdr->VetMeshPointer[i + 18 * 2 + 1];
			GlobTomb4.pAdr->pVonCroyMeskKnifeHand = GlobTomb4.pAdr->VetMeshPointer[i + 18 * 2];
		}

		// ------------- IMPOSTA SLOT PER NUOVI OGGETTI ---------------------
		// impostare twoblockplatform

		SetSlotElevator();

		pAssign = &GlobTomb4.pScriptLevelNow->AssignSlot;
		// prima imposta in ogni caso gli slot extra per le barche
		SetSlotMotorBoat(465, 466);
		SetSlotRubberBoat(467, 468);
		SetSlotMotorBikeLara();

		if (pAssign->IndiceRubberBoat != -1 && pAssign->IndiceAnimMotorBoat != -1) {
			// inizializzare slot per RUBBER BOAT da assign slot

			SetSlotRubberBoat((WORD) pAssign->IndiceRubberBoat, (WORD) pAssign->IndiceAnimRubberBoat);
		}

		if (pAssign->IndiceMotorBoat != -1 && pAssign->IndiceAnimMotorBoat != -1) {
			// inizializzare slot per MOTOR BOAT da assign slot
			SetSlotMotorBoat((WORD) pAssign->IndiceMotorBoat, (WORD) pAssign->IndiceAnimMotorBoat);
		}

		// inizializzre slot di pannelli collisioni
		// usando gli stessi valori usati per animating
		for (i = PANEL_START; i <= PANEL_END; i++) {
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[i];
			pSlotNow->Flags = 0x60;
			pSlotNow->pProcCollision = tomb4::ObjectCollision;
			pSlotNow->pProcDrawExtras = NULL;
		}

		// inizializza slot di bridge tilt3/4/custom
		for (i = 495; i <= 497; i++) {
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[i];

			pSlotNow->pProcFloor = &ProcMyBridgeFloor;
			pSlotNow->pProcCeiling = &ProcMyBridgeCeiling;
		}
		// ma anche quelli di slot standard
		for (i = 336; i <= 338; i++) {
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[i];

			pSlotNow->pProcFloor = &ProcMyBridgeFloor;
			pSlotNow->pProcCeiling = &ProcMyBridgeCeiling;
		}
		// iniziazizare slot per corda d'equilibrio (TIGHT_ROPE)
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[480];

		pSlotNow->Flags = 0x21;
		pSlotNow->pProcCollision = &TightRopeCollision;
		pSlotNow->pProcInitialise = &InitialiseTightRope;
		pSlotNow->pProcDraw = NULL;

		// inizializza laser head
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[481];
		if (pSlotNow->Flags) {
			i = pSlotNow->Flags;
			i |= 0x2c78;
			pSlotNow->Flags = (WORD) i;
			pSlotNow->ShatterableMeshes = 6;
			pSlotNow->pProcInitialise = &InitialiseGuardian;
			pSlotNow->pProcControl = &GuardianControl;
			pSlotNow->pProcCollision = tomb4::CreatureCollision;
		}

		// inizializza laser header base
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[482];
		pSlotSrc = &GlobTomb4.pAdr->pVetSlot[427]; // aimating1
		pSlotNow->Flags = pSlotSrc->Flags;
		pSlotNow->pProcCollision = pSlotSrc->pProcCollision;
		pSlotNow->pProcControl = pSlotSrc->pProcControl;

		// inizializza laser header crest
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[483];
		pSlotSrc = &GlobTomb4.pAdr->pVetSlot[427]; // aimating1
		pSlotNow->Flags = pSlotSrc->Flags;
		pSlotNow->pProcCollision = pSlotSrc->pProcCollision;
		pSlotNow->pProcControl = pSlotSrc->pProcControl;

		// imposta per parallelbar
		GlobTomb4.pAdr->pVetSlot[471].pProcCollision = &ParallelBarCollision;

		// inizializza kayak
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[492]; // Slot_492_KAYAK
		if (pSlotNow->Flags & 0x1) {
			InitSlotKayak();
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[493]; // KAYAK_LARA
			pSlotNow->Flags = GlobTomb4.pAdr->pVetSlot[33].Flags;
		}
		// inizializza hydra
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[484];

		if (pSlotNow->Flags & 0x1) {
			// usare procedura di inizializzare estratta dal codice tr5
			InitSlotHydra();
		}
		// inzializza missile hydra
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[485];

		if (pSlotNow->Flags & 0x01) {
			pSlotNow->pProcControl = (void*) &ControlBubble;
		}

		// inizializza fish_emitter

		pSlotNow = &GlobTomb4.pAdr->pVetSlot[491];
		if (pSlotNow->Flags & 0x01) {
			pSlotNow->Flags = 0x21;
			pSlotNow->pProcDraw = NULL;
			pSlotNow->pProcInitialise = &InitializeFishGenerator;
			pSlotNow->pProcControl = &TriggerFish;
		}

		// inizializza enemy mini sub
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[486];
		if (pSlotNow->Flags & 0x01) {
			InitSlotEnemySubMarine();

			// inizializza anche versone MIP
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[487];
			pSlotNow->Flags |= 0x20;

			// inizializza isslile torpedo
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[488];
			pSlotNow->Flags = 0x229;
			pSlotNow->pProcControl = &TorpedoControl;
		}

		// inizializza omino subacueo uomo rana frog man con arpione
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[489];
		if (pSlotNow->Flags & 0x01) {
			pSlotNow->pProcControl = &DiverControl;
			pSlotNow->pProcCollision = tomb4::CreatureCollision;
			pSlotNow->FootStep = 0x80;
			pSlotNow->Vitality = 0x14;
			pSlotNow->ss_Unknown3 = 0x155;
			pSlotNow->Flags |= 0x17A;
			pSlotNow->DistanceForMIP  = 0;
			pSlotNow->DistanceDetectLara = 0x0a;
		}
		// inizializza arpione usato da omino, ma potrebbe servire
		// anche perlanciare altra roba contro lara
		pSlotNow = &GlobTomb4.pAdr->pVetSlot[490];
		if (pSlotNow->Flags & 0x0001) {
			pSlotNow->pProcControl = &ControlBubble;
		}
		// --- tenere alla fine di inizializza nuovi slot ----------------
		if (EsisteDirectCB(CB_INIT_OBJECTS, CBT_ANY)) {
			pRec = &MyGlobPrivate.DataBase.pVetPlugins[1];
			for (i = 1; i < (int) MyGlobPrivate.DataBase.TotPlugins; i++) {
				if (pRec->VetDirectCB[CB_INIT_OBJECTS]) {
					CallInitObjects = (CALL_VOID) pRec->VetDirectCB[CB_INIT_OBJECTS];
					CallInitObjects();
				}
				pRec++;
			}
		}
		// --------------------- FINE INIZIALIZZA NUOVI SLOT ---------

		RiassegnaAssignSlotNew();

		GlobTomb4.BaseEnemiesNotAimable.TotSlot = 0;

		// ----------------- MODIFICA Enemy ------------------------
		// effettuare modifiche di Enemy
		for (i = 0; i < GlobTomb4.BaseEnemys.TotEnemy; i++) {
			pEnemy = &GlobTomb4.BaseEnemys.VetEnemy[i];
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[pEnemy->SlotId];
			IndiceSlot = pEnemy->SlotId;

			// qui bisognera' fare per damage

			if (pEnemy->TombFlags != SCRIPT_IGNORE)
				pSlotNow->Flags = pEnemy->TombFlags;

			if (pEnemy->Health != SCRIPT_IGNORE)
				pSlotNow->Vitality = pEnemy->Health;
			// ora analisi flag speciali ncf
			if (pEnemy->FlagsNEF != NEF_NONE) {
				FlagSlot = pSlotNow->Flags;
				// settare risposta al rimbalzo
				if ((pEnemy->FlagsNEF & NEF_HIT_DEFAULT) == 0) {
					NewFlags = pEnemy->FlagsNEF & (NEF_HIT_BLOOD | NEF_HIT_SMOKE | NEF_HIT_FRAGMENTS);
					FlagSlot &= ~0x0c00;
					FlagSlot |= NewFlags;
				}

				if (pEnemy->FlagsNEF & NEF_NON_TARGET) {
					// salvare lo slot di questo enemy da non puntare
					// memorizzare IndiceSlot nella lista dei nemici
					// non puntabili
					// a meno che non fosse gia' stato salvato
					for (j = 0; j < GlobTomb4.BaseEnemiesNotAimable.TotSlot; j++) {
						if (IndiceSlot == GlobTomb4.BaseEnemiesNotAimable.VetSlotNonPuntabili[j])
							break;
					}
					if (j == GlobTomb4.BaseEnemiesNotAimable.TotSlot) {
						GlobTomb4.BaseEnemiesNotAimable.VetSlotNonPuntabili[j] = IndiceSlot;
						GlobTomb4.BaseEnemiesNotAimable.TotSlot++;
					}
				}
				if (pEnemy->FlagsNEF & NEF_SET_AS_CREATURE) {
					// imposta come se fosse una creature
					if (pEnemy->Health == SCRIPT_IGNORE) {
						pSlotNow->Vitality = 0x30;
					}
					FlagSlot |= 0x72;
				}
				if ((pEnemy->FlagsNEF & (NEF_ONLY_EXPLODE | NEF_SET_AS_SEMIGOD)) != 0) {
					FlagSlot |= 0x1000;
				}
				if (pEnemy->FlagsNEF & NEF_SAVE_MESH_VISIBILITY) {
					FlagSlot |= 0x2000;
				}

				if (pEnemy->FlagsNEF & NEF_SET_AS_MORTAL) {
					FlagSlot &= ~0x1000;
				}

				if (pEnemy->FlagsNEF & NEF_SET_AS_BRIDGE_FLAT) {
					// trasformare questo slot in bridge flat
					FlagSlot = 0x0200;
					pSlotNow->Vitality = -0x4000;
					pSlotNow->ss_Unknown3 = 0x0a;
					pSlotNow->pProcControl = NULL;
					pSlotNow->pProcCollision = NULL;
					pSlotNow->pProcDrawExtras = NULL;

					pSlotNow->pProcFloor = tomb4::BridgeFlatFloor;
					pSlotNow->pProcCeiling = tomb4::BridgeFlatCeiling;
					pSlotNow->pProcDraw = tomb4::DrawAnimatingItem;
				}
				if (pEnemy->FlagsNEF & NEF_SET_AS_BRIDGE_TILT1) {
					// trasformare questo slot in bridge tilt1
					FlagSlot = 0x0200;
					pSlotNow->Vitality = -0x4000;
					pSlotNow->ss_Unknown3 = 0x0a;
					pSlotNow->pProcControl = NULL;
					pSlotNow->pProcCollision = NULL;
					pSlotNow->pProcDrawExtras = NULL;

					pSlotNow->pProcFloor = tomb4::BridgeTilt1Floor;
					pSlotNow->pProcCeiling = tomb4::BridgeTilt1Ceiling;
					pSlotNow->pProcDraw = tomb4::DrawAnimatingItem;
				}
				if (pEnemy->FlagsNEF & NEF_SET_AS_BRIDGE_TILT2) {
					// trasformare questo slot in bridge tilt2
					FlagSlot = 0x0200;
					pSlotNow->Vitality = -0x4000;
					pSlotNow->ss_Unknown3 = 0x0a;
					pSlotNow->pProcControl = NULL;
					pSlotNow->pProcCollision = NULL;
					pSlotNow->pProcDrawExtras = NULL;

					pSlotNow->pProcFloor = tomb4::BridgeTilt2Floor;
					pSlotNow->pProcCeiling = tomb4::BridgeTilt2Ceiling;
					pSlotNow->pProcDraw = tomb4::DrawAnimatingItem;
				}

				pSlotNow->Flags = FlagSlot;
			}
		}

		// modifica gli eventuali oggetti enemy per quel che riguarda damage
		ImpostaEnemyDamage();
	}

	void SetSlotMotorBoat(WORD SlotBoat, WORD SlotLaraBoat)
	{
		__try { throw __func__; } __finally {}
	}

	// imposta tutte le procedure necessarie nei due slot
	// per rubber boat
	void SetSlotRubberBoat(WORD SlotBoat, WORD SlotLaraBoat)
	{
		__try { throw __func__; } __finally {}
	}

	// inizializza il nuovo slot extra per le animazioni di lara sulla moto
	void SetSlotMotorBikeLara(void)
	{
		__try { throw __func__; } __finally {}
	}

	void InitSlotKayak(void)
	{
		__try { throw __func__; } __finally {}
	}

	void InitSlotHydra(void)
	{
		__try { throw __func__; } __finally {}
	}

	void InitSlotEnemySubMarine(void)
	{
		__try { throw __func__; } __finally {}
	}

	// restituisce true se c'e' una richiesta per la callback CB_Numero fornita.
	// NOTA: funziona SOLO per le direct cb ossia CB_  < MAX_DIRECT_CB
	// flags puo essere CBT_FIRST, CBT_AFTER, CBT_REPLACE o anche CBT_ANY
	bool EsisteDirectCB(int CB_Numero, WORD Flags)
	{
		if (MyGlobPrivate.DataBase.TotPlugins < 2)
			return false;
		if (MyGlobPrivate.BaseVetCbFirstAfter.VetDirectCB[CB_Numero] & Flags)
			return true;
		return false;
	}

	void RiassegnaAssignSlotNew(void)
	{
		__try { throw __func__; } __finally {}
	}

	// receive in input absolute slot value of some moveable and returns the further reassigned slot
	// in the case there was no AssignSlot for that slot, it will return the same SlotNow value
	WORD ConvertiSlotAssigned(WORD SlotNow)
	{
		int i;

		for (i = 0; i < GlobTomb4.BaseAssignSlot.TotNewAssign; i++) {
			if (GlobTomb4.BaseAssignSlot.VetNewAssign[i].MioSlot == SlotNow) {
				return GlobTomb4.BaseAssignSlot.VetNewAssign[i].TipoSlot;
			}
		}
		return SlotNow;
	}

	// verfica se nemico di tipo Slot aveva flag per esplosione
	bool IsNemicoEsploso(WORD SlotId)
	{
		int i;
		StrRecordEnemyScript *pEnemy;
		int TotEnemy;

		// se gia' esiste il flag in slot per morte solo con esplosione (come
		// scheletri o mummia) dire si
		if (GlobTomb4.pAdr->pVetSlot[SlotId].Flags & 0x1000)
			return true;

		TotEnemy = GlobTomb4.BaseEnemys.TotEnemy;
		if (TotEnemy == 0)
			return false;
		pEnemy = &GlobTomb4.BaseEnemys.VetEnemy[0];

		for (i = 0; i < TotEnemy; i++) {
			if (SlotId == pEnemy->SlotId && (pEnemy->FlagsNEF & (NEF_EXPLODE_AFTER + NEF_EXPLODE + NEF_ONLY_EXPLODE)) != 0) {
				return true;
			}
			// fixed bug
			pEnemy++;
		}
		return false;
	}

	// chiamata prima di salvare in savegame gli item creati
	// deve contare quanti item verranno salvati e restituire quel numero
	WORD ContaItemCreatiDaSalvare(void)
	{
		StrItemTr4 *pItem;
		int i;
		int TotItems;
		WORD TotNuovi;

		TotItems = BaseGlobMisc.TotItemOlds + 256;
		if (TotItems > 1024)
			TotItems = 1024;
		TotNuovi = 0;

		for (i = BaseGlobMisc.TotItemOlds; i < TotItems; i++) {
			pItem = &GlobTomb4.pAdr->pVetItems[i];
			if (DaSalvare(pItem) != -1) {
				TotNuovi++;
			}
		}

		return TotNuovi;
	}

	// analizza se questo e' uno degli oggetti da salvare
	// esclude dardi e scarabeo meccanico
	// se e' flare restiuiwce 0
	// se e' torcia restituisce 1
	// se e' un altro oggetto restituisce 2
	// se non e' da salvare restituisce -1
	short DaSalvare(StrItemTr4 *pItem)
	{
		WORD Slot;

		Slot = pItem->SlotID;
		if ((pItem->FlagsMain & 1) == 0) {
			// non e' stato attivato ma se e' un pushable o un animating salvarlo ugualmente
			if (SlotSempreAttivo(Slot) == false)
				return -1;
		}

		switch (Slot) {
		case 0x174:
			// flare
			return 0;
		case 0xf7:
			// torcia
			return 1;
		case 0xf8:
			// scarabeo meccanico
			return -1;

		case 0x72:
			// dardo
			return -1;
		}

		return 2;
	}

	bool SlotSempreAttivo(WORD Slot)
	{
		// se e' uno slot di quegli oggetti che non vanno attivati ma sono sempre attivi
		// allora restituire true
		// se rope polerope firerope o raising block o pushable objects
		if (Slot >= 146 && Slot <= 160)
			return true;

		// se animatings
		if (Slot >= 427 && Slot <= 458)
			return true;

		return false;
	}

	void SalvaItemCreati(void)
	{
		StrItemTr4 *pItem;
		int i;
		int TotItems;
		TYPE_SalvaInBuffer SalvaInBuffer;
		short Tipo;

		SalvaInBuffer = (TYPE_SalvaInBuffer) tomb4::WriteSG;
		TotItems = BaseGlobMisc.TotItemOlds + 256;
		if (TotItems > 1024)
			TotItems = 1024;

		for (i = BaseGlobMisc.TotItemOlds; i < TotItems; i++) {
			pItem = &GlobTomb4.pAdr->pVetItems[i];
			Tipo = DaSalvare(pItem);

			if (Tipo != -1) {
				// salvare il tipo di dato
				SalvaInBuffer(&Tipo, 1);
				// coordinate e orientamneto
				SalvaInBuffer(&pItem->CordX, 0x12);
				// room
				SalvaInBuffer(&pItem->Room, 2);
				// velocita' orizzontale
				SalvaInBuffer(&pItem->SpeedH, 2);
				// velocita' verticale
				SalvaInBuffer(&pItem->SpeedV, 2);

				// valori diversi a seconda di tipo
				switch (Tipo) {
				case 0:
					// flare
					SalvaInBuffer(&pItem->pZonaSavegame, 4);
					break;
				case 1:
					// torcia
					SalvaInBuffer(&pItem->Reserved_3A, 2);
					break;
				case 2:
					// tutti gli altri item
					// slot
					SalvaInBuffer(&pItem->SlotID, 2);
					// health
					SalvaInBuffer(&pItem->Health, 2);
					// object timer e object buttons
					SalvaInBuffer(&pItem->ObjectTimer, 4);
					// flagsmain
					SalvaInBuffer(&pItem->FlagsMain, 4);
					// meshvisibilitymask
					SalvaInBuffer(&pItem->MeshVisibilityMask, 4);

					// tutti e 4 i valori reserved
					SalvaInBuffer(&pItem->Reserved_34, 8);
					// state id, state next, stateid ai, animazione e frame
					SalvaInBuffer(&pItem->StateIdCurrent, 10);
					break;
				}
			}
		}
	}

	// a differenza dei valori di InizializzaAdrGlobali() gli indirizzi iniializzati da questa procedura
	// sono immediatamente disponibili visto che puntano a tomb4 e non conterranno un puntatore di memoria

	void InizializzaAdrImmediati(void)
	{
		StrAdrCamera *pCam;

		GlobTomb4.pAdr->pTotRooms = (WORD *) &tomb4::number_rooms;
		GlobTomb4.pAdr->pVetSlot = (StrSlot*) tomb4::objects;
		GlobTomb4.pAdr->VetMeshLara = (StrMeshTr4 **) tomb4::lara.mesh_ptrs;

		GlobTomb4.pAdr->pTotItemsAtBegin = (int*) &tomb4::level_items;
		GlobTomb4.pAdr->pTotItems = (int*) &tomb4::level_items;
		GlobTomb4.pAdr->pVetInputKeyboard = (BYTE*) tomb4::keymap;
		GlobTomb4.pAdr->pVetSfxSoundInfos = (StrZonaSound*) tomb4::LaSlot;

		GlobTomb4.pAdr->pInventory = (StrInventoryItems *) &tomb4::lara.pistols_type_carried;
		// variabili
		GlobTomb4.pAdr->pFlagsLaraHands = (WORD *) &tomb4::lara.gun_status;
		GlobTomb4.pAdr->pObjInLaraHandsNow = (WORD*) &tomb4::lara.gun_type;
		GlobTomb4.pAdr->pObjInLaraHandsNext = (WORD*) &tomb4::lara.request_gun_type;
		GlobTomb4.pAdr->pRopeNowIndex = (int *) &tomb4::lara.RopePtr;
		GlobTomb4.pAdr->p2CurrentEnemyTarget = (StrItemTr4 **) &tomb4::lara.target;
		GlobTomb4.pAdr->pWeaponSelected = (WORD *) &tomb4::lara.last_gun_type;
		GlobTomb4.pAdr->pDashBarValue = &tomb4::DashTimer;
		GlobTomb4.pAdr->pVetDrip = tomb4::lara.drip;
		GlobTomb4.pAdr->pWeaponHolding = &tomb4::lara.weapon_item;
		GlobTomb4.pAdr->pInputExtGameCommands = (DWORD*) &tomb4::linput;
		GlobTomb4.pAdr->pLaraIndex = (WORD *) &tomb4::lara.item_number;
		GlobTomb4.pAdr->pTimerScreen = (int*) &tomb4::savegame.Level.Timer;
		GlobTomb4.pAdr->pFlagsLara = (BYTE *) &tomb4::lara.bitfield;
		GlobTomb4.pAdr->pFlagsLara2 = (BYTE*) ((char *) &tomb4::lara.bitfield + 1);
		GlobTomb4.pAdr->pInputGameCommands = (WORD*) &tomb4::input;
		GlobTomb4.pAdr->pLaraLocationFlags = (WORD*) &tomb4::lara.water_status;
		GlobTomb4.pAdr->pSlopeType = (int *) &tomb4::height_type;
		GlobTomb4.pAdr->pSlopeX = (int *) &tomb4::tiltyoff;
		GlobTomb4.pAdr->pSlopeZ = (int *) &tomb4::tiltxoff;
		GlobTomb4.pAdr->pSizeScreenX = (short*) &tomb4::phd_winwidth;
		GlobTomb4.pAdr->pSizeScreenY = (short*) &tomb4::phd_winheight;
		GlobTomb4.pAdr->pRowCharHeight = (short*) &tomb4::font_height;
		GlobTomb4.pAdr->pEarthQuake = (int*) &tomb4::camera.bounce;
		GlobTomb4.pAdr->pWindowHandle = &tomb4::App.hWnd;
		GlobTomb4.pAdr->pScriptLevelFlags = &tomb4::gfLevelFlags;
		GlobTomb4.pAdr->pLevelNow = &tomb4::gfCurrentLevel;
		GlobTomb4.pAdr->pTotSecrets = &tomb4::savegame.Game.Secrets;
		GlobTomb4.pAdr->pAirAvailable = &tomb4::lara.air;
		GlobTomb4.pAdr->pPoison1 = (WORD *) &tomb4::lara.poisoned;
		GlobTomb4.pAdr->pPoison2 = (WORD *) &tomb4::lara.dpoisoned;
		GlobTomb4.pAdr->pFrameCounter = (DWORD*) &tomb4::GnFrameCounter;
		GlobTomb4.pAdr->pTestFlybyInProgress = (int*) &tomb4::bUseSpotCam;
		GlobTomb4.pAdr->pTestLoadOrNewLevel = &tomb4::gfGameMode;

		GlobTomb4.pAdr->pSetting_MusicVolume = (int*) &tomb4::MusicVolume;
		GlobTomb4.pAdr->pSetting_SFXVolume = (int*) &tomb4::SFXVolume;
		GlobTomb4.pAdr->pSetting_SoundQuality = (int*) &tomb4::SoundQuality;

		// ---- globali per CAMERA -----------
		pCam = &GlobTomb4.pAdr->Camera;

		pCam->pSecondsTimerCamera = &tomb4::camera.timer;
		pCam->pIndexCameraNext = &tomb4::camera.number;
		pCam->pIndexCameraNow = &tomb4::camera.last;
		pCam->pModeCameraNext = (int*) &tomb4::camera.type;
		pCam->pModeCameraNow = (int*) &tomb4::camera.old_type;
		pCam->pTargetCameraNext = (StrItemTr4 **) &tomb4::camera.item;
		pCam->pTargetCameraNow = (StrItemTr4 **) &tomb4::camera.last_item;
		pCam->pButtonTriggerCamera = (WORD *) &tomb4::camera.speed;
		pCam->pTotCameras = (int *) &tomb4::number_cameras;

		pCam->pCameraSrc = (GAME_VECTOR *) &tomb4::camera.pos;

		pCam->pCameraTarget = (GAME_VECTOR *) &tomb4::camera.target;

		// ----- roba per sky layer ------
		GlobTomb4.pAdr->pColorLayer1 = (DWORD *) &tomb4::gfLayer1Col;
		GlobTomb4.pAdr->pColorLayer2 = (DWORD *) &tomb4::gfLayer2Col;
		GlobTomb4.pAdr->pSpeedLayer1 = (BYTE *) &tomb4::gfLayer1Vel;
		GlobTomb4.pAdr->pSpeedLayer2 = (BYTE *) &tomb4::gfLayer2Vel;
		GlobTomb4.pAdr->pVetLightningColors = tomb4::LightningRGB;
		GlobTomb4.pAdr->pVetLightningSourceColors = tomb4::LightningRGBs;
		GlobTomb4.pAdr->pVetSavegameItems = (BYTE *) &tomb4::lara.pistols_type_carried;
		GlobTomb4.pAdr->pVetAmmos = &tomb4::lara.num_pistols_ammo;

		GlobTomb4.pAdr->pVetCustObjectsHand = (StrCustDatiOggettoMano *) tomb4::PistolTable;

		GlobTomb4.pAdr->pVetRoomOfDestroyedShatter = (WORD *) tomb4::SmashedMeshRoom;
		GlobTomb4.pAdr->pVetStructOfDestroyedShatter = (StrMeshInfo**) tomb4::SmashedMesh;
		GlobTomb4.pAdr->pTotDestroyedShatters = (WORD *) &tomb4::SmashedMeshCount;
		GlobTomb4.pAdr->pAudioTrackLoop = (char *) &tomb4::CurrentAtmosphere;
		GlobTomb4.pAdr->pTestAudioTrackLoop = &tomb4::IsAtmospherePlaying;
		GlobTomb4.pAdr->pTestWorkingOnMoveables = &tomb4::InItemControlLoop;
		GlobTomb4.pAdr->pStartFog = &tomb4::FogStart;

		GlobTomb4.pAdr->pTestDisableFogBulbs = (BOOL *) &tomb4::GlobalFogOff;
		GlobTomb4.pAdr->pVehicleIndex = &tomb4::lara.vehicle;
		GlobTomb4.pAdr->pObjectActive = (int*) &tomb4::lara.GeneralPtr;

		GlobTomb4.pAdr->pFlareLifeTime = (WORD *) &tomb4::lara.left_arm.flash_gun;
		GlobTomb4.pAdr->pSetting_Volumetric = (BYTE *) &tomb4::App.Volumetric;

		GlobTomb4.pAdr->pVetStructInventoryItems = (StrDatoInventario *) tomb4::inventry_objects_list;
		GlobTomb4.pAdr->pVetFlagsInventoryItems = (WORD *) tomb4::options_table;
		GlobTomb4.pAdr->pZonaRecord30 = (int*) &tomb4::phd_mxptr;

		GlobTomb4.pAdr->pVetFish = (StrFish *) tomb4::Scarabs;
		GlobTomb4.pAdr->pInclinationType = (int *) &tomb4::height_type;
		GlobTomb4.pAdr->pInclinationX = (int *) &tomb4::tiltyoff;
		GlobTomb4.pAdr->pInclinationZ = (int *) &tomb4::tiltxoff;

		GlobTomb4.pAdr->pSetCameraHOrient = &tomb4::camera.target_angle;
		GlobTomb4.pAdr->pSetCameraVOrient = &tomb4::camera.target_elevation;
		GlobTomb4.pAdr->pSetCameraDistance = (short *) &tomb4::camera.target_distance;
		GlobTomb4.pAdr->pSetCameraSpeed = (WORD *) &tomb4::camera.speed;
		GlobTomb4.pAdr->pTestOverPlatform = (BOOL *) &tomb4::OnObject;

		GlobTomb4.pAdr->pTestLaserSight = (bool *) &tomb4::LaserSight;
		GlobTomb4.pAdr->pZoomFactor = (int *) &tomb4::BinocularRange;
		GlobTomb4.pAdr->pTestGrayScreen = (bool *) &tomb4::InventoryActive;
		GlobTomb4.pAdr->pTestLoading = (bool *) &tomb4::LevelLoadingThread.active;
		GlobTomb4.pAdr->pFadeScreen = (short *) &tomb4::bDisableLaraControl;
		GlobTomb4.pAdr->pCDTrackNow = (int *) &tomb4::XATrack;
		GlobTomb4.pAdr->pTestCdLoop = (int *) &tomb4::audio_play_mode;
		GlobTomb4.pAdr->pTotAIData = &tomb4::nAIObjects;

		GlobTomb4.pAdr->pTurnHLaraHeadEnd = &tomb4::lara.torso_y_rot;
		GlobTomb4.pAdr->pTurnVLaraHeadEnd = &tomb4::lara.torso_x_rot;
		GlobTomb4.pAdr->pTurnRLaraHeadEnd = &tomb4::lara.torso_z_rot;

		GlobTomb4.pAdr->pTurnHLaraHeadNow = &tomb4::lara.head_y_rot;
		GlobTomb4.pAdr->pTurnVLaraHeadNow = &tomb4::lara.head_x_rot;
		GlobTomb4.pAdr->pTurnRLaraHeadNow = &tomb4::lara.head_z_rot;

		GlobTomb4.pAdr->pFlashRed = (WORD*) &tomb4::FlashFadeR;
		GlobTomb4.pAdr->pFlashGreen = (WORD *) &tomb4::FlashFadeG;
		GlobTomb4.pAdr->pFlashBlue = (WORD *) &tomb4::FlashFadeB;
		GlobTomb4.pAdr->pFlashDurate = (WORD*) &tomb4::FlashFader;
		GlobTomb4.pAdr->pLevelNext = &tomb4::gfLevelComplete;
		GlobTomb4.pAdr->pInputCommandFlags = (DWORD *) &tomb4::dbinput;
		GlobTomb4.pAdr->pTotFlyBy = &tomb4::number_spotcams;

		GlobTomb4.pAdr->pFadeCurtain = (WORD *) &tomb4::FadeScreenHeight;
		*GlobTomb4.pAdr->pInclinationType = 0;
		GlobTomb4.pAdr->pInventoryChosenItem = (int *) &tomb4::GLOBAL_inventoryitemchosen;
		GlobTomb4.pAdr->pInventoryRequiredSlotItem = (int *) &tomb4::GLOBAL_enterinventory;
	}

	// chiamata solo una volta all'inizio del gioco imposta
	// i valori di default per tutti i valori customize, prima che venga letto il file script
	// con i nuovi eventuali customize
	void InitCustomize(void)
	{
		static WORD VetDefSlotColl[21] = {
			35 | HIT_PUSH_AWAY, // SKELETON
			37 | HIT_PUSH_AWAY, // GUIDE
			39 | HIT_PUSH_AWAY, // VON_CROY
			45 | HIT_PUSH_AWAY , //SETHA
			47 | HIT_PUSH_AWAY, // MUMMY
			49 | HIT_WALL, // SPHINX
			53 | HIT_WALL, // HORSEMAN
			55 | HIT_WALL, // SCORPION
			57 | HIT_PUSH_AWAY, // JEAN_YVES
			61 | HIT_WALL, // KNIGHTS_TEMPLAR
			63 | HIT_PUSH_AWAY, // MUTANT
			65 | HIT_WALL,  // HORSE
			77 | HIT_PUSH_AWAY | HIT_HURT, // DEMIGOD1
			79 | HIT_PUSH_AWAY | HIT_HURT, // DEMIGOD2
			81 | HIT_PUSH_AWAY | HIT_HURT, // DEMIGOD
			102 | HIT_PUSH_AWAY | HIT_HURT,  // AHME
			481 | HIT_WALL, // LASER_HEAD
			482 | HIT_WALL, // LASER_HEAD_BASE
			483 | HIT_WALL,  // LASER_HEAD_TENTACLE
			484 | HIT_HURT, // HYDRA
			0};

		StrBaseCustomize *pCust;
		StrCustAmmo *pAmmo;
		StrCustWeapon *pWeap;
		StrCustFlare *pFlare;
		BYTE *pVet;
		StrCustCamera *pCamera;
		StrBarraCust *pBar;
		StrCustLightItems *pLight;
		StrBaseHarpoon *pHarp;
		int i;

		pCust = GlobTomb4.pBaseCustomizeDefault;

		pCust->BugsToFix = 0;
		pCust->BaseSlotFlags.TotSlotFlags = 0;
		pCust->BaseShatterSpecific.TotSpecific = 0;
		pCust->TestDisabilitaDoppiaTesta = false;
		pCust->SecretsAmount = 70;
		pCust->CreditsLevel = 39;
		pCust->TestDisableAnim96 = false;
		pCust->ShatterInizio = 0x32;
		pCust->ShatterFine = 0x3b;
		pCust->SpeedMoving = 32;
		pCust->SlotChiaveJeep = 175;
		pCust->TrasparenzaGlass = 128; // ossia 50 %
		pCust->TrasparenzaIce = 208; // ossia 81 %
		pCust->DamageStatic = 10;
		pCust->PoisonStatic = 256;
		pCust->TestNoTransparencyLara = false;
		pCust->HairType = HAIR_NON_CAMBIARE;

		pCust->TestOldCDTrigger = false;
		pCust->TestEscapeFlyCamera = false;
		pCust->TastoEsciFlyCamera = 1; // escape
		pCust->TestPauseFlyCamera = false;
		pCust->TastoPauseFlyCamera = 25; // tasto p
		pCust->TestPrintOnFlyby = false;
		pCust->FlagsFMV = 0;
		pCust->TestKeepNemiciMorti = false;
		pCust->TestDisableMissingSounds = false;
		pCust->TestNoTimeInSaveList = false;
		pCust->ScreenShotInner.TestAddInnerShot = false;
		pCust->ScreenShotInner.FlagQSF = 1;
		pCust->TestFixWaterFogBug = false;
		pCust->TestSaveLocust = false;
		pCust->TestTr5Collisions = false;
		// inizializza dati per customiza cattura screenshot
		pCust->BaseCatturaShot.QaulitaImage = -1;
		pCust->BaseCatturaShot.FrameGap = 0;
		pCust->BaseCatturaShot.Secondi = 0;
		pCust->BaseCatturaShot.TestInCorso = false;

		// inizializza dati per customize still collision
		pCust->BaseStillCollision.Flags = 0;
		pCust->BaseStillCollision.LowerHeight = 300;
		for (i = 0; i < SLOT_NUMBER_OBJECTS; i++) {
			pCust->BaseStillCollision.VetSlotStillCollisions[i] = 0;
		}

		// default per arpione
		pHarp = &pCust->BaseHarpoon;
		pHarp->TestArpione = false;
		pHarp->ArpioneFlags = 0;
		pHarp->Distance = 0x480;
		pHarp->OrientX = 0x2000;
		pHarp->OrientY = 0x1000;
		pHarp->OrientZ = 0x0000;
		pHarp->HSpeed = -1;
		pHarp->TopY = -16;
		pHarp->Gravity = 24;

		// inizializzare valori per luci
		// amber light
		pLight = &pCust->AmberLight;
		pLight->Rosso = 0;
		pLight->Verde = 0;
		pLight->Blue = 0;
		pLight->Intensita = 18;
		pLight->Time = -2048;
		// white light
		pLight = &pCust->WhiteLight;
		pLight->Rosso = 0;
		pLight->Verde = 0;
		pLight->Blue = 0;
		pLight->Intensita = 16;
		pLight->Time = 160;
		// blinking time
		pLight = &pCust->BlinkingLight;
		pLight->Rosso = 255;
		pLight->Verde = 192;
		pLight->Blue = 16;
		pLight->Intensita = 16;
		pLight->Time = 30;

		pCust->TipoCDM = CDM_RESTORE_FROM_MIDDLE;
		pCust->BaseAddAnimMorte.TotCustAnimMorte = 0;
		pCust->ParallelBarFlags = 0;
		pCust->ParalledSpeedSlide = 6;
		pCust->ParallelMaxTurns = 10;
		// inizializzare dati per camera customize
		pCamera = &pCust->CameraCust;
		pCamera->ChaseDistance = 0x600;
		pCamera->ChaseHeight = -1820;
		pCamera->ChaseHOrient = 0;

		pCamera->CombatDistance = 0x600;
		pCamera->CombatHeight = -2730;
		pCamera->Flags = 0;
		pCamera->LookDistance = -1024;
		pCamera->LookHeight = 16;
		pCamera->Speed = 10;

		// dati per barre ------------
		for (i = 0; i < BAR_CUST_TOT; i++) {
			pBar = &pCust->VetBar[i];
			pBar->Flags = 0;
			pBar->Color1 = GlobTomb4.VetBarDefault[i].DefColor1;
			pBar->Color2 = GlobTomb4.VetBarDefault[i].DefColor2;
			pBar->OrgX = -1;
			pBar->OrgY = -1;
			pBar->Extra = -1;

			if (i != BAR_LOAD_LEVEL) {
				pBar->SizeX = 150;
				pBar->SizeY = 12;
			} else {
				pBar->SizeX = 600;
				pBar->SizeY = 15;
			}
		}

		// dati custom per spingi rolling ball ------
		pCust->RollingBallPush.Animation = 316;
		pCust->RollingBallPush.AnimFallito = 120;
		pCust->RollingBallPush.FrameStartPush = 20;
		pCust->RollingBallPush.FrameStartActivation = 50;
		pCust->RollingBallPush.FrameInvulnerabile = 30;
		pCust->RollingBallPush.SpeedPushing = 6;
		pCust->RollingBallPush.Distance = 600;

		// valori default per new sound engine -----------
		pCust->BassDll.Flags = 0;
		pCust->BassDll.Frequenza = 44100;
		pCust->BassDll.TipoEstensione = SEXT_WAV;
		pCust->BassDll.TimeFadeOut = 1000;
		pCust->BassDll.TimeFadeOutCorto = 300;

		// ---- imposta tutti i valori di munizioni per ogni scatola raccolta ---

		pCust->AmmoFucileNormale.Pickup = 6*6;
		pCust->AmmoFucilePotenziate.Pickup = 6*6;
		pCust->AmmoFucileNormale.PickupRegalo = 6*6;

		pCust->AmmoBalestraNormali.Pickup = 10;
		pCust->AmmoBalestraNormali.PickupRegalo = 10;
		pCust->AmmoBalestraEsplosive.Pickup = 10;
		pCust->AmmoBalestraVelenose.Pickup = 10;

		pCust->AmmoRevolver.Pickup = 6;
		pCust->AmmoRevolver.PickupRegalo = 6;

		pCust->AmmoGranateNormali.Pickup = 10;
		pCust->AmmoGranateEsplosive.Pickup = 4;
		pCust->AmmoGranateLuminose.Pickup = 4;
		pCust->AmmoGranateNormali.PickupRegalo = 10;

		pCust->AmmoPistols.Pickup = -1;
		pCust->AmmoPistols.PickupRegalo = -1;

		pCust->AmmoUZI.Pickup = 30;
		pCust->AmmoUZI.PickupRegalo = 30;

		// imposta default per tutte le ammo  --------------
		// Pistole
		pAmmo = &pCust->AmmoPistols;
		pAmmo->DamageNormale = 1;
		pAmmo->Flags = 0;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Extra = -1;
		// relvolver
		pAmmo = &pCust->AmmoRevolver;
		pAmmo->DamageNormale = 21;
		pAmmo->Flags = 0;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Extra = -1;

		// UZI
		pAmmo = &pCust->AmmoUZI;
		pAmmo->DamageNormale = 1;
		pAmmo->Flags = 0;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Extra = -1;

		// Fucile normale
		pAmmo = &pCust->AmmoFucileNormale;
		pAmmo->DamageNormale = 3;
		pAmmo->Flags = 0;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Extra = -1;

		// fucile potenziate
		pAmmo = &pCust->AmmoFucilePotenziate;
		pAmmo->DamageNormale = 3;
		pAmmo->Flags = 0;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Extra = -1;

		// granate normale
		pAmmo = &pCust->AmmoGranateNormali;
		pAmmo->DamageNormale = 20;
		pAmmo->DamageEsplosivo = 30;
		pAmmo->Flags = 0;
		pAmmo->Gravity = -1;  // vuol dire NON modificarla
		pAmmo->IdAddEffect = -1;
		pAmmo->IdTriggerAtEnd = -1;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Speed = 128;
		pAmmo->Extra = -1;

		// granate potenziate

		pAmmo = &pCust->AmmoGranateEsplosive;
		pAmmo->DamageNormale = 20;
		pAmmo->DamageEsplosivo = 30;
		pAmmo->Flags = 0;
		pAmmo->Gravity = -1;
		pAmmo->IdAddEffect = -1;
		pAmmo->IdTriggerAtEnd = -1;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Speed = 128;
		pAmmo->Extra = -1;

		// granate luminose
		pAmmo = &pCust->AmmoGranateLuminose;
		pAmmo->DamageNormale = 0;
		pAmmo->DamageEsplosivo = 0;
		pAmmo->Flags = 0;
		pAmmo->Gravity = -1;
		pAmmo->IdAddEffect = -1;
		pAmmo->IdTriggerAtEnd = -1;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Speed = 128;
		pAmmo->Extra = -1;

		// balestra normali
		pAmmo = &pCust->AmmoBalestraNormali;
		pAmmo->DamageEsplosivo = 0;
		pAmmo->DamageNormale = 5;
		pAmmo->Flags = 0;
		pAmmo->Gravity = -1;
		pAmmo->IdAddEffect = -1;
		pAmmo->IdTriggerAtEnd = -1;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Speed = 512;
		pAmmo->Extra = -1;

		//  balestra esplosive
		pAmmo = &pCust->AmmoBalestraEsplosive;
		pAmmo->DamageEsplosivo = 30;
		pAmmo->DamageNormale = 0;
		pAmmo->Flags = 0;
		pAmmo->Gravity = -1;
		pAmmo->IdAddEffect = -1;
		pAmmo->IdTriggerAtEnd = -1;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Speed = 512;
		pAmmo->Extra = -1;

		// balestra velenose
		pAmmo = &pCust->AmmoBalestraVelenose;
		pAmmo->DamageEsplosivo = 1; // e' quota di veleno
		pAmmo->DamageNormale = 5;
		pAmmo->Flags = 0;
		pAmmo->Gravity = -1;
		pAmmo->IdAddEffect = -1;
		pAmmo->IdTriggerAtEnd = -1;
		pAmmo->IdTriggerHitEnemy = -1;
		pAmmo->Speed = 512;
		pAmmo->Extra = -1;

		// ------------ WEAPONS ------------
		// pistole
		pWeap = &pCust->WeaponPistols;
		memset(pWeap, sizeof(StrCustWeapon), 0);

		pWeap->Dispersion = 1456;
		pWeap->DistanceAiming = 8192;
		pWeap->FrameCounter = 4;
		pWeap->FrameMinRange = 5;
		pWeap->FrameMaxRange = 0x18;
		pWeap->FramesRicarica = 9;
		pWeap->FrameToTakeWeapon = 0x0d;
		pWeap->FrameToLetWeapon = 0x0d;
		pWeap->SizeShell = 3;
		pWeap->SoundShot = 8;
		pWeap->Unknow = 0x71c;
		pWeap->VPositionOfWeapon = 650;
		// REVOLVER
		pWeap = &pCust->WeaponRevolver;
		memset(pWeap, sizeof(StrCustWeapon), 0);

		pWeap->Dispersion = 728;
		pWeap->DistanceAiming = 8192;
		pWeap->FrameCounter = 7;
		pWeap->FrameMinRange = 8;
		pWeap->FrameMaxRange = 0x1d;
		pWeap->FramesRicarica = 16;
		pWeap->FrameToTakeWeapon = 0x0f;
		pWeap->FrameToLetWeapon = 0x0f;
		pWeap->SizeShell = 3;
		pWeap->SoundShot = 121;
		pWeap->Unknow = 0x71c;
		pWeap->VPositionOfWeapon = 650;
		// UZI
		pWeap = &pCust->WeaponUzi;
		memset(pWeap, sizeof(StrCustWeapon), 0);

		pWeap->Dispersion = 728;
		pWeap->DistanceAiming = 8192;
		pWeap->FrameCounter = 4;
		pWeap->FrameMinRange = 5;
		pWeap->FrameMaxRange = 0x18;
		pWeap->FramesRicarica = 3;
		pWeap->FrameToTakeWeapon = 0x0d;
		pWeap->FrameToLetWeapon = 0x0d;
		pWeap->SizeShell = 3;
		pWeap->SoundShot = 43;
		pWeap->Unknow = 0x71c;
		pWeap->VPositionOfWeapon = 650;
		// fucile
		pWeap = &pCust->WeaponFucile;
		memset(pWeap, sizeof(StrCustWeapon), 0);
		pWeap->Dispersion = 0;
		pWeap->DistanceAiming = 8192;
		pWeap->FrameToTakeWeapon = 10;
		pWeap->FrameToLetWeapon = 21;
		pWeap->SizeShell = 3;
		pWeap->SoundShot = 45;
		pWeap->Unknow = 0x71c;
		pWeap->VPositionOfWeapon = 500;

		// balestra
		pWeap = &pCust->WeaponBalestra;
		memset(pWeap, sizeof(StrCustWeapon), 0);
		pWeap->Dispersion = 1456;
		pWeap->DistanceAiming = 8192;
		pWeap->FrameToTakeWeapon = 10;
		pWeap->FrameToLetWeapon = 21;
		pWeap->SizeShell = 2;
		pWeap->SoundShot = -1;
		pWeap->Unknow = 0x71c;
		pWeap->VPositionOfWeapon = 500;
		// lancia granate
		pWeap = &pCust->WeaponLanciaGranate;
		memset(pWeap, sizeof(StrCustWeapon), 0);
		pWeap->Dispersion = 1456;
		pWeap->DistanceAiming = 8192;
		pWeap->FrameToTakeWeapon = 10;
		pWeap->FrameToLetWeapon = 21;
		pWeap->SizeShell = 2;
		pWeap->SoundShot = -1;
		pWeap->Unknow = 0x71c;
		pWeap->VPositionOfWeapon = 500;

		pCust->BaseInvItems.TotInvItems = 0;
		pCust->ShowAmmoCounter.TestShowAmmoCounter = false;
		pCust->ShowAmmoCounter.Flags = 0;
		// - defautl per flare
		pFlare = &pCust->BaseFlare;

		pFlare->Flags = 0;
		pFlare->Durata = 30 * FRAME_SECONDO;
		pFlare->Rosso = 128;
		pFlare->Verde = 192;
		pFlare->Blu = 0;
		pFlare->Intensita = 16;
		pFlare->Valore810 = 810;
		pFlare->Valore876 = 876;

		// colori tipi di testo
		pVet = &pCust->VetTTColors[0];

		pVet[TT_ITEM_NAME] = 8;
		pVet[TT_ACTION_INVENTORY_MENU_OFF] = 5;
		pVet[TT_ACTION_INVENTORY_MENU_ON] = 1;
		pVet[TT_AMMO] = 8;
		pVet[TT_EXAMINE1_TOP] = 5;
		pVet[TT_EXAMINE1_BOTTOM] = 5;
		pVet[TT_EXAMINE3] = 8;
		pVet[TT_SELECT_LEVEL] = 6;
		pVet[TT_NEW_LEVEL_ARROWS] = 6;
		pVet[TT_LEVEL_NAME_OFF] = 2;
		pVet[TT_LEVEL_NAME_ON] = 1;
		pVet[TT_MAIN_MENU_OFF] = 2;
		pVet[TT_LEGEND] = 2;
		pVet[TT_CREDITS] = 2;
		pVet[TT_SCREEN_TIMER] = 0;
		pVet[TT_SAVEGAME_PANEL_TITLE] = 6;
		pVet[TT_SAVEGAME_DESCRIPTION_ON] = 1;
		pVet[TT_SAVEGAME_DESCRIPTION_OFF] = 2;

		pVet[TT_OPTION_DESCRIPTIONS] = 2;
		pVet[TT_OPTION_VALUES] = 6;
		pVet[TT_STATISTICS_DESCRIPTIONS] = 2;
		pVet[TT_STATISTICS_VALUES] = 6;
		pVet[TT_PAUSED_MENU_TITLE] = 6;
		pVet[TT_PAUSED_MENU_ITEMS] = 2;
		pVet[TT_MAIN_MENU_ON] = 1;
		pVet[TT_CAMERA_VIEW] = 6;

		pCust->WaterfallSpeed = -7;
		pCust->BaseRollScript.TotRollBoatScript = 0;

		// valori di default per suoni.
		pCust->VetCustSFX[TS_DIARY_CHANGE_PAGE] = 7;
		pCust->VetCustSFX[TS_DIARY_NO_PAGE] =  2;
		pCust->VetCustSFX[TS_DIARY_ZOOM_START] = 76;
		pCust->VetCustSFX[TS_SCREENSHOT_CAPTURE] = 9;
		pCust->VetCustSFX[TS_VIBRATE_RESUME_FROM_FROZEN] = 0;
		pCust->VetCustSFX[TS_AFTER_FALLING_AS_INVULNERABLE] = 1;
		pCust->VetCustSFX[TS_SAVEGAME_PANEL_SELECTED] = 109;
		pCust->VetCustSFX[TS_DAMAGE_ROOM_SCREAM_BURNING] = 0x1e;
		pCust->VetCustSFX[TS_DAMAGE_ROOM_BEEP_ALERT] = 0x70;
		pCust->VetCustSFX[TS_WHIRLPOOL_SINKED_LARA] = 33;
		pCust->VetCustSFX[TS_MISSING_REQUIRED_ITEM] = 2;
		pCust->VetCustSFX[TS_ANIMATING_DOOR_OPEN] = 162;
		pCust->VetCustSFX[TS_ANIMATING_DOOR_CLOSE] = 162;
		pCust->VetCustSFX[TS_DETECTOR_SHOW] = 0x27;
		pCust->VetCustSFX[TS_ELEVATOR_SQUASHED_LARA] = 0x1f;
		pCust->VetCustSFX[TS_MIST_EMITTER_WITH_OCB] = 0x4f;
		pCust->VetCustSFX[TS_PUSHED_ITEM_IMPACT] = 72;
		pCust->VetCustSFX[TS_BINOCULAR_ZOOM] = 309;
		pCust->VetCustSFX[TS_BINOCULAR_LIGHT] = 369;
		pCust->VetCustSFX[TS_SHOT_HARPOON_UW] = 68;

		pCust->TitleFmv = -1;
		pCust->TitleTestMultiply = false;
		pCust->TestDisablePushAway = false;
		pCust->CustBinoculars.TestPresente = false;

		pCust->BaseHpLara.LastHpValue = 1000;

		// inizializzare i vari enemy per la collisione con bike
		i = 0;
		while (VetDefSlotColl[i]) {
			pCust->BaseSlotCollideVehicles.VetSlotCollide[i] = VetDefSlotColl[i];
			i++;
		}
		pCust->BaseSlotCollideVehicles.TotSlotCollide = i;

		// trasferisce anche in valori correnti le impostazioni di default
		CustDefToCustNow();
	}

	// estrae da file language.dat attuale le eventuali extra strings
	// nota: viene chiamato da tomb4 quando si e' appena caricato il file
	// lingua.dat
	// pNomeFile contiene il file lingua nel formato "italian.dat" senza percorso

	void LeggiNG_LanguageDat(char *pNomeFile)
	{
		int i;
		int j;
		StrParseNGField  ParseField;
		WORD TotStrings;
		WORD NWords;
		char *pChar;

		// se era stato caricato un precedente languagedat con extra strings
		// liberare la memoria
		if (GlobTomb4.TotExtraStrings) {
			FreeMine(GlobTomb4.HeaderNG_Language.pNGArray);
			GlobTomb4.HeaderNG_Language.pNGArray = NULL;
		}

		GlobTomb4.TotExtraStrings = 0;

		// salvare nome lingua
		pChar = SoloNomeSenzaExt(pNomeFile);
		strcpy_s(GlobTomb4.LinguaNow, pChar);

		if (ExtractNGHeader(pNomeFile, &GlobTomb4.HeaderNG_Language) == false) {

			switch (GlobTomb4.HeaderNG_Language.Result) {
			case -2:

				sprintf_s(BufferLog, "ERROR: cann't open file: \"%s\" (to read extra ng header)", SoloNome(pNomeFile));

				InviaLog(BufferLog);

				return;
			case -1:

				InviaLog("WARNING: Extra NG Header appears corrupted");

				return;
			case 0:

				sprintf_s(BufferLog, "File %s has no extra strings", SoloNome(pNomeFile));

				InviaLog(BufferLog);

				return;
			}
		}

		InviaLog("Load extra ng strings");

		// scandire dati, saltando prima word di controllo "NG"
		i = 0;
		while (ParseNgField(GlobTomb4.HeaderNG_Language.pNGArray, i, &ParseField)) {

			// analizzare tipo di pacchetto
			switch (ParseField.Type) {
			case NGTAG_LANGUAGE_STRINGS:
				j = 0;
				TotStrings = ParseField.pData[j++];
				if (TotStrings >= 0x400) {

					sprintf_s(BufferLog, "WARNING: too much extra strings (%d). It will be loaded only first 1024 strings", TotStrings);
					InviaLog(BufferLog);

					TotStrings = 0x400;
				}
				GlobTomb4.TotExtraStrings = TotStrings;
				// caricare tutte le stringhe
				for (i = 0; i < TotStrings; i++) {
					// caricare indice di stringa
					GlobTomb4.VetExtraStrings[i].Indice = ParseField.pData[j++];
					// caricare numero di word che formano stringa
					NWords = ParseField.pData[j++];
					// salvare puntatore a stringa
					GlobTomb4.VetExtraStrings[i].pTesto = (char *) &ParseField.pData[j];
					DecryptDatString(GlobTomb4.VetExtraStrings[i].pTesto);

					j += NWords;
				}
				break;
			}
			// puntare a chunk successivo
			i = ParseField.NextIndex;
		}
		// se c'e' striga 666 imposta i valori scan code extra
		ImpostaScanCodeInputBox();
	}

	// modifica con xor 0xA5 il testo che corrisponde ad una delle extra
	// extra string di ng
	void DecryptDatString(char *pTesto)
	{
		DWORD i;

		for (i = 0; i < strlen(pTesto); i++) {
			pTesto[i] ^= 0xA5;
		}
	}

	// chiamato solo una volta (credo) appena caricate le extra ng strings.
	// imposta valori globali per InputBox con eventuali extra scan codes memorizzati in stringa "666"
	void ImpostaScanCodeInputBox(void)
	{
		char *pChar;
		char StrHex[10];
		int i;
		int j;
		bool TestErrore;
		char MioCar;
		bool TestPrimoByte;
		DWORD Valore;
		int z;
		StrBaseInputBox *pBase;
		int N;

		pBase = &GlobTomb4.BaseInputBoxes;

		pBase->TotExtraCodes = 0;
		z = 0;

		pChar = GetStringaNG(666);
		if (pChar == NULL)
			return;

		// verificare che il formato sia quello giusto
		i = 0;
		j = 0;
		TestErrore = false;
		// attendere primo byte
		TestPrimoByte = true;
		while (pChar[i]) {
			MioCar = pChar[i++];
			switch (MioCar) {
			case ' ':
				// ignorare spazio
				break;
			case ',':
				// separatore
				// dovremmo avere gia' completato l'inserimento di questo valore
				// verificare
				if (j != 0) {
					// errore di sintassi
					InviaLog("ERROR parsing 666 ng string. Syntax error: odd number of hex digits");
					pBase->TotExtraCodes = 0;
					return;
				}
				StrHex[0] = 0;
				j = 0;
				TestPrimoByte = true;

				break;
			default:
				// dovrebbe essere stringa hex
				StrHex[j] = MioCar;
				j++;
				if (j == 2) {
					// raggiunta coppia di caratteri
					StrHex[j] = 0;
					j = 0;

					Valore = GetValoreHex(StrHex, &TestErrore);
					if (TestErrore == true) {
						sprintf_s(BufferLog, "ERROR parsing extra 666 NG string, for extra scan codes for Input Boxes. Syntax error: \"%s\" is not a valid hexadecimal byte", StrHex);
						InviaLog(BufferLog);
						pBase->TotExtraCodes = 0;
						return;
					}

					// tradurre val byte hex
					if (TestPrimoByte == true) {
						// e' il byte ascii
						z = pBase->TotExtraCodes;
						pBase->TotExtraCodes++;
						pBase->VetExtraCodes[z].TotScanCodes = 0;

						pBase->VetExtraCodes[z].ValAscii = (BYTE) Valore;
						TestPrimoByte = false;
					} else {
						// e' uno degli scan code
						N = pBase->VetExtraCodes[z].TotScanCodes;

						if (N >= 3) {
							// errore
							sprintf_s(BufferLog, "Error parsing 666 ng string for input box: there are too  many scancodes in item %d of sequence", z + 1);
							InviaLog(BufferLog);
							pBase->TotExtraCodes = 0;
							return;
						}

						pBase->VetExtraCodes[z].VetScanCodes[N] = (BYTE) Valore;
						pBase->VetExtraCodes[z].TotScanCodes++;
					}
				}
				break;
			}
		}
		if (j != 0) {
			// errore di sintassi
			InviaLog("ERROR parsing 666 ng string. Syntax error: odd number of hex digits");
			pBase->TotExtraCodes = 0;
		}
	}

	// converte stringa hex (senza "0x" o "$" davanti) in valore numerico assoluto
	// se c'e' errore imposta pTestErrore=true
	DWORD GetValoreHex(char *pStringaHex, bool *pTestErrore)
	{
		DWORD Numero;

		if (sscanf_s(pStringaHex, "%X", &Numero) != 1) {
			// non convertito: errore
			*pTestErrore = true;
			return 0;
		}

		*pTestErrore = false;
		return Numero;
	}

	void * ReallocMine(void * pOldMem, DWORD NewSize, const char *pDescrizione)
	{
		__try { throw __func__; } __finally {}
	}

	// impostare roba per gestione capelli
	void ImpostaCapelliLara(WORD *pFlagLivello)
	{
		static BYTE VetCodaOld[12] = {0x25, 0x26, 0x27, 0x28, 0xFF, 0, 0, 0, 0, 0, 0, 0};
		static BYTE VetCodaNew[5] = {0x19, 0x1a, 0x1b, 0x1c, 0xff};

		int TipoHair;
		int i;
		int *pNuovoFlagCapelli;
		BYTE *pVetCodaCavallo;

		pNuovoFlagCapelli = &NuovoFlagCapelli;
		pVetCodaCavallo = (BYTE *) tomb4::HairSkinVertNums[0];  // DatiCodaCavallo

		TipoHair = GlobTomb4.pBaseCustomize->HairType;

		*pNuovoFlagCapelli = *pFlagLivello;

		// prima impostare sempre come default i valroi di coda di cavallo
		// vecchia
		for (i = 0; i < 5; i++) {
			pVetCodaCavallo[i] = VetCodaOld[i];
		}

		switch (TipoHair) {
		case HAIR_TWO_PLAITS:
			*pNuovoFlagCapelli = 1;
			break;
		case HAIR_ONE_PONYTAIL:
			*pNuovoFlagCapelli = 0;
			break;
		case HAIR_ONE_TR5_PONYTAIL:
			*pNuovoFlagCapelli = 0;
			for (i = 0; i < 5; i++) {
				pVetCodaCavallo[i] = VetCodaNew[i];
			}
			break;
		}
	}

	// riprstina priprita' normale per thread di gioco
	void RestorePriorita(void)
	{
		SetPriority(Normal_NORMAL);
	}

	void SalvaDimensioneSchermo(void)
	{
		tomb4::DXDISPLAYMODE *pDisplayMode;

		pDisplayMode = &tomb4::G_dxinfo->DDInfo[tomb4::G_dxinfo->nDD].D3DDevices[tomb4::G_dxinfo->nD3D].DisplayModes[tomb4::G_dxinfo->nDisplayMode];
		GlobTomb4.ScreenSizeY = (short) pDisplayMode->h;
		GlobTomb4.ScreenSizeX = (short) pDisplayMode->w;
	}

	// funziona come PreparaCustomize ma lavora solo per barre
	// e deve essere chiamata prima di caricamento livello
	void PreparaBarCust(void)
	{
		StrPtrBars *pBarDef;
		StrBarraCust *pBar;
		int OrgY;
		int i;

		// inizializza colore e dimensione per barre
		for (i = BAR_HEALTH; i < BAR_CUSTOM1; i++) {
			pBar = &GlobTomb4.pBaseCustomize->VetBar[i];
			pBarDef = &GlobTomb4.VetBarDefault[i];
			// calcolare orgy
			if (pBar->OrgY != -1) {
				OrgY = (int) RapportoFloatSchermo(*GlobTomb4.pAdr->pSizeScreenY, (float) 480, pBar->OrgY);
				pBar->OrgYUpdated = (short) OrgY;
			}

			*pBarDef->pColor1 = pBar->Color1 | 0xff000000;
			*pBarDef->pColor2 = pBar->Color2 | 0xff000000;

			InviaLog(BufferLog);

			*pBarDef->pSizeX = pBar->SizeX;

			*pBarDef->pSizeY = pBar->SizeY;
		}
		// inizializza valori anche per customize bar
		for (i = BAR_CUSTOM1; i <= BAR_CUST_TOT; i++) {
			pBarDef = &GlobTomb4.VetBarDefault[i];
			pBarDef->DefColor1 = 0xff0000ff;
			pBarDef->DefColor2 = 0xFF000000;

			switch (i) {
			case BAR_DAMAGE:
				pBarDef->DefColor1 = 0xffF6F923;
				break;
			case BAR_COLD:
				pBarDef->DefColor1 = 0xfff924f1;
				break;
			}
		}
	}

	// suona un cd con bass senza usare in alcun
	// modo, ne' influenzare, la gestione dei suoni di tomb
	// il numero di canale dovrebbe partire da 2 fino a 4
	void PlayExtraCD(short NumeroCd, int Canale, int Loop)
	{
		if (GlobTomb4.BaseBassHandles.TestPresente == false)
			return;
		GlobTomb4.BaseBassHandles.CanaleNow = Canale;
		GestioneCdPlay(NumeroCd, Loop);
	}

	// sostituisce S_CDPlay quando e' attivo bass
	// puo' essere chiamata direttamnte da codice tomb4
	// o da miei flipeffect
	// se in NumeroCd c'e' il bit 0x4000 attivo vuol dire che l'indice
	// riguarda un file Preload di script.dat
	// usa sempre il primo canale, a meno che:
	// il suono non sia di tipo loop=0
	// oppure
	// e' stato impostato il valore "1"  in GlobTomb4.Basess.CanaleNow
	// se c'era gia' un suono nel canale usato effettua un fadeout
	// per il suono precedente.
	// NOTA: chiamata da ogni parte del codice e questa funzione gestisce le callback per la funzione
	// effettiva SubGestionePlayCd()
	void GestioneCdPlay(short NumeroCd, int Loop)
	{
		int IndiceCanale;
		int IndiceSuono;
		char NomeFile[80];
		int i;
		DWORD Flags;
		StrImportFile *pImpFile;
		int FadeOut;
		int j;
		StrCanaleBass *pCanale;
		StrBassHandles *pBass;
		bool TestImport;
		StrBaseImportFile *pImport;
		StrListaWav *pVetNomiTracce;

		if (NumeroCd == 130) {
			j = 0;
		}
		pVetNomiTracce = tomb4::TrackFileNames;
		AggiornaVolumeBass();

		pBass = &GlobTomb4.BaseBassHandles;
		IndiceCanale = 0;
		if (GlobTomb4.pBaseCustomize->TestOldCDTrigger == false) {
			if (Loop == 0)
				IndiceCanale = 1;
		}
		if (pBass->CanaleNow) {
			IndiceCanale = pBass->CanaleNow & 0x3f;
		}

		if (NumeroCd == -1) {
			StopBassSuoni(IndiceCanale);
			pBass->CanaleNow = 0;
			return;
		}

		pCanale = &pBass->VetCanali[IndiceCanale];
		if (NumeroCd & 0x4000) {
			TestImport = true;
		} else {
			// non e' import, pero' se c'e' tra i file import un file audio con lo stesso numero
			// impostare adesso come fosse di tipo import
			pImpFile = &GlobTomb4.BaseImportedFiles.VetFiles[0];
			for (i = 0; i < GlobTomb4.BaseImportedFiles.TotFiles; i++) {
				if (pImpFile->Tipo == FTYPE_SOUND && pImpFile->NumeroFile == NumeroCd)
					break;
				pImpFile++;
			}
			if (i == GlobTomb4.BaseImportedFiles.TotFiles) {
				TestImport = false;
			} else {
				// convertire l'indice in ID
				for (j = 0; j < MAX_IMPORT_FILES * 10; j++) {
					if (GlobTomb4.BaseImportedFiles.VetID[j] == i)
						break;
				}

				NumeroCd = (short) (0x4000 | j);
				TestImport = true;
			}
		}
		// ora eseguire su canale IndiceCanale
		IndiceSuono = NumeroCd & 0x3fff;

		// qui si dovrebbe fare analisi per estensione di default
		// e anche per uso di suono precaricato
		if (TestImport == false) {
			sprintf_s(NomeFile, "audio\\%s", pVetNomiTracce[IndiceSuono].Testo);
		}

		// se canale e' gia' attivo fare il fade out
		// azzerare valore di canale now per la prossima richiesta
		pBass->CanaleNow = 0;

		// se era attivo il canale chiuderlo con fade-out

		if (pCanale->Canale) {
			// se era gia' attivo lo stesso cd in modo loop uscire subito
			if (pCanale->NumeroCd == NumeroCd && pCanale->Loop)
				return;

			FadeOut = GlobTomb4.pBaseCustomize->BassDll.TimeFadeOutCorto;

			pBass->Proc.BASS_ChannelSlideAttribute(pCanale->Canale, BASS_ATTRIB_VOL, (float) -0.02, FadeOut);
			// togliere attributo loop per far si che si chiuda da solo
			pBass->Proc.BASS_ChannelFlags(pCanale->Canale, 0, BASS_SAMPLE_LOOP);
		}

		if (Loop)
			Flags = BASS_SAMPLE_LOOP;
		else
			Flags = 0;

		if (TestImport == true) {
			pImport = &GlobTomb4.BaseImportedFiles;
			i = pImport->VetID[IndiceSuono];

			if (i == -1) {

				InviaLog("Cann't find imported file");

				return;
			}
			// usare dati id import file = i
			pImpFile = &pImport->VetFiles[i];
			pCanale->Canale = pBass->Proc.BASS_StreamCreateFile(TRUE, pImpFile->pData, 0, pImpFile->Size, BASS_STREAM_AUTOFREE + Flags);
			if (pBass->StartOffset > 0) {
				ImpostaPosizioneSuono(pCanale, pBass->StartOffset);
			}
		} else {
			pCanale->Canale = pBass->Proc.BASS_StreamCreateFile(0, NomeFile, 0, 0, BASS_STREAM_AUTOFREE + Flags);
			if (pBass->StartOffset > 0) {
				ImpostaPosizioneSuono(pCanale, pBass->StartOffset);
			}
			if (IndiceCanale == 0 && Loop != 0) {
				*GlobTomb4.pAdr->pAudioTrackLoop = (char) IndiceSuono;
				*GlobTomb4.pAdr->pTestAudioTrackLoop = 1;
			}
		}

		if (GlobTomb4.pBaseCustomize->TestOldCDTrigger == true) {
			if (IndiceCanale == 0 && pCanale->Loop != 0) {
				pBass->OldCdLoop = pCanale->NumeroCd;
			}
		}

		pBass->StartOffset = 0;

		if (pCanale->Canale == 0) {
			ShowBASSErrore(NomeFile);
			return;
		}

		if (pCanale->Canale) {
			pCanale->NumeroCd = NumeroCd;
			pCanale->Loop = Loop;
		}
		// imposta volume con crescita di fadeout
		pBass->Proc.BASS_ChannelSetAttribute(pCanale->Canale, BASS_ATTRIB_VOL, 0.1f);

		pBass->Proc.BASS_ChannelPlay(pCanale->Canale, 0);

		// ora fare slid per farlo crescere fino al massimo
		pBass->Proc.BASS_ChannelSlideAttribute(pCanale->Canale, BASS_ATTRIB_VOL, pBass->VolumeMusica, GlobTomb4.pBaseCustomize->BassDll.TimeFadeOutCorto);

		// qui nella patch del trep si crerava un synt con call back
		// poi provare a vedere a che serve
	}

	// legge il contenuto di tomb4 per il volume e lo converte in float
	// e lo salva basebass
	// non viene effettuata alcuna chiamata di funzione
	void AggiornaVolumeBass(void)
	{
		GlobTomb4.BaseBassHandles.VolumeMusica = *GlobTomb4.pAdr->pSetting_MusicVolume / (float) 100;
	}

	// se bass.dll e'attiva chiude i suoni bass
	// se invece non e' attiva chiama il normale S_CDStop()
	// iusare -1 come numero canale per chiudere tutto
	// oppure 0 per primo canale e 1 per il secondo
	void StopBassSuoni(int NumeroCanale)
	{
		StrBassHandles *pBass;
		DWORD FadeOut;
		int i;
		StrCanaleBass *pCanale;
		int Inizio, Fine;

		pBass = &GlobTomb4.BaseBassHandles;

		if (pBass->TestPresente == false) {
			tomb4::S_CDStop();
			return;
		}
		switch (NumeroCanale) {
		case -1:
			Inizio = 0;
			Fine = 2;
			break;
		case 0:
			Inizio = 0;
			Fine = 1;
			break;
		case 1:
			Inizio = 1;
			Fine = 2;
			break;
		default:
			Inizio = NumeroCanale;
			Fine = NumeroCanale + 1;
			break;
		}

		// chiudere con fade out breve
		FadeOut = GlobTomb4.pBaseCustomize->BassDll.TimeFadeOut;

		for (i = Inizio; i < Fine; i++) {
			pCanale = &pBass->VetCanali[i];

			if (pCanale->Canale) {
				pBass->Proc.BASS_ChannelSlideAttribute(pCanale->Canale, BASS_ATTRIB_VOL, (float) -0.02, FadeOut);
				// rimuove flag loop in modo che si fermi il prima
				// possibile
				pBass->Proc.BASS_ChannelFlags(pCanale->Canale, 0, BASS_SAMPLE_LOOP);
			}

			pCanale->Canale = 0;
			pCanale->Loop = 0;
			pCanale->NumeroCd = -1;
		}
	}

	// controllare errore
	void ShowBASSErrore(char *pNome)
	{
		int Codice;

		Codice = GlobTomb4.BaseBassHandles.Proc.BASS_ErrorGetCode();

		sprintf_s(BufferLog, "BassError after operation \"%s\": Error Code = %d", pNome, Codice);
		InviaLog(BufferLog);
	}

	// incrementa il numero di debug attivi
	// se alla fine c'e' un valore attivo di debug restitusice true
	bool AddTabLogScript(void)
	{
		if ((GlobTomb4.ScriptOptions.MainFlags & ngfm_Diagnostica) != 0 && (GlobTomb4.pDiagnostica->FlagsDgx & DGX_LOG_SCRIPT_COMMANDS) != 0) {

			GlobTomb4.DebugModeCounter++;
		}

		if (GlobTomb4.DebugModeCounter)
			return true;
		return false;
	}

	DWORD FindSkipPhase(void)
	{
		DWORD FlagsSkip;

		FlagsSkip = SKIP_NONE;

		if (*GlobTomb4.pAdr->pFadeScreen)
			FlagsSkip |= SKIP_FADE;

		if (*GlobTomb4.pAdr->pTestLoading)
			FlagsSkip |= SKIP_LOADING_LEVEL;

		if (*GlobTomb4.pAdr->Camera.pModeCameraNow == 1)
			FlagsSkip |= SKIP_FIXED_CAMERA;

		if (*GlobTomb4.pAdr->pTestFlybyInProgress)
			FlagsSkip |= SKIP_FLY_CAMERA;

		if (*GlobTomb4.pAdr->pLevelNow == 0 && (*GlobTomb4.pAdr->pScriptMainFlags & 0x04))
			FlagsSkip |= SKIP_TITLE_LEVEL;

		if (*GlobTomb4.pAdr->pTestGrayScreen)
			FlagsSkip |= SKIP_GRAY_SCREEN;

		if (GlobTomb4.TestSuspendObjectShowing == true)
			FlagsSkip |= SKIP_NO_VIEW_OGGETTI;

		if (*GlobTomb4.pAdr->pZoomFactor != 0 && *GlobTomb4.pAdr->pTestLaserSight == 0)
			FlagsSkip |= SKIP_BINOCULARS;

		if (*GlobTomb4.pAdr->pTestLaserSight && (*GlobTomb4.pAdr->pInputExtGameCommands & 0x200) != 0)
			FlagsSkip |= SKIP_LASER_SIGHT;

		if (GlobTomb4.TestOverlapImage == true)
			FlagsSkip |= SKIP_FULL_IMAGE;
		return FlagsSkip;
	}


	bool TastoPremutoTomb4(int ScanCode)
	{
		if (GlobTomb4.pAdr->pVetInputKeyboard[ScanCode])
			return true;
		return false;
	}

	// quando e' presente immagine per title viene allocata solo una volta all'inizio
	// verra' poi rilasciata alla fine di tutto.
	void AllocaTitleImage(void)
	{
		StrBaseImgBackGround *pTitle;
		StrShowImage *pBase;
		BLENDFUNCTION Blend;

		pTitle = &GlobTomb4.BaseImgTitle;

		if (pTitle->TestEnabled == false)
			return;
		if (pTitle->TestAllocatedImage == true)
			return;
		InviaLog("Allocate Title Image");
		pBase = &GlobTomb4.BaseImages;

		if (AllocaHdcTomb(pBase, true, false) == false) {
			pTitle->TestEnabled = false;
			return;
		}

		if ((pTitle->Flags & BKGDF_KEEP_GAME_SCREEN) == 0) {

			if (AllocaImmagine(pTitle->ImageNumber, &pBase->ImageTitle, -1, -1) == false) {
				pTitle->TestEnabled = false;
				LiberaHdcTomb(pBase, false);
				return;
			}

			SetStretchBltMode(pBase->Temp.MemHdc, COLORONCOLOR);

			// ora ridimensionare e copiare immagine title in temphdc con dimensione uguali a quelle di tomb
			StretchBlt(pBase->Temp.MemHdc, 0, 0, pBase->ZonaSchermoTomb.right, pBase->ZonaSchermoTomb.bottom, pBase->ImageTitle.MemHdc, 0, 0, pBase->ImageTitle.SizeX, pBase->ImageTitle.SizeY, SRCCOPY);
			// ora liberare title perche' poi usero' title con immagine di temp
			LiberaImmagine(&pBase->ImageTitle);

		} else {
			// c'e' flag BKGDF_KEEP_GAME_SCREEN
			if (pTitle->Flags & BKGDF_SEMI_TRANSPARENT) {
				// allocare immagine e copiarla con effetto trasparenza su quella temp
				if (AllocaImmagine(pTitle->ImageNumber, &pBase->ImageTitle, -1, -1) == false) {
					InviaLog("ERROR: Failed loading image for BKGDT_TITLE of CUST_BACKGROUND command");

					return;
				}
				Blend.AlphaFormat = 0; // 1= valore di AC_SRC_ALPHA;
				Blend.BlendFlags = 0;
				Blend.BlendOp = AC_SRC_OVER;
				Blend.SourceConstantAlpha = (BYTE) pTitle->Parameter;  // livello trasparenza 0=trasparenza / 255=opaco

				AlphaBlend(pBase->Temp.MemHdc, 0, 0, pBase->Temp.SizeX, pBase->Temp.SizeY, pBase->ImageTitle.MemHdc, 0, 0, pBase->ImageTitle.SizeX, pBase->ImageTitle.SizeY, Blend);
				LiberaImmagine(&pBase->ImageTitle);
			}
		}

		pTitle->TestAllocatedImage = true;
		InviaLog("Save in TitleImage the image from temp hdc");
		// adesso traferire dati di temp hdc in title
		pBase->ImageTitle = pBase->Temp;
		// ora segnalare temp come gia' liberato
		memset(&pBase->Temp, 0, sizeof(StrRecordImage));

		LiberaHdcTomb(&GlobTomb4.BaseImages, false);
	}

	// immagine per binocolo viene allocata all'inizio del livello e verra' poi rilasciata
	// solo al cariamento di un nuovo livello
	void AllocaBinocularImage(void)
	{
		StrBaseImgBackGround *pBin;
		StrShowImage *pBase;
		StrCustBinocular *pCust;

		pBin = &GlobTomb4.BaseImgBinocular;
		if (pBin->TestEnabled == false)
			return;

		if (pBin->TestAllocatedImage == true)
			return;

		pBase = &GlobTomb4.BaseImages;
		if (AllocaHdcTomb(pBase, true, false) == false) {

			pBin->TestEnabled = false;
			return;
		}

		// dovrei convertire l'immagine in una dimensioje fissa?
		// magari per ora no, solo dopo customize per binocular faro' sta cosa

		if (AllocaImmagine(pBin->ImageNumber, &pBase->ImageBinocular, -1, -1) == false) {
			pBin->TestEnabled = false;
			LiberaHdcTomb(pBase, false);
			return;
		}

		pBin->TestAllocatedImage = true;

		pCust = &GlobTomb4.pBaseCustomize->CustBinoculars;

		if (pCust->TestPresente == true) {
			// c''e cusotmize, non cambiare dimensione e richiedere che sia 1024x768
			if (pBase->ImageBinocular.SizeX != 1024 || pBase->ImageBinocular.SizeY != 768) {
				InviaLog("ERROR: binocular image background different than 1024x768");
			}
			// allocare immagine eventuale per compass
			if ((pCust->Flags & BINF_COMPASS) != 0 && (pCust->CompassRect & BINT_STRIP) != 0) {
				if (AllocaImmagine(pCust->CompassImage, &pBase->ImageBinocCompass, -1, -1) == false) {
					InviaLog("Error trying to allocate image for compass strip of binocular");
					pBin->TestEnabled = false;
					pCust->TestPresente = false;
					LiberaHdcTomb(pBase, false);
					return;
				}
			}

			if ((pCust->Flags & BINF_SEXTANT) != 0 && (pCust->SextantRect & BINT_STRIP) != 0) {
				if (AllocaImmagine(pCust->SextantImage, &pBase->ImageBinocSextant, -1, -1) == false) {
					InviaLog("Error trying to allocate image for sextant strip of binocular");
					pBin->TestEnabled = false;
					pCust->TestPresente = false;
					LiberaHdcTomb(pBase, false);
					return;
				}
			}

		} else {

			// ora ridimensionare e copiare immagine binocolo in temphdc con dimensione uguali a quelle di tomb
			StretchBlt(pBase->Temp.MemHdc, 0, 0, pBase->ZonaSchermoTomb.right, pBase->ZonaSchermoTomb.bottom, pBase->ImageBinocular.MemHdc, 0, 0, pBase->ImageBinocular.SizeX, pBase->ImageBinocular.SizeY, SRCCOPY);
			// ora liberare imagebinocula perche' poi usero' title con immagine di temp
			LiberaImmagine(&pBase->ImageBinocular);

			// adesso traferire dati di temp hdc in title
			pBase->ImageBinocular = pBase->Temp;
			// ora segnalare temp come gia' liberato
			memset(&pBase->Temp, 0, sizeof(StrRecordImage));
		}
		LiberaHdcTomb(&GlobTomb4.BaseImages, false);
		InviaLog("Allocated binocular image");
	}

	// immagine per mirino viene allocata all'inizio del livello e verra' poi rilasciata
	// solo al cariamento di un nuovo livello
	void AllocaLaserSightImage(void)
	{
		StrBaseImgBackGround *pMirino;
		StrShowImage *pBase;

		pMirino = &GlobTomb4.BaseImgLaserSight;
		if (pMirino->TestEnabled == false)
			return;

		if (pMirino->TestAllocatedImage == true)
			return;

		pBase = &GlobTomb4.BaseImages;
		if (AllocaHdcTomb(pBase, true, false) == false) {

			pMirino->TestEnabled = false;
			return;
		}

		if (AllocaImmagine(pMirino->ImageNumber, &pBase->ImageLaserSight, -1, -1) == false) {
			pMirino->TestEnabled = false;
			LiberaHdcTomb(pBase, false);
			return;
		}

		pMirino->TestAllocatedImage = true;

		// ora ridimensionare e copiare immagine title in temphdc con dimensione uguali a quelle di tomb
		StretchBlt(pBase->Temp.MemHdc, 0, 0, pBase->ZonaSchermoTomb.right, pBase->ZonaSchermoTomb.bottom, pBase->ImageLaserSight.MemHdc, 0, 0, pBase->ImageLaserSight.SizeX, pBase->ImageLaserSight.SizeY, SRCCOPY);
		// ora liberare title perche' poi usero' title con immagine di temp
		LiberaImmagine(&pBase->ImageLaserSight);

		// adesso traferire dati di temp hdc in title
		InviaLog("Save temp image in Laser Sight image record");
		pBase->ImageLaserSight = pBase->Temp;
		// ora segnalare temp come gia' liberato
		memset(&pBase->Temp, 0, sizeof(StrRecordImage));

		LiberaHdcTomb(&GlobTomb4.BaseImages, false);
		InviaLog("Allocated LaserSight image");
	}

	void SalvaScreenShotTr4(void)
	{
		DWORD TempoNow;
		char NomeFile[256];

		TempoNow = (DWORD) GetTickCount64();

		if ((TempoNow - GlobTomb4.ScreenShot.LastTimeScreenShot) < 500)
			return;
		TrovaNuovoNomeShot(NomeFile);

		SalvaShotTomb4(NomeFile, true);

		// avviare un soundeffect sempre presente
		tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_SCREENSHOT_CAPTURE], NULL, 2);

		GlobTomb4.ScreenShot.LastTimeScreenShot = (DWORD) GetTickCount64();
	}

	void TrovaNuovoNomeShot(char *pNuovoNome)
	{
		__try { throw __func__; } __finally {}
	}

	// restituisce true se i piedi di lara sono in palude
	bool IsLaraPiediInPalude(void)
	{
		StrMovePosition TriRec;
		void *pFloor;
		short Room;
		int BaseLaraY;

		TriRec.RelX = 0;
		TriRec.RelY = 0;
		TriRec.RelZ = 0;
		tomb4::GetJointAbsPosition((tomb4::ITEM_INFO *) GlobTomb4.pAdr->pLara, (tomb4::PHD_VECTOR *) &TriRec, JOINT_LEFT_ANCKLE);
		BaseLaraY = TriRec.RelY;

		Room = GlobTomb4.pAdr->pLara->Room;
		pFloor = tomb4::GetFloor(GlobTomb4.pAdr->pLara->CordX, BaseLaraY, GlobTomb4.pAdr->pLara->CordZ, &Room);

		if (GlobTomb4.pAdr->pVetRooms[Room].FlagsRoom & 0x4)
			return true;
		return false;
	}

	// chiamata prima di entrare in inventario o in pannello di salvataggio
	// savegame
	// cattura lo schermo in anticipo in modo da poter eventualmwente
	// salvarne l'immagine in savegame
	void SalvaMiniShot(void)
	{
		if (GlobTomb4.ScreenShot.TestSalvaMiniShot == false)
			return;

		// provare a salvarlo direttamente in memoria
		SalvaShotTomb4("ShotGame.bmp", false);
	}

	// gestisce TUTTE (non proprio tutte in realta') le callback directCB con flags ma senza argomenti

	int EseguiCallBackDirects(WORD CB_Type, WORD CBT_Flags, StrItemTr4 *pItem, short IndiceItem, bool Test1, bool Test2, void *pVertici)
	{
		DWORD i;
		StrMyDatabase *pDB;
		StrPluginRec *pRec;
		StrRecordCallBack *pCall;
		int j;
		int CallRetValue;
		int Temp;
		CALL_LARA_CTRL CallLaraCtrl;
		CALL_LARA_DRAW CallLaraDraw;
		CALL_HAIR_DRAW CallHairDraw;
		CALL_HAIR_CONTROL CallHairControl;
		CALL_INVENTORY_MAIN CallInventory;
		CALL_INVENTORY_BACKGROUND CallBackGroundInvent;
		CALL_ANIMATE_LARA CallAnimateLara;
		CALL_OPTIONS_MANAGER CallOptions;

		CallRetValue = SRET_OK;

		pDB = &MyGlobPrivate.DataBase;

		pRec = &pDB->pVetPlugins[1];

		for (i = 1; i < pDB->TotPlugins; i++) {
			if (pRec->VetDirectCB[CB_Type]) {

				// c'e' una callback del tipo cercato
				pCall = &pRec->VetRequiredCB[0];
				for (j = 0; j < pRec->TotRequiredCB; j++) {
					if (pCall->CB_Tipo == CB_Type && (pCall->Flags & CBT_Flags) != 0) {
						// trovata, ora eseguirla in modo diverso a seconda del tipo
						switch (CB_Type) {
						case CB_OPTIONS_MANAGER:
							CallOptions = (CALL_OPTIONS_MANAGER) pCall->pCall;
							// (bool TestTitle, bool TestCommands, int SelectedRow);
							Temp = CallOptions(Test1, Test2, IndiceItem);
							CallRetValue |= Temp;
							break;

						case CB_LARA_CONTROL:
							CallLaraCtrl = (CALL_LARA_CTRL) pCall->pCall;
							pItem = GlobTomb4.pAdr->pLara;
							Temp = CallLaraCtrl(CBT_Flags, pItem);
							CallRetValue |= Temp;
							break;
						case CB_LARA_DRAW:
							//  (WORD CBT_Flags, StrItemTr4 * pLara, bool TestNoUpdateLight, bool TestMirror);
							CallLaraDraw = (CALL_LARA_DRAW) pCall->pCall;
							Temp = CallLaraDraw(CBT_Flags, pItem, Test1, Test2);
							CallRetValue |= Temp;
							break;
						case CB_LARA_HAIR_DRAW:
							// (WINAPI *CALL_HAIR_DRAW) (WORD CBT_Flags);
							CallHairDraw = (CALL_HAIR_DRAW) pCall->pCall;
							Temp = CallHairDraw(CBT_Flags);
							CallRetValue |= Temp;
							break;
						case CB_LARA_HAIR_CONTROL:
							// CALL_HAIR_CONTROL) (WORD CBT_Flags, bool TestKeepDownHair, bool TestSecondTail, void *pData);
							CallHairControl = (CALL_HAIR_CONTROL) pCall->pCall;
							Temp = CallHairControl(CBT_Flags, Test2, Test1, pVertici);
							CallRetValue |= Temp;
							break;
						case CB_INVENTORY_MAIN:
							CallInventory = (CALL_INVENTORY_MAIN) pCall->pCall;
							// (WORD CBT_Flags, bool TestLoadedGame, int SelectedItem);
							Temp = CallInventory(CBT_Flags, Test1, SlotSceltoInventario);
							CallRetValue |= Temp;
							break;
						case CB_INVENT_BACKGROUND_CREATE:
						case CB_INVENT_BACKGROUND_DRAW:
						case CB_INVENT_BACKGROUND_QUIT:
							CallBackGroundInvent = (CALL_INVENTORY_BACKGROUND) pCall->pCall;
							// (WORD CB_Type, WORD CBT_Flags, WORD PHASE_Type);

							Temp = CallBackGroundInvent(CB_Type, CBT_Flags, IndiceItem);
							CallRetValue |= Temp;
							break;
						case CB_ANIMATE_LARA:
							CallAnimateLara = (CALL_ANIMATE_LARA) pCall->pCall;
							// (WORD CBT_Flags, StrItemTr4 *pLara);
							Temp = CallAnimateLara(CBT_Flags, pItem);
							CallRetValue |= Temp;
							break;
						}
					}

					pCall++;
				}
			}

			pRec++;
		}

		return CallRetValue;
	}

	int EseguiCB_SlotFirstAfter(int CB_Value, short ItemIndex, StrItemTr4 *pItem, int CB_Flags, StrCollisionLara *pColl)
	{
		// eseguire tutte le patch del tipo di input nella sequenza dei plugin
		// funziona per: CB_SLOT_INITIALISE ; CB_SLOT_CONTROL e CB_SLOT_COLLISION e CB_SLOT_DRAW
		DWORD i;
		StrMyDatabase *pDB;
		StrPluginRec *pRec;
		StrRecordCallBack *pCall;
		int j;
		int SlotNow;
		int SlotRetValue;
		CALL_SLOT_MANY MyCall;
		CALL_SLOT_CB_COLLISION MyCallCollision;
		int Temp;

		SlotRetValue = SRET_OK;

		SlotNow = pItem->SlotID;
		pDB = &MyGlobPrivate.DataBase;

		pRec = &pDB->pVetPlugins[1];

		for (i = 1; i < pDB->TotPlugins; i++) {
			pCall = &pRec->VetRequiredCB[0];
			for (j = 0; j < pRec->TotRequiredCB; j++) {
				if (pCall->CB_Tipo == CB_Value && (pCall->Flags & CB_Flags) != 0 && pCall->Numero == SlotNow) {

					// trovata call back di stesso tipo e numero: eseguirla
					switch (CB_Value) {
					case CB_SLOT_INITIALISE:
					case CB_SLOT_CONTROL:
					case CB_SLOT_DRAW:
					case CB_SLOT_DRAW_EXTRA:

						MyCall = (CALL_SLOT_MANY) pCall->pCall;
						Temp = MyCall(ItemIndex, pItem, (WORD) CB_Flags);

						if (Temp != SRET_OK) {
							SlotRetValue |= Temp;
						}
						break;
					case CB_SLOT_COLLISION:
						MyCallCollision = (CALL_SLOT_CB_COLLISION) pCall->pCall;
						//(short IndexItem, StrItemTr4 *pItem, WORD CBT_Flags, StrCollisionLara * pCollision);
						Temp = MyCallCollision(ItemIndex, pItem, (WORD) CB_Flags,  pColl);

						if (Temp != SRET_OK) {
							SlotRetValue |= Temp;
						}
						break;
					}
				}

				pCall++;

			}
			pRec++;
		}

		return SlotRetValue;
	}

	// viene chiamata PRIMA di eseguire sub CONTROL di oggetto
	// restituisce true per far eseguire la funzione control
	// restituisce false se si deve saltare l'esecuzione della sub control
	bool GestioneControlObject(StrItemTr4 *pItem, int ItemIndex)
	{
		int i;
		StrRecordEnemyScript *pEnemy;
		short *pFloorDataNow;
		int TotEnemy;
		WORD Slot;
		bool TestGiaEseguitoHeavy;
		void *pFloor;
		short Room;
		StrBaseCutscene *pCut;
		StrRecordFreeze *pFreeze;
		int n;

		TestGiaEseguitoHeavy = false;
		// impostare indice
		GlobTomb4.ItemIndexLastMoved = (short) ItemIndex;

		// verificare se fa parte di moveable che richiedono controllo  basic collision
		pCut = GlobTomb4.pBaseCutscene;
		for (i = 0; i < pCut->TotBasicCollision; i++) {
			if (pCut->VetBasicCollisionIndices[i] == ItemIndex) {
				GestioneBasicCollision(pItem, ItemIndex);
			}
		}

		if (pItem->Health <= 0 && pItem->Health != -0x4000) {
			// sta morendo
			// vedere  se e' una di quelli da far esplodere
			TotEnemy = GlobTomb4.BaseEnemys.TotEnemy;
			for (i = 0; i < TotEnemy; i++) {
				pEnemy = &GlobTomb4.BaseEnemys.VetEnemy[i];
				if (pItem->SlotID == pEnemy->SlotId && (pEnemy->FlagsNEF & NEF_EXPLODE) != 0) {
					// attivare esplosione
					tomb4::CreatureDie((short) ItemIndex, true);
					tomb4::SoundEffect(0x69, 0, 0);
					tomb4::SoundEffect(0x6A, 0, 0);
					break;
				}
			}
		}

		// vedere se vanno bloccati tutti gli enemyes
		if (GlobTomb4.TestFreezeAll == true) {
			//  bloccare ma evitando gl iemitter
			Slot = pItem->SlotID;
			switch (Slot) {
			case 142:
			case 143:
			case 144:
			case 145:
			case 146:
			case 147:
			case 148:

			case 380:
			case 381:
			case 382:
				// questi eseguirli
				break;
			default:
				return false;
			}
		}

		// vedere se questo indice e' uno di quelli da ignorare
		pFreeze = &GlobTomb4.BaseFreeze.VetFreeze[0];

		n = GlobTomb4.BaseFreeze.TotFreeze;

		for (i = 0; i < n; i++) {
			if (ItemIndex == pFreeze->ItemIndex)
				break;

			pFreeze++;
		}

		if (i < n) {
			// trovato

			if (pFreeze->Tempo != 0xFFFF)
				pFreeze->Tempo--;
			if (pFreeze->Tempo > 0)
				return false;

			// finito il tempo
			// disattivare questo record
			if (n > 1) {
				*pFreeze = GlobTomb4.BaseFreeze.VetFreeze[n - 1];
			}
			GlobTomb4.BaseFreeze.TotFreeze--;
		}

		Slot = pItem->SlotID;

		TotEnemy = GlobTomb4.BaseEnemys.TotEnemy;
		for (i = 0; i < TotEnemy; i++) {
			pEnemy = &GlobTomb4.BaseEnemys.VetEnemy[i];
			if (pEnemy->SlotId == Slot && (pEnemy->FlagsNEF & NEF_EASY_HEAVY_ENABLING) != 0) {
				// attivare heavy trigger in questa posizione
				Room = pItem->Room;

				pFloor = tomb4::GetFloor(pItem->CordX, pItem->CordY, pItem->CordZ, &Room);
				tomb4::GetHeight((tomb4::FLOOR_INFO *) pFloor, pItem->CordX, pItem->CordY, pItem->CordZ);
				pFloorDataNow = tomb4::trigger_index;

				GlobTomb4.ItemIndexEnabledTrigger = (short) ItemIndex;

				tomb4::TestTriggers(pFloorDataNow, 1, 0);
				TestGiaEseguitoHeavy = true;
			}

		}

		// se non e' bloccoato, ed e' leading actor, allora eseguire tirgger heavy immediati
		if (TestGiaEseguitoHeavy == false && ItemIndex == GlobTomb4.pBaseCutscene->LeadingActorIndex) {
			Room = pItem->Room;
			pFloor = tomb4::GetFloor(pItem->CordX, pItem->CordY, pItem->CordZ, &Room);
			tomb4::GetHeight((tomb4::FLOOR_INFO *) pFloor, pItem->CordX, pItem->CordY, pItem->CordZ);
			pFloorDataNow = tomb4::trigger_index;

			tomb4::TestTriggers(pFloorDataNow, 1, 0);
		}
		return true;
	}

	// Moveable su cui effettuare controllo per basic collision
	// solo relativo a floor e gavita'
	void GestioneBasicCollision(StrItemTr4 *pItem, int ItemIndex)
	{
		void *pFloor;
		short Room;
		int Altezza;
		int IndiceSlot;
		bool TestMod;
		StrBoxCollisione *pBox;
		int TopY, BottomY;
		DWORD DistanzaAvanti;
		int IncX, IncZ;
		int MaxY;
		int StopAnim;
		int Distanza;

		TestMod = false;
		IndiceSlot = pItem->SlotID;
		pBox = (StrBoxCollisione *) tomb4::GetBestFrame((tomb4::ITEM_INFO *) pItem);

		if (pItem->SpeedV != 0) {
			pItem->CordY += pItem->SpeedV;
			pItem->SpeedV += 5;
			if (pItem->SpeedV > 128)
				pItem->SpeedV = 128;
			TestMod = true;
		}

		TopY = pItem->CordY + pBox->MinY;
		MaxY = pBox->MaxY;
		// considerare posizione bottom y solo per rollingball, tutti gli altri sono al pavimento
		if (pItem->SlotID != 130) {
			// e' diverso da rollingball: ignorare bottomy
			MaxY = 0;
		}

		BottomY = pItem->CordY + MaxY;
		DistanzaAvanti = pBox->MaxZ;

		// scoprire se sta per sbattere addosso a un muro
		CalcolaIncremento(pItem->OrientationH, &IncX, &IncZ, DistanzaAvanti);
		Room = pItem->Room;
		pFloor = tomb4::GetFloor(pItem->CordX + IncX, pItem->CordY, pItem->CordZ + IncZ, &Room);

		Altezza = tomb4::GetHeight((tomb4::FLOOR_INFO *) pFloor, pItem->CordX + IncX, pItem->CordY, pItem->CordZ + IncZ);

		if (Altezza == WALL_FLOOR) {

			if (pItem->SpeedH) {
				// spostarloindietro rispetto al senso di marcia della velocita' di speed ma in direzione opposta
				// e poi cambiare animazione
				Distanza = (pItem->SpeedH << 1) + pItem->SpeedH;

				CalcolaIncremento(pItem->OrientationH - 0x7fff, &IncX, &IncZ, Distanza);
				AggiornaPosizioneItem((short) ItemIndex, pItem->CordX + IncX, pItem->CordY, pItem->CordZ + IncZ, 0);
			}

			// impostare animzione per blocco
			StopAnim = TrovaAnimazioneStop(pItem);
			EsecuzioneActionTrigger(0, (WORD) (15 | (StopAnim << 8)), ItemIndex, SCANF_DIRECT_CALL);
			pItem->StateIdNext = pItem->StateIdCurrent;
			pItem->SpeedH = 0;
			return;
		}

		// ora fare analisi floor

		Room = pItem->Room;
		pFloor = tomb4::GetFloor(pItem->CordX, pItem->CordY, pItem->CordZ, &Room);

		Altezza = tomb4::GetHeight((tomb4::FLOOR_INFO *) pFloor, pItem->CordX, pItem->CordY, pItem->CordZ);

		pItem->HeightFloor = Altezza;

		if (BottomY > Altezza) {
			pItem->SpeedV = 0;
			pItem->CordY = Altezza - MaxY;
			TestMod = true;
		}

		if (BottomY == Altezza) {
			pItem->SpeedV = 0;
		}

		if (BottomY < Altezza && pItem->SpeedV == 0)
			pItem->SpeedV = 30;

		// ora analisi per soffitto
		Altezza = tomb4::GetCeiling((tomb4::FLOOR_INFO *) pFloor, pItem->CordX, pItem->CordY, pItem->CordZ);

		if (TopY < Altezza) {
			// stiamo sforando soffitto
			pItem->CordY = Altezza - pBox->MinY;
			TestMod = true;
		}

		// se e' stato modificata posizione item fare aggiornamento
		if (TestMod) {
			// aggiornare numero stanza
			AggiornaPosizioneItem((short) ItemIndex, pItem->CordX, pItem->CordY, pItem->CordZ, 0);
		}
	}

	// trova animazione (numero relativo da zero) di moveable pItem che NON abbia velocita' orizzontale
	// cerca solo nelle prime 32 animazioni (da 0 a 31)
	int TrovaAnimazioneStop(StrItemTr4 *pItem)
	{
		StrSlot *pSlot;
		int i;
		StrAnimationTr4 *pAnim;

		pSlot = &GlobTomb4.pAdr->pVetSlot[pItem->SlotID];

		i = 0;

		while (i < 32) {
			pAnim = &GlobTomb4.pAdr->pVetAnimations[pSlot->IndexFirstAnim + i];
			if (pAnim->Speed == 0 && pAnim->Accel == 0)
				return i;

			i++;
		}

		// non trovata, restituire la prima
		return 0;
	}

	void LaraBreath(tomb4::ITEM_INFO *item)
	{
		tomb4::PHD_VECTOR p;
		tomb4::PHD_VECTOR v;

		// lara e 'sott'acqua
		if (tomb4::lara.water_status == tomb4::LW_UNDERWATER)
			return;

		// calcolare cosa  bisogna fare sulla base di contatore
		if (!ContatoreFiato)
			ContatoreFiato = 60;
		ContatoreFiato--;
		if (ContatoreFiato > 15)
			return;

		// se e' morta niente fiato
		if (tomb4::lara_item->hit_points <= 0)
			return;

		// controllare se siamo in stanza cold
		if ((tomb4::room[tomb4::lara_item->room_number].flags & tomb4::ROOM_COLD) == 0)
			return;

		p.x = 0;
		p.y = -4;
		p.z = 96;
		tomb4::GetLaraJointPos(&p, 8);

		v.x = (tomb4::GetRandomControl() & 7) - 4;
		v.y = (tomb4::GetRandomControl() & 7) - 8;
		v.z = (tomb4::GetRandomControl() & 0x7F) + 64;
		tomb4::GetLaraJointPos(&v, 8);

		tomb4::BikeTriggerExhaustSmoke(p.x, p.y, p.z, (short) (v.x - p.x), v.y - p.y, v.z - p.z);
	}

	// verifica se c'e' l'esecuzione del singolo globaltrigger
	// col dato parametro
	bool VerificaSingleGlobalTrigger(short GlobalTrigger, short Parametro, bool TestIgnoraParametro)
	{
		int i;
		StrGlobalTrigger *pRec;
		int Tot;
		bool TestEsegui;
		bool TestTrovato;
		bool TestAlmenoUno;
		bool TestEsito;

		Tot = GlobTomb4.pBaseGlobalTriggers->TotTriggers;
		pRec = &GlobTomb4.pBaseGlobalTriggers->VetTriggers[0];

		TestAlmenoUno = false;

		for (i = 0; i < Tot; i++) {
			TestEsegui = false;
			TestTrovato = false;

			if ((pRec->Flags & FGT_DISABLED) == 0) {

				// vedere se va disattivato il log per queso global trigger
				if (pRec->Flags & FGT_HIDE_IN_DEBUG) {
					SospendiLogScript(BREAK_GLOBAL_TRIGGER);
				}
				if (pRec->GlobalTrigger == GlobalTrigger) {

					TestTrovato = true;
					if (TestIgnoraParametro) {
						TestEsegui = true;
					} else {

						if (Parametro == pRec->Parameter)
							TestEsegui = true;
					}

					if (pRec->Flags & FGT_NOT_TRUE)
						TestEsegui ^= 1;
				}


				if (TestTrovato) {
					TestEsito = GestioneGlobaleOk(pRec, TestEsegui);
					if (TestEsito) {
						if ((pRec->Flags & FGT_REPLACE_MANAGEMENT) != 0 || pRec->GlobalTrigger != GT_SELECTED_INVENTORY_ITEM)
							TestAlmenoUno = true;
					}
				}

				if (pRec->Flags & FGT_HIDE_IN_DEBUG) {
					RiprendiLogScript(BREAK_GLOBAL_TRIGGER);
				}
			}
			pRec++;
		}

		return TestAlmenoUno;
	}

	// sospende temporaneamente logscript
	// questo non riguarda la sospensione col tasto f9
	// ma una sospensione per eliminare solo qualche procedura dal log
	// WORD OldFlagsDgx;
	// int OldDebugCounter;
	// i valori attuali vengono salvati in  VetOldDebug[] record

	void SospendiLogScript(int IndiceSave)
	{
		VetSalvaOldDebug[IndiceSave].OldFlagsDgx = GlobTomb4.pDiagnostica->FlagsDgx;
		VetSalvaOldDebug[IndiceSave].OldCounter = (WORD) GlobTomb4.DebugModeCounter;

		GlobTomb4.DebugModeCounter = 0;
		GlobTomb4.pDiagnostica->FlagsDgx &= ~DGX_LOG_SCRIPT_COMMANDS;
	}

	void RiprendiLogScript(int IndiceSave)
	{
		GlobTomb4.pDiagnostica->FlagsDgx = VetSalvaOldDebug[IndiceSave].OldFlagsDgx;
		GlobTomb4.DebugModeCounter = VetSalvaOldDebug[IndiceSave].OldCounter;
	}

	void OpenAllDoors(void)
	{
		int i;
		WORD Slot;

		for (i = 0; i < GlobTomb4.pAdr->TotItemsMax; i++) {
			Slot = GlobTomb4.pAdr->pVetItems[i].SlotID;

			if ((Slot >= 122 && Slot <= 129) || (Slot >= 322 && Slot <= 334)) {

				// ok provare eseguendo l'action per chiudere porta
				// azione per aprire porta
				// azione 26 (0x14) per Aprire (0x100) porta con indice (i)
				EsecuzioneActionTrigger(0, 0x11A, i, SCANF_DIRECT_CALL);
			}

		}
	}

	// calcola variazione coordinate pPos sulla base di record mirror attuale
	// salvato in GlobTomb4.BaseMirror.pRecNow
	// salva  lle coordinate cosi' ottenute
	// in GlobTomb4.BaseMirror.CordX/Y/Z

	void CalcolaCordMirror(StrPosizione *pPos)
	{
		BaseMirrors *pMirror;
		RecordMirror *pRecNow;

		pMirror = &GlobTomb4.BaseMirror;
		pRecNow = pMirror->pRecNow;

		pMirror->CordX = pPos->OrgX;
		pMirror->CordY = pPos->OrgY;
		pMirror->CordZ = pPos->OrgZ;

		switch (pRecNow->MirrorType) {
		case MIR_WEST_WALL:
		case MIR_INVERSE_WEST:
		case MIR_EAST_WALL:

			if (pRecNow->MirrorType == MIR_INVERSE_WEST) {

				pMirror->CordX = pRecNow->MaxCordMirror - pMirror->CordX;
				pMirror->CordX += pRecNow->MinCordMirror;
			}

			pMirror->CordZ = pRecNow->CordMirror - pMirror->CordZ;
			break;
		case MIR_SOUTH_WALL:
		case MIR_NORTH_WALL:
			pMirror->CordX = pRecNow->CordMirror - pMirror->CordX;
			break;
		case MIR_FLOOR:
		case MIR_CEILING:
			pMirror->CordY = pRecNow->CordMirror - pMirror->CordY;
			break;
		}
	}

	// calcola variazione orientamenti sulla base di record mirror
	// salvato in GlobTomb4.BaseMirror.pRecNow
	// e salva gli orientamenti ottenuti in GlobTomb4.BaseMirror.OrientV/H/R
	// nota: se testaltrnate = true cerca un modo alternativo di effettuare la rotazione
	void CalcolaOrientMirror(StrOrient *pOrient, bool TestLara, bool TestAlternate)
	{
		BaseMirrors *pMirror;
		RecordMirror *pRecNow;

		pMirror = &GlobTomb4.BaseMirror;
		pRecNow = pMirror->pRecNow;

		if (TestLara) {

			switch (pRecNow->MirrorType) {
			case MIR_WEST_WALL:
			case MIR_EAST_WALL:

				pMirror->OrientV = -pOrient->OrientV;
				pMirror->OrientH = -pOrient->OrientH;
				pMirror->OrientR = pOrient->OrientR - 32768;
				break;
			case MIR_INVERSE_WEST:
				pMirror->OrientV = pOrient->OrientV;
				pMirror->OrientH = pOrient->OrientH + 0x8000;
				pMirror->OrientR = pOrient->OrientR;
				break;
			case MIR_SOUTH_WALL:
			case MIR_NORTH_WALL:
				pMirror->OrientV = -pOrient->OrientV;
				pMirror->OrientH = -pOrient->OrientH;
				pMirror->OrientH += -32768;
				pMirror->OrientR = pOrient->OrientR - 32768;
				break;
			case MIR_FLOOR:
			case MIR_CEILING:

				pMirror->OrientV = pOrient->OrientV + 32768;
				pMirror->OrientH = pOrient->OrientH;
				pMirror->OrientR = pOrient->OrientR - 32768;
				break;
			}
		}

		if (TestLara == false) {
			// in questi calcoli omettere la rotazione relativa
			// va usato per altri oggetti tipo flare e capelli
			pMirror->OrientR = pOrient->OrientR;

			switch (pRecNow->MirrorType) {
			case MIR_WEST_WALL:
			case MIR_EAST_WALL:
				if (TestAlternate == false) {
					pMirror->OrientV = pOrient->OrientV;
					pMirror->OrientH = 0x8000 - pOrient->OrientH;
				} else {
					pMirror->OrientH = 0x8000 - pOrient->OrientH;
					pMirror->OrientR = 0x8000 - pOrient->OrientR;
					pMirror->OrientV = 0x8000 - pOrient->OrientV;
				}

				break;
			case MIR_SOUTH_WALL:
			case MIR_NORTH_WALL:
				if (TestAlternate == false) {
					pMirror->OrientV = pOrient->OrientV;
					pMirror->OrientH = -pOrient->OrientH;
				} else {
					pMirror->OrientH = 0x8000 - pOrient->OrientH;
					pMirror->OrientR = -pOrient->OrientR;
					pMirror->OrientV = -pOrient->OrientV;
				}
				break;

			case MIR_INVERSE_WEST:
				// questo e'sempre giusto: niente testalternate
				pMirror->OrientV = pOrient->OrientV;
				pMirror->OrientH = pOrient->OrientH + 0x8000;

				break;

			case MIR_FLOOR:
			case MIR_CEILING:
				if (TestAlternate == false) {
					pMirror->OrientV = 0x8000 - pOrient->OrientV;
					pMirror->OrientH = pOrient->OrientH;
				} else {
					pMirror->OrientR = pOrient->OrientR + 0x8000;
					pMirror->OrientH = pOrient->OrientH;
					pMirror->OrientV = pOrient->OrientV;
				}
				break;
			}
		}
	}

	// verifica che gli item della lista siano ancora presenti.
	// quelli che non sono presenti vengono eliminati
	// se alla fine non ne rimane uno disabilita il detector
	void VerificaTargetDetector(void)
	{
		StrDetector *pDetector;
		int i;
		int j;

		j = 0;
		pDetector = &GlobTomb4.BaseDetector;

		for (i = 0; i < pDetector->TotIndici; i++) {
			if ((GlobTomb4.pAdr->pVetItems[pDetector->VetIndici[i]].Objectbuttons & 0x8000) == 0) {
				// target ancora presnte
				if (j != i) {
					pDetector->VetIndici[j] = pDetector->VetIndici[i];
					// copiare anche targert item se e' di tipo radar
					if (pDetector->Flags & DTF_RADAR_MODE) {
						memcpy(&pDetector->VetTargets[j], &pDetector->VetTargets[i], sizeof(StrTargetDetector));
					}
				}

				j++;
			}
		}

		pDetector->TotIndici = (WORD) j;
		if (j == 0) {
			pDetector->TestAttivo = false;
			pDetector->TestMostra = false;
		}

		pDetector->Indice = pDetector->VetIndici[0];
	}

	// ok, viene chiamato subito dopo aver incrementato un frame
	// adesso inserire in puntatore attuale e poi incrementare
	// puntatore e calcolare anche fps
	// nota: se bisogna recuperare frame restituisce false
	// se tutto e' ok restituisce true
	bool CalcolaFPS(DWORD FrameNow)
	{
		StrBaseFPS *pFps;
		int i;
		DWORD TempoNow;
		DWORD DifNow;
		DWORD DifFrame;
		int j;
		float Totale, Divisore;

		TempoNow = (DWORD) GetTickCount64();
		pFps = &GlobTomb4.BaseFPS;
		i = pFps->IndiceNow;

		pFps->VetTempi[i] = TempoNow;
		pFps->VetFrameCount[i] = FrameNow;
		if (pFps->TotCicli < MAX_TEMPI_FPS)
			pFps->TotCicli++;
		pFps->LastIndice = i;
		pFps->IndiceNow++;
		if (pFps->IndiceNow >= MAX_TEMPI_FPS)
			pFps->IndiceNow = 0;
		// ora fare calcolo di fps, a patto di avere gia' salvato
		// tutti i valori
		if (pFps->TotCicli == MAX_TEMPI_FPS) {
			// calcolo fps
			// indietreggiare fino a trovare una distanza di almeno un secondo

			i = pFps->LastIndice;
			for (j = 0; j < MAX_TEMPI_FPS; j++) {
				DifNow = TempoNow - pFps->VetTempi[i];
				if (DifNow >= 950) {
					// ok trovato ora fare il calcolo dei frame
					DifFrame = FrameNow - pFps->VetFrameCount[i];
					DifFrame *= 1000;
					// adesso fare calcolo in floating point
					Totale = (float) DifFrame;
					Divisore = (float) DifNow;

					pFps->FPS = Totale / Divisore;
					pFps->LastFps = (int) pFps->FPS;

					if (pFps->FPS < 29.0)
						return false;
					return true;
				}
				i--;
				if (i < 0)
					i = MAX_TEMPI_FPS - 1;

			}
		}

		pFps->FPS = -1;
		pFps->LastFps = -1;
		return true;
	}

	// chiamata quando c'e' u ntrigger finish per salvare in basehub ng
	// i dati di livello attuale sotto forma di header savegame
	void SalvataggioHubNg(void)
	{
		StrBaseNG_Hub *pHub;
		int i;
		WORD NLivello;
		int Indice;
		int TotaleWords;

		NLivello = *GlobTomb4.pAdr->pLevelNow;

		// verifica global trigger prima di salvatraggio vriabili
		VerificaSingleGlobalTrigger(GT_BEFORE_SAVING_VARIABLES, NLivello, false);

		pHub = &GlobTomb4.BaseHub_NG;
		Indice = -1;
		// prima vedere se gia' c'era un record per questo livello
		for (i = 0; i < pHub->TotHub; i++) {
			if (pHub->VetNG[i].NumeroLivello == NLivello) {
				Indice = i;
				break;
			}

		}
		if (Indice == -1) {
			// non e' stato trovato
			// ora cercare un record vuoto
			if (pHub->TotHub <= 0) {
				Indice = 0;
				pHub->TotHub++;
			} else {
				i = pHub->TotHub;
				if (i >= 10) {
					// siamo gia' pieni.
					// allora sovrascrivere un record gia' presente
					i = pHub->LastIndex + 1;
					if (i >= 10)
						i = 0;
					Indice = i;
				} else {
					Indice = i;
					pHub->TotHub++;
				}
			}
		}
		pHub->LastIndex = (WORD) Indice;
		// liberare memoria
		if (pHub->VetNG[Indice].pVetWords) {
			FreeMine(pHub->VetNG[Indice].pVetWords);
			pHub->VetNG[Indice].pVetWords = NULL;
		}

		// adesso creare vettore header ng per livello attuale

		pHub->VetNG[Indice].NumeroLivello = NLivello;
		pHub->VetNG[Indice].pVetWords = NULL;
		pHub->VetNG[Indice].TotWords = 0;

		TotaleWords = 0;
		// prepara i dati variabili da salvare
		RiempiDatiVariabili();
		// salva dati di livello per Nlivello
		FormattaHeaderSavegame(&pHub->VetNG[Indice].pVetWords, &TotaleWords, false, false);

		sprintf_s(BufferLog, "Prepared HUB For Level = %d", NLivello);
		InviaLog(BufferLog);

		pHub->VetNG[Indice].TotWords = (WORD) TotaleWords;

		// ora salvare anche dati di lara
		if (pHub->LaraHUB.pNGArray)
			FreeMine(pHub->LaraHUB.pNGArray);
		pHub->LaraHUB.pNGArray = NULL;
		pHub->LaraHUB.NWords = 0;
		TotaleWords = 0;

		FormattaHeaderSavegame(&pHub->LaraHUB.pNGArray, &TotaleWords, false, true);
		pHub->LaraHUB.NWords = TotaleWords;
	}

	// e' chiamata quando c'e' stato un errore directx.
	// in pMexErrore c'e' il testo del messaggio
	// salvare informazioni dell'errore nella variabile globale LastErrorDX

	void AnalisiErroreDirectX(const char *pMexErrore, DWORD AdrRitorno)
	{
		sprintf_s(BufferLog, "ERROR DIRECT X: %s   CALLED BY: 0x%X", pMexErrore, AdrRitorno);
		InviaLog(BufferLog);

		strcpy_s(LastErrorDX, pMexErrore);
		if (GlobTomb4.TestFirstTime == false) {
			InviaLog(LastErrorDX);
			GlobTomb4.TestFirstTime = true;
		}
	}

	// viene chiamato dopo ultimo aggiornamento seguente a caricamwnto
	// di savegame
	// ossia viene chiamato SOLO dopo che e' stato caricato savegame
	// attezione, questa procedura in realta' puo' essere chiamata
	// dopo il caricamento standard  di un savegame, ma anche
	// dopo il caricamnto di un livello basato su un trigger finish di un
	// precedente livello.
	// nel caso si tratti di un livello da finish caricare il miniheader ng
	void InitDopoLoadGame(void)
	{
		int i;
		StrTempRoomFlags *pTemp;
		int IndiceRoom;
		WORD Flags;
		int NumeroCd;
		StrBaseSalvaCords *pSalva;
		StrSalvaCords *pAnim;
		StrBassHandles *pBass;
		StrItemTr4 *pItem;
		DWORD ValoreFlag;
		int Indice;
		StrScriptImage *pImage;

		if (MyGlobPrivate.TestNG_NoScript == false && GlobTomb4.TestHubLevel == true) {

			pTemp = &GlobTomb4.TempRoomFlags;

			// ripristinare status di flags di ogni room
			for (i = 0; i < pTemp->TotRooms; i++) {
				// prima eliminare tutti i flag modificabili
				IndiceRoom = TrovaIndiceMainRoom(i);
				if (IndiceRoom != -1 && pTemp->VetRoomFlags[i] != SCRIPT_IGNORE) {
					Flags = GlobTomb4.pAdr->pVetRooms[IndiceRoom].FlagsRoom & ~0x1C35;
					Flags |= pTemp->VetRoomFlags[i];
					GlobTomb4.pAdr->pVetRooms[IndiceRoom].FlagsRoom = Flags;
				}
			}
			pSalva = &GlobTomb4.BaseSalvaCoordinate;

			// reimpostare coordinate di moveable mossi
			for (i = 0; i < pSalva->TotSalvati; i++) {
				Indice = pSalva->VetIndici[i];

				pItem = &GlobTomb4.pAdr->pVetItems[Indice];
				pAnim = &pSalva->VetSalvati[i];

				pItem->OrientationH = pAnim->OrientingH;
				pItem->OrientationV = pAnim->OrientingV;
				ValoreFlag = (DWORD) pAnim->FlagInvisibile;
				if (ValoreFlag) {
					// era invisibile
					pItem->FlagsMain |= 6;
				} else {
					// renderlo di nuovo visibile
					pItem->FlagsMain &= ~4;
				}

				AggiornaPosizioneItem((short) Indice, pAnim->CordX, pAnim->CordY, pAnim->CordZ, -256);

			}

			RipristinaDatiStatici();
			RipristinaTimerOggetti();
		}

		// se e' attiva patch per aprire tutte le porte o uccidere tutti
		// i nemici farlo adesso
		if (GlobTomb4.StatusNG & SNG_OPEN_ALL_DOORS) {
			OpenAllDoors();
			GlobTomb4.StatusNG &= ~SNG_OPEN_ALL_DOORS;
		}

		if (GlobTomb4.StatusNG & SNG_KILL_ALL_ENEMIES) {
			// ucidere tutti i nemici

			tomb4::KillActiveBaddies(NULL);
		}

		if (GlobTomb4.StatusNG & SNG_UPDATE_LARA_POS) {

			AggiornaMoveLara();

			GlobTomb4.StatusNG &= ~SNG_UPDATE_LARA_POS;
		}

		//rimozione tutte le patch speciali di trlm 2009
		if (GlobTomb4.StatusNG & SNG_REMOVE_IMMORTAL_LARA) {
			// rimuove immortalita' ed eventuale trasparenza
			EsecuzioneFlipeffect(0, 93, 0, SCANF_DIRECT_CALL);

			for (i = 0; i < GlobTomb4.TotProgressiveActions; i++) {
				if (GlobTomb4.VetProgressiveActions[i].ActionType == AZ_SHOW_FLARE_LIGHT) {
					GlobTomb4.VetProgressiveActions[i].ActionType = 0;
				}

			}
			GlobTomb4.StatusNG &= ~SNG_REMOVE_IMMORTAL_LARA;
		}

		if (GlobTomb4.BaseBassHandles.TestPresente && GlobTomb4.TestAsSavegame) {

			*GlobTomb4.pAdr->pTestAudioTrackLoop = 0;
			// ripristina suoni cd
			pBass = &GlobTomb4.BaseBassHandles;
			pBass->OldCdLoop = *GlobTomb4.pAdr->pAudioTrackLoop;
			// canale primario
			NumeroCd = GlobTomb4.pDatiVariabili->CdLoopMain;
			if (NumeroCd != -1) {
				// ripristinare su canale 1 il suono NumeroCd
				// loopato
				pBass->CanaleNow = 0x40;
				pBass->StartOffset = GlobTomb4.pDatiVariabili->Canale1StartPos;
				tomb4::S_CDPlay(NumeroCd, 1);
				// ora impostare posizione
				*GlobTomb4.pAdr->pTestAudioTrackLoop = 1;
			}

			NumeroCd = GlobTomb4.pDatiVariabili->CdSingleMain;
			if (NumeroCd != -1) {
				pBass->CanaleNow = 0x40; // forzare canale 0
				pBass->StartOffset = GlobTomb4.pDatiVariabili->Canale1StartPos;
				tomb4::S_CDPlay(NumeroCd, 0);
			}

			// canale secondario
			NumeroCd = GlobTomb4.pDatiVariabili->CdLoopSecondario;
			if (NumeroCd != -1) {
				// ripristinare su canale 2 il suono NumeroCd
				// loopato
				pBass->CanaleNow = 1;
				pBass->StartOffset = GlobTomb4.pDatiVariabili->Canale2StartPos;
				tomb4::S_CDPlay(NumeroCd, 1);
			}

			NumeroCd = GlobTomb4.pDatiVariabili->CdSingleSecondario;
			if (NumeroCd != -1) {
				pBass->CanaleNow = 1;
				pBass->StartOffset = GlobTomb4.pDatiVariabili->Canale2StartPos;
				tomb4::S_CDPlay(NumeroCd, 0);
			}
		}

		if (GlobTomb4.pDatiVariabili->TestPopUp == 1 && GlobTomb4.TestHubLevel) {
			// bisogna far riprartie immagine popup
			i = GlobTomb4.pDatiVariabili->PopUpIndiceImageCmd;
			i = GlobTomb4.pBaseScriptImages->VetID[i];
			pImage = &GlobTomb4.pBaseScriptImages->VetImages[i];

			AvviaPopUpImage(GlobTomb4.pDatiVariabili->PopUpIndiceImageCmd, pImage, GlobTomb4.pDatiVariabili->PopUpContatore);
		}

		VerificaSingleGlobalTrigger(GT_AFTER_RELOADING_VARIABLES, *GlobTomb4.pAdr->pLevelNow, false);

		if (GlobTomb4.TestExtraKayak) {
			i = *GlobTomb4.pAdr->pVehicleIndex;

			if (i == -1) {
				InviaLog("ERROR: it's present extra data for kayak but it's not set any current vehicle");
			} else {
				pItem = &GlobTomb4.pAdr->pVetItems[i];
				if (pItem->SlotID != 492) {
					InviaLog("ERROR: it's present extra data for kayak but lara is not on kayak");
				} else {
					memcpy(pItem->pZonaSavegame, &GlobTomb4.DatiExtraKayak[0], 0x2e);
				}
			}
		}

		ImpostaTempoUltimoComando();
	}

	void RipristinaDatiStatici(void)
	{
		StrSalvaStatic *pRec;
		int i;
		int Tot;
		StrMeshInfo *pMesh;
		StrRoomTr4 *pRoom;

		Tot = GlobTomb4.BaseSalvaStatic.TotStatics;

		for (i = 0; i < Tot; i++) {
			pRec = &GlobTomb4.BaseSalvaStatic.VetStatics[i];

			pRoom = &GlobTomb4.pAdr->pVetRooms[pRec->Indici.IndiceRoom];
			pMesh = &pRoom->Ptr_StaticMesh[pRec->Indici.IndiceStatic];

			pMesh->OCB = pRec->Flags;
			pMesh->Orient = pRec->Orient;
			pMesh->x = pRec->OrgX;
			pMesh->y = pRec->OrgY;
			pMesh->z = pRec->OrgZ;
			pMesh->Color = pRec->Colore;
		}
	}

	// ripristina i valori timer di oggetti vari
	void RipristinaTimerOggetti(void)
	{
		StrItemTr4 *pItem;
		int i;
		StrTimerOggetti *pTimer;
		WORD *pValOscilla;
		DWORD *pQuindicesimi;
		StrBaseTimerOggetti *pBase;

		pValOscilla = &tomb4::GlobalCounter;
		pQuindicesimi = (DWORD *) &tomb4::wibble;
		pBase = &GlobTomb4.BaseTimerOggetti;

		if (pBase->TotOggetti == 0)
			return;

		*pValOscilla = pBase->Header.ValOscilla;
		*pQuindicesimi = pBase->Header.ContaQuindicesimi;

		for (i = 0; i < pBase->TotOggetti; i++) {

			pTimer = &GlobTomb4.BaseTimerOggetti.VetOggetti[i];

			pItem = &GlobTomb4.pAdr->pVetItems[pTimer->ItemIndex];

			pItem->Reserved_34 = pTimer->Campo34;
			pItem->Reserved_36 = pTimer->Campo36;
			pItem->Reserved_38 = pTimer->Campo38;
			pItem->Reserved_3A = pTimer->Campo3A;
		}
	}

	// aggiorna lara per nuova posizione attuale x,y,z calcolando la nuova
	// stanza mentre in Lara->Room  c'e' il vecchio numero di stanza
	void AggiornaMoveLara(void)
	{
		BYTE NewRoom;
		StrItemTr4 *pLara;

		NewRoom = TrovaRoomXYZ((StrMovePosition*) &GlobTomb4.pAdr->pLara->CordX);

		// ora fare i calcoli per scoprire cambio di stanza e aggiornare
		// come se fosse
		pLara = GlobTomb4.pAdr->pLara;

		AggiornaPositioneLara(pLara->CordX, pLara->CordY, pLara->CordZ, NewRoom, false);
	}

	// restituisce il numero di stanza che corrisponde a X,y,z di pPos
	BYTE TrovaRoomXYZ(StrMovePosition *pPos)
	{
		static WORD *pRoomNumber = (WORD *) &tomb4::IsRoomOutsideNo;

		tomb4::IsRoomOutside(pPos->RelX, pPos->RelY, pPos->RelZ);
		return (BYTE) *pRoomNumber;
	}

	// chiamata durante WinClose, viene usata per ripristinare valori di
	// settings prima che vengano salvate nel registro
	void RipristinaSettings(void)
	{
		static BYTE *pSetting_BumpMap = (BYTE *) &tomb4::App.BumpMapping;
		static int *pSetting_WindowX = (int*) &tomb4::App.dx.rScreen.left;
		static int *pSetting_WindowY = (int*) &tomb4::App.dx.rScreen.top;
		static int *FlagsSettingRegistro = (int*) &tomb4::App.StartFlags;
		static int *pSetting_VMod = (int*) &tomb4::App.DXInfo.nDisplayMode;
		static BYTE *pFlagsWindow = (BYTE *) &tomb4::App.dx.Flags;

		StrSalvaSettings *pDef;
		int n;

		if (GlobTomb4.TestSetup)
			return;

		*pSetting_BumpMap = GlobTomb4.DefSettings.DefBumpMapping;
		*GlobTomb4.pAdr->pSetting_Volumetric = GlobTomb4.DefSettings.DefVolumetricFX;

		pDef = &GlobTomb4.DefSettings;

		if (pDef->TestCambiate) {
			*FlagsSettingRegistro = pDef->FlagsSettingRegistro;
			*pSetting_WindowX = pDef->Setting_WindowX;
			*pSetting_WindowY = pDef->Setting_WindowY;
			*pSetting_VMod = pDef->Setting_VMode;
			n = *pFlagsWindow;
			n &= ~3;
			n |= (pDef->FlagsSettingRegistro & 3);
			*pFlagsWindow = (BYTE) n;
			pDef->TestCambiate = false;
		}
	}

	// rilsciae eventali plugins presenti
	void LiberaPlugins(void)
	{
		__try { throw __func__; } __finally {}
	}

	// procedura che riceve in ecx il puntatore a stack dove ci sono tutti
	// gli argomenti gia' pronti.
	// aggiunge all'inizio quello speciale per doslide
	void CallSlide(int CordX, int CordY, int SizeX, int SizeY, int Percentuale, DWORD Colore, DWORD ColoreFade)
	{
		// ora mettere tutti gli altri argomnti
		tomb4::DoSlider(CordX, CordY, SizeX, SizeY, Percentuale, Colore, ColoreFade, ColorSlide);
	}
}

void LoadTombNextGenerationInject_ZPatchesTomb4(bool replace)
{
	ProcessInject(0x100B027E, (unsigned int)trng::SalvaDimensioniMesh, replace);
	ProcessInject(0x100AF989, (unsigned int)trng::FreeMine, false);
	ProcessInject(0x100AFBAA, (unsigned int)trng::MallocMine, false);
	ProcessInject(0x100BBE7F, (unsigned int)trng::InitSlot, replace);
	ProcessInject(0x100BB302, (unsigned int)trng::SetSlotMotorBoat, false);
	ProcessInject(0x100BB1AD, (unsigned int)trng::SetSlotRubberBoat, false);
	ProcessInject(0x100BB457, (unsigned int)trng::SetSlotMotorBikeLara, false);
	ProcessInject(0x100BB69D, (unsigned int)trng::InitSlotKayak, false);
	ProcessInject(0x100BB568, (unsigned int)trng::InitSlotHydra, false);
	ProcessInject(0x100BB614, (unsigned int)trng::InitSlotEnemySubMarine, false);
	ProcessInject(0x100AFC45, (unsigned int)trng::EsisteDirectCB, replace);
	ProcessInject(0x100BB6C8, (unsigned int)trng::RiassegnaAssignSlotNew, false);
	ProcessInject(0x100D386D, (unsigned int)trng::ConvertiSlotAssigned, replace);
	ProcessInject(0x100BF7CA, (unsigned int)trng::IsNemicoEsploso, replace);
	ProcessInject(0x100D15B0, (unsigned int)trng::ContaItemCreatiDaSalvare, replace);
	ProcessInject(0x100D151A, (unsigned int)trng::DaSalvare, replace);
	ProcessInject(0x100D14CB, (unsigned int)trng::SlotSempreAttivo, replace);
	ProcessInject(0x100D1636, (unsigned int)trng::SalvaItemCreati, replace);
	ProcessInject(0x100B0948, (unsigned int)trng::InizializzaAdrImmediati, replace);
	ProcessInject(0x100BA3E8, (unsigned int)trng::InitCustomize, replace);
	ProcessInject(0x100BD816, (unsigned int)trng::LeggiNG_LanguageDat, replace);
	ProcessInject(0x100BD53D, (unsigned int)trng::DecryptDatString, replace);
	ProcessInject(0x100BD5BC, (unsigned int)trng::ImpostaScanCodeInputBox, replace);
	ProcessInject(0x100BD57C, (unsigned int)trng::GetValoreHex, replace);
	ProcessInject(0x100AFC13, (unsigned int)trng::ReallocMine, false);
	ProcessInject(0x100CCB8E, (unsigned int)trng::ImpostaCapelliLara, replace);
	ProcessInject(0x100C523C, (unsigned int)trng::RestorePriorita, replace);
	ProcessInject(0x100C411A, (unsigned int)trng::SalvaDimensioneSchermo, replace);
	ProcessInject(0x100B9277, (unsigned int)trng::PreparaBarCust, replace);
	ProcessInject(0x100C7C10, (unsigned int)trng::PlayExtraCD, replace);
	ProcessInject(0x100C7858, (unsigned int)trng::GestioneCdPlay, replace);
	ProcessInject(0x100C7802, (unsigned int)trng::AggiornaVolumeBass, replace);
	ProcessInject(0x100C7C3C, (unsigned int)trng::StopBassSuoni, replace);
	ProcessInject(0x100C7820, (unsigned int)trng::ShowBASSErrore, replace);
	ProcessInject(0x100AFE13, (unsigned int)trng::AddTabLogScript, replace);
	ProcessInject(0x100C0D03, (unsigned int)trng::FindSkipPhase, replace);
	ProcessInject(0x100CCD5E, (unsigned int)trng::TastoPremutoTomb4, replace);
	ProcessInject(0x100CA197, (unsigned int)trng::AllocaTitleImage, replace);
	ProcessInject(0x100C7F9E, (unsigned int)trng::AllocaBinocularImage, replace);
	ProcessInject(0x100C9ECA, (unsigned int)trng::AllocaLaserSightImage, replace);
	ProcessInject(0x100CD777, (unsigned int)trng::SalvaScreenShotTr4, replace);
	ProcessInject(0x100CD726, (unsigned int)trng::TrovaNuovoNomeShot, false);
	ProcessInject(0x100CC782, (unsigned int)trng::IsLaraPiediInPalude, replace);
	ProcessInject(0x100CD82E, (unsigned int)trng::SalvaMiniShot, replace);
	ProcessInject(0x100BCFCB, (unsigned int)trng::EseguiCallBackDirects, replace);
	ProcessInject(0x100D1C98, (unsigned int)trng::EseguiCB_SlotFirstAfter, replace);
	ProcessInject(0x100BFC9C, (unsigned int)trng::GestioneControlObject, replace);
	ProcessInject(0x100BF97F, (unsigned int)trng::GestioneBasicCollision, replace);
	ProcessInject(0x100BF90E, (unsigned int)trng::TrovaAnimazioneStop, replace);
	ProcessInject(0x100D3678, (unsigned int)trng::LaraBreath, replace);
	ProcessInject(0x100CB839, (unsigned int)trng::VerificaSingleGlobalTrigger, replace);
	ProcessInject(0x100AFE59, (unsigned int)trng::SospendiLogScript, replace);
	ProcessInject(0x100B00F7, (unsigned int)trng::RiprendiLogScript, replace);
	ProcessInject(0x100CB71C, (unsigned int)trng::OpenAllDoors, replace);
	ProcessInject(0x100C36FA, (unsigned int)trng::CalcolaCordMirror, replace);
	ProcessInject(0x100C3809, (unsigned int)trng::CalcolaOrientMirror, replace);
	ProcessInject(0x100B7DDA, (unsigned int)trng::VerificaTargetDetector, replace);
	ProcessInject(0x100CC9DD, (unsigned int)trng::CalcolaFPS, replace);
	ProcessInject(0x100CD9A4, (unsigned int)trng::SalvataggioHubNg, replace);
	ProcessInject(0x100B08A7, (unsigned int)trng::AnalisiErroreDirectX, replace);
	ProcessInject(0x100CB97E, (unsigned int)trng::InitDopoLoadGame, replace);
	ProcessInject(0x100CB58D, (unsigned int)trng::RipristinaDatiStatici, replace);
	ProcessInject(0x100CB650, (unsigned int)trng::RipristinaTimerOggetti, replace);
	ProcessInject(0x100CB7E9, (unsigned int)trng::AggiornaMoveLara, replace);
	ProcessInject(0x100CB7C0, (unsigned int)trng::TrovaRoomXYZ, replace);
	ProcessInject(0x100BDF5D, (unsigned int)trng::RipristinaSettings, replace);
	ProcessInject(0x100D0784, (unsigned int)trng::LiberaPlugins, false);
//	ProcessInject(0x100D3605, (unsigned int)trng::CallSlide, replace);
}
