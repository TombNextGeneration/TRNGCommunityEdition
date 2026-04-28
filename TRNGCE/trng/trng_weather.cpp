#include "trng_weather.h"
#include <cstring>
#include "../inject.h"

namespace trng {
	StrWeather &RainSnowData = *reinterpret_cast<decltype(&RainSnowData)>(0x10609558);

	// initialise default data for rain & snow
	void InitRainSnow(void)
	{
		static float VettoreSizeSnow[32] = {-24, -24, -24, +24, +24, -24, +24, +24, -12, -12, -12, +12, +12, -12, +12, +12,
						-8, -8, -8, +8, +8, -8, +8, +8, -6, -6, -6, +6, +6, -6, +6, +6};

		int i;

		memset(&RainSnowData, 0, sizeof(StrWeather));

		RainSnowData.ContaFrameSnow = 0;
		RainSnowData.Rain_Float_1 = 1;
		RainSnowData.Rain_Float_16 = 16;
		RainSnowData.Rain_Float_2 = 2;
		RainSnowData.Rain_Float_20480 = 0x5000;
		RainSnowData.Rain_Float_4 = 4;
		RainSnowData.Rain_Float_8 = 8;
		RainSnowData.Splash_Rain = 1;

		for (i = 0; i < 32; i++) {
			RainSnowData.VettoreSizeSnow[i] = VettoreSizeSnow[i];
		}
	}
}

void LoadTombNextGenerationInject_TrngWeather(bool replace)
{
	ProcessInject(0x100ADBF9, (unsigned int)trng::InitRainSnow, replace);
}
