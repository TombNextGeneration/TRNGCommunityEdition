#include "lara1gun.h"
#include "../../inject.h"
#include "control.h"
#include "lara.h"
#include "items.h"
#include "../../trng/zPatchesTomb4.h"

namespace tomb4
{
	void TriggerUnderwaterExplosion(ITEM_INFO* item, long vehicle)
	{
		__try { throw __func__; } __finally {}
	}

	void undraw_shotgun(long weapon_type)
	{
		ITEM_INFO* item;

		item = &items[lara.weapon_item];

		if (lara.water_status == LW_SURFACE)
			item->goal_anim_state = 9;
		else
			item->goal_anim_state = 3;

		AnimateItem(item);

		if (item->status == ITEM_DEACTIVATED)
		{
			lara.gun_status = LG_NO_ARMS;
			lara.target = 0;
			lara.right_arm.lock = 0;
			lara.left_arm.lock = 0;
			KillItem(lara.weapon_item);
			lara.weapon_item = NO_ITEM;
			lara.right_arm.frame_number = 0;
			lara.left_arm.frame_number = 0;
		}
		else if (item->current_anim_state == 3)
		{
			trng::ValGlobale = trng::TrovaFrameArmaPesante();

			if (item->frame_number - anims[item->anim_number].frame_base == trng::ValGlobale)
				undraw_shotgun_meshes(weapon_type);
		}

		lara.right_arm.frame_base = anims[item->anim_number].frame_ptr;
		lara.left_arm.frame_base = lara.right_arm.frame_base;
		lara.right_arm.frame_number = item->frame_number - anims[item->anim_number].frame_base;
		lara.left_arm.frame_number = lara.right_arm.frame_number;
		lara.right_arm.anim_number = item->anim_number;
		lara.left_arm.anim_number = lara.right_arm.anim_number;
	}

	void undraw_shotgun_meshes(long weapon_type)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Lara1Gun(bool replace)
{
	ProcessInject(0x42B080, (unsigned int)tomb4::TriggerUnderwaterExplosion, false);
	ProcessInject(0x42AC40, (unsigned int)tomb4::undraw_shotgun, replace);
	ProcessInject(0x428B20, (unsigned int)tomb4::undraw_shotgun_meshes, false);
}
