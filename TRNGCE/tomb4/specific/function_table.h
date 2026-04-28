#pragma once
#include "../types.h"

namespace tomb4
{
	HRESULT HWBeginScene();
	void SetFogColor(long r, long g, long b);
}

void Inject_FunctionTable(bool replace);
