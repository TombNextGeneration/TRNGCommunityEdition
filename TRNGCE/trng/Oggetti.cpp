#include "Oggetti.h"
#include <cstdlib>
#include "../inject.h"
#include "Tomb_NextGeneration.h"
#include "zRoomEditor.h"
#include "zPatchesTomb4.h"
#include "../tomb4/specific/audio.h"
#include "../tomb4/game/sound.h"
#include "../tomb4/specific/output.h"
#include "../tomb4/specific/time.h"
#include "../tomb4/specific/winmain.h"
#include "../tomb4/specific/cmdline.h"
#include "../tomb4/game/tomb4fx.h"
#include "../tomb4/game/draw.h"
#include "../tomb4/specific/3dmath.h"
#define malloc ((void *(*)(size_t)) 0x10135531)
#define realloc ((void *(*)(void *, size_t)) 0x101353F9)
#define free ((void (*)(void *)) 0x101355BD)

namespace trng {
	char (&ZonaReplace)[32000] = *reinterpret_cast<decltype(&ZonaReplace)>(0x10193C68);
	BYTE &TestAppenaAvviatoGame = *reinterpret_cast<decltype(&TestAppenaAvviatoGame)>(0x10193418);

	// usa sottoprocedura SubBridgeTilt(pBridge, CordX, CordZ)
	void ProcMyBridgeFloor(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY)
	{
		__try { throw __func__; } __finally {}
	}

	void ProcMyBridgeCeiling(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY)
	{
		__try { throw __func__; } __finally {}
	}

	void TightRopeCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseTightRope(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseGuardian(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void GuardianControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	// ------- codici barra parallela ---------------------------------------
	// procedura collisione di tomb5 originale per gestire giravolte
	// di lara intorno alla parallelbar
	void ParallelBarCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll)
	{
		__try { throw __func__; } __finally {}
	}

	// procedura redirezionata per bubble per poter lanciare singolo
	// oggetto come arpione
	void ControlBubble(short fx_number)
	{
		__try { throw __func__; } __finally {}
	}

	// ****************** FUNZIONI PER FISH ************************************
	// riposiziona l'emitter in modo che sia in una posizione centrale
	void InitializeFishGenerator(short IndiceGeneratore)
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerFish(short ItemIndex)
	{
		__try { throw __func__; } __finally {}
	}

	void TorpedoControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void DiverControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	// visualizzare una piccola finestra al centro dello schermo
	// solo per informare di prmeere tasto ctrl
	void CreaFinestraAvviso(void)
	{
		__try { throw __func__; } __finally {}
	}

	bool IsModoWindowed(void)
	{
		__try { throw __func__; } __finally {}
	}

	// questa finestra va fatta:
	// 1) se siamo in modalita' fullscreen fare schermo nero sotto
	void CreaBlackWindow(void)
	{
		HINSTANCE TombInstance;
		WNDCLASS wc;

		wc = {0};

		// trovare handle di instanza

		TombInstance = GetModuleHandle(NULL);

		// ok, ora fare tutto il necessario

		// Set up and register window class

		wc.lpfnWndProc = WindowBlackProc;
		wc.hInstance = TombInstance;
		wc.lpszClassName = BLACK_FIELD;
		if (!RegisterClass(&wc))
			return;

		GlobTomb4.BaseFMV.WindowBlack = CreateWindowEx(0, BLACK_FIELD, "", WS_POPUP, 0, 0, GlobTomb4.BaseWideScreen.SizeX, GlobTomb4.BaseWideScreen.SizeY, NULL, NULL, TombInstance, 0);

		if (GlobTomb4.BaseFMV.WindowBlack == NULL) {
			UnregisterClass(BLACK_FIELD, TombInstance);
			return;
		}

		DisattivaAnimWindow();
		ShowWindow(GlobTomb4.BaseFMV.WindowBlack, SW_NORMAL);
		NascondiTaskBar();
	}

	long FAR PASCAL WindowBlackProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		__try { throw __func__; } __finally {}
	}

	// disattiva l'animazione delle finestre per evitare lo schifotto
	// della finestra che si modifica quando avvio fmv in modo full screen
	void DisattivaAnimWindow(void)
	{
		__try { throw __func__; } __finally {}
	}

	void NascondiTaskBar(void)
	{
		__try { throw __func__; } __finally {}
	}

	// funzione analoga a CreaWindowsFont() ma usata per gestire callback CB_WINDOWS_FONT_CREATE
	HFONT CreaWindowsFontForCB(StrWindowsFont *pFont, bool TestNoResize)
	{
		CALL_WINDOWS_FONT_CREATE MyCall;
		HFONT hFont;

		// vedere se c'e' la callback
		MyCall = (CALL_WINDOWS_FONT_CREATE) MyGlobPrivate.BaseVetCbReplace.VetDirectCB[CB_WINDOWS_FONT_CREATE];
		if (MyCall) {
			hFont = MyCall(pFont, TestNoResize);
			if (hFont)
				return hFont;
		}
		return CreaWindowsFont(pFont, TestNoResize);
	}

	// crea font di windows usando i dati di pFont
	// nota: non seleziona in alcun hdc il font, lo crea soltando
	HFONT CreaWindowsFont(StrWindowsFont *pFont, bool TestNoResize)
	{
		LOGFONT TempFont;
		float SizeX, SizeY;

		if (pFont->hFont != NULL) {
			SelectObject(pFont->HdcConFont, pFont->hFontOld);
			DeleteObject(pFont->hFont);
			pFont->hFont = NULL;
		}

		memset(&TempFont, 0, sizeof(TempFont));

		if (pFont->FlagsWFF & WFF_BOLD) {
			TempFont.lfWeight = 700;
		}

		if (pFont->FlagsWFF & WFF_ULTRA_BOLD) {
			TempFont.lfWeight = 800;
		}

		if (pFont->FlagsWFF & WFF_LIGHT) {
			TempFont.lfWeight = 300;
		}

		if (pFont->FlagsWFF & WFF_ITALIC) {
			TempFont.lfItalic = TRUE;
		}

		if (pFont->FlagsWFF & WFF_UNDERLINE) {
			TempFont.lfUnderline = TRUE;
		}

		if (pFont->FlagsWFF & WFF_FORCE_FIXED_PITCH) {
			TempFont.lfPitchAndFamily = FIXED_PITCH;
		}

		if (pFont->FlagsWFF & WFF_ROTATE_90) {
			TempFont.lfEscapement = -900;
			TempFont.lfOrientation = -900;
		}

		if (pFont->FlagsWFF & WFF_ROTATE_INV_90) {
			TempFont.lfEscapement = 900;
			TempFont.lfOrientation = 900;
		}

		TempFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;

		TempFont.lfCharSet = (BYTE) pFont->CharSet;

		strcpy_s(TempFont.lfFaceName, pFont->NomeFont);
		SizeX = ((float) pFont->SizeFont * 50.0f) / 100.0f;
		SizeY = (float) pFont->SizeFont;

		if (TestNoResize == false) {

			// se c'e' bsogno di rfixare dimensione ridurre leggermente larghezza
			if (GlobTomb4.BaseImages.TestWideScreen) {
				SizeX *= 0.833f;
			}

			SizeX = RapportoFloatSchermo(*GlobTomb4.pAdr->pSizeScreenX, (float) 1024, SizeX);
			SizeY = RapportoFloatSchermo(*GlobTomb4.pAdr->pSizeScreenY, (float) 768, SizeY);
		}

		pFont->OutSizePixel = Float2Int(SizeY);

		TempFont.lfWidth = Float2Int(SizeX);
		TempFont.lfHeight = Float2Int(SizeY);

		pFont->hFont = CreateFontIndirect(&TempFont);
		return pFont->hFont;
	}

	// restituisce il valore della variabile sulla base del valore
	// codificato in CodiceVariabile
	// e' in grado di leggere tutte le variabili numeriche ma non quelle di testo
	int LeggiVariabile(WORD CodiceVariabile)
	{
		int Result;
		int Indice;
		WORD N;
		StrBaseVarAll *pVar;

		pVar = GlobTomb4.pBaseVariableTRNG;

		// vedere se e' variabile speciale
		if (CodiceVariabile & VAR_TYPE_INPUT_NUMBER) {
			if (GlobTomb4.DebugModeCounter) {
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("{LastInputNumber} = %d", pVar->Globals.LastInputNumber, 0);
			}

			return pVar->Globals.LastInputNumber;
		}

		if (CodiceVariabile & VAR_TYPE_CURRENT_VALUE) {
			if (GlobTomb4.DebugModeCounter) {
				if (GlobTomb4.DebugModeCounter)
					ShowMsgDebug("{CurrentValue} = %d", pVar->Globals.CurrentValue, 0);
			}
			return pVar->Globals.CurrentValue;
		}

		Result = 0;

		// vedere se e' di tipo store
		if (CodiceVariabile & VAR_TYPE_STORE) {
			// si
			Indice = CodiceVariabile & STORE_MASK_INDEX;
			N = CodiceVariabile & STORE_MASK_SIZE;

			switch (N) {
			case STORE_TYPE_BYTE:
				Result = pVar->Globals.VetStoreByte[Indice];
				break;
			case STORE_TYPE_SHORT:
				Indice &= STORE_MASK_INDEX >> 1;
				Result = pVar->Globals.VetStoreShort[Indice];
				break;
			case STORE_TYPE_LONG:
				Indice &= STORE_MASK_INDEX >> 2;
				Result = pVar->Globals.VetStoreLong[Indice];
				break;
			}

			if (GlobTomb4.DebugModeCounter)
				ShowMsgDebug("{%s} = %d", GetNomeVariabile(CodiceVariabile), Result);

			return Result;
		}
		// non e' store
		Indice = CodiceVariabile & VAR_MASK_INDEX;
		N = CodiceVariabile & VAR_MASK_SIZE;

		// vedere se e' variabile locale
		if (CodiceVariabile & VAR_TYPE_LOCAL) {
			// e' locale

			switch (N) {
			case VAR_TYPE_BYTE:
				Result = pVar->Locals.VetNumeriByte[Indice];
				break;
			case VAR_TYPE_SHORT:
				Indice &= VAR_MASK_INDEX >> 1;
				Result = pVar->Locals.VetNumeriShort[Indice];
				break;
			case VAR_TYPE_LONG:
				Indice &= VAR_MASK_INDEX >> 2;
				Result = pVar->Locals.VetNumeriLong[Indice];
				break;
			}

			if (GlobTomb4.DebugModeCounter)
				ShowMsgDebug("{%s} = %d", GetNomeVariabile(CodiceVariabile), Result);
			return Result;
		}

		// deve essere variabile numerica globale
		switch (N) {
		case VAR_TYPE_BYTE:
			Result = pVar->Globals.NumWar.VetNumeriByte[Indice];
			break;
		case VAR_TYPE_SHORT:
			Indice &= VAR_MASK_INDEX >> 1;
			Result = pVar->Globals.NumWar.VetNumeriShort[Indice];
			break;
		case VAR_TYPE_LONG:
			Indice &= VAR_MASK_INDEX >> 2;
			Result = pVar->Globals.NumWar.VetNumeriLong[Indice];
			break;
		}

		if (GlobTomb4.DebugModeCounter)
			ShowMsgDebug("{%s} = %d", GetNomeVariabile(CodiceVariabile), Result);
		return Result;
	}

