#pragma once

namespace tomb4
{
	extern long &KillEverythingFlag;
	extern long &SmokeCountL;
	extern long &SmokeCountR;
	extern long &SplashCount;
	extern long &wibble;

	void ClearDynamics();
	void KillEverything();
	void UpdateSparks();
	void UpdateSplashes();
	void TriggerExplosionSparks(long x, long y, long z, long extras, long dynamic, long uw, short room_number);
}

void Inject_Effect2(bool replace);
