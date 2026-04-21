#include "3dmath.h"
#include "../../inject.h"

namespace tomb4
{
	long* &phd_mxptr = *reinterpret_cast<decltype(&phd_mxptr)>(0x7E70C8);
	long &phd_winwidth = *reinterpret_cast<decltype(&phd_winwidth)>(0x753C60);
	long &phd_winheight = *reinterpret_cast<decltype(&phd_winheight)>(0x753BB0);
	float &FogStart = *reinterpret_cast<decltype(&FogStart)>(0x4B2498);
	short &phd_winxmax = *reinterpret_cast<decltype(&phd_winxmax)>(0x753BEC);
	float &FogEnd = *reinterpret_cast<decltype(&FogEnd)>(0x4B249C);
	short (&rcossin_tbl)[8192] = *reinterpret_cast<decltype(&rcossin_tbl)>(0x4B34D0);
	short &phd_winymax = *reinterpret_cast<decltype(&phd_winymax)>(0x753C10);

	ulong phd_sqrt(ulong num)
	{
		__try { throw __func__; } __finally {}
	}

	void phd_GetVectorAngles(long x, long y, long z, short* angles)
	{
		__try { throw __func__; } __finally {}
	}

	short phd_sin(long angle)
	{
		angle >>= 3;
		return 4 * rcossin_tbl[angle & 0x1FFE];
	}

	short phd_cos(long angle)
	{
		angle >>= 3;
		return 4 * rcossin_tbl[(angle & 0x1FFE) + 1];
	}

	void phd_PopMatrix()
	{
		phd_mxptr -= indices_count;
	}

	void AlterFOV(short fov)
	{
		__try { throw __func__; } __finally {}
	}

	ulong mGetAngle(long x, long z, long x1, long z1)
	{
		__try { throw __func__; } __finally {}
	}

	long phd_atan(long x, long y)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_3dmath(bool replace)
{
	ProcessInject(0x48DF00, (unsigned int)tomb4::phd_sqrt, false);
	ProcessInject(0x48E710, (unsigned int)tomb4::phd_GetVectorAngles, false);
	ProcessInject(0x48D660, (unsigned int)tomb4::AlterFOV, false);
	ProcessInject(0x48D9C0, (unsigned int)tomb4::mGetAngle, false);
	ProcessInject(0x48DE90, (unsigned int)tomb4::phd_atan, false);
}
