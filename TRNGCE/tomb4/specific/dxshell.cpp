#include "dxshell.h"
#include "../../inject.h"

namespace tomb4
{
	DXPTR* &G_dxptr = *reinterpret_cast<decltype(&G_dxptr)>(0x754468);
	char (&keymap)[256] = *reinterpret_cast<decltype(&keymap)>(0x754260);
	DXINFO* &G_dxinfo = *reinterpret_cast<decltype(&G_dxinfo)>(0x754088);

	long DXAttempt(HRESULT r)
	{
		__try { throw __func__; } __finally {}
	}

	void DXReadKeyboard(char* KeyMap)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Dxshell(bool replace)
{
	ProcessInject(0x48F8A0, (unsigned int)tomb4::DXAttempt, false);
	ProcessInject(0x492090, (unsigned int)tomb4::DXReadKeyboard, false);
}