	// restituisce il nome descrittivo della variabile numerica Codice
	const char *GetNomeVariabile(WORD Codice)
	{
		static char Buffer[128];
		static const char *VetNomeNum[4] = {"Alfa", "Beta", "Delta", "Timer"};

		const char *pTipo;
		int Indice;
		int N;

		// analisi per codici speciali:
		switch (Codice) {
		case VAR_TYPE_INPUT_NUMBER:
			return "Last Input Number";
		case VAR_TYPE_INPUT_TEXT:
			return "Last Input Text";
		case VAR_TYPE_CURRENT_VALUE:
			return "Current Value";
		case VAR_TYPE_BIG_TEXT:
			return "Big Text";
		}

		if (Codice & VAR_TYPE_STORE) {
			strcat_s(Buffer, "Store ");
			N = Codice & STORE_MASK_SIZE;
			Indice = Codice & STORE_MASK_INDEX;

			switch (N) {
			case STORE_TYPE_BYTE:

				Indice /= 4;
				sprintf_s(Buffer, "Store Byte %c%c", 'A' + Indice, '1' + (Codice & 0x3));

				break;
			case STORE_TYPE_SHORT:
				Indice &= STORE_MASK_INDEX >> 1;
				Indice /= 2;
				sprintf_s(Buffer, "Store Short %c%c", 'A' + Indice, '1' + (Codice & 0x1));
				break;
			case STORE_TYPE_LONG:
				Indice &= STORE_MASK_INDEX >> 2;
				sprintf_s(Buffer, "Store Long %c", 'A' + Indice);
				break;
			}

			return Buffer;
		}

		Indice = Codice & VAR_MASK_INDEX;
		N = Codice & VAR_MASK_SIZE;

		// vedere se e' variabile locale
		if (Codice & VAR_TYPE_LOCAL) {
			pTipo = "Local";
		} else {
			pTipo = "Global";
		}

		switch (N) {
		case VAR_TYPE_BYTE:
			Indice /= 4;
			sprintf_s(Buffer, "%s Byte %s%c", pTipo, VetNomeNum[Indice], '1' + (Codice & 0x3));
			break;
		case VAR_TYPE_SHORT:
			Indice &= VAR_MASK_INDEX >> 1;
			Indice /= 2;
			sprintf_s(Buffer, "%s Short %s%c", pTipo, VetNomeNum[Indice], '1' + (Codice & 0x1));
			break;
		case VAR_TYPE_LONG:
			Indice &= VAR_MASK_INDEX >> 2;
			sprintf_s(Buffer, "%s Long %s", pTipo, VetNomeNum[Indice]);
			break;
		}
		return Buffer;
	}

	// visualizza diario
	void MostraDiario(StrBaseDiario *pDiario)
	{
		int IndicePagina;
		DWORD FlagTasti;
		bool TestWait;
		StrShowImage *pBase;
		bool TestNoInput;
		int LastY;
		RECT *pMioRect;
		bool TestTrasparente;
		bool TestPrimaVolta;
		int i;
		bool TestCorreggiWide;
		bool TestSospendi;
		bool TestFirst;
		bool TestRefresh;

		TestPrimaVolta = true;
		pBase = &GlobTomb4.BaseImages;
		AllocaDiario(pDiario);
		if (pDiario->FlagsPL & PL_FIX_WIDE_SCREEN) {
			TestCorreggiWide = true;
		} else {
			TestCorreggiWide = false;
		}

		pBase->TestWideScreen = TestCorreggiWide;

		// alloca hdc tomb per caricare immagine di schermo tombraider in temp
		if (AllocaHdcTomb(pBase, true, false) == false) {
			LiberaDiario(pDiario);
			return;
		}
		// allocare immagine per diario

		if (AllocaImmagine(-1, &pBase->ImagePageDiario, -1, -1) == false) {
			LiberaDiario(pDiario);
			LiberaHdcTomb(pBase, false);
			return;
		}

		// copiare immagine sfondo tomb di pagediario
		if (BitBlt(pBase->ImagePageDiario.MemHdc, 0, 0, pBase->ImagePageDiario.SizeX, pBase->ImagePageDiario.SizeY, pBase->Temp.MemHdc, 0, 0, SRCCOPY) == 0) {
			InviaLog("ERROR: Diary() failed bitblt() to copy game background in DiaryPage");
			LiberaDiario(pDiario);
			LiberaHdcTomb(pBase, false);
			return;
		}

		LiberaHdcTomb(pBase, true);

		if (pDiario->IndicePaginaToShow == -1) {
			IndicePagina = pDiario->TotPagine - 1;
		} else {
			i = pDiario->IndicePaginaToShow;

			if (i < pDiario->TotPagine) {
				IndicePagina = i;
			} else
				IndicePagina = 0;
		}
		pDiario->CdIsPlaying = -1;

		TestSospendi = ScopriSospendiAudioDiario(pDiario);

		*GlobTomb4.pAdr->pTestGrayScreen = true;

		if (TestSospendi) {
			SospendiAudio(-1, 0);
		} else {
			// in ogni caso sospendere almeno II canale
			if (GlobTomb4.BaseBassHandles.TestPresente) {
				StopBassSuoni(1);
			}
		}

		TestFirst = true;

		TestNoInput = false;
		do {
			// questa parte di codice viene eseguita ad ogni nuova pagina
			TestRefresh = true;
			// prima liberare eventuale immaginie background o little precedente
			if (pBase->ImageBackGround.TestUsata)
				LiberaImmagine(&pBase->ImageBackGround);
			if (pBase->ImageLittle.TestUsata)
				LiberaImmagine(&pBase->ImageLittle);

			AllocaPaginaDiario(pDiario, IndicePagina);
			SuonaAudioPagina(pDiario, IndicePagina);

			// ora caricare background image
			if (AllocaImmagine(pDiario->PaginaNow.BgImage, &pBase->ImageBackGround, -1, -1) == false)
				break;

			// ora allocare eventuale immagine little
			if (pDiario->PaginaNow.NImage != -1) {
				if (AllocaImmagine(pDiario->PaginaNow.NImage, &pBase->ImageLittle, -1, -1) == false) {
					pDiario->PaginaNow.NImage = -1;
					break;
				}
			}

			// costruisce immagine e testi in ImagePageDiario
			SetStretchBltMode(pBase->ImagePageDiario.MemHdc, COLORONCOLOR);
			if (pDiario->FlagsLDF & LDF_TRANSPARENT_BKG) {
				TransparentBlt(pBase->ImagePageDiario.MemHdc, 0, 0, pBase->ImagePageDiario.SizeX, pBase->ImagePageDiario.SizeY, pBase->ImageBackGround.MemHdc, 0, 0, pBase->ImageBackGround.SizeX, pBase->ImageBackGround.SizeY, 0xff00ff);
			} else {

				// copiare immagine di sfondo
				StretchBlt(pBase->ImagePageDiario.MemHdc, 0, 0, pBase->ImagePageDiario.SizeX, pBase->ImagePageDiario.SizeY, pBase->ImageBackGround.MemHdc, 0, 0, pBase->ImageBackGround.SizeX, pBase->ImageBackGround.SizeY, SRCCOPY);
			}
			if (pDiario->PaginaNow.NImage != -1) {
				pMioRect = &pDiario->PaginaNow.FrameImg;
				// qui bisogna fare calcolo per ridimensionare immagine
				// in destinazione e modificare frame testi
				// se c'e' immagine e fix per widescreen ampliare la size y di frame image

				LastY = ShowImageProp(pBase->ImagePageDiario.MemHdc, pMioRect);
				if (LastY > pDiario->PaginaNow.FrameText1.top) {
					LastY += 3;
					if (LastY > pDiario->PaginaNow.FrameText1.bottom) {
						LastY = pDiario->PaginaNow.FrameText1.bottom - 1;
					}
					pDiario->PaginaNow.FrameText1.top = LastY;
				}
			}

			// ora scrivere testo
			StampaTestoPaginaNow(GlobTomb4.BaseImages.ImagePageDiario.MemHdc, pDiario);

			// se c'e' zoom eseguirlo
			if (TestPrimaVolta == true && (pDiario->FlagsLDF & LDF_ZOOM_START) != 0) {
				if (pDiario->FlagsLDF & LDF_SOUND_EFFECTS) {
					tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_DIARY_ZOOM_START], NULL, 0);
				}
				if (pDiario->FlagsLDF & LDF_TRANSPARENT_BKG) {
					TestTrasparente = true;
				} else {
					TestTrasparente = false;
				}

				ZoomImageDiario(&pBase->ZonaSchermoTomb, pBase->ImagePageDiario.MemHdc, pBase->ImagePageDiario.SizeX, pBase->ImagePageDiario.SizeY, TestTrasparente);
			}

			TestPrimaVolta = false;
			// analizza comandi tastiera

