#include "winmain.h"
#include "../../inject.h"
#include "function_stubs.h"
#include "registry.h"
#include "dxshell.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	WINAPP &App = *reinterpret_cast<decltype(&App)>(0x753858);

	void WinClose()
	{
		trng::RipristinaSettings();
		trng::LiberaPlugins();
		Log(2, "WinClose");

		// se modo setup non scrivere di nuovo le impostazioni
		if (!trng::GlobTomb4.TestSetup)
			SaveSettings();

		CloseHandle(App.mutex);
		DXFreeInfo(&App.DXInfo);
		DestroyAcceleratorTable(App.hAccel);
		DXClose();

		if (!G_dxptr)
			return;

		DXAttempt(G_dxptr->Keyboard->Unacquire());

		if (G_dxptr->Keyboard)
		{
			Log(4, "Released %s @ %x - RefCnt = %d", "Keyboard", G_dxptr->Keyboard, G_dxptr->Keyboard->Release());
			G_dxptr->Keyboard = 0;
		}
		else
			Log(1, "%s Attempt To Release NULL Ptr", "Keyboard");

		if (G_dxptr->lpDirectInput)
		{
			Log(4, "Released %s @ %x - RefCnt = %d", "DirectInput", G_dxptr->lpDirectInput, G_dxptr->lpDirectInput->Release());
			G_dxptr->lpDirectInput = 0;
		}
		else
			Log(1, "%s Attempt To Release NULL Ptr", "DirectInput");
	}
}

void Inject_Winmain(bool replace)
{
	ProcessInject(0x48CBE0, (unsigned int)tomb4::WinClose, replace);
}
