#include "newinv.h"
#include "../../inject.h"
#include "lara.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../plugin/classicinventory/trng.h"
#include "../../plugin/classicinventory/Plugin_ClassicInventory.h"

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

	void DEL_picked_up_object(short objnum)
	{
		trng::StrBaseCustomize *pCust;
		long lf;

		if (plugin::classicinventory::Trng.IdMyPlugin != -1 && plugin::classicinventory::picked_up_object(objnum))
			return;

		pCust = trng::GlobTomb4.pBaseCustomize;

		switch (objnum)
		{
		case WATERSKIN1_EMPTY:
			lara.small_water_skin = 1;
			break;

		case WATERSKIN2_EMPTY:
			lara.big_water_skin = 1;
			break;

		case UZI_ITEM:

			if (!(lara.uzis_type_carried & 1))
				lara.uzis_type_carried = 9;

			if (lara.num_uzi_ammo != -1)
				lara.num_uzi_ammo += pCust->AmmoUZI.PickupRegalo;

			break;

		case PISTOLS_ITEM:

			if (!(lara.pistols_type_carried & 1))
				lara.pistols_type_carried = 9;

			lara.num_pistols_ammo = pCust->AmmoPistols.PickupRegalo;
			break;

		case SHOTGUN_ITEM:

			if (!(lara.shotgun_type_carried & 1))
				lara.shotgun_type_carried = 9;

			if (lara.num_shotgun_ammo1 != -1)
				lara.num_shotgun_ammo1 += pCust->AmmoFucileNormale.PickupRegalo;

			break;

		case SIXSHOOTER_ITEM:

			if (!(lara.sixshooter_type_carried & 1))
				lara.sixshooter_type_carried = 9;

			if (lara.num_revolver_ammo != -1)
				lara.num_revolver_ammo += pCust->AmmoRevolver.PickupRegalo;

			break;

		case CROSSBOW_ITEM:

			if (!(lara.crossbow_type_carried & 1))
				lara.crossbow_type_carried = 9;

			if (lara.num_crossbow_ammo1 != -1)
				lara.num_crossbow_ammo1 += pCust->AmmoBalestraNormali.PickupRegalo;

			break;

		case GRENADE_GUN_ITEM:

			if (!(lara.grenade_type_carried & 1))
				lara.grenade_type_carried = 9;

			if (lara.num_grenade_ammo1 != -1)
				lara.num_grenade_ammo1 += pCust->AmmoGranateNormali.PickupRegalo;

			break;

		case SHOTGUN_AMMO2_ITEM:

			if (lara.num_shotgun_ammo2 != -1)
				lara.num_shotgun_ammo2 += pCust->AmmoFucilePotenziate.Pickup;

			break;

		case GRENADE_GUN_AMMO1_ITEM:

			if (lara.num_grenade_ammo1 != -1)
				lara.num_grenade_ammo1 += pCust->AmmoGranateNormali.Pickup;

			break;

		case GRENADE_GUN_AMMO2_ITEM:

			if (lara.num_grenade_ammo2 != -1)
				lara.num_grenade_ammo2 += pCust->AmmoGranateEsplosive.Pickup;

			break;

		case GRENADE_GUN_AMMO3_ITEM:

			if (lara.num_grenade_ammo3 != -1)
				lara.num_grenade_ammo3 += pCust->AmmoGranateLuminose.Pickup;

			break;

		case CROSSBOW_AMMO2_ITEM:

			if (lara.num_crossbow_ammo2 != -1)
				lara.num_crossbow_ammo2 += pCust->AmmoBalestraVelenose.Pickup;

			break;

		case CROSSBOW_AMMO3_ITEM:

			if (lara.num_crossbow_ammo3 != -1)
				lara.num_crossbow_ammo3 += pCust->AmmoBalestraEsplosive.Pickup;

			break;

		case FLARE_INV_ITEM:

			if (lara.num_flares != -1)
				lara.num_flares += 12;

			break;

		case LASERSIGHT_ITEM:
			lf = (lara.pistols_type_carried | lara.uzis_type_carried | lara.shotgun_type_carried | lara.sixshooter_type_carried |
				lara.crossbow_type_carried | lara.grenade_type_carried) & 4;

			if (!lf)
				lara.lasersight = 1;

			break;

		case BIGMEDI_ITEM:

			if (lara.num_large_medipack != -1)
				lara.num_large_medipack++;

			break;

		case SMALLMEDI_ITEM:

			if (lara.num_small_medipack != -1)
				lara.num_small_medipack++;

			break;

		case BINOCULARS_ITEM:
			lara.binoculars = 1;
			break;

		case CROWBAR_ITEM:
			lara.crowbar = 1;
			break;

		case CLOCKWORK_BEETLE:
			lara.mechanical_scarab |= 1;
			break;

		case CLOCKWORK_BEETLE_COMBO1:
			lara.mechanical_scarab |= 2;
			break;

		case CLOCKWORK_BEETLE_COMBO2:
			lara.mechanical_scarab |= 4;
			break;

		case EXAMINE1:
			lara.examine1 = 1;
			break;

		case EXAMINE2:
			lara.examine2 = 1;
			break;

		case EXAMINE3:
			lara.examine3 = 1;
			break;

		default:

			trng::ValEsito = trng::AnalisiScatolaMunizioni(objnum);

			if (trng::ValEsito)
				break;

			if (objnum >= PUZZLE_ITEM1_COMBO1 && objnum <= PUZZLE_ITEM8_COMBO2)
				lara.puzzleitemscombo |= 1 << (objnum - PUZZLE_ITEM1_COMBO1);
			else if (objnum >= PUZZLE_ITEM1 && objnum <= PUZZLE_ITEM12)
				lara.puzzleitems[objnum - PUZZLE_ITEM1]++;
			else if (objnum >= KEY_ITEM1_COMBO1 && objnum <= KEY_ITEM8_COMBO2)
				lara.keyitemscombo |= 1 << (objnum - KEY_ITEM1_COMBO1);
			else if (objnum >= KEY_ITEM1 && objnum <= KEY_ITEM12)
				lara.keyitems |= 1 << (objnum - KEY_ITEM1);
			else if (objnum >= PICKUP_ITEM1_COMBO1 && objnum <= PICKUP_ITEM4_COMBO2)
				lara.pickupitemscombo |= 1 << (objnum - PICKUP_ITEM1_COMBO1);
			else if (objnum >= PICKUP_ITEM1 && objnum <= PICKUP_ITEM4)
				lara.pickupitems |= 1 << (objnum - PICKUP_ITEM1);
			else if (objnum >= QUEST_ITEM1 && objnum <= QUEST_ITEM6)
				lara.questitems |= 1 << (objnum - QUEST_ITEM1);

			break;
		}
	}
}

void Inject_Newinv(bool replace)
{
	ProcessInject(0x43B0F0, (unsigned int)tomb4::S_CallInventory2, false);
	ProcessInject(0x43E950, (unsigned int)tomb4::convert_obj_to_invobj, false);
	ProcessInject(0x43DAE0, (unsigned int)tomb4::update_laras_weapons_status, replace);
	ProcessInject(0x43E380, (unsigned int)tomb4::DEL_picked_up_object, replace);
}
