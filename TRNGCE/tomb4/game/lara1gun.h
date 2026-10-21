#pragma once
#include "../types.h"

namespace tomb4
{
	extern long &CrossbowOffsetX;
	extern long &CrossbowOffsetY;
	extern long &CrossbowOffsetZ;
	extern uchar &GrenadeWeight;
	extern long &GrenadeRotation;
	extern uchar &GrenadeOneTouch;

	void TriggerUnderwaterExplosion(ITEM_INFO* item, long vehicle);
	void undraw_shotgun(long weapon_type);
	void undraw_shotgun_meshes(long weapon_type);
	void ControlGrenade(short item_number);
	void DoGrenadeDamageOnBaddie(ITEM_INFO* baddie, ITEM_INFO* item);
}

void Inject_Lara1Gun(bool replace);
