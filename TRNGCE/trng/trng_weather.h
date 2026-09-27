#pragma once
#include "structures.h"

namespace trng {
	extern StrWeather &RainSnowData;

	void InitRainSnow(void);
	void SetCustomizeWeatherDefault(void);
	void ClearRainSnowBuffers(void);
}

void LoadTombNextGenerationInject_TrngWeather(bool replace);
