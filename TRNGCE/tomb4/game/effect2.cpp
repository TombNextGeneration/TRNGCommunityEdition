#include "effect2.h"
#include "../../inject.h"

namespace tomb4
{
	long &KillEverythingFlag = *reinterpret_cast<decltype(&KillEverythingFlag)>(0x4BF23C);
	long &SmokeCountL = *reinterpret_cast<decltype(&SmokeCountL)>(0x804D48);
	long &SmokeCountR = *reinterpret_cast<decltype(&SmokeCountR)>(0x804D4C);
	long &SplashCount = *reinterpret_cast<decltype(&SplashCount)>(0x4BF244);
	long &wibble = *reinterpret_cast<decltype(&wibble)>(0x4BF238);

	void ClearDynamics()
	{
		__try { throw __func__; } __finally {}
	}

	void KillEverything()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateSparks()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateSplashes()	//(and ripples)
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerExplosionSparks(long x, long y, long z, long extras, long dynamic, long uw, short room_number)
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerDynamic(long x, long y, long z, long falloff, long r, long g, long b)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Effect2(bool replace)
{
	ProcessInject(0x435D70, (unsigned int)tomb4::ClearDynamics, false);
	ProcessInject(0x435AA0, (unsigned int)tomb4::KillEverything, false);
	ProcessInject(0x4338E0, (unsigned int)tomb4::UpdateSparks, false);
	ProcessInject(0x435440, (unsigned int)tomb4::UpdateSplashes, false);
	ProcessInject(0x434480, (unsigned int)tomb4::TriggerExplosionSparks, false);
	ProcessInject(0x435BF0, (unsigned int)tomb4::TriggerDynamic, false);
}
