#pragma once
#include "../types.h"

namespace tomb4
{
	extern DXPTR* &G_dxptr;
	extern char (&keymap)[256];
	extern DXINFO* &G_dxinfo;
	extern HWND &G_hwnd;

	long DXAttempt(HRESULT r);
	void DXReadKeyboard(char* KeyMap);
	const char* DXGetErrorString(HRESULT hr);
	void DXFreeInfo(DXINFO* dxinfo);
	void DXClose();
	long DXGetInfo(DXINFO* dxinfo, HWND hwnd);
	BOOL __stdcall DXEnumDirectDraw(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);
	BOOL __stdcall DXEnumDirectSound(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
}

void Inject_Dxshell(bool replace);
