#pragma once

namespace tomb4
{
	extern long &health_bar_timer;
	extern long &bad_hitpoints;

	void DrawHealthBar(long flash_state);
}

void Inject_Health(bool replace);
