#include "file.h"
#include <cstring>
#include <process.h>
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
#include "../../trng/zRoomEditor.h"
#include "output.h"
#include "../game/gameflow.h"
#include "../game/sound.h"
#include "dxsound.h"
#include "../game/lara.h"
#include "dxshell.h"
#include "texture.h"
#include "LoadSave.h"
#include "audio.h"
#include "winmain.h"
#include "specificfx.h"
#include "lighting.h"
#include "../game/tomb4fx.h"
#include "../../trng/trng_elevator.h"

namespace tomb4
{
	static char* &FileData = *reinterpret_cast<decltype(&FileData)>(0x4A6D34);
	static FILE* &level_fp = *reinterpret_cast<decltype(&level_fp)>(0x533944);
	static char* &CompressedData = *reinterpret_cast<decltype(&CompressedData)>(0x533928);

	short* &mesh_base = *reinterpret_cast<decltype(&mesh_base)>(0x53394C);
	CHANGE_STRUCT* &changes = *reinterpret_cast<decltype(&changes)>(0x53393C);
	RANGE_STRUCT* &ranges = *reinterpret_cast<decltype(&ranges)>(0x533940);
	short* &commands = *reinterpret_cast<decltype(&commands)>(0x53395C);
	short* &frames = *reinterpret_cast<decltype(&frames)>(0x533954);
	long &number_cameras = *reinterpret_cast<decltype(&number_cameras)>(0x7FE820);
	short &nAIObjects = *reinterpret_cast<decltype(&nAIObjects)>(0x7FD0E0);
//	THREAD &LevelLoadingThread = *reinterpret_cast<decltype(&LevelLoadingThread)>(0x4A6D38);
	AIOBJECT* &AIObjects = *reinterpret_cast<decltype(&AIObjects)>(0x7FD0E4);
	short* &aranges = *reinterpret_cast<decltype(&aranges)>(0x753B44);
	long &nAnimUVRanges = *reinterpret_cast<decltype(&nAnimUVRanges)>(0x4A6D30);
	TEXTURESTRUCT* &textinfo = *reinterpret_cast<decltype(&textinfo)>(0x533990);
	TEXTURESTRUCT* (&AnimatingWaterfalls)[3] = *reinterpret_cast<decltype(&AnimatingWaterfalls)>(0x7FD0C0);
	long (&AnimatingWaterfallsV)[3] = *reinterpret_cast<decltype(&AnimatingWaterfallsV)>(0x7FD0D0);
	SPRITESTRUCT* &spriteinfo = *reinterpret_cast<decltype(&spriteinfo)>(0x533994);

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

	bool LoadCinematic()
	{
		// sostituisce loadsizedemodata per vedere se si usa tabella suoni
		// estesa
		trng::GlobTomb4.TotSizeDemoData = *(short*)FileData;

		if (trng::GlobTomb4.TotSizeDemoData)
		{
			// tabella estesa: forzare flag
			trng::GlobTomb4.FlagsLevelTr4 |= trng::FLT_EXTRA_SOUND_TABLE;
		}

		FileData += sizeof(short);
		return 1;
	}

	long LoadFile(const char* name, char** dest)
	{
		FILE* file;
		long size, count;

		Log(2, "LoadFile");
		Log(5, "File - %s", name);
		file = FileOpen(name);

		if (!file)
			return 0;

		trng::RetValue = trng::CorreggiSizeFile(name, file, (BYTE**)dest);
		size = trng::RetValue;

		if (!*dest)
			*dest = (char*)malloc(size);

		count = fread(*dest, 1, size, file);
		Log(5, "Read - %d FileSize - %d", count, size);

		if (count != size)
		{
			Log(1, "Error Reading File");
			FileClose(file);
			free(*dest);
			return 0;
		}

		FileClose(file);
		return size;
	}

	FILE* FileOpen(const char* name)
	{
		FILE* file;
		char path_name[256];

		strcpy_s(path_name, name);
		Log(5, "FileOpen - %s", path_name);

		if (fopen_s(&file, path_name, "rb"))
		{
			Log(1, "Unable To Open %s", path_name);
			return 0;
		}

		return file;
	}

	long FileSize(FILE* file)
	{
		long size;

		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
		return size;
	}

	void FileClose(FILE* file)
	{
		Log(2, "FileClose");
		fclose(file);
	}

