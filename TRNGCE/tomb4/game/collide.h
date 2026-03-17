#pragma once
#include "../types.h"

namespace tomb4
{
	void ObjectCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll);
	void CreatureCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll);
	long MoveLaraPosition(PHD_VECTOR* v, ITEM_INFO* item, ITEM_INFO* l);
}

void Inject_Collide(bool replace);
