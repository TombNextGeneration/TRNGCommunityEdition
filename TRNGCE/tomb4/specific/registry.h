#pragma once

namespace tomb4
{
	void SaveSettings();
	void REG_CloseKey();
	void CloseRegistry();
}

void Inject_Registry(bool replace);
