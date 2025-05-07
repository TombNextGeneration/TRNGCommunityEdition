#include "../../inject.h"
#include "../game/types.h"
#include "math_tbls.h"

namespace tomb4
{
	long* &phd_mxptr = *reinterpret_cast<decltype(&phd_mxptr)>(0x7E70C8);

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
		phd_mxptr -= (long)matrix_indices::indices_count;
	}
}

void Inject_3dmath(bool replace)
{
	ProcessInject(0x48DF00, (unsigned int)tomb4::phd_sqrt, false);
	ProcessInject(0x48E710, (unsigned int)tomb4::phd_GetVectorAngles, false);
}
