#include "trng_elevator.h"
#include "../inject.h"
#include "Tomb_NextGeneration.h"
#include "zPatchesTomb4.h"
#include "../tomb4/game/control.h"
#include "../tomb4/game/items.h"
#include "../tomb4/game/sound.h"

namespace trng {
	// when there are elevator= command in the script, the twoblockplatform object will be redirected
	// to our custom procedure to transform it in the trng elevator
	// #callback#
	void SetSlotElevator(void)
	{
		StrSlot *pSlotNow;

		if (GlobTomb4.BaseElevator.TotElelevators > 0) {
			pSlotNow = &GlobTomb4.pAdr->pVetSlot[150];
			pSlotNow->pProcCeiling = &TwoBlockPlatformCeiling;
			pSlotNow->pProcFloor = &TwoBlockPlatformFloor;
			pSlotNow->pProcControl = &ControlTwoBlockPlatform;
		}
	}

	// sostituisce TwoBlockPlatformCeiling:
	//	;esp+14= LONG* (puntatore a long)  nuova cordy
	//	;esp+10=long  cordz
	//	;esp+C=long   cordy
	//	;esp+8=long    cordx
	//	;esp+4 = ITEM_INFO* di piattaforma
	void TwoBlockPlatformCeiling(tomb4::ITEM_INFO *item, long x, long y, long z, long *height)
	{
		__try { throw __func__; } __finally {}
	}

	// sostituisce TwoBlockPlatformFloor
	void TwoBlockPlatformFloor(tomb4::ITEM_INFO *item, long x, long y, long z, long *height)
	{
		__try { throw __func__; } __finally {}
	}

	// nuova gestione di twoblockplatform quando ci sono ascensori
	void ControlTwoBlockPlatform(short ItemIndex)
	{
		__try { throw __func__; } __finally {}
	}

	// aggiorna posizione di ItemIndex (relativo ad ascensore) aggiungedo a coordinata y
	// il valore IncY
	// aggiorna anche numero di room in modo corretto
	void AggiornaPosY(int ItemIndex, int IncY)
	{
		StrItemTr4 *pItem;
		int CordY;

		pItem = &GlobTomb4.pAdr->pVetItems[ItemIndex];
		CordY = pItem->CordY + IncY;

		AggiornaPosizioneItem((short) ItemIndex, pItem->CordX, CordY, pItem->CordZ, -0x200);
	}

