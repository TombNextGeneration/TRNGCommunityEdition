#include "../../inject.h"
#include "types.h"
#include "objects.h"
#include "lara.h"
#include "enums.h"
#include "control.h"
#include "newinv.h"
#include "traps.h"
#include "switch.h"
#include "../specific/file.h"
#include "camera.h"
#include "spotcam.h"
#include "senet.h"
#include "../specific/function_stubs.h"
#include "scarab.h"
#include "gameflow.h"
#include "voncroy.h"
#include "rope.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zPatchesTomb4.h"
#include "../../flep/patches/vehicles/main.h"

namespace tomb4
{
	static char* &SGpoint = *reinterpret_cast<decltype(&SGpoint)>(0x4BF5A4);
	static long &SGcount = *reinterpret_cast<decltype(&SGcount)>(0x4BF5A8);

	void WriteSG(void* pointer, long size)
	{
		char* data;

		SGcount += size;

		for (data = (char*)pointer; size > 0; size--)
			*SGpoint++ = *data++;
	}

	void ReadSG(void* pointer, long size)
	{
		char* data;

		SGcount += size;

		for (data = (char*)pointer; size > 0; size--)
			*data++ = *SGpoint++;
	}

	static bool NemicoMorto(ITEM_INFO* item)
	{
		short object_number;

		// il nemico sarebbe morto
		// vedere se e' attiva patch per mantenere vivi nemici
		if (!trng::BaseCustomize.TestKeepNemiciMorti)
			return true;

		// la patch e' attiva
		// se lo slot pero' non e' di creatura considerarlo morto
		object_number = trng::ConvertiSlotAssigned(item->object_number);

		if (object_number < (long)object_types::SKELETON || object_number > (long)object_types::AHMET_MIP)
			return true;

		// se vitalita 0xc000 allora morto con esplosione
		if (item->hit_points == -16384)
			return true;

		// se campo di mesh visdibili mancno le prime 8 mesh
		// allora considerarlo morto in modo definitivo
		if (!((uchar)item->mesh_bits))
			return true;

		// vedere se questo nemico era stato ucciso mediante esplosione
		if (trng::IsNemicoEsploso(item->object_number))
			return true;

		return false;
	}

