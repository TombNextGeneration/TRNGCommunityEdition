#pragma once
#include "../types.h"

namespace tomb4
{
	extern float (&AnimatingTexturesV)[16][8][3];
	extern long &GlobalAlpha;

	void do_boot_screen(long language);
	void S_InitialisePolyList();
	void S_OutputPolyList();
	long S_DumpScreen();
	void phd_PutPolygons_train(short* objptr, long x);
	void _InsertRoom(ROOM_INFO* r);
}

void Inject_Output(bool replace);
