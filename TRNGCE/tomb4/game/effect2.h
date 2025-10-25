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
}

void Inject_Effect2(bool replace);
