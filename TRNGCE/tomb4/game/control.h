#pragma once
#include "../types.h"

namespace tomb4
{
	extern short** &meshes;
	extern ANIM_STRUCT* &anims;
	extern long* &bones;
	extern ulong &FmvSceneTriggered;
	extern long (*&flip_stats)[32];
#define flip_stats (*tomb4::flip_stats)
	extern long (*&flipmap)[32];
#define flipmap (*tomb4::flipmap)
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
}
