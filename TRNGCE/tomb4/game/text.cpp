#include "text.h"
#include "../../inject.h"
#include "../specific/polyinsert.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	static CVECTOR (&FontShades)[10][32] = *reinterpret_cast<decltype(&FontShades)>(0x4BF5D8);

	long &font_height = *reinterpret_cast<decltype(&font_height)>(0x7F4F30);
	long &GnFrameCounter = *reinterpret_cast<decltype(&GnFrameCounter)>(0x7E70CC);
	float &small_font_scale = *reinterpret_cast<decltype(&small_font_scale)>(0x4A7294);

	void UpdatePulseColour()
	{
		static uchar PulseCnt;

		D3DTLVERTEX v;
		uchar c, r, g, b, sr, sg, sb;

		PulseCnt = (PulseCnt + 1) & 0x1F;

		if (PulseCnt >= 16)
			c = -PulseCnt;
		else
			c = PulseCnt;

		c <<= 3;
		CalcColorSplit((((c << 8) | c) << 8) | c, &v.color);
		r = (v.color >> 16) & 0xFF;
		g = (v.color >> 8) & 0xFF;
		b = v.color & 0xFF;
		sr = (v.specular >> 16) & 0xFF;
		sg = (v.specular >> 8) & 0xFF;
		sb = v.specular & 0xFF;

		for (int i = 0; i < 16; i++)
		{
			FontShades[1][i << 1].r = r;
			FontShades[1][i << 1].g = g;
			FontShades[1][i << 1].b = b;
			FontShades[1][(i << 1) + 1].r = sr;
			FontShades[1][(i << 1) + 1].g = sg;
			FontShades[1][(i << 1) + 1].b = sb;
		}

		trng::AggiornaColorWhiteMod();
	}

	void PrintString(ushort x, ushort y, uchar col, const char* string, ushort flags)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Text(bool replace)
{
	ProcessInject(0x462AE0, (unsigned int)tomb4::UpdatePulseColour, replace);
	ProcessInject(0x462D00, (unsigned int)tomb4::PrintString, false);
}
