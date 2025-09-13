#include "control.h"

namespace tomb4
{
	short** &meshes = *reinterpret_cast<decltype(&meshes)>(0x533950);
	ANIM_STRUCT* &anims = *reinterpret_cast<decltype(&anims)>(0x533938);
	long* &bones = *reinterpret_cast<decltype(&bones)>(0x533958);
	ulong &FmvSceneTriggered = *reinterpret_cast<decltype(&FmvSceneTriggered)>(0x7FE0F0);
#undef flip_stats
	long (*&flip_stats)[32] = *reinterpret_cast<decltype(&flip_stats)>(0x4598AF);
#define flip_stats (*tomb4::flip_stats)
#undef flipmap
	long (*&flipmap)[32] = *reinterpret_cast<decltype(&flipmap)>(0x4598D8);
#define flipmap (*tomb4::flipmap)
	long &flipeffect = *reinterpret_cast<decltype(&flipeffect)>(0x4ACBFC);
	long &fliptimer = *reinterpret_cast<decltype(&fliptimer)>(0x4BF2E8);
	long &flip_status = *reinterpret_cast<decltype(&flip_status)>(0x7FE0F8);
	char (&cd_flags)[128] = *reinterpret_cast<decltype(&cd_flags)>(0x7FE060);
	uchar &CurrentAtmosphere = *reinterpret_cast<decltype(&CurrentAtmosphere)>(0x7FE0FC);
	short &number_rooms = *reinterpret_cast<decltype(&number_rooms)>(0x53392C);
	ROOM_INFO* &room = *reinterpret_cast<decltype(&room)>(0x533934);
	long &level_items = *reinterpret_cast<decltype(&level_items)>(0x4BF564);
	ITEM_INFO* &items = *reinterpret_cast<decltype(&items)>(0x7FE16C);
	long &height_type = *reinterpret_cast<decltype(&height_type)>(0x7FE170);
	long &OnObject = *reinterpret_cast<decltype(&OnObject)>(0x7FE0E0);
	long &tiltyoff = *reinterpret_cast<decltype(&tiltyoff)>(0x7FE0F4);
	long &tiltxoff = *reinterpret_cast<decltype(&tiltxoff)>(0x7FE0EC);
	short (&SmashedMeshRoom)[16] = *reinterpret_cast<decltype(&SmashedMeshRoom)>(0x7FE240);
	MESH_INFO* (&SmashedMesh)[16] = *reinterpret_cast<decltype(&SmashedMesh)>(0x7FE680);
	short &SmashedMeshCount = *reinterpret_cast<decltype(&SmashedMeshCount)>(0x4BF2D6);
	uchar &IsAtmospherePlaying = *reinterpret_cast<decltype(&IsAtmospherePlaying)>(0x7FE1C4);
	uchar &InItemControlLoop = *reinterpret_cast<decltype(&InItemControlLoop)>(0x4BF2CD);
}
