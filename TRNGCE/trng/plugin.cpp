#include "plugin.h"
#include "../inject.h"
#include "../tomb4/specific/winmain.h"
#include "Tomb_NextGeneration.h"

namespace trng {
	// scandisce file ng_constant incluso in risorse
	// per scoprire i flipeffect, action e condition usati da trng
	// e poi scrive questi valori in database
	// imposta anche first e last param e cust
	void InizializzaPluginTrng(void)
	{
		__try { throw __func__; } __finally {}
	}

	// se TestMsgBox=true visusaliza anche messagebox se e' possibile
	void InviaErroreLog(const char *pMessage, DWORD PluginID, bool TestMsgBox)
	{
		if (TestMsgBox) {
			// vedere se si puo' mandare message box
			TryMessageBox(pMessage, PluginID);
		} else {
			InviaLog(pMessage);
		}
	}

	// se modo non e' esclusivo visualizza message box, altrimenti restituisce false
	// in ogni caso manda il messaggio sul log
	bool TryMessageBox(const char *pMessage, DWORD ID_Plugin)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMai

		InviaLog(pMessage);
		if (*pTombWind4 == 0 || ScopreModoFullScreen() == false) {
			Tomb4MessageBox(pMessage, MyGlobPrivate.DataBase.pVetPlugins[ID_Plugin].Nome);
			return true;
		}
		return false;
	}

	void Tomb4MessageBox(const char *pMessaggio, char *pTitolo)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMai

		MessageBox(*pTombWind4, pMessaggio, pTitolo, MB_APPLMODAL);
	}

	// nota: cancella il comando script solo se Dynamic e' diverso da zero
	void DeleteParamCommand(int ParamType, int IdParam, bool TestSempre, bool TestSottoCommandi)
	{
		bool TestLast;
		int OldIndex;
		short *pTot;
		short n;
		int i;
		StrColoraItem *pColora;
		StrSpeechActor *pSpeech;
		WORD ComandoNow;
		int IdCommand;

		TestLast = false;

		switch (ParamType) {
		case PARAM_MOVE_ITEM:
			pTot = (short *) &GlobTomb4.BaseMoveItem.TotMove;
			OldIndex = GlobTomb4.BaseMoveItem.VetID[IdParam];
			if (OldIndex == -1)
				return;

			if (TestSempre == false && GlobTomb4.BaseMoveItem.VetMove[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_MOVE_ITEM with ID %d script command", IdParam);
			GlobTomb4.BaseMoveItem.VetID[IdParam] = -1;
			GlobTomb4.BaseMoveItem.VetMove[OldIndex].Dynamic = 0;
			break;

		case PARAM_ROTATE_ITEM:
			pTot = (short *) &GlobTomb4.BaseRotateItem.TotRotate;
			OldIndex = GlobTomb4.BaseRotateItem.VetID[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseRotateItem.VetRotate[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_ROTATE_ITEM with ID %d script command", IdParam);
			GlobTomb4.BaseRotateItem.VetID[IdParam] = -1;
			GlobTomb4.BaseRotateItem.VetRotate[OldIndex].Dynamic = 0;
			break;

		case PARAM_COLOR_ITEM:
			pTot = (short *) &GlobTomb4.BaseColoraItem.TotColoraItem;
			OldIndex = GlobTomb4.BaseColoraItem.VetID[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseColoraItem.VetColoraItem[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_COLOR_ITEM with ID %d script command", IdParam);
			GlobTomb4.BaseColoraItem.VetID[IdParam] = -1;
			GlobTomb4.BaseColoraItem.VetColoraItem[OldIndex].Dynamic = 0;
			if (TestSottoCommandi == false)
				break;
			// cancellare anche colorrgb collegati
			pColora = &GlobTomb4.BaseColoraItem.VetColoraItem[OldIndex];

			if (pColora->IdColore1 != -1) {
				DeleteColorRgb(pColora->IdColore1, false);
			}

			if (pColora->IdColore2 != -1) {
				DeleteColorRgb(pColora->IdColore2, false);
			}

			break;

		case PARAM_PRINT_TEXT:
			pTot = (short *) &GlobTomb4.BaseParamPrint.TotPrintText;
			OldIndex = GlobTomb4.BaseParamPrint.VetID[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseParamPrint.VetPrint[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_PRINT_TEXT with ID %d script command", IdParam);
			GlobTomb4.BaseParamPrint.VetID[IdParam] = -1;
			GlobTomb4.BaseParamPrint.VetPrint[OldIndex].Dynamic = 0;
			break;

		case PARAM_SET_CAMERA:
			pTot = (short *) &GlobTomb4.BaseSetCamera.TotSetCamera;
			OldIndex = GlobTomb4.BaseSetCamera.VetID[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseSetCamera.VetSetCamera[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_SET_CAMERA with ID %d script command", IdParam);
			GlobTomb4.BaseSetCamera.VetID[IdParam] = -1;
			GlobTomb4.BaseSetCamera.VetSetCamera[OldIndex].Dynamic = 0;
			break;

		case PARAM_SCALE_ITEM:
			pTot = (short *) &GlobTomb4.BaseScaleParam.TotScale;
			OldIndex = GlobTomb4.BaseScaleParam.VetIdScale[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseScaleParam.VetScaleItem[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_SCALE_ITEM with ID %d script command", IdParam);
			GlobTomb4.BaseScaleParam.VetIdScale[IdParam] = -1;
			GlobTomb4.BaseScaleParam.VetScaleItem[OldIndex].Dynamic = 0;
			break;

		case PARAM_SHOW_SPRITE:
			pTot = (short *) &GlobTomb4.BaseShowSprites.TotShowSprites;
			OldIndex = GlobTomb4.BaseShowSprites.VetIdShowSprites[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseShowSprites.VetShowSprites[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_SHOW_SPRITE with ID %d script command", IdParam);
			GlobTomb4.BaseShowSprites.VetIdShowSprites[IdParam] = -1;
			GlobTomb4.BaseShowSprites.VetShowSprites[OldIndex].Dynamic = 0;
			// nota: il colorrgb viene eliminato subito dopo aver letto il colorergb quando viene creato il param_show_sprite
			break;

		case PARAM_TRIANGLE:
			pTot = (short *) &GlobTomb4.BaseTriangles.TotTriangles;
			OldIndex = GlobTomb4.BaseTriangles.VetIdTriangles[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseTriangles.VetTriangles[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_TRIANGLE with ID %d script command", IdParam);
			GlobTomb4.BaseTriangles.VetIdTriangles[IdParam] = -1;
			GlobTomb4.BaseTriangles.VetTriangles[OldIndex].Dynamic = 0;
			break;
		case PARAM_QUADRILATERAL:
			pTot = (short *) &GlobTomb4.BaseQuads.TotQuads;
			OldIndex = GlobTomb4.BaseQuads.VetIdQuads[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseQuads.VetQuads[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_QUADRILATERAL with ID %d script command", IdParam);
			GlobTomb4.BaseQuads.VetIdQuads[IdParam] = -1;
			GlobTomb4.BaseQuads.VetQuads[OldIndex].Dynamic = 0;
			break;
		case PARAM_BIG_NUMBERS:
			// gestione particolare. se IdParam (che dovrebbe essere l'ultimo numero allocato)
			// e' uguale all'ultimo numero della serie, allora viene ridotto il numero
			// di big numbers
			i = GlobTomb4.TotBigNumbers - 1;
			if (i < 0)
				return;
			if (GlobTomb4.VetBigNumbers[i] == IdParam) {
				LogOnDebug("Deleted last PARAM_BIG_NUMBERS value: %d", IdParam);
				GlobTomb4.TotBigNumbers = i;
			}
			return;

		case PARAM_CIRCLE:
			pTot = (short *) &GlobTomb4.BaseCircles.TotCircles;
			OldIndex = GlobTomb4.BaseCircles.VetIdCircle[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseCircles.VetCircle[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_CIRCLE with ID %d script command", IdParam);
			GlobTomb4.BaseCircles.VetIdCircle[IdParam] = -1;
			GlobTomb4.BaseCircles.VetCircle[OldIndex].Dynamic = 0;
			break;

		case PARAM_LIGHTNING:
			pTot = (short*) &GlobTomb4.BaseParamLightning.TotParamLgtn;
			OldIndex = GlobTomb4.BaseParamLightning.VetId[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseParamLightning.VetRecordLgtn[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_LIGHTNING with ID %d script command", IdParam);
			GlobTomb4.BaseParamLightning.VetId[IdParam] = -1;
			GlobTomb4.BaseParamLightning.VetRecordLgtn[OldIndex].Dynamic = 0;

			break;

		case PARAM_RECT:
			pTot = (short*) &GlobTomb4.BaseParamMyRects.TotMyRect;
			OldIndex = GlobTomb4.BaseParamMyRects.VetId[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.BaseParamMyRects.VetMyRect[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_RECT with ID %d script command", IdParam);
			GlobTomb4.BaseParamMyRects.VetId[IdParam] = -1;
			GlobTomb4.BaseParamMyRects.VetMyRect[OldIndex].Dynamic = 0;
			break;
		case PARAM_SWAP_ANIMATIONS:
			pTot = (short*) &GlobTomb4.pBaseSwapAnim->TotSwapAnim;
			OldIndex = GlobTomb4.pBaseSwapAnim->VetId[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.pBaseSwapAnim->VetSwapAnim[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_SWAP_ANIMATIONS with ID %d script command", IdParam);
			GlobTomb4.pBaseSwapAnim->VetId[IdParam] = -1;
			GlobTomb4.pBaseSwapAnim->VetSwapAnim[OldIndex].Dynamic = 0;
			break;

		case PARAM_ACTOR_SPEECH:
			pTot = (short*) &GlobTomb4.pBaseSpeechActor->TotSpeechActor;
			OldIndex = GlobTomb4.pBaseSpeechActor->VetId[IdParam];
			if (OldIndex == -1)
				return;
			if (TestSempre == false && GlobTomb4.pBaseSpeechActor->VetSpeechActor[OldIndex].Dynamic == 0)
				return;
			LogOnDebug("Deleted Parameters=PARAM_ACTOR_SPEECH with ID %d script command", IdParam);
			GlobTomb4.pBaseSpeechActor->VetId[IdParam] = -1;
			GlobTomb4.pBaseSpeechActor->VetSpeechActor[OldIndex].Dynamic = 0;
			pSpeech = &GlobTomb4.pBaseSpeechActor->VetSpeechActor[OldIndex];

			// se nei comandi c'e' il comando SPC_PERFORM_TG
			for (i = 0; i < pSpeech->TotCommands; i++) {
				ComandoNow = pSpeech->VetCommands[i];

				if ((ComandoNow & SPC_MASK_COMMANDS) == SPC_PERFORM_TG) {
					IdCommand = ComandoNow & SPC_MASK_SINGLE;
					DeleteTriggerGroup(IdCommand, false);
				}
			}

			break;
		default:
			LogOnDebug("WARNING: attempt to delete an unsupported PARAM_ type %d", ParamType);
			return;
		}

		n= *pTot;
		n--;
		if (OldIndex == n)
			*pTot = n;
	}

	// Invia log con argomenti solo se e' attiva modalita' debug per trng oppure per plugin
	bool LogOnDebug(const char *szFormat, ...)
	{
		static HWND* pTombWind4 = &tomb4::App.hWnd;  //  ;HandleWindowMain
		static char MyInternalBuffer[512];

		bool TestAttivo;
	    va_list pArgs;

		TestAttivo = MyGlobPrivate.TestDebugVersione;

		if (*pTombWind4 == 0)
			return false;
		if (TestAttivo == false)
			return false;

		va_start(pArgs, szFormat);
		vsprintf_s(MyInternalBuffer, szFormat, pArgs);
		va_end(pArgs);

		InviaLog(MyInternalBuffer);

		return true;
	}

	void DeleteColorRgb(int IdColorRgb, bool TestSempre)
	{
		int OldIndex;
		int Tot;

		Tot = GlobTomb4.BaseColoriRGB.TotColori - 1;

		OldIndex = GlobTomb4.BaseColoriRGB.VetID[IdColorRgb];
		if (OldIndex == -1)
			return;
		if (TestSempre == false && GlobTomb4.BaseColoriRGB.VetColori[OldIndex].Dynamic == 0)
			return;

		LogOnDebug("Deleted ColorRgb= with ID %d script command", IdColorRgb);
		GlobTomb4.BaseColoriRGB.VetColori[OldIndex].Dynamic = 0;
		GlobTomb4.BaseColoriRGB.VetID[IdColorRgb] = -1;

		if (OldIndex == Tot) {
			GlobTomb4.BaseColoriRGB.TotColori = Tot;
		}
	}

	void DeleteTriggerGroup(int IdTriggerGroup, bool TestSempre)
	{
		int OldIndex;
		int Tot;

		OldIndex = GlobTomb4.pBaseTriggerGroups->VetID[IdTriggerGroup];
		if (OldIndex == -1)
			return;
		if (TestSempre == false && GlobTomb4.pBaseTriggerGroups->VetTriggerGroups[OldIndex].Dynamic == 0)
			return;

		GlobTomb4.pBaseTriggerGroups->VetTriggerGroups[OldIndex].Dynamic = 0;

		Tot = GlobTomb4.pBaseTriggerGroups->TotTriggerGroups - 1;

		GlobTomb4.pBaseTriggerGroups->VetID[IdTriggerGroup] = -1;

		if (OldIndex == Tot) {
			GlobTomb4.pBaseTriggerGroups->TotTriggerGroups = Tot;
		}
	}

	// nota: se testsempre=true allora ignora il campo Dynamic e anche fosse =0 eliminera' comunque il comando
	void DeleteAddEffect(int IdEffect, bool TestSempre)
	{
		int OldIndex;
		int Tot;

		Tot = GlobTomb4.pBaseEffects->TotEffects - 1;
		OldIndex = GlobTomb4.pBaseEffects->VetID[IdEffect];
		if (OldIndex == -1)
			return;
		if (TestSempre == false && GlobTomb4.pBaseEffects->VetEffects[OldIndex].Dynamic == 0)
			return;

		LogOnDebug("Deleted AddEffect= with ID %d script command", IdEffect);

		GlobTomb4.pBaseEffects->VetEffects[OldIndex].Dynamic = 0;
		GlobTomb4.pBaseEffects->VetID[IdEffect] = -1;

		if (OldIndex == Tot) {
			GlobTomb4.pBaseEffects->TotEffects = Tot;
		}
	}
}

void LoadTombNextGenerationInject_Plugin(bool replace)
{
	ProcessInject(0x10034C21, (unsigned int)trng::InizializzaPluginTrng, false);
	ProcessInject(0x1002B8F0, (unsigned int)trng::InviaErroreLog, replace);
	ProcessInject(0x1002B863, (unsigned int)trng::TryMessageBox, replace);
	ProcessInject(0x1002B845, (unsigned int)trng::Tomb4MessageBox, replace);
	ProcessInject(0x1002F9AB, (unsigned int)trng::DeleteParamCommand, replace);
	ProcessInject(0x1002B998, (unsigned int)trng::LogOnDebug, replace);
	ProcessInject(0x100302B9, (unsigned int)trng::DeleteColorRgb, replace);
	ProcessInject(0x1003021D, (unsigned int)trng::DeleteTriggerGroup, replace);
	ProcessInject(0x10030509, (unsigned int)trng::DeleteAddEffect, replace);
}
