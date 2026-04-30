#include "scarab.h"
#include "../../inject.h"
#include "control.h"
#include "objects.h"
#include "effect2.h"
#include "../specific/3dmath.h"
#include "../specific/output.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	SCARAB_STRUCT (&Scarabs)[128] = *reinterpret_cast<decltype(&Scarabs)>(0x80EBE0);

	void UpdateScarabs()
	{
		__try { throw __func__; } __finally {}
	}

	void DrawScarabs()
	{
		SCARAB_STRUCT* fx;
		short** meshpp;

		meshpp = &meshes[objects[LITTLE_BEETLE].mesh_index + (wibble >> 2 & 2)];

		for (int i = 0; i < 128; i++)
		{
			fx = &Scarabs[i];

			if (fx->On)
			{
				if (fx->On != 2)
				{
					phd_PushMatrix();
					phd_TranslateAbs(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);
					phd_RotYXZ(fx->pos.y_rot, fx->pos.x_rot, fx->pos.z_rot);
					phd_PutPolygons_train(*meshpp, 0);
					phd_PopMatrix();
				}
				else
				{
					// era un pesce: saltarlo
					trng::DisegnaMioPesce((trng::StrFish*)fx);
				}
			}
		}
	}
}

void Inject_Scarab(bool replace)
{
	ProcessInject(0x40E2F0, (unsigned int)tomb4::UpdateScarabs, false);
	ProcessInject(0x40E550, (unsigned int)tomb4::DrawScarabs, replace);
}
