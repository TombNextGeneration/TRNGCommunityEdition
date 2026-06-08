#pragma once
#include "../types.h"

namespace tomb4
{
	void SortPolyList(long count, SORTLIST** list);
	void DoSort(long left, long right, SORTLIST** list);
	void CalcColorSplit(D3DCOLOR s, D3DCOLOR* d);
}

void Inject_Polyinsert(bool replace);
