#pragma once

namespace flep
{
	extern long &camera_bounce_status;
	extern short &camera_bounce_item_number;
	extern long &camera_bounce_strength;

	void do_spotcam_bounce(void);
	void set_bounce(void);
}

void Inject_Quakecam(bool replace);
