#pragma once

namespace tomb4
{
	extern short &FadeScreenHeight;
	extern short &FlashFadeR;
	extern short &FlashFadeG;
	extern short &FlashFadeB;
	extern short &FlashFader;

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
}

void Inject_Tomb4fx(bool replace);