	// inizializza valori per ascnsori. Preleva i dati da script elevator
	// (gia' scnadito) e li converte per il livello appena caricato
	// #callback#
	void PreparaElevator(void)
	{
		static const char *VetMode[2] = {"New Level", "Load Savegame"};

		WORD ItemIndex;
		short ValShort;
		StrGlobalTrigger *pGlobal;
		StrElevator *pAscensore;
		StrScriptElevator *pElevatore;
		WORD TotElevators;
		int IdElevatore;
		WORD NSlot;
		WORD i, j, z;
		int Indice;
		int DoorY;
		bool TestSavegame;
		StrItemTr4 *pDoor;
		DWORD DoorX, DoorZ;
		int GapY;
		StrItemTr4 *pItem;
		StrRectPos *pRect;
		int OrgX, OrgZ;

		if (GlobTomb4.BaseElevator.TotElelevators == 0)
			return;
		// se = 4 allora e' stato caricato un savegame
		if (GlobTomb4.TestAsSavegame)
			TestSavegame = true;
		else
			TestSavegame = false;

		AddTabLogScript();

		if (GlobTomb4.DebugModeCounter)
			ShowMsgDebug("Initialize Elevators. Mode=%s", VetMode[(int) TestSavegame], 0);
		AddTabLogScript();

		TotElevators = GlobTomb4.BaseElevator.TotElelevators;

		for (i = 0; i < TotElevators; i++) {
			pElevatore = &GlobTomb4.BaseElevator.VetScriptElevators[i];
			pAscensore = &GlobTomb4.BaseElevator.VetAscensori[i];

			// convertire indice di elevatore
			ItemIndex = pElevatore->IndiceElevatore;
			IdElevatore = ItemIndex;

			if (GlobTomb4.DebugModeCounter)
				ShowMsgDebug("Elevator=%d", IdElevatore, 0);
			AddTabLogScript();

			if (ItemIndex == SCRIPT_IGNORE) {
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("ERROR: missing index for elevator item in Elevator=IGNORE", 0, 0);
				SubTabLogScript();
				GlobTomb4.BaseElevator.TotElelevators = 0;
				break;
			}

			pElevatore->IndiceElevatore = GlobTomb4.VetRemapObjects[ItemIndex];
			if (pElevatore->IndiceElevatore == SCRIPT_IGNORE) {

				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("ERROR elevator: Wrong elevator index (%d) in Elevator=%d script dat", ItemIndex, ItemIndex);
				SubTabLogScript();
				GlobTomb4.BaseElevator.TotElelevators = 0;
				break;
			}

			// convertire indice index door
			ItemIndex = pElevatore->IndexFirstDoor;
			if (ItemIndex != SCRIPT_IGNORE) {

				pElevatore->IndexFirstDoor = GlobTomb4.VetRemapObjects[ItemIndex];

				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("Index first door: NgleIndex=%d  TombIndex=%d", ItemIndex, pElevatore->IndexFirstDoor);

				if (pElevatore->IndexFirstDoor == SCRIPT_IGNORE) {

					if (GlobTomb4.DebugModeCounter)
						ShowMsgDebug("ERROR: Wrong first door index (%d) in Elevator=%d", ItemIndex, IdElevatore);

					SubTabLogScript();
					GlobTomb4.BaseElevator.TotElelevators = 0;
					break;
				}

				if (pElevatore->Flags & EF_DOUBLE_DOOR) {
					pElevatore->IndexFirstDoorSecodnary = GlobTomb4.VetRemapObjects[ItemIndex + 1];

					if (pElevatore->IndexFirstDoorSecodnary == SCRIPT_IGNORE) {
						if (GlobTomb4.DebugModeCounter)
							ShowMsgDebug("ERROR in Elevator command: cann''t find the paired door of double door with main door index = %d", ItemIndex, 0);

						SubTabLogScript();
						GlobTomb4.BaseElevator.TotElelevators = 0;
						break;
					}
				}

				// imposta flag interno per segnalare se e' una porta animating
				// o una porta tradizionale
				// qui c'e' il crash
				NSlot = GlobTomb4.pAdr->pVetItems[pElevatore->IndexFirstDoor].SlotID;
				if (NSlot < 0x142 || NSlot > 0x14f) {
					// e' una porta animating
					pElevatore->Flags |= EF_ANIM_DOOR;

					// impostare la posizione e il tipo di incremento
					// per la porta anim
					CalcolaInfoAnimDoor(pElevatore);
				}

			} else {
				if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
					ShowMsgDebug("No door for current elevator", 0, 0);
				pElevatore->Flags &= ~EF_MULTI_DOORS;

				pElevatore->Flags &= ~EF_SINGLE_DOOR;
			}
			// convertire indice keyupad (se presente)
			if (pElevatore->Flags & EF_INNER_KEYPAD) {
				ItemIndex = pElevatore->KeyPadIndex;
				if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
					ShowMsgDebug("Required INNER_KEYPAD with index=%d", ItemIndex, 0);

				if (ItemIndex == SCRIPT_IGNORE) {

					if (GlobTomb4.DebugModeCounter)
						ShowMsgDebug("ERROR: is missing index for inner keypad", 0, 0);

					pElevatore->Flags &= ~EF_INNER_KEYPAD;

					SubTabLogScript();
					GlobTomb4.BaseElevator.TotElelevators = 0;
					break;
				}
				pElevatore->KeyPadIndex = GlobTomb4.VetRemapObjects[ItemIndex];
				if (pElevatore->KeyPadIndex == SCRIPT_IGNORE) {

					if (GlobTomb4.DebugModeCounter)
						ShowMsgDebug("ERROR elevator: Wrong inner keypad index (%d) in script dat", ItemIndex, 0);

					SubTabLogScript();
					GlobTomb4.BaseElevator.TotElelevators = 0;
					break;
				}

				pItem = &GlobTomb4.pAdr->pVetItems[pElevatore->KeyPadIndex];

				// correggere posizione di keypad
				// inserire anche i dati di orientamernto che deve
				// avere lara per essere difornte al keypad
				pElevatore->OrientLaraPerKeyPad = pItem->OrientationH;
				// ora inserire i valori di controllo dei limiti
				// del settore, anzi, calcolare subito i limiti
				// ristretti
				pRect = &pElevatore->LimitiBloccoKeypad;
				OrgX = pItem->CordX & ~0x3ff;
				OrgZ = pItem->CordZ & ~0x3ff;
				switch ((WORD) pItem->OrientationH) {
				case 0x8000:

					pItem->CordZ += 0x20;
					// keypad verso est (ngle) lara deve essere verso ovest
					pRect->MinZ = OrgZ;
					pRect->MaxZ = OrgZ + 300;
					pRect->MinX = OrgX + 256;
					pRect->MaxX = OrgX + 768;
					break;
				case 0x0000:

					pItem->CordZ -= 0x20;
					// keypad rivolto verso ovest
					pRect->MinZ = OrgZ + 724;
					pRect->MaxZ = OrgZ + 1024;
					pRect->MinX = OrgX + 256;
					pRect->MaxX = OrgX + 768;
					break;
				case 0x4000:
					// rivolta verso sud

					pItem->CordX -= 0x20;
					pRect->MinX = OrgX + 724;
					pRect->MaxX = OrgX + 1024;
					pRect->MinZ = OrgZ + 256;
					pRect->MaxZ = OrgZ + 768;
					break;
				case 0xc000:
					// rivolto verso nord

					pItem->CordX += 0x20;

					pRect->MinX = OrgX;
					pRect->MaxX = OrgX + 300;

					pRect->MinZ = OrgZ + 256;
					pRect->MaxZ = OrgZ + 768;
					break;
				}
			}

			// convertire eventuali frameitems
			for (j = 0; j < pElevatore->TotFrameItems; j++) {
				ItemIndex = pElevatore->VetFrameItems[j];
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("FrameItem[%d] with index=%d", j + 1, ItemIndex);

				if (ItemIndex != SCRIPT_IGNORE) {
					pElevatore->VetFrameItems[j] = GlobTomb4.VetRemapObjects[ItemIndex];
					if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
						ShowMsgDebug("Tomb Frame index =%d", pElevatore->VetFrameItems[j], 0);

					if (pElevatore->VetFrameItems[j] == SCRIPT_IGNORE) {

						if (GlobTomb4.DebugModeCounter)
							ShowMsgDebug("ERROR: invalid frame index %d", ItemIndex, 0);
						SubTabLogScript();
						SubTabLogScript();
						GlobTomb4.BaseElevator.TotElelevators = 0;
						return;
					}
				}

			}
			pElevatore->pItem = &GlobTomb4.pAdr->pVetItems[pElevatore->IndiceElevatore];

			// se abbiamo appena caricato da savegame, aggiornare
			// tutti i valori

			if (TestSavegame == true) {

				pElevatore->FirstFloorY = pAscensore->FirstFloorY;

				// aggiornare subito cordy di elevatore
				pElevatore->pItem->CordY = pAscensore->CordYElevator;
				// se e' con porta singola aggiornare anche il cordy di porta
				if (pElevatore->Flags & EF_SINGLE_DOOR) {
					GlobTomb4.pAdr->pVetItems[pElevatore->IndexFirstDoor].CordY = pAscensore->CordYElevator;
				}
				// aggiornare cordy di tutti i frame
				for (j = 0; j < pElevatore->TotFrameItems; j++) {
					Indice = pElevatore->VetFrameItems[j];
					pItem = &GlobTomb4.pAdr->pVetItems[Indice];
					if (pItem->CordY != pAscensore->VetCordYFrame[j]) {
						AggiornaPosizioneItem((short) Indice, pItem->CordX, pAscensore->VetCordYFrame[j], pItem->CordZ, -0x200);
					}
				}
			}

			// se ci sono multidoor scoprire tutte le altre door
			if (pElevatore->Flags & EF_MULTI_DOORS) {

				ItemIndex = pElevatore->IndexFirstDoor;
				if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
					ShowMsgDebug("Required EF_MULTI_DOORS. First Door tomb index=%d", ItemIndex, 0);

				pElevatore->TotDoors = pElevatore->TotFloors;
				pDoor = &GlobTomb4.pAdr->pVetItems[ItemIndex];
				DoorX = pDoor->CordX;
				DoorY = pDoor->CordY;
				DoorZ = pDoor->CordZ;

				sprintf_s(BufferLog, "FirstDoor:  X=%d  Y=%d Z=%d", DoorX, DoorY, DoorZ);
				if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
					ShowMsgDebug(BufferLog, 0, 0);

				GapY = pElevatore->ClickDistance * 256;
				pElevatore->VetDoors[0] = pElevatore->IndexFirstDoor;
				if (pElevatore->Flags & EF_DOUBLE_DOOR) {
					if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
						ShowMsgDebug("Required EF_DOUBLE_DOOR: first secondary door index=%d", pElevatore->IndexFirstDoorSecodnary, 0);

					pElevatore->VetDoorsSecondary[0] = pElevatore->IndexFirstDoorSecodnary;
				}

				for (j = 1; j < pElevatore->TotDoors; j++) {
					DoorY -= GapY;

					if (GlobTomb4.DebugModeCounter)
						ShowMsgDebug("Searching door for %dst floor with CordY=%d", j + 1, DoorY);

					// ora cercare una porta che abbia coordinate di door
					for (z = 0; z < *GlobTomb4.pAdr->pTotItems; z++) {
						pDoor = &GlobTomb4.pAdr->pVetItems[z];

						if (pDoor->CordX == DoorX && pDoor->CordY == DoorY && pDoor->CordZ == DoorZ && pDoor->SlotID >= 322 && pDoor->SlotID <= 335)
							break;
					}

					if (z == *GlobTomb4.pAdr->pTotItems) {

						if (GlobTomb4.DebugModeCounter)
							ShowMsgDebug("ERROR: cann''t find the door for %dth floor", j + 1, 0);

					} else {

						pElevatore->VetDoors[j] = z;
						if (GlobTomb4.DebugModeCounter)
							ShowMsgDebug("Found for floor %dst the item door = %d", j + 1, GetNgleIndice(z));

						if (z != SCRIPT_IGNORE && (pElevatore->Flags & EF_DOUBLE_DOOR) != 0) {
							// localizzare porta doppia
							z = (WORD) GetNgleIndice(z);

							pElevatore->VetDoorsSecondary[j] = GlobTomb4.VetRemapObjects[z + 1];

							if (pElevatore->VetDoorsSecondary[j] == SCRIPT_IGNORE) {
								sprintf_s(BufferLog, "ERROR in Elevator command: cann't find the paired door of double door with main door index = %d", z);
								InviaLog(BufferLog);
							}
						}
					}

				}
			}

			// ora inizializza dati dinamici di ascensore
			// a meno che non abbiamo appena caricato savegame

			if (TestSavegame == false) {
				pElevatore->FirstFloorY = GlobTomb4.pAdr->pVetItems[pElevatore->IndiceElevatore].CordY;
				if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
					ShowMsgDebug("New Level Mode: reset elevator record", 0, 0);
				pAscensore->FloorNow = 0;
				pAscensore->FloorTarget = 0;
				pAscensore->IncY = 0;
				// salvare origine y

				pAscensore->Soffitto = 0;
				pAscensore->Status = EST_ATTESA;
				pAscensore->LastIncy = pElevatore->Speed;
			}
			// calcolare cordy di massima altezza di ascensore
			pElevatore->MaxYFloor = pElevatore->FirstFloorY - pElevatore->ClickDistance * 256 * pElevatore->TotFloors;
			pElevatore->MaxRoom = pElevatore->pItem->Room;
			if (GlobTomb4.DebugModeCounter && !(GlobTomb4.pDiagnostica->DgxExtra & EDGX_CONCISE_SCRIPT_LOG))
				ShowMsgDebug("MaxYFloor=%d  Highest Room=%d", pElevatore->MaxYFloor, GetNgleRoomIndice(pElevatore->pItem->Room));

			// ora usare numero di stanza per calcolare coordinata y di soffitto
			pElevatore->MaxYFloor = GlobTomb4.pAdr->pVetRooms[pElevatore->MaxRoom].OrigYBottom - 1;

			// attivare item
			tomb4::AddActiveItem(pElevatore->IndiceElevatore);
			if (TestSavegame == false) {
				// controllare che porta di piano attuale sia aperta
				if (((pElevatore->Flags & EF_MULTI_DOORS) || (pElevatore->Flags & EF_SINGLE_DOOR)) && (pElevatore->Flags & EF_MODE_YO_YO) == 0) {

					if (pElevatore->Flags & EF_MULTI_DOORS) {
						ItemIndex = pAscensore->FloorNow;
						Indice = pElevatore->VetDoors[ItemIndex];

						if (GlobTomb4.DebugModeCounter)
							ShowMsgDebug("MULTI_DOORS: Open door=%d", GetNgleIndice(Indice), 0);

						EsecuzioneActionTrigger(0, 0x011A, Indice, SCANF_DIRECT_CALL);

						if (pElevatore->Flags & EF_DOUBLE_DOOR) {
							if (GlobTomb4.DebugModeCounter)
								ShowMsgDebug("Oper double door=%d", GetNgleIndice(pElevatore->VetDoorsSecondary[ItemIndex]), 0);
							EsecuzioneActionTrigger(0, 0x011A, pElevatore->VetDoorsSecondary[ItemIndex], SCANF_DIRECT_CALL);
						}

					} else {
						// se e' singola porta usare indice fornito
						Indice = pElevatore->IndexFirstDoor;
						if (GlobTomb4.DebugModeCounter)
							ShowMsgDebug("SINGLE_DOOR: Open door %d", GetNgleIndice(Indice), 0);
						// aprire porta
						if (pElevatore->Flags & EF_ANIM_DOOR) {
							// muovere porta animating

							GestionePortaAnimating(pElevatore, true);
						} else {
							// aprire porta tradizionale
							EsecuzioneActionTrigger(0, 0x011A, Indice, SCANF_DIRECT_CALL);

							if (pElevatore->Flags & EF_DOUBLE_DOOR) {
								if (GlobTomb4.DebugModeCounter)
									ShowMsgDebug("Open double door %d", GetNgleIndice(pElevatore->IndexFirstDoorSecodnary), 0);
								EsecuzioneActionTrigger(0, 0x011A, pElevatore->IndexFirstDoorSecodnary, SCANF_DIRECT_CALL);
							}
						}
					}
				}

				if (pElevatore->Flags & EF_MODE_YO_YO) {
					// inserire comando per muovere verso l'alto
					pAscensore->Status = EST_INIZIO_MOVIMENTO;
					pAscensore->FloorTarget = (BYTE) (pElevatore->TotFloors - 1);
				}

				if (pElevatore->Flags & EF_MODE_STOP_AND_GO) {
					// attivare apertura porta e attesa
					pAscensore->Status = EST_OPEN_AND_STOP;
					pAscensore->FloorTarget = 0;
				}
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("Floor Target = %dst", pAscensore->FloorTarget + 1, 0);
			}
			SubTabLogScript();

		}
		// se ci sono global trigger relativi a indici ascensori
		// convetitre adesso i loro indici da ngle a tomb4
		for (i = 0; i < GlobTomb4.pBaseGlobalTriggers->TotTriggers; i++) {
			pGlobal = &GlobTomb4.pBaseGlobalTriggers->VetTriggers[i];

			if (pGlobal->GlobalTrigger == GT_ELEVATOR_STOPS_AT_FLOOR || pGlobal->GlobalTrigger == GT_ELEVATOR_STARTS_FROM_FLOOR) {

				// convertire valore parametro
				ValShort = pGlobal->Parameter & 0x0fff;
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("Convert Elevator Index=%d for GlobalTrigger=%d", ValShort, pGlobal->Id);

				ValShort = GlobTomb4.VetRemapObjects[ValShort];
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("New tomb index = %d", ValShort, 0);
				ValShort |= (pGlobal->Parameter & 0xf000);
				pGlobal->Parameter = ValShort;
			}
		}

		// attivare evento global trigger per ascensore arrivato al primo
		// piano per tutti gli ascensori (a patto che non siano in fase
		// caricasavegame
		if (TestSavegame == false) {
			for (i = 0; i < GlobTomb4.BaseElevator.TotElelevators; i++) {
				// evento per piano 1
				ValShort = GlobTomb4.BaseElevator.VetScriptElevators[i].IndiceElevatore;
				ValShort |= 0x1000;
				ImpostaEventoNow(GT_ELEVATOR_STOPS_AT_FLOOR, ValShort);
			}
		}
		SubTabLogScript();
		SubTabLogScript();
	}

