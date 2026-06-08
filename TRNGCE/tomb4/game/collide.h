#pragma once
#include "../types.h"

namespace tomb4
{
	void ObjectCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll);
	void CreatureCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll);
	long MoveLaraPosition(PHD_VECTOR* v, ITEM_INFO* item, ITEM_INFO* l);
	void ShiftItem(ITEM_INFO* item, COLL_INFO* coll);
	long TestBoundsCollide(ITEM_INFO* item, ITEM_INFO* l, long rad);
	long ItemPushLara(ITEM_INFO* item, ITEM_INFO* l, COLL_INFO* coll, long spaz, long BigPush);
}

void Inject_Collide(bool replace);
