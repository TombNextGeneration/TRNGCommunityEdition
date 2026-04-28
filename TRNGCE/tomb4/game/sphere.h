#pragma once
#include "../types.h"

namespace tomb4
{
	extern char &GotLaraSpheres;

	void GetJointAbsPosition(ITEM_INFO* item, PHD_VECTOR* pos, long joint);
	long TestCollision(ITEM_INFO* item, ITEM_INFO* l);
}

void Inject_Sphere(bool replace);
