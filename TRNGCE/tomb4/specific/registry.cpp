#include "registry.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../../inject.h"

namespace tomb4
{
	static HKEY &phkResult = *reinterpret_cast<decltype(&phkResult)>(0x670D0C);

	void SaveSettings()
	{
		__try { throw __func__; } __finally {}
	}

	void REG_CloseKey()
	{
		// salvare
		if (!phkResult)
			return;

		RegCloseKey(phkResult);

		// azzerarla perche' gia' chiusa
		phkResult = NULL;
	}

	void CloseRegistry()
	{
		REG_CloseKey();
	}

	bool LoadSettings()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Registry(bool replace)
{
	ProcessInject(0x483200, (unsigned int)tomb4::SaveSettings, false);
	ProcessInject(0x482940, (unsigned int)tomb4::REG_CloseKey, replace);
	ProcessInject(0x482AD0, (unsigned int)tomb4::CloseRegistry, replace);
	ProcessInject(0x482AE0, (unsigned int)tomb4::LoadSettings, false);
}
