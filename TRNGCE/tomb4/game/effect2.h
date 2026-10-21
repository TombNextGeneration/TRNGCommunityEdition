#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &KillEverythingFlag;
	extern long &SmokeCountL;
	extern long &SmokeCountR;
	extern long &SplashCount;
	extern long &wibble;
	extern SPLASH_SETUP &splash_setup;
	extern uchar &ricochet_spark_count_hit;
	extern uchar &ricochet_spark_count_no_hit;

	void ClearDynamics();
	void KillEverything();
	void UpdateSparks();
	void UpdateSplashes();
	void TriggerExplosionSparks(long x, long y, long z, long extras, long dynamic, long uw, short room_number);
	void TriggerDynamic(long x, long y, long z, long falloff, long r, long g, long b);
	void TriggerRocketSmoke(long x, long y, long z, long col);
	void SetupSplash(SPLASH_SETUP* setup);
	void TriggerFireFlame(long x, long y, long z, long body_part, long type);
	void TriggerRicochetSpark(GAME_VECTOR* pos, long ang, long num, long smoke_only);
}

void Inject_Effect2(bool replace);
