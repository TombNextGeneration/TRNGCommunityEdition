#pragma once

namespace tomb4
{
	extern short &FadeScreenHeight;
	extern short &FlashFadeR;
	extern short &FlashFadeG;
	extern short &FlashFadeB;
	extern short &FlashFader;
	extern short &ScreenFading;
	extern short &ScreenFadedOut;

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
}

void Inject_Tomb4fx(bool replace);
