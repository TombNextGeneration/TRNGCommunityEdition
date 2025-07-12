#include "../types.h"

namespace tomb4
{
	short** &meshes = *reinterpret_cast<decltype(&meshes)>(0x533950);
	ANIM_STRUCT* &anims = *reinterpret_cast<decltype(&anims)>(0x533938);
	long* &bones = *reinterpret_cast<decltype(&bones)>(0x533958);
	ulong &FmvSceneTriggered = *reinterpret_cast<decltype(&FmvSceneTriggered)>(0x7FE0F0);
	long (*&flip_stats)[32] = *reinterpret_cast<decltype(&flip_stats)>(0x4598AF);
#define flip_stats (*flip_stats)
	long (*&flipmap)[32] = *reinterpret_cast<decltype(&flipmap)>(0x4598D8);
#define flipmap (*flipmap)
	long &flipeffect = *reinterpret_cast<decltype(&flipeffect)>(0x4ACBFC);
	long &fliptimer = *reinterpret_cast<decltype(&fliptimer)>(0x4BF2E8);
	long &flip_status = *reinterpret_cast<decltype(&flip_status)>(0x7FE0F8);
	char (&cd_flags)[128] = *reinterpret_cast<decltype(&cd_flags)>(0x7FE060);
	uchar &CurrentAtmosphere = *reinterpret_cast<decltype(&CurrentAtmosphere)>(0x7FE0FC);
	short &number_rooms = *reinterpret_cast<decltype(&number_rooms)>(0x53392C);
	ROOM_INFO* &room = *reinterpret_cast<decltype(&room)>(0x533934);
	long &level_items = *reinterpret_cast<decltype(&level_items)>(0x4BF564);
	ITEM_INFO* &items = *reinterpret_cast<decltype(&items)>(0x7FE16C);
}
