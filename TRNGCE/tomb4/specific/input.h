#pragma once

namespace tomb4
{
	extern long &linput;
	extern long &input;
	extern long &dbinput;

	long S_UpdateInput();
}

void Inject_Input(bool replace);
