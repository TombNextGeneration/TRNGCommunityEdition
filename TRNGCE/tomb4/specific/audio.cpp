#include "audio.h"
#include "../../inject.h"

namespace tomb4
{
	long &XATrack = *reinterpret_cast<decltype(&XATrack)>(0x4B01C4);
	long &audio_play_mode = *reinterpret_cast<decltype(&audio_play_mode)>(0x4BFB60);
//	trng::StrListaWav (*&TrackFileNames)[256] = *reinterpret_cast<decltype(&TrackFileNames)>(0x46C8AD);

	void S_CDStop()
	{
		__try { throw __func__; } __finally {}
	}

	void ACMSetVolume()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Audio(bool replace)
{
	ProcessInject(0x46BDC0, (unsigned int)tomb4::S_CDStop, false);
	ProcessInject(0x46BEB0, (unsigned int)tomb4::ACMSetVolume, false);
}
