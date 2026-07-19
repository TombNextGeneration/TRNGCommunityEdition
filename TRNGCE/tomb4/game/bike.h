#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &bike_booster_object;
	extern uchar &bike_explode_in_water;
	extern long &bike_maximum_depth;

	void BikeTriggerExhaustSmoke(long x, long y, long z, short angle, long velocity, long thing);
	void BikeCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll);
	void TriggerBikeBeam(ITEM_INFO* item);
	long GetOnBike(short item_number, COLL_INFO* coll);
	void BikeControl(short item_number);
	long BikeDynamics(ITEM_INFO* item);
	void BikeExplode(ITEM_INFO* item);
	long TestHeight(ITEM_INFO* item, long z, long x, PHD_VECTOR* pos);
	void AnimateBike(ITEM_INFO* item, long hitWall, long killed);
	void BikeStart(ITEM_INFO* item, ITEM_INFO* l);
	void DrawBikeExtras(ITEM_INFO* item);
	void DrawBikeBeam(ITEM_INFO* item);
}

void Inject_Bike(bool replace);
