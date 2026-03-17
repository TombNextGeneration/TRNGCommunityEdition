#include "collide.h"
#include "../../inject.h"

namespace tomb4
{
	void ObjectCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	void CreatureCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long MoveLaraPosition(PHD_VECTOR* v, ITEM_INFO* item, ITEM_INFO* l)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Collide(bool replace)
{
	ProcessInject(0x446D60, (unsigned int)tomb4::ObjectCollision, false);
	ProcessInject(0x446BE0, (unsigned int)tomb4::CreatureCollision, false);
	ProcessInject(0x447B50, (unsigned int)tomb4::MoveLaraPosition, false);
}
