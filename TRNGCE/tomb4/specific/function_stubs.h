#pragma once

namespace tomb4
{
	long GetRandomControl();
	void SeedRandomControl(long seed);
	long GetRandomDraw();
	void SeedRandomDraw(long seed);
}

void Inject_FunctionStubs(bool replace);
