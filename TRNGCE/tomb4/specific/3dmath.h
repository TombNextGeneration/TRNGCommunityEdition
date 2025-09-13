#pragma once
#include "../types.h"

namespace tomb4
{
	extern long* &phd_mxptr;
	extern long &phd_winwidth;
	extern long &phd_winheight;
	extern float &FogStart;

	ulong phd_sqrt(ulong num);
	void phd_GetVectorAngles(long x, long y, long z, short* angles);
	short phd_sin(long angle);
	short phd_cos(long angle);
	void phd_PopMatrix();
}

void Inject_3dmath(bool replace);
