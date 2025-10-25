#include "deltapak.h"

namespace tomb4
{
	long &cutseq_trig = *reinterpret_cast<decltype(&cutseq_trig)>(0x4BFB50);
	long &cutseq_num = *reinterpret_cast<decltype(&cutseq_num)>(0x4BFB4C);
	long &GLOBAL_playing_cutseq = *reinterpret_cast<decltype(&GLOBAL_playing_cutseq)>(0x4BFB54);
}
