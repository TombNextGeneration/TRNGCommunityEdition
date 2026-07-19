#include "collide.h"
#include "../../inject.h"
#include "control.h"
#include "sphere.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	void ObjectCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
	{
		ITEM_INFO* item;

		// controllare se questo e' uno degli item di cui ignorare la collisione
		for (int i = trng::GlobTomb4.TotItemNoCollisions - 1; i >= 0; i--)
		{
			if (trng::GlobTomb4.VetItemNoCollisions[i] == item_number)
			{
				// e' da ignroare le collisioni
				return;
			}
		}

		item = &items[item_number];

		if (TestBoundsCollide(item, l, coll->radius))
		{
			// il bound collide e' giusto
			// ora se questo oggetto e' un pannello di collisione
			// saltare il testcollision
			if ((item->object_number >= trng::PANEL_START && item->object_number <= trng::PANEL_END) || (TestCollision(item, l) && coll->enable_baddie_push))
			{
				// in esi e edi ci sono i due item che collidono
				// chiamare funzione per analisi specifica
				ItemPushLara(item, l, coll, 0, 1);
			}
		}
	}

	void CreatureCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long MoveLaraPosition(PHD_VECTOR* v, ITEM_INFO* item, ITEM_INFO* l)
	{
		__try { throw __func__; } __finally {}
	}

	void ShiftItem(ITEM_INFO* item, COLL_INFO* coll)
	{
		__try { throw __func__; } __finally {}
	}

	long TestBoundsCollide(ITEM_INFO* item, ITEM_INFO* l, long rad)
	{
		__try { throw __func__; } __finally {}
	}

	long ItemPushLara(ITEM_INFO* item, ITEM_INFO* l, COLL_INFO* coll, long spaz, long BigPush)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Collide(bool replace)
{
	ProcessInject(0x446D60, (unsigned int)tomb4::ObjectCollision, replace);
	ProcessInject(0x446BE0, (unsigned int)tomb4::CreatureCollision, false);
	ProcessInject(0x447B50, (unsigned int)tomb4::MoveLaraPosition, false);
	ProcessInject(0x446700, (unsigned int)tomb4::ShiftItem, false);
	ProcessInject(0x447270, (unsigned int)tomb4::TestBoundsCollide, false);
	ProcessInject(0x446EC0, (unsigned int)tomb4::ItemPushLara, false);
}