	bool LoadAIInfo()
	{
		long num_ai;

		num_ai = *(long*)FileData;

		// salvare il totale massimo di record ai registrabili
		trng::BaseGlobMisc.TotOldAIRecords = num_ai;
		trng::BaseGlobMisc.TotMaxAIRecords = num_ai + 200;

		FileData += sizeof(long);
		nAIObjects = (short)num_ai;

		// in ebx c'e' la dimensione di memoria richiesta
		// aumentarla per avere 200 record in piu'
		AIObjects = (AIOBJECT*)game_malloc(sizeof(AIOBJECT) * (num_ai + 200), 0);
		memcpy(AIObjects, FileData, sizeof(AIOBJECT) * num_ai);
		FileData += sizeof(AIOBJECT) * num_ai;
		return 1;
	}

	void S_GetUVRotateTextures()
	{
		TEXTURESTRUCT* tex;
		short* pRange;

		if (!trng::MyGlobPrivate.TestNG_NoScript)
		{
			// patch per inizializzare dati globali per animazioni texture animate
			trng::InitTextureAnimateTomb4();
			return;
		}

		pRange = aranges + 1;

		for (int i = 0; i < nAnimUVRanges; i++)
		{
			for (int j = *pRange++; j >= 0; j--)
			{
				tex = &textinfo[*pRange++];
				AnimatingTexturesV[i][j][0] = tex->v1;
			}
		}
	}

	long S_LoadLevelFile(long num)
	{
		char name[80];

		Log(2, "S_LoadLevelFile");

		// se c'e' immagine background per load level allocare adesso immagine e creare memhdc
		if (*trng::AdrGlobali.pLevelNow)
			trng::GlobTomb4.TestFirstLoadTitle = false;

		if (trng::GlobTomb4.BaseImgLoadingLevel.TestEnabled)
			trng::AllocaImgLoadingLevel();

		strcpy_s(name, &gfFilenameWad[gfFilenameOffset[num]]);
		strcat_s(name, ".TR4");
		LevelLoadingThread.active = 1;
		LevelLoadingThread.ended = 0;
		LevelLoadingThread.handle = _beginthreadex(0, 0, &LoadLevel, name, 0, (unsigned int*)&LevelLoadingThread.address);

		do Sleep(10); while (LevelLoadingThread.active);

		return 1;
	}

	unsigned int __stdcall LoadLevel(void* name)
	{
		OBJECT_INFO* obj;
		TEXTURESTRUCT* tex;
		char* pData;
		long version, size, compressedSize;
		short RTPages, OTPages, BTPages;

		Log(2, "LoadLevel");
		FreeLevel();
		memset(malloc_ptr, 0, MALLOC_SIZE);
		memset(&lara, 0, sizeof(LARA_INFO));

		Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
		nTextures = 1;
		Textures[0].tex = 0;
		Textures[0].surface = 0;
		Textures[0].width = 0;
		Textures[0].height = 0;
		Textures[0].bump = 0;

		S_InitLoadBar(20);
		S_LoadBar();

		// in eax c'e' il nome del file tr4 da leggere

		CompressedData = 0;
		trng::LeggiExtraHeader_Tr4((const char*)name);
		FileData = 0;
		level_fp = 0;
		level_fp = FileOpen((const char*)name);

		if (level_fp)
		{
			fread(&version, 1, 4, level_fp);
			fread(&RTPages, 1, 2, level_fp);

			// in [esp+40h] c'e' dword di file tr4 con "tr4" o "tr4c"
			trng::TestAttivaCryptTr4 = 0;

			if (char(version >> 24) == 'c')
				trng::TestAttivaCryptTr4 = 1;

			fread(&OTPages, 1, 2, level_fp);
			fread(&BTPages, 1, 2, level_fp);

			Log(7, "Process Level Data");
			LoadTextures(RTPages, OTPages, BTPages);
			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);
			CompressedData = (char*)malloc(compressedSize);

			if (!CompressedData)
			{
				LevelLoadingThread.active = 0;
				return 1;
			}

			FileData = (char*)malloc(size);
			fread(CompressedData, compressedSize, 1, level_fp);

			if (trng::TestAttivaCryptTr4)
			{
				trng::NumeroBloccoCrypt = 4;
				trng::CriptaZona((BYTE*)CompressedData, compressedSize);
			}

			Decompress(FileData, CompressedData, compressedSize, size);
			free(CompressedData);

			pData = FileData;
			S_LoadBar();

			LoadRooms();
			S_LoadBar();

			LoadObjects();
			S_LoadBar();

			LoadSprites();
			S_LoadBar();

			LoadCameras();
			S_LoadBar();

			LoadSoundEffects();
			S_LoadBar();

			LoadBoxes();
			S_LoadBar();

			LoadAnimatedTextures();
			S_LoadBar();

			LoadTextureInfos();
			S_LoadBar();

			LoadItems();
			S_LoadBar();

			LoadAIInfo();
			S_LoadBar();

			LoadCinematic();
			S_LoadBar();

			if (acm_ready && !App.SoundDisabled)
				LoadSamples();

			free(pData);
			S_LoadBar();

			for (int i = 0; i < 3; i++)
			{
				obj = &objects[WATERFALL1 + i];

				if (obj->loaded)
				{
					tex = &textinfo[mesh_vtxbuf[obj->mesh_index]->gt4[4] & 0x7FFF];
					AnimatingWaterfalls[i] = tex;
					AnimatingWaterfallsV[i] = (long)tex->v1;
				}
			}

			S_LoadBar();
			S_GetUVRotateTextures();

			InitTarget_2();
			S_LoadBar();

			MallocD3DLights();
			CreateD3DLights();
			SetupGame();
			S_LoadBar();

			SetFadeClip(0, 1);
			reset_cutseq_vars();
			FileClose(level_fp);
		}

