#include "file.h"
#include <string.h>
#include "../../inject.h"
#include "function_stubs.h"
#include "../game/objects.h"
#include "../game/draw.h"
#include "../game/control.h"
#include "../game/laraskin.h"
#include "../game/setup.h"
#include "drawroom.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	static char* &FileData = *reinterpret_cast<decltype(&FileData)>(0x4A6D34);

	short* &mesh_base = *reinterpret_cast<decltype(&mesh_base)>(0x53394C);
	CHANGE_STRUCT* &changes = *reinterpret_cast<decltype(&changes)>(0x53393C);
	RANGE_STRUCT* &ranges = *reinterpret_cast<decltype(&ranges)>(0x533940);
	short* &commands = *reinterpret_cast<decltype(&commands)>(0x53395C);
	short* &frames = *reinterpret_cast<decltype(&frames)>(0x533954);
	long &number_cameras = *reinterpret_cast<decltype(&number_cameras)>(0x7FE820);
	short &nAIObjects = *reinterpret_cast<decltype(&nAIObjects)>(0x7FD0E0);
//	THREAD &LevelLoadingThread = *reinterpret_cast<decltype(&LevelLoadingThread)>(0x4A6D38);

	bool LoadObjects()
	{
		static long num_meshes, num_anims;

		OBJECT_INFO* obj;
		STATIC_INFO* stat;
		short** mesh;
		short** mesh_size;
		long size, num, slot;

		Log(2, "LoadObjects");
		memset(objects, 0, sizeof(OBJECT_INFO) * NUMBER_OBJECTS);
		memset(static_objects, 0, sizeof(STATIC_INFO) * NUMBER_STATIC_OBJECTS);

		size = *(long*)FileData;
		FileData += sizeof(long);
		mesh_base = (short*)game_malloc(size * sizeof(short), 0);
		memcpy(mesh_base, FileData, size * sizeof(short));
		FileData += size * sizeof(short);

		size = *(long*)FileData;
		FileData += sizeof(long);
		meshes = (short**)game_malloc(2 * size * sizeof(short*), 0);
		memcpy(meshes, FileData, size * sizeof(short*));
		FileData += size * sizeof(short*);

		for (int i = 0; i < size; i++)
			meshes[i] = mesh_base + (long)meshes[i] / 2;

		num_meshes = size;

		//Patch0
		//salva la dimensione reale di tutte le mesh
		//in ebx totale mesh
		//in [Ptr_VetMeshPointers] inizio vettore dword
		//con tutti i puntatori alle mesh

		trng::SalvaDimensioniMesh((WORD**)meshes, size);

		num_anims = *(long*)FileData;
		FileData += sizeof(long);
		anims = (ANIM_STRUCT*)game_malloc(sizeof(ANIM_STRUCT) * num_anims, 0);
		memcpy(anims, FileData, sizeof(ANIM_STRUCT) * num_anims);
		FileData += sizeof(ANIM_STRUCT) * num_anims;

		size = *(long*)FileData;
		FileData += sizeof(long);
		changes = (CHANGE_STRUCT*)game_malloc(sizeof(CHANGE_STRUCT) * size, 0);
		memcpy(changes, FileData, sizeof(CHANGE_STRUCT) * size);
		FileData += sizeof(CHANGE_STRUCT) * size;

		size = *(long*)FileData;
		FileData += sizeof(long);
		ranges = (RANGE_STRUCT*)game_malloc(sizeof(RANGE_STRUCT) * size, 0);
		memcpy(ranges, FileData, sizeof(RANGE_STRUCT) * size);
		FileData += sizeof(RANGE_STRUCT) * size;

		size = *(long*)FileData;
		FileData += sizeof(long);
		commands = (short*)game_malloc(sizeof(short) * size, 0);
		memcpy(commands, FileData, sizeof(short) * size);
		FileData += sizeof(short) * size;

		size = *(long*)FileData;
		FileData += sizeof(long);
		bones = (long*)game_malloc(sizeof(long) * size, 0);
		memcpy(bones, FileData, sizeof(long) * size);
		FileData += sizeof(long) * size;

		size = *(long*)FileData;
		FileData += sizeof(long);
		frames = (short*)game_malloc(sizeof(short) * size, 0);
		memcpy(frames, FileData, sizeof(short) * size);
		FileData += sizeof(short) * size;

		for (int i = 0; i < num_anims; i++)
			anims[i].frame_ptr = (short*)((long)anims[i].frame_ptr + (long)frames);

		num = *(long*)FileData;
		FileData += sizeof(long);

		for (int i = 0; i < num; i++)
		{
			slot = *(long*)FileData;
			FileData += sizeof(long);
			obj = &objects[slot];

			obj->nmeshes = *(short*)FileData;
			FileData += sizeof(short);

			obj->mesh_index = *(short*)FileData;
			FileData += sizeof(short);

			obj->bone_index = *(long*)FileData;
			FileData += sizeof(long);

			obj->frame_base = (short*)(*(short**)FileData);
			FileData += sizeof(short*);

			obj->anim_index = *(short*)FileData;
			FileData += sizeof(short);

			obj->loaded = 1;
		}

		CreateSkinningData();

		for (int i = 0; i < NUMBER_OBJECTS; i++)
		{
			obj = &objects[i];
			obj->mesh_index *= 2;
		}

		// salvare indirizzo per vettore animazioni
		trng::AdrGlobali.pVetAnimations = (trng::StrAnimationTr4*)anims;
		trng::AdrGlobali.VetMeshPointer = (trng::StrMeshTr4**)meshes;

		mesh = meshes;
		mesh_size = &meshes[num_meshes];
		memcpy(mesh_size, mesh, num_meshes * 4);

		for (int i = 0; i < num_meshes; i++)
		{
			*mesh++ = *mesh_size;
			*mesh++ = *mesh_size;
			mesh_size++;
		}

		InitialiseObjects();

		num = *(long*)FileData;	//statics
		FileData += sizeof(long);

		for (int i = 0; i < num; i++)
		{
			slot = *(long*)FileData;
			FileData += sizeof(long);
			stat = &static_objects[slot];

			stat->mesh_number = *(short*)FileData;
			FileData += sizeof(short);

			memcpy(&stat->x_minp, FileData, 6 * sizeof(short));
			FileData += 6 * sizeof(short);

			memcpy(&stat->x_minc, FileData, 6 * sizeof(short));
			FileData += 6 * sizeof(short);

			stat->flags = *(short*)FileData;
			FileData += sizeof(short);
		}

		for (int i = 0; i < NUMBER_STATIC_OBJECTS; i++)
		{
			stat = &static_objects[i];
			stat->mesh_number *= 2;
		}

		ProcessMeshData(num_meshes * 2);

		// chiamata subito dopo iniziliazzazione slot da parte di tomb4
		// e prima di chiamare funzione di initiliase per ogni moveable
		trng::InitSlot();

		return 1;
	}
}

void Inject_File(bool replace)
{
	ProcessInject(0x473090, (unsigned int)tomb4::LoadObjects, replace);
}
