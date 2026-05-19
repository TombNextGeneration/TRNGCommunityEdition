#include "newinv.h"
#include "../../inject.h"
#include "lara.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	static char &CurrentShotGunAmmoType = *reinterpret_cast<decltype(&CurrentShotGunAmmoType)>(0x4BF28A);
	static char &CurrentGrenadeGunAmmoType = *reinterpret_cast<decltype(&CurrentGrenadeGunAmmoType)>(0x4BF27C);
	static char &CurrentCrossBowAmmoType = *reinterpret_cast<decltype(&CurrentCrossBowAmmoType)>(0x4BF29E);

	long &GLOBAL_lastinvitem = *reinterpret_cast<decltype(&GLOBAL_lastinvitem)>(0x4AC05C);
	short (&options_table)[NUM_INVOBJ] = *reinterpret_cast<decltype(&options_table)>(0x4AC9B8);
	INVOBJ (&inventry_objects_list)[NUM_INVOBJ] = *reinterpret_cast<decltype(&inventry_objects_list)>(0x4AC068);
	long &GLOBAL_inventoryitemchosen = *reinterpret_cast<decltype(&GLOBAL_inventoryitemchosen)>(0x4AC064);
	long &GLOBAL_enterinventory = *reinterpret_cast<decltype(&GLOBAL_enterinventory)>(0x4AC060);
	long &InventoryActive = *reinterpret_cast<decltype(&InventoryActive)>(0x4BF2A0);

	long S_CallInventory2()
	{
		__try { throw __func__; } __finally {}
	}

	long convert_obj_to_invobj(short obj)
	{
		__try { throw __func__; } __finally {}
	}

	void update_laras_weapons_status()
	{
		char crossbow_ammo_type;

		if (lara.shotgun_type_carried & 1)
		{
			lara.shotgun_type_carried &= 0xC7;

			if (CurrentShotGunAmmoType)
				lara.shotgun_type_carried |= 0x10;
			else
				lara.shotgun_type_carried |= 0x8;
		}

		if (lara.grenade_type_carried & 1)
		{
			lara.grenade_type_carried &= 0xC7;

			if (!CurrentGrenadeGunAmmoType)
				lara.grenade_type_carried |= 0x8;
			else if (CurrentGrenadeGunAmmoType == 1)
				lara.grenade_type_carried |= 0x10;
			else if (CurrentGrenadeGunAmmoType == 2)
				lara.grenade_type_carried |= 0x20;
		}

		if (lara.crossbow_type_carried & 1)
		{
			lara.crossbow_type_carried &= 0xC7;
			crossbow_ammo_type = CurrentCrossBowAmmoType;

			// se c'e' patch arpione e due tipi di munizione
			// correggere l'enventuale 1 facendolo diventare 2
			if (trng::BaseCustomize.BaseHarpoon.ArpioneFlags & trng::HRP_DOUBLE_AMMO && crossbow_ammo_type == 1)
				crossbow_ammo_type = 2;

			if (!crossbow_ammo_type)
				lara.crossbow_type_carried |= 0x8;
			else if (crossbow_ammo_type == 1)
				lara.crossbow_type_carried |= 0x10;
			else if (crossbow_ammo_type == 2)
				lara.crossbow_type_carried |= 0x20;
		}
	}
}

void Inject_Newinv(bool replace)
{
	ProcessInject(0x43B0F0, (unsigned int)tomb4::S_CallInventory2, false);
	ProcessInject(0x43E950, (unsigned int)tomb4::convert_obj_to_invobj, false);
	ProcessInject(0x43DAE0, (unsigned int)tomb4::update_laras_weapons_status, replace);
}
