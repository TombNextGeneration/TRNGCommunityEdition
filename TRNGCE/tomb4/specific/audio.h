#pragma once
#include "../../trng/structures.h"

namespace tomb4
{
	extern long &XATrack;
	extern long &audio_play_mode;
	inline struct { trng::StrListaWav (*&_)[256] = *reinterpret_cast<decltype(&_)>(0x46C8AD); decltype(*_) operator()() { return *_; } } TrackFileNames;
#define TrackFileNames TrackFileNames()
	extern HANDLE &NotificationThreadHandle;

	void S_CDStop();
	void ACMSetVolume();
	void S_CDPlay(long track, long mode);
}

void Inject_Audio(bool replace);
