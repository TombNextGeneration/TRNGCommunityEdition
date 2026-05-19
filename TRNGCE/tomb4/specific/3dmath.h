#pragma once
#include "../types.h"

namespace tomb4
{
	extern long* &phd_mxptr;
	extern long &phd_winwidth;
	extern long &phd_winheight;
	extern float &FogStart;
	extern short &phd_winxmax;
	extern float &FogEnd;
	extern short (&rcossin_tbl)[8192];
	extern short &phd_winymax;

	ulong phd_sqrt(ulong num);
	void phd_GetVectorAngles(long x, long y, long z, short* angles);
	short phd_sin(long angle);
	short phd_cos(long angle);
	void phd_PopMatrix();
	void AlterFOV(short fov);
	ulong mGetAngle(long x, long z, long x1, long z1);
	long phd_atan(long x, long y);
	void phd_PushMatrix();
	void phd_TranslateAbs(long x, long y, long z);
	void phd_RotYXZ(short y, short x, short z);
}

void Inject_3dmath(bool replace);
