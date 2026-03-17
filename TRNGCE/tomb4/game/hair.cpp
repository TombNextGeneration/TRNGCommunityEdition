#include "hair.h"
#include "../../inject.h"

namespace tomb4
{
	void HairControl(long in_cutscene, long pigtail, short* cutscenething)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseHair()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Hair(bool replace)
{
	ProcessInject(0x41FCA0, (unsigned int)tomb4::HairControl, false);
	ProcessInject(0x41FC20, (unsigned int)tomb4::InitialiseHair, false);
}
