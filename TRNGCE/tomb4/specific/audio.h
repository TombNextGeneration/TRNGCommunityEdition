#pragma once
#include "../../trng/structures.h"

namespace tomb4
{
	extern long &XATrack;
	extern long &audio_play_mode;
	extern trng::StrListaWav (&TrackFileNames)[256];
	extern HANDLE &NotificationThreadHandle;

	void S_CDStop();
	void ACMSetVolume();
	void S_CDPlay(long track, long mode);
}

void Inject_Audio(bool replace);
