#pragma once
#include "../types.h"

namespace tomb4
{
	extern short &WhiteLightFrameOn;
	extern short &AmberLightSwitchSpeed;
	extern short &BlinkingLightDelay;
	extern uchar &BlinkingLightBlue;
	extern uchar &BlinkingLightGreen;
	extern uchar &BlinkingLightRed;
	extern uchar &BlinkingLightFalloff;

	void ControlElectricalLight(short item_number);
}

void Inject_Objlight(bool replace);
