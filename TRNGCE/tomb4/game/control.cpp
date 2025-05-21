#include "types.h"

namespace tomb4
{
	short** &meshes = *reinterpret_cast<decltype(&meshes)>(0x533950);
	ANIM_STRUCT* &anims = *reinterpret_cast<decltype(&anims)>(0x533938);
	long* &bones = *reinterpret_cast<decltype(&bones)>(0x533958);
}
