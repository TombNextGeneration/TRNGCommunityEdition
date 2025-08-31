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

	typedef int (__cdecl * TYPE_convert_obj_to_invobj) (short SlotId);

	// prototype for CB_WINDOWS_FONT_CREATE callback
	// received in input:
	// pFont: pointer to StrWindowsFont structure with many data about feature of required font (gotten from script.dat)
	// TestFixWideScreen: if == true it requires to resize wide of font to compensate widescreen distorsion
	// return an handle of created font, or NULL if callback wants let to original code the creation of this font
	// note: This callback has been imagined for who wishes fix some problem with view of eastern charset fonts
	//       probably setting right font you coudl fix that problem with china fonts
	typedef HFONT (__cdecl *CALL_WINDOWS_FONT_CREATE) (StrWindowsFont *pFont, bool TestFixWideScreen);
}
