#include "audio.h"

namespace tomb4
{
	long &XATrack = *reinterpret_cast<decltype(&XATrack)>(0x4B01C4);
	long &audio_play_mode = *reinterpret_cast<decltype(&audio_play_mode)>(0x4BFB60);
}
