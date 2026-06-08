#include "polyinsert.h"
#include "../../inject.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "output.h"

namespace tomb4
{
	void SortPolyList(long count, SORTLIST** list)
	{
		if (trng::GlobTomb4.BaseTurbo.Flags & trng::TRB_OPTIMIZE_SORTING || !count)
			return;

		for (int i = 0; i < count; i++)
			list[i]->zVal -= (float)i * 0.1F;

		DoSort(0, count - 1, list);
	}

	void DoSort(long left, long right, SORTLIST** list)
	{
		SORTLIST* swap;
		float z;
		long l, r;

		l = left;
		r = right;
		z = list[(left + right) / 2]->zVal;

		do
		{
			while (l < right && list[l]->zVal > z)
				l++;

			while (r > left && list[r]->zVal < z)
				r--;

			if (l <= r)
			{
				swap = list[l];
				list[l] = list[r];
				list[r] = swap;
				l++;
				r--;
			}

		} while (l <= r);

		if (r > left)
			DoSort(left, r, list);

		if (l < right)
			DoSort(l, right, list);
	}

	void CalcColorSplit(D3DCOLOR s, D3DCOLOR* d)
	{
		long r, g, b, sr, sg, sb;

		sr = 0;
		sg = 0;
		sb = 0;
		r = (s >> 16) & 0xFF;
		g = (s >> 8) & 0xFF;
		b = s & 0xFF;

		if (r - 128 <= 0)
			r <<= 1;
		else
		{
			sr = r - 128;
			r = 255;
		}

		if (g - 128 <= 0)
			g <<= 1;
		else
		{
			sg = g - 128;
			g = 255;
		}

		if (b - 128 <= 0)
			b <<= 1;
		else
		{
			sb = b - 128;
			b = 255;
		}

		if (r > 255)
			r = 255;

		if (g > 255)
			g = 255;

		if (b > 255)
			b = 255;

		d[0] = (d[0] & 0xFF000000) | (((r << 8) | g) << 8) | b;		//color
		d[0] &= 0xFFFFFF;
		d[0] |= GlobalAlpha;

		sr >>= 1;
		sg >>= 1;
		sb >>= 1;
		d[1] = (d[1] & 0xFF000000) | (((sr << 8) | sg) << 8) | sb;	//specular
	}
}

void Inject_Polyinsert(bool replace)
{
	ProcessInject(0x47F6B0, (unsigned int)tomb4::SortPolyList, replace);
	ProcessInject(0x47F600, (unsigned int)tomb4::DoSort, replace);
	ProcessInject(0x482830, (unsigned int)tomb4::CalcColorSplit, replace);
}
