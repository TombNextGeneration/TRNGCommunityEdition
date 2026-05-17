#pragma once
#include "../types.h"

namespace tomb4
{
	void TriggerUnderwaterExplosion(ITEM_INFO* item, long vehicle);
	void undraw_shotgun(long weapon_type);
	void undraw_shotgun_meshes(long weapon_type);
}

void Inject_Lara1Gun(bool replace);
