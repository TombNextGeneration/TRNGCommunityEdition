#include "senet.h"
#include "../../inject.h"
#include "control.h"
#include "sound.h"
#include "items.h"
#include "../../trng/Tomb_NextGeneration.h"

namespace tomb4
{
	short (&senet_item)[6] = *reinterpret_cast<decltype(&senet_item)>(0x4BF2D8);
	char (&senet_piece)[6] = *reinterpret_cast<decltype(&senet_piece)>(0x7FE038);
	char (&senet_board)[17] = *reinterpret_cast<decltype(&senet_board)>(0x7FE220);
	char &last_throw = *reinterpret_cast<decltype(&last_throw)>(0x4BF2E4);
	long &SenetTargetX = *reinterpret_cast<decltype(&SenetTargetX)>(0x7FE0E4);
	long &SenetTargetZ = *reinterpret_cast<decltype(&SenetTargetZ)>(0x7FE0E8);
	char &piece_moving = *reinterpret_cast<decltype(&piece_moving)>(0x4ACBF8);

	void GameStixControl(short item_number)
	{
		ITEM_INFO* item;
		ITEM_INFO* item2;
		ITEM_INFO* piece;
		long piece_num, num, x, z, change;
		short room_number;

		item = &items[item_number];

		if (item->trigger_flags > -1)
		{
			if (item->hit_points == 100)
				SoundEffect(SFX_SPINNING_PUZZLE, &item->pos, SFX_DEFAULT);

			for (int i = 0; i < 4; i++)
			{
				if (item->hit_points < 100 - 2 * i)
				{
					item->item_flags[i] -= item->hit_points << 7;

					if (item->hit_points < 40 - 2 * i)
					{
						if (abs(item->item_flags[i]) < 4096 && item->trigger_flags & 1 << i)
							item->item_flags[i] = 0;
						else if ((item->item_flags[i] > 28672 || item->item_flags[i] < -28672) && !(item->trigger_flags & 1 << i))
							item->item_flags[i] = -0x8000;
					}
				}
			}

			item->hit_points--;

			if (!item->hit_points)
			{
				for (int i = 0; i < 3; i++)
					items[senet_item[i]].trigger_flags = 0;

				item->trigger_flags = -1;

				if (piece_moving == -1 && !last_throw)
				{
					RemoveActiveItem(item_number);
					item->status = ITEM_INACTIVE;
				}
			}

			return;
		}

		if (piece_moving > -1)
		{
			num = piece_moving >= 3 ? 2 : 1;	//>= 3 means it's not our piece
			piece = &items[senet_item[piece_moving]];
			piece->flags |= IFL_TRIGGERED;
			piece->after_death = 48;
			piece_num = senet_piece[piece_moving];

			if (piece_num == -1 || piece_num >= 5)
			{
				if (piece_num == -1)
					piece_num = 16;

				x = SenetTargetX + 1024;
				z = SenetTargetZ + ((piece_num - 5) << 10);
			}
			else
			{
				x = SenetTargetX + (num << 11) - 2048;
				z = SenetTargetZ + ((4 - piece_num) << 10);
			}

			if (abs(x - piece->pos.x_pos) < 128)
				piece->pos.x_pos = x;
			else if (x > piece->pos.x_pos)
				piece->pos.x_pos += 128;
			else
				piece->pos.x_pos -= 128;

			if (abs(z - piece->pos.z_pos) < 128)
				piece->pos.z_pos = z;
			else if (z > piece->pos.z_pos)
				piece->pos.z_pos += 128;
			else
				piece->pos.z_pos -= 128;

			room_number = piece->room_number;
			GetFloor(piece->pos.x_pos, piece->pos.y_pos - 32, piece->pos.z_pos, &room_number);

			if (piece->room_number != room_number)
				ItemNewRoom(senet_item[piece_moving], room_number);

			if (x == piece->pos.x_pos && z == piece->pos.z_pos)
			{
				piece->after_death = 0;

				if (piece_num == 16)
				{
					if (num == 1)
					{
						ShockwaveExplosion(piece, 0x6060E0, -32);
						ShockwaveExplosion(piece, 0x6060E0, 48);
					}
					else
					{
						ShockwaveExplosion(piece, 0xFF8020, -32);
						ShockwaveExplosion(piece, 0xFF8020, 48);
					}

					KillItem(senet_item[piece_moving]);

					if (CheckSenetWinner(num))
					{
						for (int i = 0; i < level_items; i++)
						{
							item2 = &items[i];

							if (item2->object_number >= GAME_PIECE1 && item2->object_number <= WHEEL_OF_FORTUNE)
							{
								item2->flags |= IFL_INVISIBLE | IFL_CODEBITS;
								RemoveActiveItem((short)i);
								item2->status = ITEM_INACTIVE;
								item2->after_death = !trng::GlobTomb4.pBaseCustomize->TestKeepNemiciMorti;
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < 6; i++)
					{
						if (piece_moving != i)
						{
							piece = &items[senet_item[i]];

							if (x == piece->pos.x_pos && z == piece->pos.z_pos)
							{
								if (num == 1)
									ShockwaveExplosion(piece, 0xFF8020, -64);
								else
									ShockwaveExplosion(piece, 0x6060E0, -64);

								piece->pos.x_pos = SenetTargetX - (num << 12) + 7168;
								piece->pos.z_pos = SenetTargetZ + ((i % 3) << 10);
								room_number = piece->room_number;
								GetFloor(piece->pos.x_pos, piece->pos.y_pos - 32, piece->pos.z_pos, &room_number);

								if (piece->room_number != room_number)
									ItemNewRoom(senet_item[i], room_number);

								if (num == 1)
									ShockwaveExplosion(piece, 0xFF8020, -64);
								else
									ShockwaveExplosion(piece, 0x6060E0, -64);
							}
						}
					}
				}

				if (!last_throw)
				{
					RemoveActiveItem(item_number);
					piece->status = ITEM_INACTIVE;
				}

				piece_moving = -1;
			}

			return;
		}

		if (last_throw == -1)
		{
			ThrowSticks(item);

			for (int i = 3; i < 6; i++)
			{
				MakeMove(i, last_throw);

				if (last_throw == -1 || !last_throw)
					break;
			}

			if (!last_throw || last_throw == 6)
				last_throw = -1;
			else
				last_throw = 0;
		}
		else if (!last_throw)	//keep an eye on me uwu
		{
			ThrowSticks(item);
			change = 0;

			for (int i = 0; i < 3; i++)
			{
				if (senet_piece[i] != -1 && last_throw && senet_piece[i] + last_throw < 17 && !(senet_board[senet_piece[i] + last_throw] & 1))
					change = 1;
			}

			if (!change)
			{
				if (last_throw == 6)
					last_throw = 0;
				else
					last_throw = -1;
			}
		}
	}

	void ShockwaveExplosion(ITEM_INFO* item, ulong col, long speed)
	{
		__try { throw __func__; } __finally {}
	}

	long CheckSenetWinner(long ourPiece)
	{
		__try { throw __func__; } __finally {}
	}

	void ThrowSticks(ITEM_INFO* item)
	{
		__try { throw __func__; } __finally {}
	}

	void MakeMove(long piece, long displacement)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Senet(bool replace)
{
	ProcessInject(0x40F540, (unsigned int)tomb4::GameStixControl, replace);
	ProcessInject(0x41CE70, (unsigned int)tomb4::ShockwaveExplosion, false);
	ProcessInject(0x40F230, (unsigned int)tomb4::CheckSenetWinner, false);
	ProcessInject(0x40FAE0, (unsigned int)tomb4::ThrowSticks, false);
	ProcessInject(0x40F3E0, (unsigned int)tomb4::MakeMove, false);
}
