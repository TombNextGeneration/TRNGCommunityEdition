#include "output.h"
#include "../../inject.h"
#include "d3dmatrix.h"
#include "drawroom.h"
#include "../../trng/zPatchesTomb4.h"
#include "time.h"
#include "../game/text.h"
#include "function_table.h"
#include "dxshell.h"
#include "winmain.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	float (&AnimatingTexturesV)[16][8][3] = *reinterpret_cast<decltype(&AnimatingTexturesV)>(0x4746A3);
	long &GlobalAlpha = *reinterpret_cast<decltype(&GlobalAlpha)>(0x4AB7B8);

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
		long n;

		n = Sync();

		while (n < 2)
		{
			while (!Sync());	//wait for sync
			n++;
		}

		// se e' attivo aync frames non incrementare qui il numero di frame
		if (!(trng::GlobTomb4.BaseTurbo.Flags & trng::TRB_ASYNC_FRAMES))
			GnFrameCounter++;

		_EndScene();
		DXShowFrame();
		App.dx.DoneBlit = 1;
		return n;
	}

	void phd_PutPolygons_train(short* objptr, long x)
	{
		__try { throw __func__; } __finally {}
	}

	void _InsertRoom(ROOM_INFO* r)
	{
		trng::pInsRecordRoom = (trng::StrRoomTr4*)r;
		SetD3DViewMatrix();
		InsertRoom((ROOM_INFO*)trng::pInsRecordRoom);
		trng::pInsRecordRoom = 0;
	}
}

__declspec(naked) static void** Inject_Output_AnimatingTexturesV() { __asm lea eax, [tomb4::AnimatingTexturesV] __asm ret }

void Inject_Output(bool replace)
{
	IndirectReferenceInject(Inject_Output_AnimatingTexturesV());

	ProcessInject(0x47E910, (unsigned int)tomb4::do_boot_screen, false);
	ProcessInject(0x47B6E0, (unsigned int)tomb4::S_InitialisePolyList, false);
	ProcessInject(0x47D990, (unsigned int)tomb4::S_OutputPolyList, false);
	ProcessInject(0x47DCB0, (unsigned int)tomb4::S_DumpScreen, replace);
	ProcessInject(0x47E340, (unsigned int)tomb4::phd_PutPolygons_train, false);
	ProcessInject(0x47D8D0, (unsigned int)tomb4::_InsertRoom, replace);
}