			TestWait = true;
			do {

				TestFirst = false;

				if (pDiario->FlagsLDF & LDF_TRANSPARENT_BKG) {
					TransparentBlt(pBase->Temp.MemHdc, pBase->ZonaSchermoTomb.left, pBase->ZonaSchermoTomb.top, pBase->ZonaSchermoTomb.right, pBase->ZonaSchermoTomb.bottom, pBase->ImagePageDiario.MemHdc, 0, 0, pBase->ImagePageDiario.SizeX, pBase->ImagePageDiario.SizeY, 0xff00ff);
				} else {

					StretchBlt(pBase->Temp.MemHdc, pBase->ZonaSchermoTomb.left, pBase->ZonaSchermoTomb.top, pBase->ZonaSchermoTomb.right, pBase->ZonaSchermoTomb.bottom, pBase->ImagePageDiario.MemHdc, 0, 0, pBase->ImagePageDiario.SizeX, pBase->ImagePageDiario.SizeY, SRCCOPY);
				}

				if (TestRefresh) {

					// ora iniziare ciclo polylist
					tomb4::S_InitialisePolyList();
					AllocaHdcTomb(pBase, false, true);

					// ora mandare in onda temp.hdc
					BitBlt(pBase->HdcTomb, 0, 0, pBase->Temp.SizeX, pBase->Temp.SizeY, pBase->Temp.MemHdc, 0, 0, SRCCOPY);

					LiberaHdcTomb(pBase, true);
					// qui mettere aggiornamento finale con dumpscreen
					tomb4::S_OutputPolyList();
					tomb4::S_DumpScreen();
					TestRefresh = false;
				}

				FlagTasti = LeggiDirectInput();

				if (TestNoInput) {
					if (FlagTasti == 0)
						TestNoInput = false;
					FlagTasti = 0;
				}

				// se escape uscre
				if (FlagTasti & 0x200000)
					TestWait = false;
				// vedere [destra]
				if (FlagTasti & 0x000028) {

					if ((IndicePagina + 1) < pDiario->TotPagine) {
						if (pDiario->FlagsLDF & LDF_SOUND_EFFECTS) {
							tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_DIARY_CHANGE_PAGE], NULL, 0);
						}

						IndicePagina++;
						TestWait = false;
					} else {
						// se e' stato premuto spazio invece di suono no
						// ricominciare da pagina zero
						if (FlagTasti & 0x20) {
							IndicePagina = 0;
							TestWait = false;
							if (pDiario->FlagsLDF & LDF_SOUND_EFFECTS) {
								tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_DIARY_CHANGE_PAGE], NULL, 0);
							}
						} else {
							if (pDiario->FlagsLDF & LDF_SOUND_EFFECTS) {
								tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_DIARY_NO_PAGE], NULL, 0);
							}
						}
					}
				}

				if (FlagTasti & 0x000004) {

					// sinistra
					if (IndicePagina > 0) {
						if (pDiario->FlagsLDF & LDF_SOUND_EFFECTS) {
							tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_DIARY_CHANGE_PAGE], NULL, 0);
						}
						IndicePagina--;
						TestWait = false;
					} else {
						if (pDiario->FlagsLDF & LDF_SOUND_EFFECTS) {
							tomb4::SoundEffect(GlobTomb4.pBaseCustomize->VetCustSFX[TS_DIARY_NO_PAGE], NULL, 0);
						}
					}
				}

				if (TastoVKPremuto(VK_F3)) {
					SalvaScreenShotTr4();
				}
				if (FlagTasti)
					TestNoInput = true;

			} while (TestWait);

		} while ((FlagTasti & 0x200000) == 0);

		AttendiFineEscape();
		*GlobTomb4.pAdr->pTestGrayScreen = false;
		LiberaDiario(pDiario);
		LiberaImmagine(&pBase->Temp);
		LiberaImmagine(&pBase->ImageBackGround);
		LiberaImmagine(&pBase->ImageLittle);
		LiberaImmagine(&pBase->ImagePageDiario);

		pDiario->IndicePaginaToShow = 0;

		if (TestSospendi) {
			RiprendiAudio();
		}
		tomb4::TIME_Init();
	}

	// Crea il testo complessivo di diario
	// Se c'e' un errore restituisce false
	// nota: all fine dovra' essere chiamato LiberaTestoDiario()
	//		per liberare la memoria allocata delle varie pagine
	// nota: imposta in pDiario->TotPagine il numero complessivo di pagine
	void AllocaDiario(StrBaseDiario *pDiario)
	{
		int i;
		char *pChar;
		char *pTesto;
		int n;
		int Indice;

		pDiario->SizeTestoDiario = 0;
		pDiario->pTestoDiario = NULL;

		// verifica se ci sara' bisogno di fixare widescreen
		pDiario->TestWideScreen = false;
		GlobTomb4.BaseImages.TestWideScreen = false;

		if (GlobTomb4.BaseWideScreen.RapportoSchermo > 1.4f && ScopreModoFullScreen() == true && (pDiario->FlagsPL & PL_FIX_WIDE_SCREEN) != 0) {
			pDiario->TestWideScreen = true;
			GlobTomb4.BaseImages.TestWideScreen = true;
		}

		if (pDiario->TotStringhe == 0) {
			pDiario->TotPagine = 1;
			pChar = (char *) malloc(50);

			if (pChar != NULL) {
				pChar[0] = 0;
				pDiario->pTestoDiario = pChar;
			}

			return;
		}

		for (i = 0; i < pDiario->TotStringhe; i++) {
			pChar = GetString(pDiario->VetStringhe[i]);
			n = strlen(pChar) + 10;
			pDiario->SizeTestoDiario += n;
			if (pDiario->pTestoDiario == NULL) {
				pDiario->pTestoDiario = (char *) malloc(pDiario->SizeTestoDiario);
				if (pDiario->pTestoDiario != NULL)
					pDiario->pTestoDiario[0] = 0;
			} else {
				pTesto = (char *) realloc(pDiario->pTestoDiario, pDiario->SizeTestoDiario);
				if (pTesto != NULL)
					pDiario->pTestoDiario = pTesto;
			}
			if (pDiario->pTestoDiario != NULL)
				strcat_s(pDiario->pTestoDiario, pDiario->SizeTestoDiario, pChar);
		}
		// ora cotnare il numero di pagine
		pDiario->TotPagine = 1;
		Indice = 0;

		do {
			Indice = InStr(Indice, pDiario->pTestoDiario, "#END_PAGE#");
			if (Indice != -1) {
				pDiario->TotPagine++;
				Indice++;
			}
		} while (Indice != -1);
	}

	// libera tutta la memoria e le risorse allocate da diario
	void LiberaDiario(StrBaseDiario *pDiario)
	{
		if (pDiario->pTestoDiario) {
			free(pDiario->pTestoDiario);
			pDiario->pTestoDiario = NULL;
		}
		LiberaPaginaDiario(pDiario);
	}

	void LiberaPaginaDiario(StrBaseDiario *pDiario)
	{
		if (pDiario->PaginaNow.pTesto) {
			free(pDiario->PaginaNow.pTesto);
			pDiario->PaginaNow.pTesto = NULL;
		}

		if (pDiario->PaginaNow.pTitolo) {
			free(pDiario->PaginaNow.pTitolo);
			pDiario->PaginaNow.pTitolo = NULL;
		}
		// liberare eventuali font
		if (pDiario->PaginaNow.FontText.hFont) {
			LiberaWindowsFont(&pDiario->PaginaNow.FontText);
		}

		if (pDiario->PaginaNow.FontTitle.hFont) {
			LiberaWindowsFont(&pDiario->PaginaNow.FontTitle);
		}
	}

	bool ScopriSospendiAudioDiario(StrBaseDiario *pDiario)
	{
		bool TestSospendi;
		char *pChar;
		int i;

		TestSospendi = false;
		if (pDiario->FlagsLDF & LDF_SILENT) {
			TestSospendi = true;
		}

		if (TestSospendi == false && GlobTomb4.BaseBassHandles.TestPresente == false) {

			if ((pDiario->FlagsLDF & LDF_PLAY_TRACK) != 0) {
				TestSospendi = true;
			} else {
				// oppure se c'e' un comando #BG_AUDIO#

				for (i = 0; i < pDiario->TotStringhe; i++) {
					pChar = GetString(pDiario->VetStringhe[i]);
					if (InStr(0, pChar, "#BG_AUDIO#") != -1) {
						TestSospendi = true;
						break;
					}
				}
			}
		}

		return TestSospendi;
	}

	// sosende l'audio sulla traccia 0 e salva i dati in GlobTomb4.AudioSospeso
	// poi si dovra' chiamare RiprendiAudio()
	void SospendiAudio(int NuovoCd, int NuovoTestLoop)
	{
		StrBassHandles *pBass;
		StrCanaleBass *pCanale;
		StrAudioSospeso *pSospeso;
		int Indice;
		StrRecordSospensione *pRec;

		pSospeso = &GlobTomb4.AudioSospeso;

		Indice = pSospeso->CountSuspend;

		pRec = &pSospeso->VetSospeso[Indice];

		if (GlobTomb4.BaseBassHandles.TestPresente) {
			// c'e' bass.dll
			pBass = &GlobTomb4.BaseBassHandles;
			pCanale = &pBass->VetCanali[0];

			pRec->NumeroCD = pCanale->NumeroCd;
			pRec->Posizione = TrovaPosizioneSuono(pCanale);
			pRec->TestLoop = pCanale->Loop;
			pRec->NuovoCD = NuovoCd;
			pRec->NuovoTestLoop = NuovoTestLoop;
			StopBassSuoni(-1);
			StopAllSounds();
			tomb4::S_CDStop();
		} else {
			pRec->NumeroCD = *GlobTomb4.pAdr->pCDTrackNow;
			pRec->TestLoop = *GlobTomb4.pAdr->pTestCdLoop;
			tomb4::S_CDStop();
			StopAllSounds();
		}

		if (pSospeso == 0)
			SospendiThreadNotifica();
		pSospeso->CountSuspend++;
	}

	// imposta testo, formattazione
	bool AllocaPaginaDiario(StrBaseDiario *pDiario, int IndicePagina)
	{
		static const char * VetPL_Mex[11] = {"PL_DOUBLE_PAGE", "PL_LEFT_IMAGE",
				"PL_LEFT_IMAGE_LOGO", "PL_RIGHT_IMAGE",
				"PL_RIGHT_IMAGE_LOGO", "PL_CENTRAL_IMAGE",
				"PL_WIDE_IMAGE", "PL_ADD_INFO_BAR",
				"PL_CUSTOM_LAYOUT", "PL_FIX_WIDE_SCREEN", NULL};
		static RECT VetFrameImage[8] = {{-1, -1, -1, -1},
			{73, 79, 380, 397}, // PL_DOUBLE_PAGE
			{29, 38, 434, 414}, // PL_LEFT_IMAGE
			{29, 38, 434, 414}, // PL_LEFT_IMAGE_LOGO
			{524, 25, 448, 436}, // PL_RIGHT_IMAGE
			{524, 25, 448, 436},  // PL_RIGHT_IMAGE_LOGO
			{229, 16, 527, 468},  // PL_CENTRAL_IMAGE
			{36, 22, 929, 442}};	// PL_WIDE_IMAGE
		static RECT VetFrameText1[8] = {{-1, -1, -1, -1},
			{73, 500, 380, 436}, // PL_DOUBLE_PAGE
			{495, 41, 473, 414}, // PL_LEFT_IMAGE
			{21, 495, 954, 462}, // PL_LEFT_IMAGE_LOGO
			{21, 32, 473, 464},  // PL_RIGHT_IMAGE
			{24, 511, 953, 449}, // PL_RIGHT_IMAGE_LOGO
			{24, 524, 953, 442}, // PL_CENTRAL_IMAGE
			{36, 498, 927, 465}}; // PL_WIDE_IMAGE
		static RECT VetFrameText2[8] = {{-1, -1, -1, -1},
			{555, 79, 380, 857}, // PL_DOUBLE_PAGE
			{21, 495, 954, 462}, // PL_LEFT_IMAGE
			{-1, -1, -1, -1},		// PL_LEFT_IMAGE_LOGO
			{24, 511, 953, 449}, // PL_RIGHT_IMAGE
			{-1, -1, -1, -1},		// PL_RIGHT_IMAGE_LOGO
			{-1, -1, -1, -1},		// PL_CENTRAL_IMAGE
			{-1, -1, -1, -1}};		// PL_WIDE_IMAGE
		static WORD VetPL_Values[10] = {1, 2,
				3, 4,
				5, 6,
				7, 0x100,
				0x200, 0x400};

		// localizza pagina IndicePagina (da 0 a totpagine-1)
		// se non c'e' restituisce false e non modifica nulla
		int PaginaNow;
		RECT *pMioRect;
		int Indice;
		int Inizio;
		RECT TempRect;
		int Fine;
		int SizePagina;
		char *pFormat;
		char *pChar;
		RECT *pImg;
		char *pArg;
		bool TestErrore;
		int Numero;
		StrWindowsFont *pFont;
		int TotParti;
		char **VetParti;
		int i;
		int j;
		int Totale;
		int StartPoint;
		int SizeTitolo;

		PaginaNow = 0;
		Indice = 0;
		StartPoint = 0;

		while (PaginaNow != IndicePagina && Indice >= 0) {
			// cercare prossima pagina
			Indice = InStr(StartPoint, pDiario->pTestoDiario, "#END_PAGE#");
			PaginaNow++;
			StartPoint = Indice + 1;
		}

		if (Indice < 0)
			return false;
		// adesso indice punta a inizio testo di pagina IndicePagine
		// potrebbe esserci un #end_page# oppure no
		if (Indice > 0) {
			// punta a "#END_PAGE#: saltarlo assieme a due caratteri seguenti
			// che saranno quelli di 0x0d e 0x0a
			Inizio = Indice + strlen("#END_PAGE#") + 1;
		} else {
			Inizio = Indice;
		}

		Fine = InStr(Inizio, pDiario->pTestoDiario, "#END_PAGE#");
		if (Fine < 0)
			Fine = strlen(pDiario->pTestoDiario);
		SizePagina = Fine - Inizio;

		// liberare pagina diario precedente sec'era
		if (pDiario->PaginaNow.pTesto) {
			LiberaPaginaDiario(pDiario);
		}

		pDiario->PaginaNow.pTesto = (char *) malloc(SizePagina + 4);
		memcpy(pDiario->PaginaNow.pTesto, &pDiario->pTestoDiario[Inizio], SizePagina);
		pDiario->PaginaNow.pTesto[SizePagina] = 0;
		// iniziallizare con valori base i dati di formattazione
		pDiario->PaginaNow.FontText = pDiario->FontText;
		pDiario->PaginaNow.FontTitle = pDiario->FontTitle;
		pDiario->PaginaNow.FlagsPL = pDiario->FlagsPL;
		pDiario->PaginaNow.NImage = -1;
		pDiario->PaginaNow.BgImage = pDiario->IdImage;
		pDiario->PaginaNow.pTitolo = NULL;
		pDiario->PaginaNow.CbBack = -1;

		// segnalare che i frame devono essere impostati dinamicamente
		pDiario->PaginaNow.FrameImg.left = -1;
		pDiario->PaginaNow.FrameText1.left = -1;
		pDiario->PaginaNow.FrameText2.left = -1;
		// ora estrarre zona formattazione (se presente)
		pFormat = EstraeParteTesto(pDiario->PaginaNow.pTesto, "FORMAT", true);
		if (pFormat) {
			//trovati dati di formattaione

			// --------------- TITLE_FONT ----------------------------------

			pArg = EstraeDatiTag(pFormat, "#TITLE_FONT#=");
			if (pArg) {

				Numero = GetArgNumerico(pArg, &TestErrore);
				if (TestErrore == true) {
					sprintf_s(BufferLog, "ERROR DIARY in #TITLE_FONT#= tag of Page=%d. Not valid number", IndicePagina + 1);
					InviaLog(BufferLog);
				} else {
					i = GlobTomb4.BaseFonts.VetID[Numero];
					if (i == -1) {
						sprintf_s(BufferLog, "ERROR DIARY in #TITLE_FONT tag of Page=%d. Cann't find the WindowsFont=%d", IndicePagina + 1, Numero);
						InviaLog(BufferLog);
					} else {
						pFont = &GlobTomb4.BaseFonts.VetFonts[i];
						pDiario->PaginaNow.FontTitle = *pFont;
					}
				}
			}
			// --------------- #TEXT_FONT#= ----------------------------------

			pArg = EstraeDatiTag(pFormat, "#TEXT_FONT#=");
			if (pArg) {

				Numero = GetArgNumerico(pArg, &TestErrore);
				if (TestErrore == true) {
					sprintf_s(BufferLog, "ERROR DIARY in #TEXT_FONT#= tag of Page=%d. Not valid number", IndicePagina + 1);
					InviaLog(BufferLog);
				} else {
					i = GlobTomb4.BaseFonts.VetID[Numero];
					if (i == -1) {
						sprintf_s(BufferLog, "ERROR DIARY in #TEXT_FONT#= tag of Page=%d. Cann't find the WindowsFont=%d", IndicePagina + 1, Numero);
						InviaLog(BufferLog);
					} else {
						pFont = &GlobTomb4.BaseFonts.VetFonts[i];
						pDiario->PaginaNow.FontText = *pFont;
					}
				}
			}
			// -------------- #PAGE_LAYOUT#= -------------------
			pArg = EstraeDatiTag(pFormat, "#PAGE_LAYOUT#=");
			if (pArg) {
				pDiario->PaginaNow.FlagsPL = 0;
				Totale = 0;
				VetParti = Split(pArg, '+', &TotParti, NULL, NULL, false);
				for (i = 0; i < TotParti; i++) {
					pChar = Trim(VetParti[i]);
					// prima vedere se questo valore corrispone
					// ad un nome simbolico
					j = 0;
					Numero = -1;
					while (VetPL_Mex[j] != NULL) {
						if (_stricmp(VetPL_Mex[j], pChar) == 0) {
							Numero = VetPL_Values[j];
							break;
						}
						j++;
					}
					if (Numero == -1) {
						// non era un simbolo, vedere se e' un numero
						Numero = GetArgNumerico(VetParti[i], &TestErrore);
						if (TestErrore == true) {
							sprintf_s(BufferLog, "ERROR DIARY. In tag #PAGE_LAYOUT# of page %d the value '%s' is not a valid number and neither a PL_ constant value", IndicePagina, VetParti[i]);
							InviaLog(BufferLog);
							Numero = 0;
						}
					}
					Totale |= Numero;

				}
				pDiario->PaginaNow.FlagsPL = (WORD) Totale;
			}

			// ------------ #BG_IMAGE#= ----------------------------------
			pArg = EstraeDatiTag(pFormat, "#BG_IMAGE#=");
			if (pArg) {
				Numero = GetArgNumerico(pArg, &TestErrore);
				if (TestErrore == true) {
					sprintf_s(BufferLog, "ERROR DIARY. Non valid value (%s) in tag #BG_IMAGE# of page %d", pArg, IndicePagina);
					InviaLog(BufferLog);
				} else {
					pDiario->PaginaNow.BgImage = (short) Numero;
				}
			}

			// ------------ #POP_IMAGE#= ----------------------------------
			pArg = EstraeDatiTag(pFormat, "#POP_IMAGE#=");
			if (pArg) {
				Numero = GetArgNumerico(pArg, &TestErrore);
				if (TestErrore == true) {
					sprintf_s(BufferLog, "ERROR DIARY. Non valid value (%s) in tag #POP_IMAGE#=of page %d", pArg, IndicePagina);
					InviaLog(BufferLog);
				} else {
					pDiario->PaginaNow.NImage = (short) Numero;
				}
			}

			// ------------ #BG_AUDIO#= ----------------------------------
			pArg = EstraeDatiTag(pFormat, "#BG_AUDIO#=");
			if (pArg) {
				Numero = GetArgNumerico(pArg, &TestErrore);
				if (TestErrore == true) {
					sprintf_s(BufferLog, "ERROR DIARY. Non valid value (%s) in tag #BG_AUDIO#=of page %d", pArg, IndicePagina);
					InviaLog(BufferLog);
				} else {
					pDiario->PaginaNow.CbBack = (short) Numero;
				}
			}
			// ------------- #TITLE#= --------------------------------------
			pArg = EstraeDatiTag(pFormat, "#TITLE#=");
			if (pArg) {

				SizeTitolo = strlen(pArg) + 4;
				pDiario->PaginaNow.pTitolo = (char*) malloc(SizeTitolo);
				strcpy_s(pDiario->PaginaNow.pTitolo, SizeTitolo, pArg);
			}
			// ------------- #FRAME_IMG#= ----------
			pMioRect = EstraeDatiFrame(pFormat, "#FRAME_IMG#=", &TestErrore);
			if (TestErrore) {
				sprintf_s(BufferLog, "ERROR DIARY. Error in tag #FRAME_IMG# of page %d", IndicePagina);
				InviaLog(BufferLog);
			} else {
				pDiario->PaginaNow.FrameImg = *pMioRect;
			}

			// ------------- #FRAME_T1#= ----------
			pMioRect = EstraeDatiFrame(pFormat, "#FRAME_T1#=", &TestErrore);
			if (TestErrore) {
				sprintf_s(BufferLog, "ERROR DIARY. Error in tag #FRAME_T1#= of page %d", IndicePagina);
				InviaLog(BufferLog);
			} else {
				pDiario->PaginaNow.FrameText1 = *pMioRect;
			}
			// ------------- #FRAME_T2#= ----------
			pMioRect = EstraeDatiFrame(pFormat, "#FRAME_T2#=", &TestErrore);
			if (TestErrore) {
				sprintf_s(BufferLog, "ERROR DIARY. Error in tag #FRAME_T2#= of page %d", IndicePagina);
				InviaLog(BufferLog);
			} else {
				pDiario->PaginaNow.FrameText2 = *pMioRect;
			}

			// rilasciare memoria pformat
			free(pFormat);
		}

		// ora calcolare i frame
		// ------- frame immagine -------
		if (pDiario->PaginaNow.FrameImg.left == -1) {
			// non e' ancora impostato
			// usare impostazione sulla base di valore PL_...
			i = pDiario->PaginaNow.FlagsPL & 0x07;
			pDiario->PaginaNow.FrameImg = VetFrameImage[i];
		}

		// ----- frame text 1  -------------
		if (pDiario->PaginaNow.FrameText1.left == -1) {
			// non e' stato impostato, usare default pl
			i = pDiario->PaginaNow.FlagsPL & 0x07;
			pDiario->PaginaNow.FrameText1 = VetFrameText1[i];
		}
		// ------ frame text 2 -------------
		if (pDiario->PaginaNow.FrameText2.left == -1) {
			// non e' stasto impostato usare default l
			i = pDiario->PaginaNow.FlagsPL & 0x07;
			pDiario->PaginaNow.FrameText2 = VetFrameText2[i];
		}

		// ora se c'e' flag per zona info ridurre frame che altrimenti arriverebbero
		// in fondo allo schermo
		if (pDiario->PaginaNow.FlagsPL & PL_ADD_INFO_BAR) {
			// dunque, il frame image non puo' mai arrivare in fondo allo schermo
			// analisi di frame text1
			if (pDiario->PaginaNow.FrameText1.left != -1) {
				i = pDiario->PaginaNow.FlagsPL & 0x07;

				if (i == PL_DOUBLE_PAGE || i == PL_LEFT_IMAGE_LOGO || i == PL_RIGHT_IMAGE_LOGO || i == PL_CENTRAL_IMAGE || i == PL_WIDE_IMAGE) {

					// modificare bottom in modo che punti a 900
					pDiario->PaginaNow.FrameText1.bottom = 900 - pDiario->PaginaNow.FrameText1.top;
				}
			}

			if (pDiario->PaginaNow.FrameText2.left != -1) {
				// se c'e' un secondo frame text valido e' sempre nella parte
				// bassa
				pDiario->PaginaNow.FrameText2.bottom = 900 - pDiario->PaginaNow.FrameText2.top;
			}
		}

		// adesso che ci sono i frame in microunits convertirli in
		// pixel effettivi sulla base della dimensione di temphdc
		// che essendo grande come schermo tomb posso usare dimensione tomb
		ConvertiRectMicroUnits(&pDiario->PaginaNow.FrameImg);
		ConvertiRectMicroUnits(&pDiario->PaginaNow.FrameText1);
		ConvertiRectMicroUnits(&pDiario->PaginaNow.FrameText2);

		// ora trasformare le dimensioni in pixel effettvi
		// ma solo per i testi, perche' per image bisogna usare
		// quello con dimensione in right e bottom

		pMioRect = &pDiario->PaginaNow.FrameText1;
		if (pMioRect->left != -1) {
			pMioRect->bottom += pMioRect->top;
			pMioRect->right += pMioRect->left;
		}

		pMioRect = &pDiario->PaginaNow.FrameText2;
		if (pMioRect->left != -1) {
			pMioRect->bottom += pMioRect->top;
			pMioRect->right += pMioRect->left;
		}

		// adesso se manca pop immagine creare una fusione tra frame image
		// e frame testo
		if (pDiario->PaginaNow.NImage == -1) {

			pMioRect = &pDiario->PaginaNow.FrameText1;
			// convertire in pixel assoluti frame img
			TempRect = pDiario->PaginaNow.FrameImg;
			TempRect.bottom += TempRect.top;
			TempRect.right += TempRect.left;

			pImg = &TempRect;

			if (pMioRect->left > pImg->left)
				pMioRect->left = pImg->left;
			if (pMioRect->right < pImg->right)
				pMioRect->right = pImg->right;
			if (pMioRect->top > pImg->top)
				pMioRect->top = pImg->top;
			if (pMioRect->bottom < pImg->bottom)
				pMioRect->bottom = pImg->bottom;
		}

		return true;
	}

	// restituisce i 4 dati in formato di RECT contenuti
	// in un tag testuale nella forma:  "NOME_TAG#=
	RECT *EstraeDatiFrame(char *pSorgente, const char *pTag, bool* pTestErrore)
	{
		static RECT MioRect;

		char *pArg;
		char **VetParti;
		int TotParti;
		int Numero;

		*pTestErrore = false;

		MioRect.left = -1;

		pArg = EstraeDatiTag(pSorgente, pTag);
		if (pArg == NULL)
			return &MioRect;

		VetParti = Split(pArg, ',', &TotParti, NULL, NULL, false);

		if (TotParti != 4) {
			*pTestErrore = true;
			return &MioRect;
		}
		// -- left
		Numero = GetArgNumerico(VetParti[0], pTestErrore);
		if (*pTestErrore == true)
			return &MioRect;

		MioRect.left = Numero;
		// -- top
		Numero = GetArgNumerico(VetParti[1], pTestErrore);
		if (*pTestErrore == true) {
			MioRect.left = -1;
			return &MioRect;
		}
		MioRect.top = Numero;

		//-- right
		Numero = GetArgNumerico(VetParti[2], pTestErrore);
		if (*pTestErrore == true) {
			MioRect.left = -1;
			return &MioRect;
		}
		MioRect.right = Numero;

		// --- bottom
		Numero = GetArgNumerico(VetParti[3], pTestErrore);
		if (*pTestErrore == true) {
			MioRect.left = -1;
			return &MioRect;
		}
		MioRect.bottom = Numero;

		return &MioRect;
	}

	// converte i millesimi di pRect in coordinate (o size) pixel di schermo attuale

	void ConvertiRectMicroUnits(RECT *pRect)
	{
		int SchermoX, SchermoY;

		SchermoX = *GlobTomb4.pAdr->pSizeScreenX;
		SchermoY = *GlobTomb4.pAdr->pSizeScreenY;

		if (pRect->left == -1)
			return;

		pRect->left = (int) RapportoFloatSchermo(SchermoX, (float) 1000.0, (float) pRect->left);

		pRect->top = (int) RapportoFloatSchermo(SchermoY, (float) 1000.0, (float) pRect->top);

		pRect->right = (int) RapportoFloatSchermo(SchermoX, (float) 1000.0, (float) pRect->right);

		pRect->bottom = (int) RapportoFloatSchermo(SchermoY, (float) 1000.0, (float) pRect->bottom);
	}

	void SuonaAudioPagina(StrBaseDiario *pDiario, int IndicePagina)
	{
		int NumeroCD;
		int TestLoop;
		int i;

		NumeroCD = -1;
		TestLoop = 0;

		if (pDiario->FlagsLDF & LDF_PLAY_TRACK) {
			NumeroCD = pDiario->FlagsLDF & 0xff;
			TestLoop = 1;
		}

		if (pDiario->PaginaNow.CbBack != -1) {
			NumeroCD = pDiario->PaginaNow.CbBack;
			TestLoop = 0;
		}

		i = GlobTomb4.AudioSospeso.CountSuspend - 1;
		if (i >= 0) {
			GlobTomb4.AudioSospeso.VetSospeso[i].NuovoCD = NumeroCD;
			GlobTomb4.AudioSospeso.VetSospeso[i].NuovoTestLoop = TestLoop;
		}

		if (NumeroCD != pDiario->CdIsPlaying) {
			if (NumeroCD == -1) {
				// stoppare il suono cd
				if (GlobTomb4.BaseBassHandles.TestPresente) {
					StopBassSuoni(1);
				}
			} else {
				GlobTomb4.BaseBassHandles.CanaleNow = 1;

				tomb4::S_CDPlay(NumeroCD, TestLoop);
			}
			pDiario->CdIsPlaying = (short) NumeroCD;
		}
	}

	// visualizza immagine presente in hdc di ImageLittle
	// che ha dimensione originale in ImageLittle
	// copiandola in pMioRect
	// mantiene le proporzioni originali pero', lasciando come fissa
	// solo la larghezza orizzontale del rect di destinazione
	// alla fine restituisce la cordy di bottom ossia della fine dell'immagine
	// in verticale dopo il ridimensionamento
	int ShowImageProp(HDC HdcOut, RECT *pMioRect)
	{
		int SizeY;
		float RapportoOriginale;
		StrRecordImage *pImage;

		pImage = &GlobTomb4.BaseImages.ImageLittle;

		RapportoOriginale = (float) pImage->SizeY / (float) pImage->SizeX;

		// ora in modo inverso scoprire la sizey finale
		SizeY = (int) ((float) pMioRect->right * (float) RapportoOriginale);

		// se c'e' fix widescreen attivo modificare ulteriormente questo valore
		if (GlobTomb4.BaseImages.TestWideScreen) {

			SizeY = Float2Int((float) SizeY / 0.833f);
		}

		TransparentBlt(HdcOut, pMioRect->left, pMioRect->top, pMioRect->right, SizeY, pImage->MemHdc, 0, 0, pImage->SizeX, pImage->SizeY, 0xff00ff);

		return pMioRect->top + SizeY;
	}

	// stampa il testo di pagina now su hdctemp
	// usando i dati di frame text1/2
	void StampaTestoPaginaNow(HDC MioHdc, StrBaseDiario *pDiario)
	{
		HFONT MioFont;
		RECT FrameText1;
		RECT FrameText2;
		StrWindowsFont *pFont;
		int NextOrgY;
		char *pTesto2;
		bool TestErrore;

		SetBkMode(MioHdc, TRANSPARENT);
		SetMapMode(MioHdc, MM_TEXT);

		MioFont = NULL;
		FrameText1 = pDiario->PaginaNow.FrameText1;
		FrameText2 = pDiario->PaginaNow.FrameText2;

		// vedere se c'e' title
		if (pDiario->PaginaNow.pTitolo != NULL) {
			pFont = &pDiario->PaginaNow.FontTitle;

			ImpostaWindowsFont(pFont, MioHdc, false, false);

			NextOrgY = StampaTestoWindowsForCB(&FrameText1, pFont, MioHdc, pDiario->PaginaNow.pTitolo, &TestErrore, true, 0);

			if (TestErrore == true) {

				// lo spazio non bastava per visualizzare titolo
				// allora provare a visualizzarlo in frame 2

				NextOrgY = StampaTestoWindowsForCB(&FrameText2, pFont, MioHdc, pDiario->PaginaNow.pTitolo, &TestErrore, false, 0);
				FrameText2.top = NextOrgY;
			} else {
				// nessun ,errore, adesso stampare davvero testo

				NextOrgY = StampaTestoWindowsForCB(&FrameText1, pFont, MioHdc, pDiario->PaginaNow.pTitolo, &TestErrore, false, 0);
				// adesso adattare il resto del rettangolo in modo
				// che si stampi sotto quello attuale
				FrameText1.top = NextOrgY;
			}
		}

		pFont = &pDiario->PaginaNow.FontText;

		ImpostaWindowsFont(pFont, MioHdc, false, false);
		// calcolare eventuali due blocchi di testo
		pTesto2 = TrovaDivisioneTesto(&FrameText1, pFont, MioHdc, pDiario->PaginaNow.pTesto);

		if (pTesto2 == pDiario->PaginaNow.pTesto)
			pTesto2 = NULL;

		if (pTesto2) {
			*pTesto2 = 0;
			pTesto2++;
			while (*pTesto2 == 0x0a)
				pTesto2++;
		}

		if (pDiario->PaginaNow.pTesto) {

			StampaTestoWindowsForCB(&FrameText1, pFont, MioHdc, pDiario->PaginaNow.pTesto, &TestErrore, false, 0);
			if (TestErrore && pDiario->PaginaNow.FrameText2.left != -1) {
				// provare a stampare in frame2

				FrameText2.top = StampaTestoWindowsForCB(&FrameText2, pFont, MioHdc, pDiario->PaginaNow.pTesto, &TestErrore, false, 0);
			}
		}

		// adesso se c'e' un altro frame di testo stampare anche quello
		if (pDiario->PaginaNow.FrameText2.left != -1 && pTesto2 != NULL) {

			StampaTestoWindowsForCB(&FrameText2, pFont, MioHdc, pTesto2, &TestErrore, false, 0);
		}
	}

	// crea handle di font corrispondente a dati in pFont
	// nota: Se TestNonCancellare = true allora, nel caso in pFont ci sia gia' un handle valido di font,
	// non lo cancella ma lo seleziona semplicemente in MioHdc
	void ImpostaWindowsFont(StrWindowsFont *pFont, HDC MioHdc, bool TestNonCancellare, bool TestNonResize)
	{
		// se c'era gia' un font selezionato eliminarlo
		if (pFont->hFont != NULL) {
			if (TestNonCancellare == false) {
				SelectObject(MioHdc, pFont->hFontOld);
				DeleteObject(pFont->hFont);
				pFont->hFont = NULL;
			}
		}

		pFont->HdcConFont = MioHdc;

		if (pFont->hFont == NULL)
			pFont->hFont = CreaWindowsFontForCB(pFont, TestNonResize);

		pFont->hFontOld = (HFONT) SelectObject(MioHdc, pFont->hFont);
	}

	// funzione analoga di StampaTestoWindows() ma creata per gestire callback
	int StampaTestoWindowsForCB(RECT *pRect, StrWindowsFont *pFont, HDC MioHdc, char *pTesto, bool *pTestErrore, bool TestSoloProva, DWORD WTF_Flags)
	{
		CALL_WINDOWS_TEXT_PRINT MyCall;
		int MyRetValue;

		MyCall = (CALL_WINDOWS_TEXT_PRINT) MyGlobPrivate.BaseVetCbReplace.VetDirectCB[CB_WINDOWS_TEXT_PRINT];

		if (MyCall) {
			//
			MyRetValue = MyCall(pRect, pFont, MioHdc, pTesto, pTestErrore, TestSoloProva, WTF_Flags);
			if (MyRetValue)
				return MyRetValue;
		}

		return StampaTestoWindows(pRect, pFont, MioHdc, pTesto, pTestErrore, TestSoloProva, WTF_Flags);
	}

	// Stampa il testo pTesto nell'hdc MioHdc, usando le imostazioni pFont
	// restituisce l'altezza del testo stampato
	// nota: si presume che nell'hdc sia gia' stato impostaot il font
	// nota: se c'e' shadow stampa due volte
	int StampaTestoWindows(RECT *pRect, StrWindowsFont *pFont, HDC MioHdc, char *pTesto, bool *pTestErrore, bool TestSoloProva, DWORD WTF_Flags)
	{
		DWORD FlagDT;
		int SizeY;
		RECT TempRect;
		int Gap;
		int AltezzaFrame;
		char *pChar;
		int OldMode;
		bool TestRuota;
		wchar_t *pTestoW;
		wchar_t *pCharW;
		DWORD SizeBuffer;
		DWORD TempFlags;
		char *pTestoBinario;
		CALL_WINDOWS_UNICODE_CONVERT MyCall;

		*pTestErrore = false;
		AltezzaFrame = pRect->bottom - pRect->top;

		TempRect = *pRect;
		OldMode = GM_COMPATIBLE;
		TestRuota = false;

		pTestoW = NULL;
		pTestoBinario = NULL;
		TempFlags = pFont->FlagsWFF;
		SizeY = 0;

		// se testo inizia con '&' allora e' una stringa binria  e va convertita
		if (pTesto[0] == '&') {
			pTestoBinario = ConvertiStringaBinaria(pTesto, &SizeBuffer);
			if (pTestoBinario == NULL)
				return 0;

			pTesto = pTestoBinario;
		}

		if (pFont->FlagsWFF & WFF_UNICODE) {
			// gestire callback CB_WINDOWS_UNICODE_CONVERT per sostituzione
			MyCall = (CALL_WINDOWS_UNICODE_CONVERT) MyGlobPrivate.BaseVetCbReplace.VetDirectCB[CB_WINDOWS_UNICODE_CONVERT];
			pTestoW = NULL;
			if (MyCall) {
				pTestoW = MyCall(pFont, pTesto);
			}
			// se non e' stato convertito da callback, farlo adesso
			if (pTestoW == NULL)
				pTestoW = (wchar_t*) pTesto;
		}

		if (TempFlags & (WFF_ROTATE_90 | WFF_ROTATE_INV_90)) {
			OldMode = SetGraphicsMode(MioHdc, GM_ADVANCED);
			TestRuota = true;
		}

		// se c'e' shadow spostare in basso a destra la stampa
		if (TempFlags & WFF_SHADOW) {

			Gap = pFont->OutSizePixel / 6;
			if (Gap < 4)
				Gap = 4;

			TempRect.left += Gap;
			TempRect.top += Gap / 2;
			SetTextColor(MioHdc, pFont->ColoreShadow);
		} else {
			SetTextColor(MioHdc, pFont->ColoreText);
		}

		SetBkMode(MioHdc, TRANSPARENT);
		FlagDT = CreaFlagDT(pFont);

		if (WTF_Flags & (WTF_FLYING_TEXT | WTF_PULSING_TEXT)) {
			// se non ci sono newline nel testo attivare centratura verticale
			if (InStr(0, pTesto, "\n") == -1)
				FlagDT |= DT_VCENTER | DT_SINGLELINE;
			FlagDT &= ~DT_WORDBREAK;
		}

		if (TestSoloProva)
			FlagDT |= DT_CALCRECT;
		if (TempFlags & WFF_UNICODE) {
			pCharW = ReplaceVarPlaceFoldersW(pTestoW);
			pChar = NULL;
		} else {
			pChar = ReplaceVarPlaceFolders(pTesto);
			pCharW = NULL;
		}

		if (TestRuota) {
			if (TempFlags & WFF_UNICODE) {
				TextOutW(MioHdc, TempRect.left, TempRect.top, pCharW, TempRect.right - TempRect.left);
			} else {
				TextOut(MioHdc, TempRect.left, TempRect.top, pChar, TempRect.right - TempRect.left);
			}
		} else {
			if (TempFlags & WFF_UNICODE) {
				SizeY = DrawTextW(MioHdc, pCharW, -1, &TempRect, FlagDT);
			} else {

				SizeY = DrawText(MioHdc, pChar, -1, &TempRect, FlagDT);
			}
			// controllare se lo spazio richiesto e' maggiore di quello concesso
			if (SizeY > AltezzaFrame)
				*pTestErrore = true;
		}
		if (TempFlags & WFF_SHADOW) {
			SetTextColor(MioHdc, pFont->ColoreText);

			if (TestRuota) {
				if (TempFlags & WFF_UNICODE) {
					TextOutW(MioHdc, pRect->left, pRect->top, pCharW, TempRect.right - TempRect.left);
				} else {

					TextOut(MioHdc, pRect->left, pRect->top, pChar, TempRect.right - TempRect.left);
				}
			} else {

				TempRect = *pRect;

				if (TempFlags & WFF_UNICODE) {
					SizeY = DrawTextW(MioHdc, pCharW, -1, &TempRect, FlagDT);
				} else {

					SizeY = DrawText(MioHdc, pChar, -1, &TempRect, FlagDT);
				}
			}
		}

		// se c'e' rotazione flag ripristinare vecchio modo grafico
		if (TempFlags & (WFF_ROTATE_90 | WFF_ROTATE_INV_90)) {
			SetGraphicsMode(MioHdc, OldMode);
		}

		if (pTestoBinario != NULL)
			free(pTestoBinario);

		return pRect->top + SizeY;
	}

	// riceve in input una stringa binaria nel formato "!A010E6..." e restituisce i singoli byte che la compongono
	// imposta di pSize il numero di byte dopo la conversione, inclusi due byte extra a zero aggiunti dalla funzione
	// nota: il puntatore restituito e' una memoria allocata dinamicamente che deve essere rilasciata
	// dalla procedura chiamante
	char *ConvertiStringaBinaria(char *pTesto, DWORD *pSize)
	{
		DWORD TotSource;
		DWORD i;
		DWORD j;
		char VetHex[17];
		char CarNow;
		char *pOut;
		char ValNow;
		DWORD TotDest;

		strcpy_s(VetHex, "0123456789ABCDEF");
		TotSource = strlen(pTesto);
		pOut = (char *) malloc(TotSource + 2);
		if (pOut == NULL)
			return NULL;
		TotDest = 0;

		pTesto++;

		for (i = 0; i < TotSource; i++) {
			CarNow = pTesto[i];
			if (CarNow == 0)
				break;
			for (j = 0; j < 16; j++) {
				if (CarNow == VetHex[j])
					break;
			}

			if (j == 16) {
				// carattere non trovato
				InviaLog("ERROR: not valid hex character in binary string");
				return NULL;
			}
			if ((i & 1) == 0) {
				ValNow = (char) (j << 4);
			} else {
				ValNow |= j;
				pOut[TotDest++] = ValNow;
			}
		}
		pOut[TotDest++] = 0;
		pOut[TotDest++] = 0;
		*pSize = TotDest;

		return pOut;
	}

	// sulla base di pFont crea i flag DT da usare con DrawText()
	DWORD CreaFlagDT(StrWindowsFont *pFont)
	{
		DWORD FlagDT;

		FlagDT = DT_EXPANDTABS | DT_EXTERNALLEADING | DT_NOPREFIX | DT_WORDBREAK;

		if (pFont->FlagsWFF & WFF_LEFT_ALIGN) {
			FlagDT |= DT_LEFT;
		}

		if (pFont->FlagsWFF & WFF_RIGHT_ALIGN) {
			FlagDT |= DT_RIGHT;
		}

		if (pFont->FlagsWFF & WFF_CENTER_ALIGN) {
			FlagDT |= DT_CENTER;
		}

		if (pFont->FlagsWFF & WFF_FROM_RIGHT_TO_LEFT) {
			FlagDT |= DT_RTLREADING;
		}

		return FlagDT;
	}

	wchar_t * ReplaceVarPlaceFoldersW(wchar_t *pTesto)
	{
		static wchar_t BufferRep[32000];

		DWORD i;
		DWORD Indice;
		char StrHex[10];
		DWORD j;
		int Codice;
		DWORD z;
		wchar_t *pChar;
		char Buffer[120];
		int Valore;
		bool TestPlaceFolder;
		wchar_t MioCar;
		bool TestReplaced;

		z = 0;
		BufferRep[z] = 0;
		Indice = 0;
		i = 0;
		TestPlaceFolder = false;
		while (pTesto[i]) {
			MioCar = pTesto[i];
			TestReplaced = false;

			if (MioCar == '#') {
				// potrebbe essere placefolder, provare a estrarlo
				for (j = 0; j < 4; j++) {
					StrHex[j] = (char) pTesto[i + 1 + j];
				}
				StrHex[j] = 0;

				if (sscanf_s(StrHex, "%X", &Codice) == 1) {
					TestReplaced = true;

					TestPlaceFolder = true;
					// trovato place folder valido
					i = i + 1 + j; // saltare caratteri di testo originale dove c'era il placefoldedr

					// ok, adesso devo ottenere il testo che corrisponde a variabile
					// di questo placefolder
					// e copiarlo in BufferRep[z]
					// vedere se e' variabile speciale
					switch (Codice) {
					case VAR_TYPE_INPUT_NUMBER:
						sprintf_s(Buffer, "%d", GlobTomb4.pBaseVariableTRNG->Globals.LastInputNumber);
						pChar = Char2Unicode(Buffer);
						break;
					case VAR_TYPE_INPUT_TEXT:
						pChar = Char2Unicode(GlobTomb4.pBaseVariableTRNG->Globals.LastInputText);
						break;
					case VAR_TYPE_BIG_TEXT:
						pChar = Char2Unicode(GlobTomb4.pBaseVariableTRNG->Globals.TextBig);
						break;
					default:
						// non e' speciale
						// ora vedere se e' variabile testo o numerica

						if ((Codice & VAR_TYPE_STORE) == 0 && (Codice & VAR_MASK_SIZE) == VAR_TYPE_TEXT) {
							// e' una variabile di testo, infatti se manca store
							pChar = Char2Unicode(LeggiVariabileTesto((WORD) Codice));
							break;
						}

						// e' una numerica normale, store o locale,o globale
						Valore = LeggiVariabile((WORD) Codice);
						// se e' di tipo timer formattarla come cronometro
						if (Codice == 0x33 || Codice == 0x73) {
							// e' cronometro
							pChar = Char2Unicode(FormattaTimer(Valore));
						} else {
							// e' numero normale

							sprintf_s(Buffer, "%d", Valore);
							pChar = Char2Unicode(Buffer);
						}
						break;
					}

					for (j = 0; j < wcslen(pChar); j++) {
						BufferRep[z++] = pChar[j];
					}
				}
			}

			if (TestReplaced == false) {
				BufferRep[z++] = pTesto[i++];
			}

		}

		BufferRep[z] = 0;

		if (TestPlaceFolder == false)
			return pTesto;
		// c'erano place folder:

		return BufferRep;
	}

	// effettua conversionne (semplice, tra tresto normale e unicode

	wchar_t * Char2Unicode(char *pTesto)
	{
		static wchar_t MyBufInterno[1024];

		DWORD i;

		for (i = 0; i < strlen(pTesto); i++) {
			MyBufInterno[i] = (wchar_t) pTesto[i];
		}
		MyBufInterno[i] = 0;

		return MyBufInterno;
	}

	// restituisce il puntatore al testo di una delle variabili
	char *LeggiVariabileTesto(WORD CodiceVariabile)
	{
		int Indice;

		// NOTA: per i codici di LastInputText e BigText viene accettato anche il codice accorciato
		// presente in #VAR_TEXT# di ng_constants
		// vedere se e' l'ultima testo inserito in inputtext
		if (CodiceVariabile == VAR_TYPE_INPUT_TEXT || CodiceVariabile == 54) {
			return GlobTomb4.pBaseVariableTRNG->Globals.LastInputText;
		}

		if (CodiceVariabile == VAR_TYPE_BIG_TEXT || CodiceVariabile == 55) {
			return GlobTomb4.pBaseVariableTRNG->Globals.TextBig;
		}

		Indice = CodiceVariabile & (VAR_MASK_INDEX >> 2);
		return GlobTomb4.pBaseVariableTRNG->Globals.VetTextVar[Indice].Text;
	}

	// se in pTesto vengono trovati dei place folder "#03A3" per variabili
	// li sostituisce e resittuisce il testo tradotto.
	// nota: il testo e' sempre in variabile globale ZonaReplace
	// per cui non bisogna fare chiamate nidiicate
	// remark se la variabile e' store L (come Log) mostrare
	// il valore in decimale, esadecimale e binario
	char *ReplaceVarPlaceFolders(char *pTesto)
	{
		DWORD i;
		DWORD Indice;
		char StrHex[10];
		DWORD j;
		int Codice;
		DWORD z;
		char *pChar;
		char Buffer[120];
		int Valore;
		bool TestPlaceFolder;
		char MioCar;
		bool TestReplaced;

		z = 0;
		ZonaReplace[z] = 0;
		Indice = 0;
		i = 0;
		TestPlaceFolder = false;
		while (pTesto[i]) {
			MioCar = pTesto[i];
			TestReplaced = false;

			if (MioCar == '#') {
				// potrebbe essere placefolder, provare a estrarlo
				for (j = 0; j < 4; j++) {
					StrHex[j] = pTesto[i + 1 + j];
				}
				StrHex[j] = 0;

				if (sscanf_s(StrHex, "%X", &Codice) == 1) {
					TestReplaced = true;

					TestPlaceFolder = true;
					// trovato place folder valido
					i = i + 1 + j; // saltare caratteri di testo originale dove c'era il placefoldedr

					// ok, adesso devo ottenere il testo che corrisponde a variabile
					// di questo placefolder
					// e copiarlo in ZonaReplace[z]
					// vedere se e' variabile speciale
					switch (Codice) {
					case VAR_TYPE_INPUT_NUMBER:
						sprintf_s(Buffer, "%d", GlobTomb4.pBaseVariableTRNG->Globals.LastInputNumber);
						pChar = Buffer;
						break;
					case VAR_TYPE_INPUT_TEXT:
						pChar = GlobTomb4.pBaseVariableTRNG->Globals.LastInputText;
						break;
					case VAR_TYPE_BIG_TEXT:
						pChar = GlobTomb4.pBaseVariableTRNG->Globals.TextBig;
						break;
					default:
						// non e' speciale
						// ora vedere se e' variabile testo o numerica

						if ((Codice & VAR_TYPE_STORE) == 0 && (Codice & VAR_MASK_SIZE) == VAR_TYPE_TEXT) {
							// e' una variabile di testo, infatti se manca store
							pChar = LeggiVariabileTesto((WORD) Codice);
							break;
						}

						// e' una numerica normale, store o locale,o globale
						Valore = LeggiVariabile((WORD) Codice);
						// se e' di tipo timer formattarla come cronometro
						if (Codice == 0x33 || Codice == 0x73) {
							// e' cronometro
							pChar = FormattaTimer(Valore);
						} else {
							// e' numero normale

							sprintf_s(Buffer, "%d", Valore);
							pChar = Buffer;
						}
						break;
					}

					for (j = 0; j < strlen(pChar); j++) {
						ZonaReplace[z++] = pChar[j];
					}
				}
			}

			if (TestReplaced == false) {
				ZonaReplace[z++] = pTesto[i++];
			}

		}

		ZonaReplace[z] = 0;

		if (TestPlaceFolder == false)
			return pTesto;
		// c'erano place folder:

		return ZonaReplace;
	}

	// trova quanto testo puo' essere contenuto per intero in pRect
	// e restituisce il puntatore al carattere (sempre 0x0a)
	// dove effettuare la divisione dei due testi
	// nota: se restituisce NULL vuol dire che tutto il testo (pTesto)
	// puo' essere contenuto in pRect
	// nota: se il puntatore restituisco e' uguale e pTesto
	// vuol dire che neanche una linea puo' essere ospitata in pRect
	char *TrovaDivisioneTesto(RECT *pRect, StrWindowsFont *pFont, HDC MioHdc, char *pTesto)
	{
		DWORD FlagDT;
		int Indice;
		RECT TempRect;
		int SizeY;
		int SizeFrame;
		int i;
		char *pChar;

		FlagDT = CreaFlagDT(pFont);
		FlagDT |= DT_CALCRECT;

		Indice = strlen(pTesto);
		SizeFrame = pRect->bottom - pRect->top;

		do {
			TempRect = *pRect;
			pChar = ReplaceVarPlaceFolders(pTesto);
			SizeY = DrawText(MioHdc, pChar, Indice, &TempRect, FlagDT);

			if (SizeY > SizeFrame) {
				// ridurre il testo da visualizzare indietreggiando fino
				// a riga precedente
				for (i = Indice - 1; i >= 0; i--) {
					if (pTesto[i] == 0x0a)
						break;
				}
				if (i < 0)
					return pTesto;

				Indice = i;
			}
		} while (SizeY > SizeFrame);

		if ((DWORD) Indice == strlen(pTesto)) {
			return NULL;
		}
		return &pTesto[Indice];
	}

	// esegue uno zoom di immagine che si trova in HdcSource e che
	// ha dimensione SrcSizeX SrcSizeY, visualizzandola su hdctom
	// ingrandendola partendo da un 1/10 della sua dimensione finale
	// fino a farle arrivare a posizione edimensione finale di pFine
	// nota: usa anche hdc temp dove e' stato salvato background di gioco
	void ZoomImageDiario(RECT *pFine, HDC HdcSource, int SrcSizeX, int SrcSizeY, bool TestTransparent)
	{
		StrEffettoImage *pEffetto;
		float OrgX, OrgY;
		DWORD FlagTasti;
		StrEffettoImage StoreEffetto;
		StrShowImage *pBase;
		DWORD StartTime;
		DWORD LastTick;
		DWORD TickNow;
		RECT StoreRect;
		RECT *pMioRect;
		DWORD TotFrames;
		bool TestTombAllocatoNow;

		pMioRect = &StoreRect;

		TestTombAllocatoNow = false;

		pBase = &GlobTomb4.BaseImages;
		pEffetto = &StoreEffetto;

		pEffetto->Fine.OrgX = (float) pFine->left;
		pEffetto->Fine.OrgY = (float) pFine->top;
		pEffetto->Fine.SizeX = (float) pFine->right;
		pEffetto->Fine.SizeY = (float) pFine->bottom;

		// ora calcolare quale sara' il punto d'inizio
		//diciamo che l'immagine in partenza deve essere 10 volte piu' piccola

		pEffetto->Inizio.SizeX = (float) pEffetto->Fine.SizeX / 10;
		pEffetto->Inizio.SizeY = (float) pEffetto->Fine.SizeY / 10;

		// ora devo calcolare la coordinata iniziale
		// devo partire dal centro dell'immagine in posizione finale
		OrgX = pEffetto->Fine.OrgX + (pEffetto->Fine.SizeX / 2);
		OrgY = pEffetto->Fine.OrgY + (pEffetto->Fine.SizeY / 2);

		// adesso aumentare a questi orgx orgxy la meta' della dimensione
		// iniziale
		OrgX -= (pEffetto->Inizio.SizeX / 2);
		OrgY -= (pEffetto->Inizio.SizeY / 2);

		pEffetto->Inizio.OrgX = OrgX;
		pEffetto->Inizio.OrgY = OrgY;

		// ok, ora calcolare con il numero di passaggi TotFrames
		// gli incrementi
		TotFrames = 20;

		pEffetto->Inc.OrgX = (pEffetto->Fine.OrgX - pEffetto->Inizio.OrgX) / TotFrames;
		pEffetto->Inc.OrgY = (pEffetto->Fine.OrgY - pEffetto->Inizio.OrgY) / TotFrames;

		pEffetto->Inc.SizeX = (pEffetto->Fine.SizeX - pEffetto->Inizio.SizeX) / TotFrames;
		pEffetto->Inc.SizeY = (pEffetto->Fine.SizeY - pEffetto->Inizio.SizeY) / TotFrames;
		pEffetto->TotFrames = TotFrames;
		// adesso eseguire dinamicamente l'effetto

		FlagTasti = 0;
		StartTime = (DWORD) GetTickCount64();
		LastTick = 0;
		TickNow = 1;

		// partire con pmiorect in posizione inizio
		pMioRect->left = (int) pEffetto->Inizio.OrgX;
		pMioRect->top = (int) pEffetto->Inizio.OrgY;
		pMioRect->right = (int) pEffetto->Inizio.SizeX;
		pMioRect->bottom = (int) pEffetto->Inizio.SizeY;

		SetStretchBltMode(pBase->Temp.MemHdc, COLORONCOLOR);

		do {
			BeginCicloDraw();

			LeggiDirectInput();

			if (TickNow > LastTick) {

				LastTick = TickNow;

				pEffetto->Inizio.OrgX += pEffetto->Inc.OrgX;
				pEffetto->Inizio.OrgY += pEffetto->Inc.OrgY;
				pEffetto->Inizio.SizeX += pEffetto->Inc.SizeX;
				pEffetto->Inizio.SizeY += pEffetto->Inc.SizeY;

				pEffetto->TotFrames--;

				if (pEffetto->TotFrames) {

					pMioRect->left = (int) pEffetto->Inizio.OrgX;
					pMioRect->top = (int) pEffetto->Inizio.OrgY;
					pMioRect->right = (int) pEffetto->Inizio.SizeX;
					pMioRect->bottom = (int) pEffetto->Inizio.SizeY;
				}
				// ora copiare l'immagine little sull hdc temp
				// nella posizione edimensione di pMioRecord

				if (TestTransparent) {
					TransparentBlt(pBase->Temp.MemHdc, pMioRect->left, pMioRect->top, pMioRect->right, pMioRect->bottom, HdcSource, 0, 0, SrcSizeX, SrcSizeY, 0xff00ff);
				} else {
					StretchBlt(pBase->Temp.MemHdc, pMioRect->left, pMioRect->top, pMioRect->right, pMioRect->bottom, HdcSource, 0, 0, SrcSizeX, SrcSizeY, SRCCOPY);
				}
			}

			AllocaHdcTomb(pBase, false, true);
			BitBlt(pBase->HdcTomb, 0, 0, pBase->Temp.SizeX, pBase->Temp.SizeY, pBase->Temp.MemHdc, 0, 0, SRCCOPY);
			LiberaHdcTomb(pBase, true);
			EndCicloDraw();

			TickNow = (DWORD) GetTickCount64() - StartTime;
			TickNow /= 8;

		} while (pEffetto->TotFrames);
	}

	// chiama initpolylist, inizio ciclo principale di draw in tomb4
	void BeginCicloDraw(void)
	{
		tomb4::S_InitialisePolyList();
	}

	// chiama outputpolylist e dumpscreen per completar eil ciclo di draw
	void EndCicloDraw(void)
	{
		tomb4::S_OutputPolyList();
		tomb4::S_DumpScreen();
	}

	// riprende la traccia audio principlae dal punto in cui era stata
	// sospesa
	// attenzione: e' necessario che sia stata chiamata SospendiAudio()
	void RiprendiAudio(void)
	{
		StrBassHandles *pBass;
		StrAudioSospeso *pSospeso;
		StrRecordSospensione *pRec;
		int Indice;

		pSospeso = &GlobTomb4.AudioSospeso;
		Indice = pSospeso->CountSuspend;
		Indice--;
		if (Indice < 0) {
			pSospeso->CountSuspend = 0;
			return;
		}
		pRec = &pSospeso->VetSospeso[Indice];

		pBass = &GlobTomb4.BaseBassHandles;

		if (pBass->TestPresente) {
			StopBassSuoni(-1);
			StopAllSounds();

			pBass->CanaleNow = 0 | 0x40;
			pBass->StartOffset = pRec->Posizione;
		} else {
			tomb4::S_CDStop();
			StopAllSounds();
		}
		if (pRec->NumeroCD != -1)
			tomb4::S_CDPlay(pRec->NumeroCD, pRec->TestLoop);
		*GlobTomb4.pAdr->pCDTrackNow = pRec->NumeroCD;
		*GlobTomb4.pAdr->pTestCdLoop = pRec->NumeroCD;

		pSospeso->CountSuspend--;
		if (pSospeso->CountSuspend == 0)
			RiprendiThreadNotifica();
	}

	// viene chiamato quando si trova trigger fmv
	// in NumeroFmv c'e' il numero
	// imposta in variabile globale GlobTomb4.BaseFMV.IndiceFmvAttivato
	void ElaboraTriggerFMV(int NumeroFmv)
	{
		int i;
		BYTE *pFlagWindow;

		pFlagWindow = (BYTE*) &tomb4::App.dx.Flags;
		if (NumeroFmv >= 128 || GlobTomb4.BaseFMV.VetFmvEseguiti[NumeroFmv])
			return;

		for (i = 0; i < GlobTomb4.BaseFMV.TotFmv; i++) {
			if ((GlobTomb4.BaseFMV.VetFmv[i] & 0x7f) == NumeroFmv) {

				PreparaLancioFilmato(GlobTomb4.BaseFMV.VetFmv[i]);

				GlobTomb4.BaseFMV.VetFmvEseguiti[NumeroFmv] = 1;

				return;
			}
		}
		GlobTomb4.BaseFMV.VetFmvEseguiti[NumeroFmv] = 1;

		sprintf_s(BufferLog, "ERROR: Not found in script.dat FMV with number %d", NumeroFmv);
		InviaLog(BufferLog);
	}

	// eseguire le seguenti operazioni:
	// 1) Azionare fade in
	// 2) Lanciare azione per azionare filmato quando fade in e' terminato
	// 3) Disabilitare tutti i suoni
	// 4) Disabilitare critical section

	void PreparaLancioFilmato(int NumeroFMV)
	{
		StrProgressiveAction *pAzione;
		int IndiceAzione;
		char Buffer[256];
		int *pTestOggettoSoundAttivo;
		BYTE *pSettingNoFMV;
		short *pTestAttivoFade;
		short *pSchermoBuio;
		StrFMV *pFmv;
		bool TestFade;

		pTestOggettoSoundAttivo = (int*) &tomb4::sound_active;
		pSettingNoFMV = (BYTE*) &tomb4::fmvs_disabled;
		pTestAttivoFade = &tomb4::ScreenFading;
		pSchermoBuio = &tomb4::ScreenFadedOut;

		if (*pSettingNoFMV) {

			InviaLog("Ignore current FMV: It's present setting: no animated sequences (FMVs).");
			return;
		}

		if (TrovaFileFMV(Buffer, NumeroFMV & 0x7f) == false)
			return;

		pFmv = &GlobTomb4.BaseFMV;
		TestFade = false;
		if (GlobTomb4.pBaseCustomize->FlagsFMV & FMV_FADE_OUT)
			TestFade = true;

		IndiceAzione = CreaNuovaAzioneProgressiva();
		pAzione = &GlobTomb4.VetProgressiveActions[IndiceAzione];
		pAzione->ActionType = AZ_PREPARA_FILMATO;
		pAzione->ItemIndex = (short) NumeroFMV;
		// se lo shcermo e' gia' hide non fare il fade out
		if (GlobTomb4.TestNoUpdate)
			TestFade = false;

		if (TestFade == false) {
			pAzione->Arg1 = 2;

			GlobTomb4.TestNoUpdate = true;

		} else {
			pAzione->Arg1 = 30;
		}

		pFmv->SalvaBloccatiFMV = GlobTomb4.KeysToStop;
		GlobTomb4.KeysToStop = -1;

		SospendiSuoniPerFMV();

		pFmv->TestFattoFadeOut = false;

		if (TestFade) {

			tomb4::SetScreenFadeOut(30, 0);
			pFmv->TestFattoFadeOut = true;
		}
	}

	// verifica se esiste un file fmv con estensione dello script in cartelle "fmvs" / "store" o in cartella "trle"
	bool TrovaFileFMV(char NomeFmv[], int Indice)
	{
		__try { throw __func__; } __finally {}
	}

	// chiamata all'avvio di filmato, salva i dati relativi
	// a suoni cd e li chiude
	void SospendiSuoniPerFMV(void)
	{
		StrCanaleBass *pCanale;
		StrBassHandles *pBass;
		int i;
		StrFMV *pFmv;

		// agigungere info sui cd in azione

		pBass = &GlobTomb4.BaseBassHandles;
		pFmv = &GlobTomb4.BaseFMV;

		pFmv->LastCdSound = -1;
		pFmv->LastCdLoop = false;
		if (pBass->TestPresente) {

			pBass = &GlobTomb4.BaseBassHandles;
			for (i = 0; i < 2; i++) {
				pCanale = &pBass->VetCanali[i];

				if (pCanale->Canale != NULL && pBass->Proc.BASS_ChannelIsActive(pCanale->Canale) != 0) {
					// canale attivo
					pFmv->LastCdSound = pCanale->NumeroCd;
					if (pCanale->Loop)
						pFmv->LastCdLoop = true;

					// salvare posizione di suono
					pFmv->LastCdPosizione = (DWORD) pBass->Proc.BASS_ChannelGetPosition(pCanale->Canale, BASS_POS_BYTE);
					break;
				}

			}
			StopBassSuoni(-1);

		} else {
			// non c'e' bass, usare vecchio metodo perconoscere il cd attivo
			// e se ha il loop o meno
			pFmv->LastCdSound = *GlobTomb4.pAdr->pAudioTrackLoop;
			pFmv->LastCdLoop = *GlobTomb4.pAdr->pTestAudioTrackLoop;
			tomb4::S_CDStop();
		}
	}

	// funzione che fverifica in modo dettagliato se box di collisione
	// di moveable pItem tocca il box di collisione di oggetto generico pCustom
	// nota: ruota entrambi i box collisione e salva questi valori in GlobTomb4.pMisc->CollisionLast
	bool CollideItemConCustom(StrItemTr4 *pItem, StrCustomItem *pCustom, int Bordo)
	{
		StrBoxCollisione *pBoxRelItem;
		StrBoxCollisione *pTempColl;
		StrRettangolo *pRet;
		StrMioPuntoInt *pPunto;
		int i;
		StrAbsBoxCollision *pBoxItem;
		StrAbsBoxCollision *pBoxCustom;
		int x, z;

		pBoxItem = &GlobTomb4.pMisc->CollisionLast.BoxItem;
		pBoxCustom = &GlobTomb4.pMisc->CollisionLast.BoxSecondary;

		// prima vedere se valori y sono tali da rendere possibile
		// collisione
		pBoxRelItem = (StrBoxCollisione *) tomb4::GetBestFrame((tomb4::ITEM_INFO *) pItem);

		pBoxItem->MinY = pItem->CordY + pBoxRelItem->MinY;
		pBoxItem->MaxY = pItem->CordY + pBoxRelItem->MaxY;

		pBoxCustom->MinY = pCustom->CordY + pCustom->pBoxRel->MinY;
		pBoxCustom->MaxY = pCustom->CordY + pCustom->pBoxRel->MaxY;

		GlobTomb4.BaseCollItem.OutCollisioneBox.MinY = pBoxCustom->MinY;
		GlobTomb4.BaseCollItem.OutCollisioneBox.MaxY = pBoxCustom->MaxY;

		if (pBoxCustom->MaxY < pBoxItem->MinY)
			return false;
		if (pBoxCustom->MinY > pBoxItem->MaxY)
			return false;

		// ora ruotare i  box
		// e trasformarli in valori assoluti
		pTempColl = RuotaBox(pCustom->pBoxRel, pCustom->hOrient);

		pBoxCustom->MinX = pCustom->CordX + pTempColl->MinX - Bordo;
		pBoxCustom->MaxX = pCustom->CordX + pTempColl->MaxX + Bordo;
		pBoxCustom->MinZ = pCustom->CordZ + pTempColl->MinZ - Bordo;
		pBoxCustom->MaxZ = pCustom->CordZ + pTempColl->MaxZ + Bordo;

		// ora trasformare in assoluto quello di item
		pBoxItem->MinX = pItem->CordX + pBoxRelItem->MinX;
		pBoxItem->MaxX = pItem->CordX + pBoxRelItem->MaxX;
		pBoxItem->MinZ = pItem->CordZ + pBoxRelItem->MinZ;
		pBoxItem->MaxZ = pItem->CordZ + pBoxRelItem->MaxZ;

		pRet = RuotaBoxAbs(pItem->CordX, pItem->CordZ, &GlobTomb4.pMisc->CollisionLast.BoxItem, pItem->OrientationH);

		// ora verificare se almeno uno dei quattro vertici di collisione item
		// e' interno in box custom

		for (i = 0; i < 4; i++) {
			pPunto = &pRet->VetVertici[i];

			if (pPunto->x >= pBoxCustom->MinX && pPunto->x <= pBoxCustom->MaxX && pPunto->z >= pBoxCustom->MinZ && pPunto->z <= pBoxCustom->MaxZ)
				return true;
		}

		// considerare anche se origine di item principale sia dentro box collisione custom
		x = (int) pItem->CordX;
		z = (int) pItem->CordZ;

		if (x >= pBoxCustom->MinX && x <= pBoxCustom->MaxX && z >= pBoxCustom->MinZ && z <= pBoxCustom->MaxZ)
			return true;

		// ora vedere se origine di oggetto custom e' interno a collisione di item principale

		if (IsInsideRettangolo(pCustom->CordX, pCustom->CordZ, pRet) == true)
			return true;

		// ora vedere se uno dei vertici di oggetto custom e' interno a collision item
		if (IsInsideRettangolo(pBoxCustom->MinX, pBoxCustom->MinZ, pRet) == true)
			return true;

		if (IsInsideRettangolo(pBoxCustom->MinX, pBoxCustom->MaxZ, pRet) == true)
			return true;

		if (IsInsideRettangolo(pBoxCustom->MaxX, pBoxCustom->MinZ, pRet) == true)
			return true;

		if (IsInsideRettangolo(pBoxCustom->MaxX, pBoxCustom->MaxZ, pRet) == true)
			return true;

		return false;
	}

	// ruota in modo preciso (qualunque numero di gradi)
	// il pBox con valori gia' resi assoluti
	StrRettangolo *RuotaBoxAbs(DWORD CX, DWORD CZ, StrAbsBoxCollision *pBox, short Gradi)
	{
		static StrRettangolo Ret;

		int i;

		Ret.VetVertici[0].x = pBox->MinX;
		Ret.VetVertici[0].z = pBox->MinZ;

		Ret.VetVertici[1].x = pBox->MaxX;
		Ret.VetVertici[1].z = pBox->MinZ;

		Ret.VetVertici[2].x = pBox->MinX;
		Ret.VetVertici[2].z = pBox->MaxZ;

		Ret.VetVertici[3].x = pBox->MaxX;
		Ret.VetVertici[3].z = pBox->MaxZ;

		for (i = 0; i < 4; i++) {

			RuotaPuntoInt(CX, CZ, &Ret.VetVertici[i].x, &Ret.VetVertici[i].z, Gradi);
		}

		return &Ret;
	}

	// funzione che restituisce la rotazione di un punto
	// intorno ad un centro di tot gradi
	// e' usata per ruotare i vertici di un box di  collisione
	// intorno al pivot dell'roeintamento attule dell'oggetto
	void RuotaPuntoInt(DWORD CX, DWORD CZ, int * pPX, int * pPZ, short Gradi)
	{
		int DifX, DifZ;
		int Distanza;
		short OrientNow;
		int IncX, IncZ;

		if (Gradi == 0)
			return;

		// prima calcolare distanza tra cx e cz

		DifX = CX - *pPX;
		DifZ = CZ - *pPZ;

		Distanza = Float2Int((float) sqrt((DifX * DifX) + (DifZ * DifZ)));

		// ora trovare angolo tra C e P
		OrientNow = (short) tomb4::mGetAngle(CX, CZ, *pPX, *pPZ);
		OrientNow += 0x4000;

		// ora aggiungere gradi di rotazione
		OrientNow += Gradi;

		// ora trovare punto da cx,cz con distanza in direzione OrientNow
		CalcolaIncremento(OrientNow, &IncX, &IncZ, Distanza);

		*pPX = CX + IncX;
		*pPZ = CZ + IncZ;

		return;
	}

	// verifica se il punto (x,z) e' interno al rettangolo stabilito dal rettangolo ruotato
	// ottenuto da funzione RuotaBoxAbs()
	bool IsInsideRettangolo(DWORD x, DWORD z, StrRettangolo *pRet)
	{
		StrTriangolo Tria;

		Tria.A.x = (float) pRet->VetVertici[0].x;
		Tria.A.y = (float) pRet->VetVertici[0].z;

		Tria.B.x = (float) pRet->VetVertici[1].x;
		Tria.B.y = (float) pRet->VetVertici[1].z;

		Tria.C.x = (float) pRet->VetVertici[2].x;
		Tria.C.y = (float) pRet->VetVertici[2].z;

		if (IsPuntoInternoTriangolo((float) x, (float) z, &Tria))
			return true;

		// altro triangolo
		// ora provare nell'altro triangolo
		Tria.A.x = (float) pRet->VetVertici[1].x;
		Tria.A.y = (float) pRet->VetVertici[1].z;

		Tria.B.x = (float) pRet->VetVertici[2].x;
		Tria.B.y = (float) pRet->VetVertici[2].z;

		Tria.C.x = (float) pRet->VetVertici[3].x;
		Tria.C.y = (float) pRet->VetVertici[3].z;

		return IsPuntoInternoTriangolo((float) x, (float) z, &Tria);
	}
}

