#include "../inject.h"
#include "structures.h"
#include "Tomb_NextGeneration.h"
#include "../tomb4/game/control.h"
#include "DefTomb4Funct.h"
#include "MyStructures.h"
#include "trng_elevator.h"
#include "../tomb4/game/collide.h"
#include "Oggetti.h"
#include "MyStructures.h"
#include "../tomb4/game/objects.h"
#include "../tomb4/game/draw.h"

namespace trng {
	void * MallocMine(DWORD Size, const char *pDescrizione)
	{
		__try { throw __func__; } __finally {}
	}

	// libera memoria con cattura eccezioni
	bool FreeMine(void *pMemory)
	{
		__try { throw __func__; } __finally {}
	}

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

	// gli slot sono stati appena impostati con le procedure e altri valori
	// come quelli di resistenza ecc
	// ora si puo' cambiarli in questa funzione
	void InitSlot(void)
	{
		StrIndiciAssign *pAssign;
		int i,j;
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

		GlobTomb4.BaseEnemiesNotAimable.TotSlot=0;

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
}

void Inject_ZPatchesTomb4(bool replace)
{
	ProcessInject(0x100AFBAA, (unsigned int)trng::MallocMine, false);
	ProcessInject(0x100AF989, (unsigned int)trng::FreeMine, false);
	ProcessInject(0x100B027E, (unsigned int)trng::SalvaDimensioniMesh, replace);
	ProcessInject(0x100BB302, (unsigned int)trng::SetSlotMotorBoat, false);
	ProcessInject(0x100BB1AD, (unsigned int)trng::SetSlotRubberBoat, false);
	ProcessInject(0x100BB457, (unsigned int)trng::SetSlotMotorBikeLara, false);
	ProcessInject(0x100BB69D, (unsigned int)trng::InitSlotKayak, false);
	ProcessInject(0x100BB568, (unsigned int)trng::InitSlotHydra, false);
	ProcessInject(0x100BB614, (unsigned int)trng::InitSlotEnemySubMarine, false);
	ProcessInject(0x100AFC45, (unsigned int)trng::EsisteDirectCB, replace);
	ProcessInject(0x100BB6C8, (unsigned int)trng::RiassegnaAssignSlotNew, false);
	ProcessInject(0x100BBE7F, (unsigned int)trng::InitSlot, replace);
}
