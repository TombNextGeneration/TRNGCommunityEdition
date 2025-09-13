#include "output.h"
#include "../../inject.h"

namespace tomb4
{
	void do_boot_screen(long language)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Output(bool replace)
{
	ProcessInject(0x47E910, (unsigned int)tomb4::do_boot_screen, false);
}
