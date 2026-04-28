#pragma once
#include "structures.h"
#include "../tomb4/types.h"

namespace trng {
	extern char (&ZonaReplace)[32000];
	extern BYTE &TestAppenaAvviatoGame;

	void ProcMyBridgeFloor(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY);
	void ProcMyBridgeCeiling(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY);
	void TightRopeCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll);
	void InitialiseTightRope(short item_number);
	void InitialiseGuardian(short item_number);
	void GuardianControl(short item_number);
	void ParallelBarCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll);
	void ControlBubble(short fx_number);
	void InitializeFishGenerator(short IndiceGeneratore);
	void TriggerFish(short ItemIndex);
	void TorpedoControl(short item_number);
	void DiverControl(short item_number);
	void CreaFinestraAvviso(void);
	bool IsModoWindowed(void);
	void CreaBlackWindow(void);
	long FAR PASCAL WindowBlackProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void DisattivaAnimWindow(void);
	void NascondiTaskBar(void);
	HFONT CreaWindowsFontForCB(StrWindowsFont *pFont, bool TestNoResize);
	HFONT CreaWindowsFont(StrWindowsFont *pFont, bool TestNoResize);
	int LeggiVariabile(WORD CodiceVariabile);
	const char *GetNomeVariabile(WORD Codice);
	void MostraDiario(StrBaseDiario *pDiario);
	void AllocaDiario(StrBaseDiario *pDiario);
	void LiberaDiario(StrBaseDiario *pDiario);
	void LiberaPaginaDiario(StrBaseDiario *pDiario);
	bool ScopriSospendiAudioDiario(StrBaseDiario *pDiario);
	void SospendiAudio(int NuovoCd, int NuovoTestLoop);
	bool AllocaPaginaDiario(StrBaseDiario *pDiario, int IndicePagina);
	RECT *EstraeDatiFrame(char *pSorgente, const char *pTag, bool* pTestErrore);
	void ConvertiRectMicroUnits(RECT *pRect);
	void SuonaAudioPagina(StrBaseDiario *pDiario, int IndicePagina);
	int ShowImageProp(HDC HdcOut, RECT *pMioRect);
	void StampaTestoPaginaNow(HDC MioHdc, StrBaseDiario *pDiario);
	void ImpostaWindowsFont(StrWindowsFont *pFont, HDC MioHdc, bool TestNonCancellare, bool TestNonResize);
	int StampaTestoWindowsForCB(RECT *pRect, StrWindowsFont *pFont, HDC MioHdc, char *pTesto, bool *pTestErrore, bool TestSoloProva, DWORD WTF_Flags);
	int StampaTestoWindows(RECT *pRect, StrWindowsFont *pFont, HDC MioHdc, char *pTesto, bool *pTestErrore, bool TestSoloProva, DWORD WTF_Flags);
	char *ConvertiStringaBinaria(char *pTesto, DWORD *pSize);
	DWORD CreaFlagDT(StrWindowsFont *pFont);
	wchar_t * ReplaceVarPlaceFoldersW(wchar_t *pTesto);
	wchar_t * Char2Unicode(char *pTesto);
	char *LeggiVariabileTesto(WORD CodiceVariabile);
	char *ReplaceVarPlaceFolders(char *pTesto);
	char *TrovaDivisioneTesto(RECT *pRect, StrWindowsFont *pFont, HDC MioHdc, char *pTesto);
	void ZoomImageDiario(RECT *pFine, HDC HdcSource, int SrcSizeX, int SrcSizeY, bool TestTransparent);
	void BeginCicloDraw(void);
	void EndCicloDraw(void);
	void RiprendiAudio(void);
	void ElaboraTriggerFMV(int NumeroFmv);
	void PreparaLancioFilmato(int NumeroFMV);
	bool TrovaFileFMV(char NomeFmv[], int Indice);
	void SospendiSuoniPerFMV(void);
	bool CollideItemConCustom(StrItemTr4 *pItem, StrCustomItem *pCustom, int Bordo);
	StrRettangolo *RuotaBoxAbs(DWORD CX, DWORD CZ, StrAbsBoxCollision *pBox, short Gradi);
	void RuotaPuntoInt(DWORD CX, DWORD CZ, int * pPX, int * pPZ, short Gradi);
	bool IsInsideRettangolo(DWORD x, DWORD z, StrRettangolo *pRet);
}

void LoadTombNextGenerationInject_Oggetti(bool replace);
