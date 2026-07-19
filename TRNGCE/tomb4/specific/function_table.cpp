#include "function_table.h"
#include "../../inject.h"
#include "winmain.h"
#include "function_stubs.h"
#include "3dmath.h"

namespace tomb4
{
	HRESULT (*&_EndScene)() = *reinterpret_cast<decltype(&_EndScene)>(0x5339AC);
	HRESULT (*&_BeginScene)() = *reinterpret_cast<decltype(&_BeginScene)>(0x5339B8);

	HRESULT HWBeginScene()
	{
		HRESULT result;

		if (App.dx.InScene)
			Log(1, "Already In Scene");

		App.dx.InScene = 1;
		App.dx.DoneBlit = 0;
		while (App.dx.WaitAtBeginScene) {};
		result = App.dx.lpD3DDevice->BeginScene();

		// per esperimento provare qui a forzare nuovamente
		// minfog
		App.dx.lpD3DDevice->SetLightState(D3DLIGHTSTATE_FOGSTART, *(DWORD*)(&FogStart));

		return result;
	}

	void SetFogColor(long r, long g, long b)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_FunctionTable(bool replace)
{
	ProcessInject(0x474CE0, (unsigned int)tomb4::HWBeginScene, replace);
	ProcessInject(0x475090, (unsigned int)tomb4::SetFogColor, false);
}
