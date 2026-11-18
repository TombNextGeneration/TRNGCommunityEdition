#pragma once
#include "../types.h"

namespace tomb4
{
	extern BOX_INFO* &boxes;

	void AlertNearbyGuards(ITEM_INFO* item);
	void CreatureDie(short item_number, long explode);
	long CreatureActive(short item_number);
	void GetAITarget(CREATURE_INFO* creature);
	void CreatureAIInfo(ITEM_INFO* item, AI_INFO* info);
	void GetCreatureMood(ITEM_INFO* item, AI_INFO* info, long violent);
	void CreatureMood(ITEM_INFO* item, AI_INFO* info, long violent);
	short CreatureTurn(ITEM_INFO* item, short maximum_turn);
	short CreatureEffectT(ITEM_INFO* item, BITE_INFO* bite, short damage, short angle, short (*generate)(long x, long y, long z, short damage, short angle, short room_number));
	long CreatureAnimation(short item_number, short angle, short tilt);
	void CreatureFloat(short item_number);
}

void Inject_Box(bool replace);
