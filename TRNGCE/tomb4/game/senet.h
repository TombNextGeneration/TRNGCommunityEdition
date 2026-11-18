#pragma once
#include "../types.h"

namespace tomb4
{
	extern short (&senet_item)[6];
	extern char (&senet_piece)[6];
	extern char (&senet_board)[17];
	extern char &last_throw;
	extern long &SenetTargetX;
	extern long &SenetTargetZ;
	extern char &piece_moving;

	void GameStixControl(short item_number);
	void ShockwaveExplosion(ITEM_INFO* item, ulong col, long speed);
	long CheckSenetWinner(long ourPiece);
	void ThrowSticks(ITEM_INFO* item);
	void MakeMove(long piece, long displacement);
}

void Inject_Senet(bool replace);
