#pragma once
#include <cstdio>
#include "../types.h"

namespace tomb4
{
	extern short* &mesh_base;
	extern CHANGE_STRUCT* &changes;
	extern RANGE_STRUCT* &ranges;
	extern short* &commands;
	extern short* &frames;
	extern long &number_cameras;
	extern short &nAIObjects;
	inline struct { volatile long active; volatile long ended; ulong handle; ulong address; } &LevelLoadingThread = *reinterpret_cast<decltype(&LevelLoadingThread)>(0x4A6D38);
	extern AIOBJECT* &AIObjects;
	extern short* &aranges;
	extern long &nAnimUVRanges;
	extern TEXTURESTRUCT* &textinfo;
	extern TEXTURESTRUCT* (&AnimatingWaterfalls)[3];
	extern long (&AnimatingWaterfallsV)[3];
	extern SPRITESTRUCT* &spriteinfo;

	bool LoadObjects();
	bool LoadCinematic();
	long LoadFile(const char* name, char** dest);
	FILE* FileOpen(const char* name);
	long FileSize(FILE* file);
	void FileClose(FILE* file);
	bool LoadAIInfo();
	void S_GetUVRotateTextures();
	long S_LoadLevelFile(long num);
	unsigned int __stdcall LoadLevel(void* name);
	void FreeLevel();
	bool LoadSamples();
	bool LoadTextures(long RTPages, long OTPages, long BTPages);
	bool Decompress(char* pDest, char* pCompressed, long compressedSize, long size);
	bool LoadRooms();
	bool LoadSprites();
	bool LoadCameras();
	bool LoadSoundEffects();
	bool LoadBoxes();
	bool LoadAnimatedTextures();
	bool LoadTextureInfos();
	bool LoadItems();
}

void Inject_File(bool replace);
