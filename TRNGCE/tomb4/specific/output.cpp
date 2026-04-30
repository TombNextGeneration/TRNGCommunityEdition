#include "output.h"
#include "../../inject.h"

namespace tomb4
{
	void do_boot_screen(long language)
	{
		__try { throw __func__; } __finally {}
	}

	void S_InitialisePolyList()
	{
		__try { throw __func__; } __finally {}
	}

	void S_OutputPolyList()
	{
		__try { throw __func__; } __finally {}
	}

	long S_DumpScreen()
	{
		__try { throw __func__; } __finally {}
	}

	void phd_PutPolygons_train(short* objptr, long x)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Output(bool replace)
{
	ProcessInject(0x47E910, (unsigned int)tomb4::do_boot_screen, false);
	ProcessInject(0x47B6E0, (unsigned int)tomb4::S_InitialisePolyList, false);
	ProcessInject(0x47D990, (unsigned int)tomb4::S_OutputPolyList, false);
	ProcessInject(0x47DCB0, (unsigned int)tomb4::S_DumpScreen, false);
	ProcessInject(0x47E340, (unsigned int)tomb4::phd_PutPolygons_train, false);
}
