#pragma once
#include "../types.h"

namespace tomb4
{
	extern short** &meshes;
	extern ANIM_STRUCT* &anims;
	extern long* &bones;
	extern ulong &FmvSceneTriggered;
	inline struct { long (*&_)[32] = *reinterpret_cast<decltype(&_)>(0x4598AF); decltype(*_) operator()() { return *_; } } flip_stats;
#define flip_stats flip_stats()
	inline struct { long (*&_)[32] = *reinterpret_cast<decltype(&_)>(0x4598D8); decltype(*_) operator()() { return *_; } } flipmap;
#define flipmap flipmap()
	extern long &flipeffect;
	extern long &fliptimer;
	extern long &flip_status;
	extern char (&cd_flags)[128];
	extern uchar &CurrentAtmosphere;
	extern short &number_rooms;
	extern ROOM_INFO* &room;
	extern long &level_items;
	extern ITEM_INFO* &items;
	extern long &height_type;
	extern long &OnObject;
	extern long &tiltyoff;
	extern long &tiltxoff;
	extern short (&SmashedMeshRoom)[16];
	extern MESH_INFO* (&SmashedMesh)[16];
	extern short &SmashedMeshCount;
	extern uchar &IsAtmospherePlaying;
	extern uchar &InItemControlLoop;
	extern long &SetDebounce;
	extern long &framecount;
	extern ushort &GlobalCounter;
	extern long &reset_flag;
	extern uchar &WeaponDelay;
	extern short &XSoff1;
	extern short &YSoff1;
	extern short &ZSoff1;
	extern short &XSoff2;
	extern short &YSoff2;
	extern short &ZSoff2;
	extern char &PoisonFlag;
	extern short* &trigger_index;

	long ControlPhase(long nframes, long demo_mode);
	void UpdateSky();
	void KillMoveItems();
	void KillMoveEffects();
	FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number);
	long GetHeight(FLOOR_INFO* floor, long x, long y, long z);
	void TestTriggers(short* data, long heavy, long HeavyFlags);
	void RefreshCamera(short type, short* data);
}

void Inject_Control(bool replace);