	// imposta i dati usati per muovere porta anim door di elevatore
	void CalcolaInfoAnimDoor(StrScriptElevator *pElevatore)
	{
		StrItemTr4 *pPorta;
		WORD Orient;
		StrInfoAnimDoor *pSecondario;
		StrItemTr4 *pPorta2;
		bool TestSecondario;

		if (pElevatore->Flags & EF_DOUBLE_DOOR) {
			TestSecondario = true;
		} else {
			TestSecondario = false;
		}

		pPorta = &GlobTomb4.pAdr->pVetItems[pElevatore->IndexFirstDoor];
		pPorta2 = NULL;
		if (TestSecondario) {
			pPorta2 = &GlobTomb4.pAdr->pVetItems[pElevatore->IndexFirstDoorSecodnary];
		}

		Orient = (WORD) pPorta->OrientationH;
		pSecondario = &pElevatore->AnimDoorSecondary;

		if (TestSecondario == true) {
			// se ci sono due porte il movimento e' opposto
			// le porte devono scivolare verso l'esterno
			switch (Orient) {
			case 0x8000:
				// muovere verso nord
				pElevatore->AnimDoor.FlagsMov = fmov_CordX;
				pElevatore->AnimDoor.Incremento = 45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordX;
				pElevatore->AnimDoor.CordAperta = pPorta->CordX + 1024;
				// secondaria
				pSecondario->FlagsMov = fmov_CordX;
				pSecondario->Incremento = -45;
				pSecondario->CordChiusa = pPorta2->CordX;
				pSecondario->CordAperta = pPorta2->CordX - 1024;
				break;
			case 0xc000:
				// muovere verso est
				pElevatore->AnimDoor.FlagsMov = fmov_CordZ;
				pElevatore->AnimDoor.Incremento = -45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordZ;
				pElevatore->AnimDoor.CordAperta = pPorta->CordZ - 1024;

				// muovere verso est
				pSecondario->FlagsMov = fmov_CordZ;
				pSecondario->Incremento = 45;
				pSecondario->CordChiusa = pPorta->CordZ;
				pSecondario->CordAperta = pPorta->CordZ + 1024;
				break;
			case 0x0000:
				// muovere verso sud
				pElevatore->AnimDoor.FlagsMov = fmov_CordX;
				pElevatore->AnimDoor.Incremento = -45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordX;
				pElevatore->AnimDoor.CordAperta = pPorta->CordX - 1024;

				// muovere verso sud
				pSecondario->FlagsMov = fmov_CordX;
				pSecondario->Incremento = 45;
				pSecondario->CordChiusa = pPorta2->CordX;
				pSecondario->CordAperta = pPorta2->CordX + 1024;

				break;
			case 0x4000:
				// muovere verso ovest
				pElevatore->AnimDoor.FlagsMov = fmov_CordZ;
				pElevatore->AnimDoor.Incremento = 45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordZ;
				pElevatore->AnimDoor.CordAperta = pPorta->CordZ + 1024;
				// muovere verso ovest
				pSecondario->FlagsMov = fmov_CordZ;
				pSecondario->Incremento = -45;
				pSecondario->CordChiusa = pPorta2->CordZ;
				pSecondario->CordAperta = pPorta2->CordZ - 1024;
				break;
			}

		} else {
			// normale

			switch (Orient) {
			case 0x8000:
				// muovere verso nord
				pElevatore->AnimDoor.FlagsMov = fmov_CordX;
				pElevatore->AnimDoor.Incremento = -45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordX;
				pElevatore->AnimDoor.CordAperta = pPorta->CordX - 1024;

				break;
			case 0xc000:
				// muovere verso est
				pElevatore->AnimDoor.FlagsMov = fmov_CordZ;
				pElevatore->AnimDoor.Incremento = 45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordZ;
				pElevatore->AnimDoor.CordAperta = pPorta->CordZ + 1024;
				break;
			case 0x0000:
				// muovere verso sud
				pElevatore->AnimDoor.FlagsMov = fmov_CordX;
				pElevatore->AnimDoor.Incremento = 45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordX;
				pElevatore->AnimDoor.CordAperta = pPorta->CordX + 1024;
				break;
			case 0x4000:
				// muovere verso ovest
				pElevatore->AnimDoor.FlagsMov = fmov_CordZ;
				pElevatore->AnimDoor.Incremento = -45;
				pElevatore->AnimDoor.CordChiusa = pPorta->CordZ;
				pElevatore->AnimDoor.CordAperta = pPorta->CordZ - 1024;
				break;
			}
		}
	}

