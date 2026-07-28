#include "tomb4fx.h"
#include "../../inject.h"
#include "../specific/function_stubs.h"
#include "sound.h"
#include "delstuff.h"
#include "gameflow.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "../specific/3dmath.h"
#include "../specific/output.h"
#include "control.h"
#include "objects.h"

namespace tomb4
{
	short &FadeScreenHeight = *reinterpret_cast<decltype(&FadeScreenHeight)>(0x4BF258);
	short &FlashFadeR = *reinterpret_cast<decltype(&FlashFadeR)>(0x4BF25E);
	short &FlashFadeG = *reinterpret_cast<decltype(&FlashFadeG)>(0x4BF260);
	short &FlashFadeB = *reinterpret_cast<decltype(&FlashFadeB)>(0x4BF262);
	short &FlashFader = *reinterpret_cast<decltype(&FlashFader)>(0x4BF264);
	short &ScreenFading = *reinterpret_cast<decltype(&ScreenFading)>(0x4BF254);
	short &ScreenFadedOut = *reinterpret_cast<decltype(&ScreenFadedOut)>(0x4BF252);
	LIGHTNING_STRUCT (&Lightning)[16] = *reinterpret_cast<decltype(&Lightning)>(0x7FFA00);

	void TriggerBlood(long x, long y, long z, long angle, long num)
	{
		__try { throw __func__; } __finally {}
	}

	void ClearFires()
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerLaraDrips()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateFireSparks()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateSmokeSparks()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateBubbles()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateBlood()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateDrips()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateGunShells()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateShockwaves()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateLightning()
	{
		__try { throw __func__; } __finally {}
	}

	void UpdateFadeClip()
	{
		__try { throw __func__; } __finally {}
	}

	void SetScreenFadeIn(short speed)
	{
		__try { throw __func__; } __finally {}
	}

	void SetScreenFadeOut(short speed, short back)
	{
		__try { throw __func__; } __finally {}
	}

	long ExplodingDeath2(short item_number, long mesh_bits, short Flags)
	{
		__try { throw __func__; } __finally {}
	}

	LIGHTNING_STRUCT* TriggerLightning(PHD_VECTOR* s, PHD_VECTOR* d, char variation, long rgb, uchar flags, uchar size, uchar segments)
	{
		LIGHTNING_STRUCT* lptr;

		for (int i = 0; i < 16; i++)
		{
			lptr = &Lightning[i];

			if (!lptr->Life)
			{
				lptr->Point[0].x = s->x;
				lptr->Point[0].y = s->y;
				lptr->Point[0].z = s->z;
				lptr->Point[1].x = ((s->x * 3) + d->x) >> 2;
				lptr->Point[1].y = ((s->y * 3) + d->y) >> 2;
				lptr->Point[1].z = ((s->z * 3) + d->z) >> 2;
				lptr->Point[2].x = ((d->x * 3) + s->x) >> 2;
				lptr->Point[2].y = ((d->y * 3) + s->y) >> 2;
				lptr->Point[2].z = ((d->z * 3) + s->z) >> 2;
				lptr->Point[3].x = d->x;
				lptr->Point[3].y = d->y;
				lptr->Point[3].z = d->z;
				lptr->Xvel1 = (GetRandomControl() % variation) - (variation >> 1);
				lptr->Yvel1 = (GetRandomControl() % variation) - (variation >> 1);
				lptr->Zvel1 = (GetRandomControl() % variation) - (variation >> 1);
				lptr->Xvel2 = (GetRandomControl() % variation) - (variation >> 1);
				lptr->Yvel2 = (GetRandomControl() % variation) - (variation >> 1);
				lptr->Zvel2 = (GetRandomControl() % variation) - (variation >> 1);

				if (flags & 2)
				{
					lptr->Xvel3 = (GetRandomControl() % variation) - (variation >> 1);
					lptr->Yvel3 = (GetRandomControl() % variation) - (variation >> 1);
					lptr->Zvel3 = (GetRandomControl() % variation) - (variation >> 1);
				}
				else
				{
					lptr->Xvel3 = 0;
					lptr->Yvel3 = 0;
					lptr->Zvel3 = 0;
				}

				lptr->Flags = flags;
				*(long*)&lptr->r = rgb;
				lptr->Segments = segments;
				lptr->Rand = variation;
				lptr->Size = size;
				return lptr;
			}
		}

		return 0;
	}

