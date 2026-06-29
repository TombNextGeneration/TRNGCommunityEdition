#pragma once
#include "../types.h"

namespace tomb4
{
	extern SORTLIST* (&SortList)[196608];
	extern long &SortCount;

	void SortPolyList(long count, SORTLIST** list);
	void DoSort(long left, long right, SORTLIST** list);
	void CalcColorSplit(D3DCOLOR s, D3DCOLOR* d);
	void InitialiseSortList();
	void DrawSortList();
}

void Inject_Polyinsert(bool replace);
