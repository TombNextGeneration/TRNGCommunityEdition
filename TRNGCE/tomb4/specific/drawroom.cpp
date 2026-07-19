#include "drawroom.h"
#include "../../inject.h"

namespace tomb4
{
	TEXTUREBUCKET (&Bucket)[80] = *reinterpret_cast<decltype(&Bucket)>(0x470CF8);

	void ProcessMeshData(long num_meshes)
	{
		__try { throw __func__; } __finally {}
	}

	void InsertRoom(ROOM_INFO* r)
	{
		__try { throw __func__; } __finally {}
	}

	void InitBuckets()
	{
		TEXTUREBUCKET* bucket;

		for (int i = 0; i < 80; i++)
		{
			bucket = &Bucket[i];
			bucket->tpage = -1;
			bucket->nVtx = 0;
		}
	}
}

__declspec(naked) static void** Inject_Drawroom_Bucket() { __asm lea eax, [tomb4::Bucket] __asm ret }

void Inject_Drawroom(bool replace)
{
	IndirectReferenceInject(Inject_Drawroom_Bucket());

	ProcessInject(0x46F4F0, (unsigned int)tomb4::ProcessMeshData, false);
	ProcessInject(0x470A70, (unsigned int)tomb4::InsertRoom, false);
	ProcessInject(0x470CD0, (unsigned int)tomb4::InitBuckets, replace);
}
