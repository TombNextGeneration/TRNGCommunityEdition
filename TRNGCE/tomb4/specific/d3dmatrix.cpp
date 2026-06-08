#include "d3dmatrix.h"
#include "../../inject.h"

namespace tomb4
{
	void SetD3DViewMatrix()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_D3dmatrix(bool replace)
{
	ProcessInject(0x48E7B0, (unsigned int)tomb4::SetD3DViewMatrix, false);
}