	void LaraBubbles(ITEM_INFO* item)
	{
		PHD_VECTOR pos;

		if (!trng::BaseCustomize.TestDisableMissingSounds)
			SoundEffect(SFX_LARA_BUBBLES, &item->pos, SFX_WATER);

		pos.x = 0;
		pos.y = -4;
		pos.z = 64;
		GetLaraJointPos(&pos, 8);
		trng::GlobTomb4.BaseMirror.IndiceNow = -1;

		for (int i = (GetRandomControl() & 1) + 2; i > 0; i--)
		{
			CreateBubble((PHD_3DPOS*)&pos, item->room_number, 8, 7);

			if (gfLevelFlags & GF_MIRROR)
			{
				// qui fare duplicati di bubble per tutti i mirror
				while (1)
				{
					trng::CercaRecordMirror(item->room_number, trng::GlobTomb4.BaseMirror.IndiceNow + 1);

					if (!trng::GlobTomb4.BaseMirror.pRecNow)
						break;

					trng::CalcolaCordMirror((trng::StrPosizione*)&pos);
					CreateBubble((PHD_3DPOS*)&trng::GlobTomb4.BaseMirror.CordX, item->room_number, 8, 7);
				}
			}
		}
	}

	void CreateBubble(PHD_3DPOS* pos, short room_number, long size, long biggest)
	{
		__try { throw __func__; } __finally {}
	}

	void DrawWeaponMissile(ITEM_INFO* item)
	{
		phd_PushMatrix();
		phd_TranslateAbs(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		phd_RotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
		phd_PutPolygons_train(meshes[objects[item->object_number].mesh_index], 0);
		phd_PopMatrix();

		if (gfLevelFlags & GF_MIRROR)
		{
			trng::GlobTomb4.BaseMirror.IndiceNow = -1;

			while (1)
			{
				trng::CercaRecordMirror(item->room_number, trng::GlobTomb4.BaseMirror.IndiceNow + 1);

				if (!trng::GlobTomb4.BaseMirror.pRecNow)
					break;

				// c'e' un altro mirror
				trng::CalcolaCordMirror((trng::StrPosizione*)&item->pos);
				trng::CalcolaOrientMirror((trng::StrOrient*)&item->pos.x_rot, false, false);

				// codice per visualizzare mesh
				phd_PushMatrix();
				phd_TranslateAbs(trng::GlobTomb4.BaseMirror.CordX, trng::GlobTomb4.BaseMirror.CordY, trng::GlobTomb4.BaseMirror.CordZ);
				phd_RotYXZ(trng::GlobTomb4.BaseMirror.OrientH, trng::GlobTomb4.BaseMirror.OrientV, trng::GlobTomb4.BaseMirror.OrientR);
				phd_PutPolygons_train(meshes[objects[item->object_number].mesh_index], 0);
				phd_PopMatrix();
			}
		}
	}

	void SetFadeClip(short height, short speed)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Tomb4fx(bool replace)
{
	ProcessInject(0x4388E0, (unsigned int)tomb4::TriggerBlood, false);
	ProcessInject(0x437F20, (unsigned int)tomb4::ClearFires, false);
	ProcessInject(0x439A10, (unsigned int)tomb4::TriggerLaraDrips, false);
	ProcessInject(0x437960, (unsigned int)tomb4::UpdateFireSparks, false);
	ProcessInject(0x438130, (unsigned int)tomb4::UpdateSmokeSparks, false);
	ProcessInject(0x439310, (unsigned int)tomb4::UpdateBubbles, false);
	ProcessInject(0x438780, (unsigned int)tomb4::UpdateBlood, false);
	ProcessInject(0x439910, (unsigned int)tomb4::UpdateDrips, false);
	ProcessInject(0x438D10, (unsigned int)tomb4::UpdateGunShells, false);
	ProcessInject(0x43A6A0, (unsigned int)tomb4::UpdateShockwaves, false);
	ProcessInject(0x43A910, (unsigned int)tomb4::UpdateLightning, false);
	ProcessInject(0x4396F0, (unsigned int)tomb4::UpdateFadeClip, false);
	ProcessInject(0x439790, (unsigned int)tomb4::SetScreenFadeIn, false);
	ProcessInject(0x439740, (unsigned int)tomb4::SetScreenFadeOut, false);
	ProcessInject(0x43A030, (unsigned int)tomb4::ExplodingDeath2, false);
	ProcessInject(0x43A7E0, (unsigned int)tomb4::TriggerLightning, replace);
	ProcessInject(0x439250, (unsigned int)tomb4::LaraBubbles, replace);
	ProcessInject(0x4391A0, (unsigned int)tomb4::CreateBubble, false);
	ProcessInject(0x43AFC0, (unsigned int)tomb4::DrawWeaponMissile, replace);
	ProcessInject(0x4396D0, (unsigned int)tomb4::SetFadeClip, false);
}
