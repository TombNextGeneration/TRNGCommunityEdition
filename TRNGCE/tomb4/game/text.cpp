#include "text.h"
#include "../../inject.h"

namespace tomb4
{
	long &font_height = *reinterpret_cast<decltype(&font_height)>(0x7F4F30);
	long &GnFrameCounter = *reinterpret_cast<decltype(&GnFrameCounter)>(0x7E70CC);

	void UpdatePulseColour()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Text(bool replace)
{
	ProcessInject(0x462AE0, (unsigned int)tomb4::UpdatePulseColour, false);
}
