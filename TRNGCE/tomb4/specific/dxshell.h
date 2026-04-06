#pragma once
#include "../types.h"

namespace tomb4
{
	extern DXPTR* &G_dxptr;
	extern char (&keymap)[256];
	extern DXINFO* &G_dxinfo;

	long DXAttempt(HRESULT r);
	void DXReadKeyboard(char* KeyMap);
	const char* DXGetErrorString(HRESULT hr);
	void DXFreeInfo(DXINFO* dxinfo);
	void DXClose();
}

void Inject_Dxshell(bool replace);
