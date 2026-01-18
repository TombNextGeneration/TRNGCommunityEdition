#include "sphere.h"
#include "../../inject.h"

namespace tomb4
{
	char &GotLaraSpheres = *reinterpret_cast<decltype(&GotLaraSpheres)>(0x7F6DBE);

	void GetJointAbsPosition(ITEM_INFO* item, PHD_VECTOR* pos, long joint)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Sphere(bool replace)
{
	ProcessInject(0x45F160, (unsigned int)tomb4::GetJointAbsPosition, false);
}
