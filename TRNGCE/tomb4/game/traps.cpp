#include "traps.h"
#include "../../inject.h"
#include "control.h"
#include "../../trng/zPatchesTomb4.h"
#include "collide.h"
#include "sphere.h"
#include "lara.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../specific/input.h"
#include "../../trng/zRoomEditor.h"

namespace tomb4
{
	char (&LibraryTab)[8] = *reinterpret_cast<decltype(&LibraryTab)>(0x4BF1D8);

	long OnTwoBlockPlatform(ITEM_INFO* item, long x, long z)
	{
		__try { throw __func__; } __finally {}
	}

	void LaraBurn()
	{
		__try { throw __func__; } __finally {}
	}

	void OpenTrapDoor(ITEM_INFO* item)
	{
		ROOM_INFO* r;
		FLOOR_INFO* floor;
		ushort pitsky;

		trng::ControllaTrapDoor((trng::StrItemTr4*)item);
		pitsky = item->item_flags[3];
		r = &room[item->room_number];
		floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10)];

		if (item->pos.y_pos == r->minfloor)
		{
			floor->pit_room = pitsky & 0xFF;
			r = &room[floor->pit_room];
			floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10)];
			floor->sky_room = pitsky >> 8;
		}
		else
		{
			floor->sky_room = pitsky >> 8;
			r = &room[floor->sky_room];
			floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10)];
			floor->pit_room = pitsky & 0xFF;
		}

		item->item_flags[2] = 0;
	}

	void RollingBallCollision(short item_number, ITEM_INFO* l, COLL_INFO* coll)
	{
		ITEM_INFO* item;
		long touchedBits;

		item = &items[item_number];

		if (!TestBoundsCollide(item, l, coll->radius))
			return;

		// flag spinta inclinato o spinta sempre
		if (item->trigger_flags & (trng::RB_PUSHING_ACTIVATION | trng::RB_PUSHING_MULTIPLE))
		{
			// se e' attivo un idnice di rollingball da non ferire
			// ed e' questo uscire subito con eax=0
			if (trng::GlobTomb4.TestNoDamageRollingBallIndex == item_number)
				return;

			// deve essere fermo
			if (!(item->item_flags[0] | item->item_flags[1]))
			{
				// se animazione e' gia' quella di spinta uscire con eax=0
				if (trng::BaseCustomize.RollingBallPush.Animation == lara_item->anim_number)
					return;

				// se lara ha in mano qualcosa e il suo state id e' diverso
				// da 2 uscire
				if (lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH && input & IN_ACTION)
				{
					// se ha oggetti in mano rifiutare
					if (lara.gun_status == LG_NO_ARMS)
					{
						// e' richiesto che il rolling
						// non sia ancora stato attivato
						if (!(item->trigger_flags & trng::RB_PUSHING_ACTIVATION) || (item->flags & IFL_CODEBITS) != IFL_CODEBITS)
						{
							// ok non e' ancora stato attivato
							// lara e' feerma non l'animazione giusta ecc. ecc.
							trng::RetValue = trng::ControllaSpintaRollingBall((trng::StrItemTr4*)item, item_number);

							if (trng::RetValue & 0xFF)
								return;
						}
					}
				}
			}
		}

		touchedBits = TestCollision(item, l);

		if (trng::GlobTomb4.StatusNG & trng::SNG_IMMORTAL_LARA)
		{
			// e' immortale forzare sempre come se non ci fosse contatto
			touchedBits = 0;
		}

		if (!touchedBits)
			return;

		if (TriggerActive(item) && (item->item_flags[0] || item->fallspeed))
		{
			lara_item->anim_number = ANIM_RBALL_DEATH;
			lara_item->frame_number = anims[ANIM_RBALL_DEATH].frame_base;
			lara_item->current_anim_state = AS_DEATH;
			lara_item->goal_anim_state = AS_DEATH;
			lara_item->gravity_status = 0;
		}
		else
			ObjectCollision(item_number, l, coll);
	}
}

void Inject_Traps(bool replace)
{
	ProcessInject(0x415A10, (unsigned int)tomb4::OnTwoBlockPlatform, false);
	ProcessInject(0x414D90, (unsigned int)tomb4::LaraBurn, false);
	ProcessInject(0x4135F0, (unsigned int)tomb4::OpenTrapDoor, replace);
	ProcessInject(0x415530, (unsigned int)tomb4::RollingBallCollision, replace);
}
