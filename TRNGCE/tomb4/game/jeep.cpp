#include "jeep.h"
#include "../../inject.h"
#include "lara.h"
#include "../specific/specificfx.h"
#include "../specific/3dmath.h"
#include "control.h"
#include "draw.h"
#include "debris.h"
#include "sound.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	static short (&jroomies)[22] = *reinterpret_cast<decltype(&jroomies)>(0x7F4EC0);

	long &jeep_ignition_key_object = *reinterpret_cast<decltype(&jeep_ignition_key_object)>(0x466452);

	void JeepExplode(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void DrawJeepExtras(ITEM_INFO* item)
	{
		JEEPINFO* jeep;

		// in esp+4 c'e' stritemtr4 di veicolo a cui appartiene questo drawextra
		if (item->object_number != JEEP)
			return;

		jeep = (JEEPINFO*)item->data;
		DrawJeepSpeedo(phd_winwidth - 64, phd_winheight - 16, jeep->velocity, 0x6000, 0x8000, 32, jeep->gear);
	}

	void JeepCollideStaticObjects(long x, long y, long z, short room_number, long height)
	{
		static long jminx, jmaxx, jminy, jmaxy, jminz, jmaxz, cminx, cmaxx, cminy, cmaxy, cminz, cmaxz;

		MESH_INFO* mesh;
		STATIC_INFO* sinfo;
		ROOM_INFO* r;
		PHD_VECTOR pos;
		short* doors;
		long j;
		short room_count, rn;

		pos.x = x;
		pos.y = y;
		pos.z = z;
		jminx = x - 256;
		jmaxx = x + 256;
		jminy = y - height;
		jmaxy = y;
		jminz = z - 256;
		jmaxz = z + 256;
		room_count = 1;
		jroomies[0] = room_number;
		doors = room[room_number].door;

		if (doors)
		{
			for (int i = *doors++; i > 0; i--, doors += 16)
			{
				for (j = 0; j < room_count; j++)
				{
					if (jroomies[j] == *doors)
						break;
				}

				if (j == room_count)
				{
					jroomies[room_count] = *doors;
					room_count++;
				}
			}
		}

		for (int i = 0; i < room_count; i++)
		{
			rn = jroomies[i];
			r = &room[rn];
			mesh = r->mesh;

			for (j = r->num_meshes; j > 0; j--, mesh++)
			{
				if (mesh->Flags & 1)
				{
					if (mesh->static_number >= trng::GlobTomb4.pBaseCustomize->ShatterInizio && mesh->static_number <= trng::GlobTomb4.pBaseCustomize->ShatterFine)
					{
						if (mesh->Flags & trng::OCBS_SHATTER_SPECIFIC)
						{
							// e' di tipo specific
							trng::ResultCheckSpecific = trng::CheckSpecificXVeicolo();

							if (!trng::ResultCheckSpecific)
								continue;
						}

						sinfo = &static_objects[mesh->static_number];
						cminy = mesh->y + sinfo->y_minc;
						cmaxy = mesh->y + sinfo->y_maxc;

						if (mesh->y_rot == -0x8000)
						{
							cminx = mesh->x - sinfo->x_maxc;
							cmaxx = mesh->x - sinfo->x_minc;
							cminz = mesh->z - sinfo->z_maxc;
							cmaxz = mesh->z - sinfo->z_minc;
						}
						else if (mesh->y_rot == -0x4000)
						{
							cminx = mesh->x - sinfo->z_maxc;
							cmaxx = mesh->x - sinfo->z_minc;
							cminz = mesh->z + sinfo->x_minc;
							cmaxz = mesh->z + sinfo->x_maxc;
						}
						else if (mesh->y_rot == 0x4000)
						{
							cminx = mesh->x + sinfo->z_minc;
							cmaxx = mesh->x + sinfo->z_maxc;
							cminz = mesh->z - sinfo->x_maxc;
							cmaxz = mesh->z - sinfo->x_minc;
						}
						else
						{
							cminx = mesh->x + sinfo->x_minc;
							cmaxx = mesh->x + sinfo->x_maxc;
							cminz = mesh->z + sinfo->z_minc;
							cmaxz = mesh->z + sinfo->z_maxc;
						}

						if (jmaxx > cminx &&
							jminx < cmaxx &&
							jmaxy > cminy &&
							jminy < cmaxy &&
							jmaxz > cminz &&
							jminz < cmaxz)
						{
							ShatterObject(0, mesh, -128, rn, 0);
							SoundEffect(SFX_HIT_ROCK, (PHD_3DPOS*)&pos, SFX_DEFAULT);
							SmashedMeshRoom[SmashedMeshCount] = rn;
							SmashedMesh[SmashedMeshCount] = mesh;
							SmashedMeshCount++;
							mesh->Flags &= ~1;
						}
					}
				}
			}
		}
	}
}

void Inject_Jeep(bool replace)
{
	ProcessInject(0x466D40, (unsigned int)tomb4::JeepExplode, false);
	ProcessInject(0x4665C0, (unsigned int)tomb4::DrawJeepExtras, replace);
	ProcessInject(0x467850, (unsigned int)tomb4::JeepCollideStaticObjects, replace);
}
