#include "laraflar.h"
#include "../../inject.h"

namespace tomb4
{
	void CreateFlare(short object, long thrown)
	{
		__try { throw __func__; } __finally {}
	}

	void undraw_flare_meshes()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Laraflar(bool replace)
{
	ProcessInject(0x42F400, (unsigned int)tomb4::CreateFlare, false);
	ProcessInject(0x42FAB0, (unsigned int)tomb4::undraw_flare_meshes, false);
}
