#include "polyinsert.h"
#include "../../inject.h"
#include "../../trng/Tomb_NextGeneration.h"

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
}

void Inject_Polyinsert(bool replace)
{
	ProcessInject(0x47F6B0, (unsigned int)tomb4::SortPolyList, replace);
	ProcessInject(0x47F600, (unsigned int)tomb4::DoSort, replace);
}
