#pragma once
#include <cstdio>
#include "structures.h"

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

	// prototype for CB_WINDOWS_TEXT_PRINT callback
	// received in input:
	// pRect : pointer to RECT structure with coordinate of box where to print the text
	// pFont : pointer to StrWindowsFont structure with many settings (about font) specified in script.dat
	// hDC : handle of Device Context where to print text (usually tomb raider hdc or a memory DC)
	// pText: pointer to text to print
	// pTestError: pointer to bool variable to set "true" if it happned an error, otherwise set to "false"
	// TestDummyPrint: it required to do not print really the text but perform only a computation about size
	//              of printed text (use DT_CALCRECT flag in DrawText() function)
	// WTF_Flags : one or more enumWTF_ flags
	// returns the size of printed text or 0 if callback wants letting to original code the target to print this text
	// note: the font has already been selected in hDC
	typedef int (__cdecl *CALL_WINDOWS_TEXT_PRINT)(RECT *pRect, StrWindowsFont *pFont, HDC hDC, char *pText, bool *pTestError, bool TestDummyPrint, DWORD WTF_Flags);

	// prototype for CB_WINDOWS_UNICODE_CONVERT callback
	// received in input:
	// pFont : pointer to StrWindowsFont structure with many settings (about font) specified in script.dat
	//         you should use these infos only on-read, to understand better the kind of characters you are
	//         going to convert but don't change data of StrWindowsFont structure
	// pText : pointer to byte based string of text to convert. You should read with debugger the format
	//         of this text to understand better further bugs to fix and then convert it in unicode format
	//         returning the pointer to wchar_t buffer with converted text to unicode
	// note: the pointer you returns has to be in persistent memory of course, (no local stack memory of your
	//       function
	// note:  if you return NULL it means you want letting to original code the conversion
	typedef wchar_t* (__cdecl * CALL_WINDOWS_UNICODE_CONVERT) (StrWindowsFont *pFont, char *pText);

	// prototype for CB_INVENTORY_MAIN callback
	// receive in input:
	// CBT_Flags: flag of current callback: CBT_FIRST, CBT_AFTER or CBT_REPLACE
	// TestLoadedGame: valid only for CBT_AFTER callback: it has been loaded a savegame from last inventory session
	//  SelectedItem: the slot of item chosen by inventory (like a key, puzzleitem ect)
	//					note: this parameter has a valid value only in CBT_AFTER callback
	//						  if its value ==  -1, then it has not been chosen any item
	// return a IRET_ constant
	typedef int (__cdecl *CALL_INVENTORY_MAIN) (WORD CBT_Flags, bool TestLoadedGame, int SelectedItem);

	// prototype for CB_LARA_CONTROL
	// receive in input:
	// CBT_Flags : flags of current callback CBT_FIRST, CBT_AFTER or CBT_REPLACE
	// pLara : structure of lara
	// return a SRET_ constant (read only for CBT_FIRST callback)
	typedef int (__cdecl *CALL_LARA_CTRL) (WORD CBT_Flags, StrItemTr4 *pLara);

	// prototype for CB_LARA_DRAW callback
	// receive in input:
	// CBT_Flags : flag of current callback: CBT_FIRST, CBT_AFTER or CBT_REPLACE
	// pLara     : Pointer to Lara's structure
	// TestNoUpdateLight:  if is == true, the light of lara will be not updated. If == false, the light will be
	//						calculated newly
	// TestMirror : if == true, the lara to draw is that in the mirror
	// return a SRET_ constant (read only for CBT_FIRST callback)
	typedef int (__cdecl *CALL_LARA_DRAW) (WORD CBT_Flags, StrItemTr4 * pLara, bool TestNoUpdateLight, bool TestMirror);

	// prototype for CB_LARA_HAIR_DRAW
	// receive the CBT_ flag for kind of callback (CBT_FIRST, CBT_AFTER or CBT_REPLACE)
	// return a SRET_ constant (read only for CBT_FIRST callback)
	typedef int (__cdecl *CALL_HAIR_DRAW) (WORD CBT_Flags);

	// prototype for CB_LARA_HAIR_CONTROL
	// receive in input:
	// CBT_Flags: flag of current callback: CBT_FIRST, CBT_AFTER or CBT_REPLACE
	// TestKeepDownHair: if == true, the ponytail will point down (not sure about this)
	// TestSecondTail: if == true, lara is young lara and there is to handle the second tail. If == false we are working of first, or only one, ponytail
	// pData: pointer to some data to manange hair. I don't know the meaning of this data. Sometimes it is NULL (0) to
	//		  mean : no data this time.
	// return a SRET_ constant (read only for CBT_FIRST callback)
	typedef int (__cdecl *CALL_HAIR_CONTROL) (WORD CBT_Flags, bool TestKeepDownHair, bool TestSecondTail, void *pData);

	// prototype for CB_INVENT_BACKGROUND_CREATE, CB_INVENT_BACKGROUND_DRAW, CB_INVENT_BACKGROUND_QUIT
	// receive in input:
	// CB_Type: the CB_.. constant for callback type
	// CBT_Flags: flag of current callback: CBT_FIRST, CBT_AFTER or CBT_REPLACE
	// PHASE_Type: enumPHASE about inventory, pause screen, load game or savegame panel
	// return a SRET_ constant (read only for CBT_FIRST callback)
	typedef int (__cdecl *CALL_INVENTORY_BACKGROUND) (WORD CB_Type, WORD CBT_Flags, WORD PHASE_Type);

	// prototype for CB_ANIMATE_LARA callback
	// received input:
	// CBT_Flags: flag of current callback: CBT_FIRST, CBT_AFTER or CBT_REPLACE
	// pLara: pointer to Lara's structure
	// return a SRET_ constant (read only for CBT_FIRST callback)
	typedef int (__cdecl *CALL_ANIMATE_LARA) (WORD CBT_Flags, StrItemTr4 *pLara);

	// prototype for CB_OPTIONS_MANAGER callbacks
	// received input:
	// TestTitle:  true when executed from title level
	// TestCommands: true when options are working on keyboard/joystick commands
	// SelectedRow: number of selected (and interactive) row. Starting from 1 (that at top of the screen)
	// returns: SRET constant (valid only for CBT_LOOPED callback)
	// notes: this callback accepts two kinds of flags: CBT_REPLACE and CBT_LOOPED
	//		the CBT_LOOPED is very alike than CBT_FIRST but it will be peformed in progress, contiuosly,
	//      while option screen is running

	typedef int (__cdecl *CALL_OPTIONS_MANAGER) (bool TestTitle, bool TestCommands, int SelectedRow);

	// prototype for CB_PAUSE_MANAGER callback
	// no input argument for this callback procedure
	// return PRET_ value
	typedef int (__cdecl *CALL_PAUSE_MANAGER) (void);

	// prototype for CB_SLOT_INIT , CB_SLOT_CONTROL or CB_SLOT_DRAW or CB_SLOT_DRAW_EXTRA
	// receive in input:
	// IndexItem : the index of object is calling its InitialiseObject or ControlObject procedure
	// pItem     : the structure of above moveable
	// CBT_Flags : the CBT_ flag of this callback (CBT_FIRST, CBT_AFTER or CBT_REPLACE)
	// return a SRET_ constant value
	typedef int (__cdecl *CALL_SLOT_MANY) (short IndexItem, StrItemTr4 *pItem, WORD CBT_Flags);

	// prototype for CB_SLOT_COLLISION
	// receive in input:
	// IndexItem : the index of object is calling its collision procedure
	// pItem     : the structure of above moveable
	// CBT_Flags : the CBT_ flag of this callback (CBT_FIRST , CBT_AFTER or CBT_REPLACE)
	// pCollision : pointer to StrCollisionLara structure (about lara collision and other infos)
	// return a SRET_ constant value
	typedef int (__cdecl *CALL_SLOT_CB_COLLISION) (short IndexItem, StrItemTr4 *pItem, WORD CBT_Flags, StrCollisionLara * pCollision);

	// for cbCycleEnd
	typedef int (__cdecl *CALL_CYCLE_END) (void);

	// for cbGlobalTrigger
	// it has to return a RGT_ value  (Return for Global Trigger)
	typedef int (__cdecl *CALL_GLOBAL_TRIGGER) (int GT_Value, StrGlobalTrigger *pGlobalTrigger);

	// for callback CB_SAVING_GAME
	// SavingType  SAVT_
	typedef DWORD (__cdecl *CALL_SAVING_GAME) (BYTE **pAdrZone, int SavingType);

	// for callback CB_LOADING_GAME
	typedef void (__cdecl *CALL_LOADING_GAME) (BYTE *pAdrZone, DWORD SizeData);

	typedef DWORD (__cdecl *TYPE_QuantoLungoFile) (FILE *pFile);
}
