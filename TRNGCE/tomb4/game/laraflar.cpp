#include "laraflar.h"
#include "../../inject.h"
#include "../specific/3dmath.h"
#include "../specific/output.h"
#include "control.h"
#include "objects.h"
#include "gameflow.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	void CreateFlare(short object, long thrown)
	{
		__try { throw __func__; } __finally {}
	}

	void undraw_flare_meshes()
	{
		__try { throw __func__; } __finally {}
	}

	void DrawFlareInAir(ITEM_INFO* item)
	{
		phd_PushMatrix();
		phd_TranslateAbs(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

		phd_RotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
		phd_PutPolygons_train(meshes[objects[FLARE_ITEM].mesh_index], 0);
		phd_PopMatrix();

		if (gfLevelFlags & GF_MIRROR)
		{
			trng::GlobTomb4.BaseMirror.IndiceNow = -1;

			while (1)
			{
				// vedere se stanza di oggetto attuale e' tra quella di mirror
				trng::CercaRecordMirror(item->room_number, trng::GlobTomb4.BaseMirror.IndiceNow + 1);

				if (!trng::GlobTomb4.BaseMirror.pRecNow)
				{
					// non c'e'
					break;
				}

				phd_PushMatrix();
				trng::CalcolaCordMirror((trng::StrPosizione*)&item->pos);
				phd_TranslateAbs(trng::GlobTomb4.BaseMirror.CordX, trng::GlobTomb4.BaseMirror.CordY, trng::GlobTomb4.BaseMirror.CordZ);
				trng::CalcolaOrientMirror((trng::StrOrient*)&item->pos.x_rot, false, false);
				phd_RotYXZ(trng::GlobTomb4.BaseMirror.OrientH, trng::GlobTomb4.BaseMirror.OrientV, trng::GlobTomb4.BaseMirror.OrientR);
				phd_PutPolygons_train(meshes[objects[FLARE_ITEM].mesh_index], 0);
				phd_PopMatrix();
			}
		}
	}
}

void Inject_Laraflar(bool replace)
{
	ProcessInject(0x42F400, (unsigned int)tomb4::CreateFlare, false);
	ProcessInject(0x42FAB0, (unsigned int)tomb4::undraw_flare_meshes, false);
	ProcessInject(0x42F330, (unsigned int)tomb4::DrawFlareInAir, replace);
}