		// chiamata alla fine di LoadLevel, chiama aClearFX per
		// inizalizzare rainbuffer e snowbuffer
		if (trng::GlobTomb4.BaseImgLoadingLevel.TestEnabled)
			trng::LiberaImgLoadingLevel();

		trng::PreparaCustomize();
		trng::PreparaMirror();
		trng::PreparaElevator();
		trng::PreparaCutscene();
		trng::PreparaDetector();
		trng::PreparaPedane();
		trng::PreparaPushables();
		trng::PreparaOrganizer();
		trng::PreparaItemGroup();
		trng::PreparaGlobalTriggers();
		trng::PreparaPushAway();
		trng::PreparaFontGrapchis();
		trng::NuovoInitFont();
		trng::InitModificaCodice();
		trng::ImpostaTempoUltimoComando();

		// da tenere in fondo
		trng::PreparaLivello();

		trng::aClearFX();

		LevelLoadingThread.active = 0;
		_endthreadex(1);
		return 1;
	}

	void FreeLevel()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadSamples()
	{
		static long num_sample_infos;

		long nSamples, num_samples, uncomp_size, comp_size;

		Log(2, "LoadSamples");
		sample_lut = (short*)game_malloc(2048 * sizeof(short), 0);

		// in edi c'e' zona di memoria appena allocata
		if (trng::GlobTomb4.FlagsLevelTr4 & trng::FLT_EXTRA_SOUND_TABLE)
		{
			// nuova tabella estesa
			memcpy(sample_lut, FileData, 2048 * sizeof(short));
			FileData += 2048 * sizeof(short);
		}
		else
		{
			memcpy(sample_lut, FileData, MAX_SAMPLES * sizeof(short));
			FileData += MAX_SAMPLES * sizeof(short);
		}

		num_sample_infos = *(long*)FileData;
		FileData += sizeof(long);
		Log(8, "Number Of Sample Infos %d", num_sample_infos);

		if (!num_sample_infos)
		{
			Log(1, "No Sample Infos");
			return 0;
		}

		sample_infos = (SAMPLE_INFO*)game_malloc(sizeof(SAMPLE_INFO) * num_sample_infos, 0);
		memcpy(sample_infos, FileData, sizeof(SAMPLE_INFO) * num_sample_infos);
		FileData += sizeof(SAMPLE_INFO) * num_sample_infos;
		num_samples = *(long*)FileData;
		FileData += sizeof(long);

		if (!num_samples)
		{
			Log(1, "No Samples");
			return 0;
		}

		Log(8, "Number Of Samples %d", num_samples);
		fread(&nSamples, 1, 4, level_fp);
		InitSampleDecompress();

		for (int i = 0; i < nSamples; i++)
		{
			Log(8, "CreateSample %d of %d", i, nSamples);
			fread(&uncomp_size, 1, 4, level_fp);
			fread(&comp_size, 1, 4, level_fp);

			if ((ulong)comp_size > samples_buffer_size)
				comp_size = samples_buffer_size;

			fread(samples_buffer, comp_size, 1, level_fp);

			if (!DXCreateSampleADPCM(samples_buffer, comp_size, uncomp_size, i))
			{
				FreeSampleDecompress();
				return 0;
			}
		}

		FreeSampleDecompress();
		return 1;
	}

	bool LoadTextures(long RTPages, long OTPages, long BTPages)
	{
		DXTEXTUREINFO* dxtex;
		LPDIRECTDRAWSURFACE4 tSurf;
		LPDIRECT3DTEXTURE2 pTex;
		uchar* TextureData;
		long* d;
		char* pData;
		char* pComp;
		char* s;
		long format, skip, size, compressedSize, nTex, c;
		uchar r, g, b, a;

		Log(2, "LoadTextures");
		nTextures = 1;
		format = 0;
		skip = 4;
		dxtex = &G_dxinfo->DDInfo[G_dxinfo->nDD].D3DDevices[G_dxinfo->nD3D].TextureInfos[G_dxinfo->nTexture];

		if (dxtex->rbpp == 8 && dxtex->gbpp == 8 && dxtex->bbpp == 8 && dxtex->abpp == 8)
		{
			format = 1;
			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);

			CompressedData = (char*)malloc(compressedSize);
			FileData = (char*)malloc(size);

			fread(CompressedData, compressedSize, 1, level_fp);

			// in ecx dimensione zona compressa

			// vedere se bisogna decriptare
			if (trng::TestAttivaCryptTr4)
			{
				// impostare numero blocco da decoprimere
				trng::NumeroBloccoCrypt = 1;
				trng::CriptaZona((BYTE*)CompressedData, compressedSize);
			}

			// salvare memoria dove verra' decompressa mappa tex1
			trng::GlobTomb4.pMemoriaTexture = (BYTE*)FileData;

			Decompress(FileData, CompressedData, compressedSize, size);

			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);
			fseek(level_fp, compressedSize, SEEK_CUR);
			free(CompressedData);
		}
		else if (dxtex->rbpp == 5 && dxtex->gbpp == 5 && dxtex->bbpp == 5 && dxtex->abpp == 1)
		{
			format = 2;
			skip = 2;
			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);
			fseek(level_fp, compressedSize, SEEK_CUR);

			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);

			CompressedData = (char*)malloc(compressedSize);
			FileData = (char*)malloc(size);
			fread(CompressedData, compressedSize, 1, level_fp);

			// codice per decript di texture 2 in tomb4 caricando tr4
			if (trng::TestAttivaCryptTr4)
			{
				// decriptare
				// impostare numero blocco da decoprimere
				trng::NumeroBloccoCrypt = 2;
				trng::CriptaZona((BYTE*)CompressedData, compressedSize);
			}

			Decompress(FileData, CompressedData, compressedSize, size);
			free(CompressedData);
		}
		else
		{
			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);

			CompressedData = (char*)malloc(compressedSize);
			FileData = (char*)malloc(size);

			fread(CompressedData, compressedSize, 1, level_fp);

			// in ecx dimensione zona compressa

			// vedere se bisogna decriptare
			if (trng::TestAttivaCryptTr4)
			{
				// impostare numero blocco da decoprimere
				trng::NumeroBloccoCrypt = 1;
				trng::CriptaZona((BYTE*)CompressedData, compressedSize);
			}

			// salvare memoria dove verra' decompressa mappa tex1
			trng::GlobTomb4.pMemoriaTexture = (BYTE*)FileData;

			Decompress(FileData, CompressedData, compressedSize, size);

			fread(&size, 1, 4, level_fp);
			fread(&compressedSize, 1, 4, level_fp);
			fseek(level_fp, compressedSize, SEEK_CUR);
			free(CompressedData);
		}

		Log(5, "RTPages %d", RTPages);
		size = RTPages * skip * 0x10000;
		TextureData = (uchar*)malloc(size);
		memcpy(TextureData, FileData, size);
		FileData += size;
		S_LoadBar();

		for (int i = 0; i < RTPages; i++)
		{
			Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
			nTex = nTextures;
			nTextures++;
			tSurf = CreateTexturePage(App.TextureSize, App.TextureSize, 0, (long*)(TextureData + (i * skip * 0x10000)), 0, format);
			DXAttempt(tSurf->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pTex));
			Textures[nTex].tex = pTex;
			Textures[nTex].surface = tSurf;
			Textures[nTex].width = App.TextureSize;
			Textures[nTex].height = App.TextureSize;
			Textures[nTex].bump = 0;
			App.dx.lpD3DDevice->SetTexture(0, pTex);
		}

		free(TextureData);

		Log(5, "OTPages %d", OTPages);
		size = OTPages * skip * 0x10000;
		TextureData = (uchar*)malloc(size);
		memcpy(TextureData, FileData, size);
		FileData += size;
		S_LoadBar();

		for (int i = 0; i < OTPages; i++)
		{
			Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
			nTex = nTextures;
			nTextures++;
			tSurf = CreateTexturePage(App.TextureSize, App.TextureSize, 0, (long*)(TextureData + (i * skip * 0x10000)), 0, format);
			DXAttempt(tSurf->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pTex));
			Textures[nTex].tex = pTex;
			Textures[nTex].surface = tSurf;
			Textures[nTex].width = App.TextureSize;
			Textures[nTex].height = App.TextureSize;
			Textures[nTex].bump = 0;
			App.dx.lpD3DDevice->SetTexture(0, pTex);
		}

		free(TextureData);
		S_LoadBar();

		Log(5, "BTPages %d", BTPages);

		if (BTPages)
		{
			size = BTPages * skip * 0x10000;
			TextureData = (uchar*)malloc(size);
			memcpy(TextureData, FileData, size);
			FileData += size;

			for (int i = 0; i < BTPages; i++)
			{
				if (i < (BTPages >> 1))
					tSurf = CreateTexturePage(App.TextureSize, App.TextureSize, 0, (long*)(TextureData + (i * skip * 0x10000)), 0, format);
				else
				{
					if (!App.BumpMapping)
						break;

					tSurf = CreateTexturePage(App.BumpMapSize, App.BumpMapSize, 0, (long*)(TextureData + (i * skip * 0x10000)), 0, format);
				}

				Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
				nTex = nTextures;
				nTextures++;
				DXAttempt(tSurf->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pTex));
				Textures[nTex].tex = pTex;
				Textures[nTex].surface = tSurf;

				if (i < (BTPages >> 1))
				{
					Textures[nTex].width = App.TextureSize;
					Textures[nTex].height = App.TextureSize;
				}
				else
				{
					Textures[nTex].width = App.BumpMapSize;
					Textures[nTex].height = App.BumpMapSize;
				}

				Textures[nTex].bump = 1;
				Textures[nTex].bumptpage = nTex + (BTPages >> 1);
			}

			free(TextureData);
		}

		fread(&size, 1, 4, level_fp);
		fread(&compressedSize, 1, 4, level_fp);
		CompressedData = (char*)malloc(compressedSize);

		if (!CompressedData)
			return false;

		FileData = (char*)malloc(size);

		if (!FileData)
		{
			free(CompressedData);
			return false;
		}

		fread(CompressedData, compressedSize, 1, level_fp);

		if (trng::TestAttivaCryptTr4)
		{
			// decriptare
			trng::NumeroBloccoCrypt = 3;
			trng::CriptaZona((BYTE*)CompressedData, compressedSize);
		}

		Decompress(FileData, CompressedData, compressedSize, size);
		free(CompressedData);

		pData = FileData;
		TextureData = (uchar*)malloc(0x40000);

		if (!TextureData)
		{
			free(pData);
			return false;
		}

		if (!gfCurrentLevel)	//main menu logo
		{
			CompressedData = 0;
			size = LoadFile("data\\uklogo.pak", &CompressedData);
			pComp = (char*)malloc(*(long*)CompressedData);

			if (!pComp)
			{
				free(CompressedData);
				free(TextureData);
				free(pData);
				return false;
			}

			Decompress(pComp, CompressedData + 4, size - 4, *(long*)CompressedData);
			free(CompressedData);

			for (int i = 0; i < 2; i++)
			{
				s = pComp + (i * 768);
				d = (long*)TextureData;

				for (int y = 0; y < 256; y++)
				{
					for (int x = 0; x < 256; x++)
					{
						r = *(s + (x * 3) + (y * 1536));
						g = *(s + (x * 3) + (y * 1536) + 1);
						b = *(s + (x * 3) + (y * 1536) + 2);
						a = uchar(-1);

						if (!r && !b && !g)
							a = 0;

						c = (((((a << 8) | r) << 8) | g) << 8) | b;
						*d++ = c;
					}
				}

				Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
				nTex = nTextures;
				nTextures++;
				tSurf = CreateTexturePage(256, 256, 0, (long*)TextureData, 0, 0);
				DXAttempt(tSurf->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pTex));
				Textures[nTex].tex = pTex;
				Textures[nTex].surface = tSurf;
				Textures[nTex].width = 256;
				Textures[nTex].height = 256;
				Textures[nTex].bump = 0;
			}

			free(pComp);
		}

		//font
