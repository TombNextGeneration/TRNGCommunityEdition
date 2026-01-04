#pragma once

namespace trng {
	// for generic void / void callback procedure
	typedef void (__cdecl *CALL_VOID) (void);

	typedef void (__cdecl* TYPE_tombInviaLog) (int Numero, const char *pMex);

	// for callback CB_CUSTOMIZE
	typedef void (__cdecl *CALL_CUSTOMIZE) (WORD CustomizeValue, int NumberOfItems, short *pItemArray);

	// for callback CB_PARAMETER
	typedef void (__cdecl *CALL_PARAMETER) (WORD ParameterValue, int NumberOfItems, short *pItemArray);

	// for callback CB_ASSIGN_SLOT_MINE
	typedef void (__cdecl *CALL_ASSIGN_SLOT) (WORD Slot, WORD OBJ_TYPE);

	// prototype for CB_WINDOWS_FONT_CREATE callback
	// received in input:
	// pFont: pointer to StrWindowsFont structure with many data about feature of required font (gotten from script.dat)
	// TestFixWideScreen: if == true it requires to resize wide of font to compensate widescreen distorsion
	// return an handle of created font, or NULL if callback wants let to original code the creation of this font
	// note: This callback has been imagined for who wishes fix some problem with view of eastern charset fonts
	//       probably setting right font you coudl fix that problem with china fonts
	typedef HFONT (__cdecl *CALL_WINDOWS_FONT_CREATE) (StrWindowsFont *pFont, bool TestFixWideScreen);

	// prototype for CB_COMPLETED_PROGR_ACTION callback
	// note: ActionType will be a AZ_... value to identify a trng progressive action
	// note: pAction will point to progressive action structure with all data, exception the field Action
	// that will be 0, but the previous value (AZ_) will be store in ActionType argument
	typedef void (__cdecl *CALL_COMPLETED_PROGR_ACTION) (int ActionType, StrProgressiveAction *pAction);

	// for CB_FLIPEFFECT callback
	// ActivationMode has SCANF_.. flags to inform about the source of the trigger (floor data in level map, triggergroup,
	// direct call from code)
	// CBType remember to you the kind of callback it was (CBT_FIRST, CBT_AFTER, CBT_REPLACE) in this way you could use
	// same callback procedure to handle both types of all triggers callbacks
	// return TRET_ mask values
	typedef int (__cdecl *CALL_FLIPEFFECT) (WORD FlipIndex, WORD Timer, WORD Extra, WORD ActivationMode, WORD CBType);

	// for CB_FLIPEFFECT_MINE callback:
	// ActivationMode has SCANF_.. flags to inform about the source of the trigger (floor data in level map, triggergroup,
	// direct call from code)
	// return TRET_ mask values
	typedef int (__cdecl *CALL_FLIPEFFECT_MINE) (WORD FlipIndex, WORD Timer, WORD Extra, WORD ActivationMode);

	typedef bool (__cdecl *TYPE_IsComandoPremuto) (int Index);
	typedef void (__cdecl* TYPE_StopAllSounds) (void);

	// for CB_CONDITION callback
	// note: the Response field works only for CB_CONDITION with CBT_AFTER, where your code will receive
	// in Response the previous response returned by original trng code.
	// CBType remember to you the kind of callback it was (CBT_FIRST, CBT_AFTER, CBT_REPLACE) in this way you could use
	// same callback procedure to handle both types of all triggers callbacks
	// the callback has to return a mask with CTRET_ constant values
	typedef int (__cdecl *CALL_CONDITION) (WORD ConditionIndex, int ItemIndex, WORD Extra, WORD ActivationMode, bool Response, WORD CBType);

	// for CB_CONDITION_MINE callback
	// the callback has to return a mask with CTRET_ constant values
	typedef int (__cdecl *CALL_CONDITION_MINE) (WORD ConditionIndex, int ItemIndex, WORD Extra, WORD ActivationMode);

	// for CB_ACTION_MINE callback
	// return TRET_ mask values
	typedef int (__cdecl *CALL_ACTION_MINE) (WORD ActionIndex, int ItemIndex, WORD Extra, WORD ActivationMode);

	// for CB_ACTION callback
	// CBType remember to you the kind of callback it was (CBT_FIRST, CBT_AFTER, CBT_REPLACE) in this way you could use
	// same callback procedure to handle both types of all triggers callbacks
	// return TRET_ mask values
	typedef int (__cdecl *CALL_ACTION) (WORD ActionIndex, int ItemIndex, WORD Extra, WORD ActivationMode, WORD CBType);
}