void LoadTombNextGenerationInject_Oggetti(bool replace)
{
	ProcessInject(0x1001194A, (unsigned int)trng::ProcMyBridgeFloor, false);
	ProcessInject(0x10011C6A, (unsigned int)trng::ProcMyBridgeCeiling, false);
	ProcessInject(0x1001C94C, (unsigned int)trng::TightRopeCollision, false);
	ProcessInject(0x1001C8EC, (unsigned int)trng::InitialiseTightRope, false);
	ProcessInject(0x1001D5E8, (unsigned int)trng::InitialiseGuardian, false);
	ProcessInject(0x1001D822, (unsigned int)trng::GuardianControl, false);
	ProcessInject(0x1001BF31, (unsigned int)trng::ParallelBarCollision, false);
	ProcessInject(0x10014BE3, (unsigned int)trng::ControlBubble, false);
	ProcessInject(0x10012116, (unsigned int)trng::InitializeFishGenerator, false);
	ProcessInject(0x100122A7, (unsigned int)trng::TriggerFish, false);
	ProcessInject(0x1001FE63, (unsigned int)trng::TorpedoControl, false);
	ProcessInject(0x1001548E, (unsigned int)trng::DiverControl, false);
	ProcessInject(0x10025267, (unsigned int)trng::CreaFinestraAvviso, false);
	ProcessInject(0x10025FE9, (unsigned int)trng::IsModoWindowed, false);
	ProcessInject(0x1002504C, (unsigned int)trng::CreaBlackWindow, replace);
	ProcessInject(0x10024EC9, (unsigned int)trng::WindowBlackProc, false);
	ProcessInject(0x10024FCE, (unsigned int)trng::DisattivaAnimWindow, false);
	ProcessInject(0x10024E6E, (unsigned int)trng::NascondiTaskBar, false);
	ProcessInject(0x100235F5, (unsigned int)trng::CreaWindowsFontForCB, replace);
	ProcessInject(0x100233EA, (unsigned int)trng::CreaWindowsFont, replace);
	ProcessInject(0x10021182, (unsigned int)trng::LeggiVariabile, replace);
	ProcessInject(0x10020F12, (unsigned int)trng::GetNomeVariabile, replace);
	ProcessInject(0x100245D0, (unsigned int)trng::MostraDiario, replace);
	ProcessInject(0x10021DCF, (unsigned int)trng::AllocaDiario, replace);
	ProcessInject(0x10022057, (unsigned int)trng::LiberaDiario, replace);
	ProcessInject(0x10021FC1, (unsigned int)trng::LiberaPaginaDiario, replace);
	ProcessInject(0x10024514, (unsigned int)trng::ScopriSospendiAudioDiario, replace);
	ProcessInject(0x1002238F, (unsigned int)trng::SospendiAudio, replace);
	ProcessInject(0x10022945, (unsigned int)trng::AllocaPaginaDiario, replace);
	ProcessInject(0x10022093, (unsigned int)trng::EstraeDatiFrame, replace);
	ProcessInject(0x100221F1, (unsigned int)trng::ConvertiRectMicroUnits, replace);
	ProcessInject(0x1002442A, (unsigned int)trng::SuonaAudioPagina, replace);
	ProcessInject(0x10024373, (unsigned int)trng::ShowImageProp, replace);
	ProcessInject(0x1002411F, (unsigned int)trng::StampaTestoPaginaNow, replace);
	ProcessInject(0x10023639, (unsigned int)trng::ImpostaWindowsFont, replace);
	ProcessInject(0x100240B3, (unsigned int)trng::StampaTestoWindowsForCB, replace);
	ProcessInject(0x10023D0F, (unsigned int)trng::StampaTestoWindows, replace);
	ProcessInject(0x10023829, (unsigned int)trng::ConvertiStringaBinaria, replace);
	ProcessInject(0x100236B5, (unsigned int)trng::CreaFlagDT, replace);
	ProcessInject(0x100239BC, (unsigned int)trng::ReplaceVarPlaceFoldersW, replace);
	ProcessInject(0x10023968, (unsigned int)trng::Char2Unicode, replace);
	ProcessInject(0x10021686, (unsigned int)trng::LeggiVariabileTesto, replace);
	ProcessInject(0x10020C0E, (unsigned int)trng::ReplaceVarPlaceFolders, replace);
	ProcessInject(0x10023737, (unsigned int)trng::TrovaDivisioneTesto, replace);
	ProcessInject(0x10022571, (unsigned int)trng::ZoomImageDiario, replace);
	ProcessInject(0x1002255A, (unsigned int)trng::BeginCicloDraw, replace);
	ProcessInject(0x10022562, (unsigned int)trng::EndCicloDraw, replace);
	ProcessInject(0x10022470, (unsigned int)trng::RiprendiAudio, replace);
	ProcessInject(0x10025F13, (unsigned int)trng::ElaboraTriggerFMV, replace);
	ProcessInject(0x10025D9D, (unsigned int)trng::PreparaLancioFilmato, replace);
	ProcessInject(0x10026030, (unsigned int)trng::TrovaFileFMV, false);
	ProcessInject(0x10025CA9, (unsigned int)trng::SospendiSuoniPerFMV, replace);
	ProcessInject(0x10011568, (unsigned int)trng::CollideItemConCustom, replace);
	ProcessInject(0x100113D1, (unsigned int)trng::RuotaBoxAbs, replace);
	ProcessInject(0x10011305, (unsigned int)trng::RuotaPuntoInt, replace);
	ProcessInject(0x1001147E, (unsigned int)trng::IsInsideRettangolo, replace);
}
