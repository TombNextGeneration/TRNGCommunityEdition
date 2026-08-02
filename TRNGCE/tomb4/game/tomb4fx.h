#pragma once
#include "../types.h"

namespace tomb4
{
	extern short &FadeScreenHeight;
	extern short &FlashFadeR;
	extern short &FlashFadeG;
	extern short &FlashFadeB;
	extern short &FlashFader;
	extern short &ScreenFading;
	extern short &ScreenFadedOut;
	extern LIGHTNING_STRUCT (&Lightning)[16];

	void TriggerBlood(long x, long y, long z, long angle, long num);
	void ClearFires();
	void TriggerLaraDrips();
	void UpdateFireSparks();
	void UpdateSmokeSparks();
	void UpdateBubbles();
	void UpdateBlood();
	void UpdateDrips();
	void UpdateGunShells();
	void UpdateShockwaves();
	void UpdateLightning();
	void UpdateFadeClip();
	void SetScreenFadeIn(short speed);
	void SetScreenFadeOut(short speed, short back);
	long ExplodingDeath2(short item_number, long mesh_bits, short Flags);
	LIGHTNING_STRUCT* TriggerLightning(PHD_VECTOR* s, PHD_VECTOR* d, char variation, long rgb, uchar flags, uchar size, uchar segments);
	void LaraBubbles(ITEM_INFO* item);
	void CreateBubble(PHD_3DPOS* pos, short room_number, long size, long biggest);
	void DrawWeaponMissile(ITEM_INFO* item);
	void SetFadeClip(short height, short speed);
}

void Inject_Tomb4fx(bool replace);