	void SaveLevelData(long FullSave)
	{
		ITEM_INFO* item;
		ROOM_INFO* r;
		OBJECT_INFO* obj;
		MESH_INFO* mesh;
		CREATURE_INFO* creature;
		ulong flags;
		long k;
		ushort packed;
		short pos, word;
		uchar byte;
		char lflags;

		WriteSG(&FmvSceneTriggered, sizeof(long));
		WriteSG(&GLOBAL_lastinvitem, sizeof(long));
		flags = 0;

		for (int i = 0; i < 32; i++)
		{
			if (flip_stats[i])
				flags |= (1 << i);
		}

		WriteSG(&flags, sizeof(ulong));

		for (int i = 0; i < 32; i++)
		{
			word = short(flipmap[i] >> 8);
			WriteSG(&word, sizeof(short));
		}

		WriteSG(&flipeffect, sizeof(long));
		WriteSG(&fliptimer, sizeof(long));
		WriteSG(&flip_status, sizeof(long));
		WriteSG(cd_flags, 128);
		WriteSG(&CurrentAtmosphere, sizeof(uchar));
		word = 0;
		k = 0;

		for (int i = 0; i < number_rooms; i++)
		{
			r = &room[i];

			for (int j = 0; j < r->num_meshes; j++)
			{
				mesh = &r->mesh[j];

				// salva in savegame il seguene static se rientra nel range degli shatter
				if (mesh->static_number >= trng::BaseCustomize.ShatterInizio && mesh->static_number <= trng::BaseCustomize.ShatterFine)
				{
					// si, e' uno shatter
					word |= ((mesh->Flags & 1) << k);
					k++;

					if (k == 16)
					{
						WriteSG(&word, sizeof(short));
						k = 0;
						word = 0;
					}
				}
			}
		}

		if (k)
			WriteSG(&word, sizeof(short));

		byte = 0;

		for (int i = 0; i < 8; i++)
			byte |= LibraryTab[i] << i;

		WriteSG(&byte, sizeof(uchar));
		WriteSG(&CurrentSequence, sizeof(uchar));
		byte = 0;

		for (int i = 0; i < 6; i++)
			byte |= SequenceUsed[i] << i;

		WriteSG(&byte, sizeof(uchar));
		WriteSG(Sequences, 3);

		for (int i = 0; i < number_cameras; i++)
			WriteSG(&camera.fixed[i].flags, sizeof(short));

		for (int i = 0; i < number_spotcams; i++)
			WriteSG(&SpotCam[i].flags, sizeof(short));

		for (int i = 0; i < level_items; i++)
		{
			item = &items[i];
			obj = &objects[item->object_number];
			packed = 0;

			// se livello trasparenza e' minore di 128
			// mantenerlo
			if ((item->after_death > 127 && (item->object_number < (long)object_types::GAME_PIECE1 || item->object_number > (long)object_types::ENEMY_PIECE)) || item->flags & (long)ITEM_FLAGS::IFL_CLEARBODY && NemicoMorto(item))
			{
				packed = 0x2000;
				WriteSG(&packed, sizeof(ushort));
			}
			else
			{
				// e' lara, salvare l'offset nel quale si sta per salvsre
				// struttura lara
				if (item->object_number == (long)object_types::LARA)
					trng::OffsetPosLara = SGcount;

				// e' l'item braciere usato per enigna di versa petrolio e poi
				// incendia
				// se +34h diverso da zero forzare il salvataggio dei
				// dati
				if (item->object_number == (long)object_types::ELEMENT_PUZZLE && item->item_flags[0] || item->flags & ((long)ITEM_FLAGS::IFL_CODEBITS | (long)ITEM_FLAGS::IFL_INVISIBLE | (long)ITEM_FLAGS::IFL_TRIGGERED) || item->object_number == (long)object_types::LARA && FullSave)
				{
					packed = 0x8000;

					if (item->pos.x_rot)
						packed |= 1;

					if (item->pos.z_rot)
						packed |= 2;

					if (item->pos.x_pos & 1)
						packed |= 4;

					if (item->pos.y_pos & 1)
						packed |= 8;

					if (item->pos.z_pos & 1)
						packed |= 0x10;

					if (item->speed)
						packed |= 0x20;

					if (item->fallspeed)
						packed |= 0x40;

					if (item->item_flags[0])
						packed |= 0x80;

					if (item->item_flags[1])
						packed |= 0x100;

					if (item->item_flags[2])
						packed |= 0x200;

					if (item->item_flags[3])
						packed |= 0x400;

					if (item->timer)
						packed |= 0x800;

					if (item->trigger_flags)
						packed |= 0x1000;

					if (obj->save_hitpoints && item->hit_points != obj->hit_points)
						packed |= 0x4000;

					WriteSG(&packed, sizeof(ushort));

					if (obj->save_position)
					{
						pos = short(item->pos.x_pos >> 1);
						WriteSG(&pos, sizeof(short));

						pos = short(item->pos.y_pos >> 1);
						WriteSG(&pos, sizeof(short));

						pos = short(item->pos.z_pos >> 1);
						WriteSG(&pos, sizeof(short));

						byte = (uchar)item->room_number;
						WriteSG(&byte, sizeof(uchar));

						WriteSG(&item->pos.y_rot, sizeof(short));

						if (packed & 1)
							WriteSG(&item->pos.x_rot, sizeof(short));

						if (packed & 2)
							WriteSG(&item->pos.z_rot, sizeof(short));

						if (packed & 0x20)
							WriteSG(&item->speed, sizeof(short));

						if (packed & 0x40)
							WriteSG(&item->fallspeed, sizeof(short));
					}

					if (obj->save_anim)
					{
						byte = (uchar)item->current_anim_state;
						WriteSG(&byte, sizeof(uchar));

						byte = (uchar)item->goal_anim_state;
						WriteSG(&byte, sizeof(uchar));

						byte = (uchar)item->required_anim_state;
						WriteSG(&byte, sizeof(uchar));

						if (item->object_number != (long)object_types::LARA)
						{
							byte = item->anim_number - obj->anim_index;
							WriteSG(&byte, sizeof(uchar));
						}
						else
							WriteSG(&item->anim_number, sizeof(short));

						WriteSG(&item->frame_number, sizeof(short));
					}

					if (packed & 0x4000)
						WriteSG(&item->hit_points, sizeof(short));

					if (obj->save_flags)
					{
						flags = (ushort)item->flags;
						flags |= item->active << 16;
						flags |= item->status << 17;
						flags |= item->gravity_status << 19;
						flags |= item->hit_status << 20;
						flags |= item->collidable << 21;
						flags |= item->looked_at << 22;
						flags |= item->dynamic_light << 23;
						flags |= item->poisoned << 24;
						flags |= item->ai_bits << 25;
						flags |= item->really_active << 30;

						if (obj->intelligent && item->data)
							flags |= 0x80000000;

						WriteSG(&flags, sizeof(ulong));

						if (packed & 0x80)
							WriteSG(&item->item_flags[0], sizeof(short));

						if (packed & 0x100)
							WriteSG(&item->item_flags[1], sizeof(short));

						if (packed & 0x200)
							WriteSG(&item->item_flags[2], sizeof(short));

						if (packed & 0x400)
							WriteSG(&item->item_flags[3], sizeof(short));

						if (packed & 0x800)
							WriteSG(&item->timer, sizeof(short));

						if (packed & 0x1000)
							WriteSG(&item->trigger_flags, sizeof(short));

						if (obj->intelligent)
							WriteSG(&item->carried_item, sizeof(short));

						if (flags & 0x80000000)
						{
							creature = (CREATURE_INFO*)item->data;

							if (creature->enemy)
								creature->enemy = (ITEM_INFO*)((long)creature->enemy - (long)malloc_buffer);

							WriteSG(item->data, 22);

							if (creature->enemy)
								creature->enemy = (ITEM_INFO*)((long)creature->enemy + (long)malloc_buffer);

							WriteSG(&creature->ai_target.object_number, sizeof(short));
							WriteSG(&creature->ai_target.room_number, sizeof(short));
							WriteSG(&creature->ai_target.box_number, sizeof(ushort));
							WriteSG(&creature->ai_target.flags, sizeof(short));
							WriteSG(&creature->ai_target.trigger_flags, sizeof(short));
							WriteSG(&creature->ai_target.pos, sizeof(PHD_3DPOS));

							lflags = creature->LOT.can_jump;
							lflags |= creature->LOT.can_monkey << 1;
							lflags |= creature->LOT.is_amphibious << 2;
							lflags |= creature->LOT.is_jumping << 3;
							lflags |= creature->LOT.is_monkeying << 4;
							WriteSG(&lflags, sizeof(char));
						}
					}

					if (obj->save_mesh)
					{
						WriteSG(&item->mesh_bits, sizeof(ulong));
						WriteSG(&item->meshswap_meshbits, sizeof(ulong));
					}

					flep::SaveVehicle(item);

					if (item->object_number == (long)object_types::MOTORBIKE)
						WriteSG(item->data, sizeof(BIKEINFO));

					if (item->object_number == (long)object_types::JEEP)
						WriteSG(item->data, sizeof(JEEPINFO));
				}
				else
					WriteSG(&packed, sizeof(ushort));
			}
		}

		if (objects[(long)object_types::WHEEL_OF_FORTUNE].loaded)
		{
			WriteSG(senet_item, sizeof(short) * 6);
			WriteSG(senet_piece, sizeof(char) * 6);
			WriteSG(senet_board, sizeof(char) * 17);
			WriteSG(&last_throw, sizeof(char));
			WriteSG(&SenetTargetX, sizeof(long));
			WriteSG(&SenetTargetZ, sizeof(long));
			WriteSG(&piece_moving, sizeof(char));
		}

		if (FullSave)
		{
			byte = 0;

			// conta i nuovi item creati da salvare in savegame
			if (level_items < 1024)
				byte = (uchar)trng::ContaItemCreatiDaSalvare();

			WriteSG(&byte, sizeof(uchar));

			// salva gli item creati in savegame
			if (level_items < 1024)
				trng::SalvaItemCreati();

			if (objects[(long)object_types::LITTLE_BEETLE].loaded)
			{
				byte = 0;

				for (int j = 0; j < 128; j++)
				{
					if (Scarabs[j].On == 1)
						byte++;
				}

				WriteSG(&byte, sizeof(uchar));

				for (int j = 0; j < 128; j++)
				{
					if (Scarabs[j].On == 1)
					{
						word = Scarabs[j].room_number << 8;

						if (Scarabs[j].pos.x_pos & 1)
							word |= 1;

						if (Scarabs[j].pos.y_pos & 1)
							word |= 2;

						if (Scarabs[j].pos.z_pos & 1)
							word |= 4;

						if (Scarabs[j].pos.x_rot)
							word |= 8;

						WriteSG(&word, sizeof(short));

						pos = short(Scarabs[j].pos.x_pos >> 1);
						WriteSG(&pos, sizeof(short));

						pos = short(Scarabs[j].pos.y_pos >> 1);
						WriteSG(&pos, sizeof(short));

						pos = short(Scarabs[j].pos.z_pos >> 1);
						WriteSG(&pos, sizeof(short));

						WriteSG(&Scarabs[j].pos.y_rot, sizeof(short));

						if (word & 8)
							WriteSG(&Scarabs[j].pos.x_rot, sizeof(short));
					}
				}
			}

			byte = 0;
			item = &items[level_items];

			for (int i = level_items; i < 1024; i++)
			{
				if (item->active && item->object_number == (long)object_types::CLOCKWORK_BEETLE)
				{
					byte = 1;
					break;
				}

				item++;
			}

			WriteSG(&byte, sizeof(uchar));

			if (byte)
			{
				WriteSG(&item->pos, sizeof(PHD_3DPOS));
				WriteSG(item->item_flags, sizeof(short) * 4);
			}

			if (gfCurrentLevel == 1)
			{
				flags = 0;

				for (int i = 0; i < 64; i++)
				{
					if (VonCroyCutFlags[i])
						flags |= 1 << (i & 0xF);

					if ((i & 0xF) == 0xF)
					{
						WriteSG(&flags, 2);
						flags = 0;
					}
				}
			}

			WriteSG(RopeList, 5 * sizeof(ROPE_STRUCT));
			CurrentPendulum.Rope = (ROPE_STRUCT*)((char*)CurrentPendulum.Rope - (char*)RopeList);

			WriteSG(&CurrentPendulum, sizeof(PENDULUM));
			CurrentPendulum.Rope = (ROPE_STRUCT*)((char*)CurrentPendulum.Rope + (long)RopeList);
		}
	}
}

void Inject_Savegame(bool replace)
{
	ProcessInject(0x45A3C0, (unsigned int)tomb4::WriteSG, replace);
	ProcessInject(0x45B150, (unsigned int)tomb4::ReadSG, replace);
	ProcessInject(0x459880, (unsigned int)tomb4::SaveLevelData, replace);
}
