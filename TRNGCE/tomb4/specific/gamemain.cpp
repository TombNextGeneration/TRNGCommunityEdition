#include "gamemain.h"
#include "../../inject.h"
#include "../game/savegame.h"
#include "../../trng/zPatchesTomb4.h"
#include "function_stubs.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/zRoomEditor.h"

namespace tomb4
{
	THREAD &MainThread = *reinterpret_cast<decltype(&MainThread)>(0x5339D4);
	char (&savegame_format_string)[256] = *reinterpret_cast<decltype(&savegame_format_string)>(0x4757DE);

	long S_SaveGame(long slot_num)
	{
		__try { throw __func__; } __finally {}
	}

	long S_LoadGame(long slot_num)
	{
		HANDLE file;
		ulong bytes;
		long value;
		char buffer[80];

		wsprintf(buffer, savegame_format_string, slot_num);

		// patch per mandare in file log anche il none del
		// savegame caricato

		// viene usata anche per caricare ng header
		// di file savegame
		trng::CaricaSavegame(buffer);
		Log(5, "FileOpen - %s", buffer);

		file = CreateFile(buffer, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (file != INVALID_HANDLE_VALUE)
		{
			(void)ReadFile(file, buffer, 75, &bytes, 0);
			(void)ReadFile(file, &value, sizeof(long), &bytes, 0);
			(void)ReadFile(file, &value, sizeof(long), &bytes, 0);
			(void)ReadFile(file, &value, sizeof(long), &bytes, 0);

			if (trng::MyGlobPrivate.TestNG_NoScript)
			{
				(void)ReadFile(file, &savegame, sizeof(SAVEGAME_INFO), &bytes, 0);
				CloseHandle(file);
			}
			else
			{
				// caricare primo blocco
				trng::RetValue = (DWORD)&bytes;
				(void)ReadFile(file, &savegame, 457, &bytes, 0);

				// adesso blocco moveable esteso
				(void)ReadFile(file, trng::DatiMoveables, 0x7DE0, (ulong*)trng::RetValue, 0);

				// fine blocco esteso

				trng::FineLoadSavegame(file);
			}

			return 1;
		}

		return 0;
	}
}

__declspec(naked) static void** Inject_Gamemain_savegame_format_string() { __asm lea eax, [tomb4::savegame_format_string] __asm ret }

void Inject_Gamemain(bool replace)
{
	IndirectReferenceInject(Inject_Gamemain_savegame_format_string());

	ProcessInject(0x475630, (unsigned int)tomb4::S_SaveGame, false);
	ProcessInject(0x4757D0, (unsigned int)tomb4::S_LoadGame, replace);
}
