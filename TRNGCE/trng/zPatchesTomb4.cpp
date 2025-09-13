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

namespace trng {
	DWORD &OffsetPosLara = *reinterpret_cast<decltype(&OffsetPosLara)>(0x10679E5C);
	StrBaseMemAllocata &BaseAlloc = *reinterpret_cast<decltype(&BaseAlloc)>(0x10658848);
	int &LivelloOldNumber = *reinterpret_cast<decltype(&LivelloOldNumber)>(0x10679F50); // usato per passarlo a callback cbInitLevel
	int &GlobIndiceCombine = *reinterpret_cast<decltype(&GlobIndiceCombine)>(0x10679E68);

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

			SetSlotRubberBoat(pAssign->IndiceRubberBoat , pAssign->IndiceAnimRubberBoat);
		}

		if (pAssign->IndiceMotorBoat != -1 && pAssign->IndiceAnimMotorBoat != -1) {
			// inizializzare slot per MOTOR BOAT da assign slot
			SetSlotMotorBoat(pAssign->IndiceMotorBoat, pAssign->IndiceAnimMotorBoat);
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
			pSlotNow->Flags = i;
			pSlotNow->ShatterableMeshes  = 6;
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
					pSlotNow->Vitality = (short) 0xc000;
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
					pSlotNow->Vitality = (short) 0xc000;
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
					pSlotNow->Vitality = (short) 0xc000;
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
		GlobTomb4.pAdr->pVetDrip = &tomb4::lara.electric;
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
}
