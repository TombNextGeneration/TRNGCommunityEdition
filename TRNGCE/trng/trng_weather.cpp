#include "trng_weather.h"
#include <cstring>
#include "../inject.h"
#include "Tomb_NextGeneration.h"

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

	void SetCustomizeWeatherDefault(void)
	{
		StrDatiXRain *pRain;

		pRain = &GlobTomb4.DatiRain;

		// ora copiare i valori
		RainSnowData.Rain_Float_1 = pRain->Rain_Float_1;
		RainSnowData.Rain_Float_2 = pRain->Rain_Float_2;
		RainSnowData.Rain_Float_4 = pRain->Rain_Float_4;
		RainSnowData.Rain_Float_8 = pRain->Rain_Float_8;
		RainSnowData.Rain_Float_16 = pRain->Rain_Float_16;
		RainSnowData.Max_Rain = pRain->Max_Rain;
		RainSnowData.Min_Rain = pRain->Min_Rain;
		RainSnowData.Splash_Rain = pRain->SplashRain;
		GlobTomb4.DatiRain.LastRoomCamera = -1;
		GlobTomb4.DatiSnow.LastRoomCamera = -1;
	}

	void ClearRainSnowBuffers(void)
	{
		int i;

		for (i = 0; i < SIZE_RAIN_BUFFER; i++) {
			RainSnowData.RainBuffer[i] = 0;
			RainSnowData.SnowBuffer[i] = 0;
		}
	}
}

void LoadTombNextGenerationInject_TrngWeather(bool replace)
{
	ProcessInject(0x100ADBF9, (unsigned int)trng::InitRainSnow, replace);
	ProcessInject(0x100ADB75, (unsigned int)trng::SetCustomizeWeatherDefault, replace);
	ProcessInject(0x100ADB50, (unsigned int)trng::ClearRainSnowBuffers, replace);
}
