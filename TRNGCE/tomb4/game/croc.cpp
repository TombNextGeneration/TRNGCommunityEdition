#include "croc.h"
#include <math.h>
#include "../../inject.h"
#include "lara.h"
#include "sound.h"
#include "draw.h"
#include "tomb4fx.h"
#include "../specific/function_stubs.h"
#include "../specific/3dmath.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	LOCUST_STRUCT (&Locusts)[64] = *reinterpret_cast<decltype(&Locusts)>(0x80F8E0);
	char &LocustDamage = *reinterpret_cast<decltype(&LocustDamage)>(0x403BAF);
	long &next_locust = *reinterpret_cast<decltype(&next_locust)>(0x4BF1C0);
#define LocustDamage (-LocustDamage)

	void UpdateLocusts()
	{
		LOCUST_STRUCT* fx;
		short* lb;
		long bounds[6];
		long speed, ox, oy, oz, closestdist, closestnum;
		short angles[2];
		short max_turn;

		// patch per fare freeze di locuste
		if (trng::GlobTomb4.TestFreezeAll)
			return;

		lb = GetBoundsAccurate(lara_item);
		bounds[0] = lb[0] - (lb[0] >> 2) + lara_item->pos.x_pos;
		bounds[1] = lb[1] - (lb[1] >> 2) + lara_item->pos.x_pos;
		bounds[2] = lb[2] - (lb[2] >> 2) + lara_item->pos.y_pos;
		bounds[3] = lb[3] - (lb[3] >> 2) + lara_item->pos.y_pos;
		bounds[4] = lb[4] - (lb[4] >> 2) + lara_item->pos.z_pos;
		bounds[5] = lb[5] - (lb[5] >> 2) + lara_item->pos.z_pos;
		closestdist = 0xFFFFFFF;
		closestnum = -1;

		for (int i = 0; i < 64; i++)
		{
			fx = &Locusts[i];

			if (fx->On)
			{
				if ((lara.burn || lara_item->hit_points <= 0) && fx->Counter > 90 && !(GetRandomControl() & 7))
					fx->Counter = 90;

				fx->Counter--;

				if (!fx->Counter)
				{
					fx->On = 0;
					continue;
				}

				if (!(GetRandomControl() & 7))
				{
					fx->LaraTarget = (GetRandomControl() % 640) + 128;
					fx->XTarget = (GetRandomControl() & 0x7F) - 64;
					fx->ZTarget = (GetRandomControl() & 0x7F) - 64;
				}

				phd_GetVectorAngles(lara_item->pos.x_pos + (fx->XTarget << 3) - fx->pos.x_pos, lara_item->pos.y_pos - fx->LaraTarget - fx->pos.y_pos, lara_item->pos.z_pos + (fx->ZTarget << 3) - fx->pos.z_pos, angles);

				ox = (lara_item->pos.x_pos - fx->pos.x_pos) * (lara_item->pos.x_pos - fx->pos.x_pos);
				oz = (lara_item->pos.z_pos - fx->pos.z_pos) * (lara_item->pos.z_pos - fx->pos.z_pos);

				if (ox + oz < closestdist)
				{
					closestdist = ox + oz;
					closestnum = i;
				}

				ox = phd_sqrt(ox + oz) >> 3;

				if (ox > 128)
					ox = 128;
				else if (ox < 48)
					ox = 48;

				if (fx->speed < ox)
					fx->speed++;
				else if (fx->speed > ox)
					fx->speed--;

				if (fx->Counter > 90)
				{
					max_turn = fx->speed << 7;
					oy = (ushort)angles[0] - (ushort)fx->pos.y_rot;

					if (abs(oy) > 32768)
						oy = (ushort)fx->pos.y_rot - (ushort)angles[0];

					ox = (ushort)angles[1] - (ushort)fx->pos.x_rot;

					if (abs(ox) > 32768)
						ox = (ushort)fx->pos.x_rot - (ushort)angles[0];

					ox >>= 3;
					oy >>= 3;

					if (oy > max_turn)
						oy = max_turn;
					else if (oy < -max_turn)
						oy = -max_turn;

					if (ox > max_turn)
						ox = max_turn;
					else if (ox < -max_turn)
						ox = -max_turn;

					fx->pos.y_rot += (short)oy;
					fx->pos.x_rot += (short)ox;
				}

				ox = fx->pos.x_pos;
				oy = fx->pos.y_pos;
				oz = fx->pos.z_pos;
				speed = fx->speed * phd_cos(fx->pos.x_rot) >> W2V_SHIFT;
				fx->pos.x_pos += speed * phd_sin(fx->pos.y_rot) >> W2V_SHIFT;
				fx->pos.y_pos += fx->speed * phd_sin(-fx->pos.x_rot) >> W2V_SHIFT;
				fx->pos.z_pos += speed * phd_cos(fx->pos.y_rot) >> W2V_SHIFT;

				if (!(i & 1))
				{
					if (fx->pos.x_pos > bounds[0] && fx->pos.x_pos < bounds[1] && fx->pos.y_pos > bounds[2] &&
						fx->pos.y_pos < bounds[3] && fx->pos.z_pos > bounds[4] && fx->pos.z_pos < bounds[5])
					{
						TriggerBlood(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, GetRandomControl() << 1, 2);

						if (lara_item->hit_points > 0)
							lara_item->hit_points -= LocustDamage;
					}
				}
			}
		}

		if (closestnum != -1)
		{
			fx = &Locusts[closestnum];
			SoundEffect(SFX_LOCUSTS_LOOP, &fx->pos, SFX_DEFAULT);
		}
	}
}

void Inject_Croc(bool replace)
{
	ProcessInject(0x403850, (unsigned int)tomb4::UpdateLocusts, replace);
}
