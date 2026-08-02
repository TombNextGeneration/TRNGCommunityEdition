#include "quakecam.h"
#include <cmath>
#include "../../inject.h"
#include "../../tomb4/game/camera.h"
#include "../../tomb4/specific/function_stubs.h"
#include "../../tomb4/game/control.h"

namespace flep
{
	long &camera_bounce_status = *reinterpret_cast<decltype(&camera_bounce_status)>(0x902418);
	short &camera_bounce_item_number = *reinterpret_cast<decltype(&camera_bounce_item_number)>(0x902B10);
	long &camera_bounce_strength = *reinterpret_cast<decltype(&camera_bounce_strength)>(0x902140);

	void do_spotcam_bounce(void)
	{
		long rndval, shake;

		set_bounce();

		if (tomb4::camera.bounce)
		{
			if (tomb4::camera.bounce <= 0)
			{
				rndval = -tomb4::camera.bounce;
				shake = rndval >> 1;
				tomb4::camera.target.x += tomb4::GetRandomControl() % rndval - shake;
				tomb4::camera.target.y += tomb4::GetRandomControl() % rndval - shake;
				tomb4::camera.target.z += tomb4::GetRandomControl() % rndval - shake;
				tomb4::camera.bounce += 5;
			}
			else
			{
				tomb4::camera.pos.y += tomb4::camera.bounce;
				tomb4::camera.target.y += tomb4::camera.bounce;
				tomb4::camera.bounce = 0;
			}
		}
	}

	void set_bounce(void)
	{
		tomb4::ITEM_INFO* item;
		long dx, dy, dz, distance;

		if (camera_bounce_status)
		{
			if (camera_bounce_item_number != -1)
			{
				item = &tomb4::items[camera_bounce_item_number];
				dx = item->pos.x_pos - tomb4::camera.pos.x;
				dy = item->pos.y_pos - tomb4::camera.pos.y;
				dz = item->pos.z_pos - tomb4::camera.pos.z;

				if (abs(dx) < 16384 && abs(dy) < 16384 && abs(dz) < 16384)
				{
					distance = dx * dx + dy * dy + dz * dz;

					if (distance <= 268435456)
						tomb4::camera.bounce = camera_bounce_strength * (1048576 - distance / 256) / 1048576;
				}
			}
			else
				tomb4::camera.bounce = camera_bounce_strength;
		}
	}
}

// NOLINTBEGIN(clang-analyzer-core.FixedAddressDereference)
void Inject_Quakecam(bool replace)
{
	ProcessInject(*(unsigned int*)0x90C08C, (unsigned int)flep::do_spotcam_bounce, replace);
	ProcessInject(*(unsigned int*)0x90C088, (unsigned int)flep::set_bounce, replace);
}
// NOLINTEND(clang-analyzer-core.FixedAddressDereference)
