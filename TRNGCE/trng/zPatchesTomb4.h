#pragma once
#include "structures.h"
#include "../tomb4/types.h"

namespace trng {
	extern DWORD &OffsetPosLara;
	extern StrBaseMemAllocata &BaseAlloc;
	extern int &LivelloOldNumber;
	extern int &GlobIndiceCombine;
	extern int &TestLoadedGame;
	extern WORD &RetSlotAss;
	extern int &SlotSceltoInventario;
	extern int &TestEsitoBow;
	extern int &ExitMyFunction;
	extern int &SalvaSlot;
	extern int &SalvaIndexItem;
	extern int &SalvaStrItem;
	extern int &SalvaCall;
	extern DWORD &MyOutResult;
	extern StrSalvaOldDebug (&VetSalvaOldDebug)[30];

	void SalvaDimensioniMesh(WORD *VetPtrMesh[], int TotMesh);
	bool FreeMine(void *pMemory);
	void * MallocMine(DWORD Size, const char *pDescrizione);
	void InitSlot(void);
	void SetSlotMotorBoat(WORD SlotBoat, WORD SlotLaraBoat);
	void SetSlotRubberBoat(WORD SlotBoat, WORD SlotLaraBoat);
	void SetSlotMotorBikeLara(void);
	void InitSlotKayak(void);
	void InitSlotHydra(void);
	void InitSlotEnemySubMarine(void);
	bool EsisteDirectCB(int CB_Numero, WORD Flags);
	void RiassegnaAssignSlotNew(void);
	WORD ConvertiSlotAssigned(WORD SlotNow);
	bool IsNemicoEsploso(WORD SlotId);
	WORD ContaItemCreatiDaSalvare(void);
	short DaSalvare(StrItemTr4 *pItem);
	bool SlotSempreAttivo(WORD Slot);
	void SalvaItemCreati(void);
	void InizializzaAdrImmediati(void);
	void InitCustomize(void);
	void LeggiNG_LanguageDat(char *pNomeFile);
	void DecryptDatString(char *pTesto);
	void ImpostaScanCodeInputBox(void);
	DWORD GetValoreHex(char *pStringaHex, bool *pTestErrore);
	void * ReallocMine(void * pOldMem, DWORD NewSize, const char *pDescrizione);
	void ImpostaCapelliLara(WORD *pFlagLivello);
	void RestorePriorita(void);
	void SalvaDimensioneSchermo(void);
	void PreparaBarCust(void);
	void PlayExtraCD(short NumeroCd, int Canale, int Loop);
	void GestioneCdPlay(short NumeroCd, int Loop);
	void AggiornaVolumeBass(void);
	void StopBassSuoni(int NumeroCanale);
	void ShowBASSErrore(char *pNome);
	bool AddTabLogScript(void);
	DWORD FindSkipPhase(void);
	bool TastoPremutoTomb4(int ScanCode);
	void AllocaTitleImage(void);
	void AllocaBinocularImage(void);
	void AllocaLaserSightImage(void);
	void SalvaScreenShotTr4(void);
	void TrovaNuovoNomeShot(char *pNuovoNome);
	bool IsLaraPiediInPalude(void);
	void SalvaMiniShot(void);
	int EseguiCallBackDirects(WORD CB_Type, WORD CBT_Flags, StrItemTr4 *pItem, short IndiceItem, bool Test1, bool Test2, void *pVertici);
	int EseguiCB_SlotFirstAfter(int CB_Value, short ItemIndex, StrItemTr4 *pItem, int CB_Flags, StrCollisionLara *pColl);
	bool GestioneControlObject(StrItemTr4 *pItem, int ItemIndex);
	void GestioneBasicCollision(StrItemTr4 *pItem, int ItemIndex);
	int TrovaAnimazioneStop(StrItemTr4 *pItem);
	void LaraBreath(tomb4::ITEM_INFO *item);
	bool VerificaSingleGlobalTrigger(short GlobalTrigger, short Parametro, bool TestIgnoraParametro);
	void SospendiLogScript(int IndiceSave);
	void RiprendiLogScript(int IndiceSave);
	void OpenAllDoors(void);
	void CalcolaCordMirror(StrPosizione *pPos);
	void CalcolaOrientMirror(StrOrient *pOrient, bool TestLara, bool TestAlternate);
	void VerificaTargetDetector(void);
	bool CalcolaFPS(DWORD FrameNow);
}

void LoadTombNextGenerationInject_ZPatchesTomb4(bool replace);
