#include "health.h"
#include "../../inject.h"
#include "lara.h"
#include "../specific/LoadSave.h"
#include "control.h"

namespace tomb4
{
	long &health_bar_timer = *reinterpret_cast<decltype(&health_bar_timer)>(0x4BF558);
	long &bad_hitpoints = *reinterpret_cast<decltype(&bad_hitpoints)>(0x452315);

	void DrawHealthBar(long flash_state)
	{
		static long old_hitpoints;

		long hitpoints;

		hitpoints = lara_item->hit_points;

		if (hitpoints < 0)
			hitpoints = 0;
		else if (hitpoints > 1000)
			hitpoints = 1000;

		if (old_hitpoints != hitpoints)
		{
			old_hitpoints = hitpoints;
			health_bar_timer = 40;
		}

		if (health_bar_timer < 0)
			health_bar_timer = 0;

		if (hitpoints <= bad_hitpoints)
		{
			if (flash_state)
				S_DrawHealthBar(hitpoints / 10, flash_state);
			else
				S_DrawHealthBar(0, flash_state);
		}
		else if (health_bar_timer > 0 || hitpoints <= 0 || lara.gun_status == LG_READY && lara.gun_type != 8 || lara.poisoned >= 256)
			S_DrawHealthBar(hitpoints / 10, flash_state);

		if (PoisonFlag)
			PoisonFlag--;
	}
}

void Inject_Health(bool replace)
{
	ProcessInject(0x4522D0, (unsigned int)tomb4::DrawHealthBar, replace);
}
