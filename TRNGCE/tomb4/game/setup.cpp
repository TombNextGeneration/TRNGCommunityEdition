#include "setup.h"
#include "../../inject.h"
#include "../specific/function_stubs.h"
#include "effect2.h"
#include "../specific/specificfx.h"
#include "train.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	void InitialiseObjects()
	{
		__try { throw __func__; } __finally {}
	}

	void SetupGame()
	{
		SeedRandomDraw(0xD371F947);
		SeedRandomControl(0xD371F947);
		wibble = 0;
		ClearFootPrints();
		InitBinoculars();
		InitTarget();
		trainmappos = 0;
		InitialiseGameFlags();
		InitialiseLara();
		GetCarriedItems();
		GetAIPickups();
		SeedRandomDraw(0xD371F947);
		SeedRandomControl(0xD371F947);

		// chiamata in SetupGame() subito DOPO aver caricato il nuovo livello e prima di entrare in fase gioco
		trng::InizializzaStartLivello();
	}

	void ClearFootPrints()
	{
		__try { throw __func__; } __finally {}
	}

	void InitTarget()
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseGameFlags()
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseLara()
	{
		__try { throw __func__; } __finally {}
	}

	void GetCarriedItems()
	{
		__try { throw __func__; } __finally {}
	}

	void GetAIPickups()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Setup(bool replace)
{
	ProcessInject(0x45B4A0, (unsigned int)tomb4::InitialiseObjects, false);
	ProcessInject(0x45E2F0, (unsigned int)tomb4::SetupGame, replace);
	ProcessInject(0x45E3F0, (unsigned int)tomb4::ClearFootPrints, false);
	ProcessInject(0x45E360, (unsigned int)tomb4::InitTarget, false);
	ProcessInject(0x45E2A0, (unsigned int)tomb4::InitialiseGameFlags, false);
	ProcessInject(0x45B380, (unsigned int)tomb4::InitialiseLara, false);
	ProcessInject(0x45DD90, (unsigned int)tomb4::GetCarriedItems, false);
	ProcessInject(0x45DEA0, (unsigned int)tomb4::GetAIPickups, false);
}
