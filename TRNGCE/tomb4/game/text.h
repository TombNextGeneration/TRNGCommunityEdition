#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &font_height;
	extern long &GnFrameCounter;
	extern float &small_font_scale;

	void UpdatePulseColour();
	void PrintString(ushort x, ushort y, uchar col, const char* string, ushort flags);
}

void Inject_Text(bool replace);