	int GetNgleRoomIndice(int TombIndice)
	{
		int i;

		for (i = 0; i < MAX_ROOMS; i++) {
			if (GlobTomb4.VetRemapRooms[i] == TombIndice)
				return i;

		}
		return -1;
	}

	// questa funziona crea l'azione progressiva peraprire o chiudere la porta

	void GestionePortaAnimating(StrScriptElevator *pElevatore, bool TestApri)
	{
		// aprire o chiudere porta, usare un azione progressiva
		// calcolare incrmeento

		int IndiceAzione;
		StrProgressiveAction *pAzione;
		StrInfoAnimDoor *pAnimDoor;
		StrItemTr4 *pPorta;

		pAnimDoor = &pElevatore->AnimDoor;

		pPorta = &GlobTomb4.pAdr->pVetItems[pElevatore->IndexFirstDoor];

		IndiceAzione = CreaNuovaAzioneProgressiva();

		pAzione = &GlobTomb4.VetProgressiveActions[IndiceAzione];
		pAzione->ActionType = AZ_MOVE_ANIMATING;
		AggiungiItemMosso(pElevatore->IndexFirstDoor);
		pAzione->Arg2 = pAnimDoor->FlagsMov;
		pAzione->ItemIndex = pElevatore->IndexFirstDoor;
		pAzione->VetArg[3] = 0;  // prima esecuzione

		if (TestApri == true) {
			pAzione->VetArg[0] = pAnimDoor->Incremento;
			pAzione->VetArg[1] = pAnimDoor->CordAperta;
			tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_ANIMATING_DOOR_OPEN], (tomb4::PHD_3DPOS *) &pPorta->CordX, 0);
		} else {
			// chiuderla
			pAzione->VetArg[0] = -pAnimDoor->Incremento;
			pAzione->VetArg[1] = pAnimDoor->CordChiusa;
			tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_ANIMATING_DOOR_CLOSE], (tomb4::PHD_3DPOS *) &pPorta->CordX, 0);
		}

		// se c'e' porta secondaria crea un'altra azione progressiva
		// per muovere anche l'altra porta
		if (pElevatore->Flags & EF_DOUBLE_DOOR) {

			pAnimDoor = &pElevatore->AnimDoorSecondary;

			IndiceAzione = CreaNuovaAzioneProgressiva();

			pAzione = &GlobTomb4.VetProgressiveActions[IndiceAzione];
			pAzione->ActionType = AZ_MOVE_ANIMATING;
			AggiungiItemMosso(pElevatore->IndexFirstDoorSecodnary);
			pAzione->Arg2 = pAnimDoor->FlagsMov;
			pAzione->ItemIndex = pElevatore->IndexFirstDoorSecodnary;
			pAzione->VetArg[3] = 0;  // prima esecuzione

			if (TestApri == true) {
				pAzione->VetArg[0] = pAnimDoor->Incremento;
				pAzione->VetArg[1] = pAnimDoor->CordAperta;
			} else {
				// chiuderla
				pAzione->VetArg[0] = -pAnimDoor->Incremento;
				pAzione->VetArg[1] = pAnimDoor->CordChiusa;
			}
		}
	}

	// salva globtomb4.baseeventsnow  l'evento attuale
	// nota: se e' gia' accaduto esattamente guuale lo ignora
	void ImpostaEventoNow(short GT_Evento, short Parameter)
	{
		StrBaseEventiNow *pBase;
		int i;

		pBase = &GlobTomb4.BaseEventiNow;

		for (i = 0; i < pBase->TotEventi; i++) {
			if (pBase->VetEventi[i].GlobalTrigger == GT_Evento && pBase->VetEventi[i].Parameter == Parameter)
				return;
		}

		// non c'era, aggiungerlo adesso
		i = pBase->TotEventi;
		if (i >= MAX_EVENTI_NOW) {
			InviaLog("ERROR: reached max number of Events for global trigger");
			return;
		}

		pBase->VetEventi[i].GlobalTrigger = GT_Evento;
		pBase->VetEventi[i].Parameter = Parameter;
		pBase->TotEventi++;
	}
}

void LoadTombNextGenerationInject_TrngElevator(bool replace)
{
	ProcessInject(0x100989A4, (unsigned int)trng::SetSlotElevator, replace);
	ProcessInject(0x10097457, (unsigned int)trng::TwoBlockPlatformCeiling, false);
	ProcessInject(0x100973F2, (unsigned int)trng::TwoBlockPlatformFloor, false);
	ProcessInject(0x10096116, (unsigned int)trng::ControlTwoBlockPlatform, false);
	ProcessInject(0x10095E65, (unsigned int)trng::AggiornaPosY, replace);
	ProcessInject(0x10097853, (unsigned int)trng::PreparaElevator, replace);
	ProcessInject(0x100974A7, (unsigned int)trng::CalcolaInfoAnimDoor, replace);
	ProcessInject(0x10097816, (unsigned int)trng::GetNgleRoomIndice, replace);
	ProcessInject(0x10095B44, (unsigned int)trng::GestionePortaAnimating, replace);
	ProcessInject(0x10095D18, (unsigned int)trng::ImpostaEventoNow, replace);
}
