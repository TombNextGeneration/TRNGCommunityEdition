#pragma once

namespace tomb4
{
	void SaveSettings();
	void REG_CloseKey();
	void CloseRegistry();
	bool LoadSettings();
}

void Inject_Registry(bool replace);
