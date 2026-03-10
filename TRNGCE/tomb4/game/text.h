#pragma once

namespace tomb4
{
	extern long &font_height;
	extern long &GnFrameCounter;
	extern float &small_font_scale;

	void UpdatePulseColour();
}

void Inject_Text(bool replace);
