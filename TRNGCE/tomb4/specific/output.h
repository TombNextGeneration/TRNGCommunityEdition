#pragma once

namespace tomb4
{
	void do_boot_screen(long language);
	void S_InitialisePolyList();
	void S_OutputPolyList();
	long S_DumpScreen();
}

void Inject_Output(bool replace);