#pragma warning(suppress: 6385)
		memcpy(TextureData, FileData, 0x40000);
		FileData += 0x40000;

		Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
		nTex = nTextures;
		nTextures++;
		tSurf = CreateTexturePage(256, 256, 0, (long*)TextureData, 0, 0);
		DXAttempt(tSurf->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pTex));
		Textures[nTex].tex = pTex;
		Textures[nTex].surface = tSurf;
		Textures[nTex].width = 256;
		Textures[nTex].height = 256;
		Textures[nTex].bump = 0;

		//sky
		memcpy(TextureData, FileData, 0x40000);
		FileData += 0x40000;

		Textures = (TEXTURE*)AddStruct(Textures, nTextures, sizeof(TEXTURE));
		nTex = nTextures;
		nTextures++;
		tSurf = CreateTexturePage(256, 256, 0, (long*)TextureData, 0, 0);
		DXAttempt(tSurf->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&pTex));
		Textures[nTex].tex = pTex;
		Textures[nTex].surface = tSurf;
		Textures[nTex].width = 256;
		Textures[nTex].height = 256;
		Textures[nTex].bump = 0;

		free(TextureData);
		free(pData);
		return 1;
	}

	bool Decompress(char* pDest, char* pCompressed, long compressedSize, long size)
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadRooms()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadSprites()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadCameras()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadSoundEffects()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadBoxes()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadAnimatedTextures()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadTextureInfos()
	{
		__try { throw __func__; } __finally {}
	}

	bool LoadItems()
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_File(bool replace)
{
	ProcessInject(0x473090, (unsigned int)tomb4::LoadObjects, replace);
	ProcessInject(0x474450, (unsigned int)tomb4::LoadCinematic, replace);
	ProcessInject(0x472090, (unsigned int)tomb4::LoadFile, replace);
//	ProcessInject(0x471FD0, (unsigned int)tomb4::FileOpen, replace);
	ProcessInject(0x472060, (unsigned int)tomb4::FileSize, replace);
//	ProcessInject(0x472040, (unsigned int)tomb4::FileClose, replace);
	ProcessInject(0x474460, (unsigned int)tomb4::LoadAIInfo, replace);
	ProcessInject(0x474670, (unsigned int)tomb4::S_GetUVRotateTextures, replace);
	ProcessInject(0x474B20, (unsigned int)tomb4::S_LoadLevelFile, replace);
	ProcessInject(0x4746D0, (unsigned int)tomb4::LoadLevel, replace);
	ProcessInject(0x4749F0, (unsigned int)tomb4::FreeLevel, false);
	ProcessInject(0x4744C0, (unsigned int)tomb4::LoadSamples, replace);
	ProcessInject(0x4721E0, (unsigned int)tomb4::LoadTextures, replace);
	ProcessInject(0x472140, (unsigned int)tomb4::Decompress, false);
	ProcessInject(0x472C40, (unsigned int)tomb4::LoadRooms, false);
	ProcessInject(0x4739A0, (unsigned int)tomb4::LoadSprites, false);
	ProcessInject(0x473BE0, (unsigned int)tomb4::LoadCameras, false);
	ProcessInject(0x473CA0, (unsigned int)tomb4::LoadSoundEffects, false);
	ProcessInject(0x473D30, (unsigned int)tomb4::LoadBoxes, false);
	ProcessInject(0x473EE0, (unsigned int)tomb4::LoadAnimatedTextures, false);
	ProcessInject(0x473F50, (unsigned int)tomb4::LoadTextureInfos, false);
	ProcessInject(0x474150, (unsigned int)tomb4::LoadItems, false);
}
