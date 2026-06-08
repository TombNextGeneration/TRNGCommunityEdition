#include "audio.h"
#include "../../inject.h"
#include "function_stubs.h"
#include "../../trng/zPatchesTomb4.h"
#include "LoadSave.h"
#include "../../trng/Tomb_NextGeneration.h"
#include "../../trng/trng_flipeffects.h"
#include "../game/control.h"

namespace tomb4
{
	static HANDLE (&NotifyEventHandles)[2] = *reinterpret_cast<decltype(&NotifyEventHandles)>(0x4BFCD0);
	static long &NotifySize = *reinterpret_cast<decltype(&NotifySize)>(0x4BFCFC);
	static LPDIRECTSOUNDNOTIFY &DSNotify = *reinterpret_cast<decltype(&DSNotify)>(0x4BFD2C);
	static LPDIRECTSOUNDBUFFER &DSBuffer = *reinterpret_cast<decltype(&DSBuffer)>(0x4BFD28);
	static CRITICAL_SECTION &audio_cs = *reinterpret_cast<decltype(&audio_cs)>(0x4BFCDC);
	static long &audio_counter = *reinterpret_cast<decltype(&audio_counter)>(0x4BFD44);

	long &XATrack = *reinterpret_cast<decltype(&XATrack)>(0x4B01C4);
	long &audio_play_mode = *reinterpret_cast<decltype(&audio_play_mode)>(0x4BFB60);
	trng::StrListaWav (&TrackFileNames)[256] = *reinterpret_cast<decltype(&TrackFileNames)>(0x46C8AD);
	HANDLE &NotificationThreadHandle = *reinterpret_cast<decltype(&NotificationThreadHandle)>(0x4BFCD8);
	bool &acm_ready = *reinterpret_cast<decltype(&acm_ready)>(0x4BFD38);

	void S_CDStop()
	{
		__try { throw __func__; } __finally {}
	}

	void ACMSetVolume()
	{
		long volume;

		if (trng::GlobTomb4.BaseBassHandles.TestPresente)
		{
			trng::SetVolumeBass(-1);
			return;
		}

		if (!MusicVolume)
			volume = -10000;
		else
			volume = -4000 * (100 - MusicVolume) / 100;

		if (DSBuffer)
			DSBuffer->SetVolume(volume);
	}

	void S_CDPlay(long track, long mode)
	{
		if (trng::GlobTomb4.BaseBassHandles.TestPresente)
		{
			trng::GestioneCdPlay((short)track, mode);
			return;
		}

		if (acm_ready)
		{
			__try
			{
				if (!trng::GlobTomb4.TestBloccaCritical)
					EnterCriticalSection(&audio_cs);
			}
			__finally
			{
				if (!trng::GlobTomb4.TestBloccaCritical)
					LeaveCriticalSection(&audio_cs);
			}

			IsAtmospherePlaying = track == CurrentAtmosphere;
			audio_counter = 0;
			S_CDStop();
			ACMEmulateCDPlay(track, mode);
		}
	}

	long ACMSetupNotifications()
	{
		DSBPOSITIONNOTIFY posNotif[5];
		ulong ThreadId;
		long result;

		// rimempire wstruttura Attributi
		trng::Attributi.nLength = sizeof(SECURITY_ATTRIBUTES);
		trng::Attributi.lpSecurityDescriptor = 0;
		trng::Attributi.bInheritHandle = TRUE;

		NotifyEventHandles[0] = CreateEvent(&trng::Attributi, 0, 0, 0);
		NotifyEventHandles[1] = CreateEvent(&trng::Attributi, 0, 0, 0);
		posNotif[0].dwOffset = NotifySize;
		posNotif[0].hEventNotify = NotifyEventHandles[0];
		Log(8, "Set notifies for position %lu", posNotif[0].dwOffset);

		for (int i = 1; i < 4; i++)
		{
			posNotif[i].dwOffset = NotifySize + posNotif[i - 1].dwOffset;
			posNotif[i].hEventNotify = NotifyEventHandles[0];
			Log(8, "Set notifies for positions %lu", posNotif[i].dwOffset);
		}

		posNotif[3].dwOffset--;
		posNotif[4].dwOffset = ulong(-1);
		posNotif[4].hEventNotify = NotifyEventHandles[1];
		NotificationThreadHandle = CreateThread(0, 0, ACMHandleNotifications, 0, 0, &ThreadId);

		if (!NotificationThreadHandle)
			Log(1, "Create Notification Thread failed");

		result = DSNotify->SetNotificationPositions(5, posNotif);

		if (result != DS_OK)
		{
			CloseHandle(NotifyEventHandles[0]);
			CloseHandle(NotifyEventHandles[1]);
			NotifyEventHandles[1] = 0;
			NotifyEventHandles[0] = 0;
		}
		else
			Log(8, "Setup Notifications OK");

		return result;
	}

	ulong __stdcall ACMHandleNotifications(void* ptr)
	{
		__try { throw __func__; } __finally {}
	}

	void ACMEmulateCDPlay(long track, long mode)
	{
		__try { throw __func__; } __finally {}
	}
}

__declspec(naked) static void** Inject_Audio_TrackFileNames() { __asm lea eax, [tomb4::TrackFileNames] __asm ret }

void Inject_Audio(bool replace)
{
	IndirectReferenceInject(Inject_Audio_TrackFileNames());

	ProcessInject(0x46BDC0, (unsigned int)tomb4::S_CDStop, false);
	ProcessInject(0x46BEB0, (unsigned int)tomb4::ACMSetVolume, 0x1000C4AF, replace);
	ProcessInject(0x46BD20, (unsigned int)tomb4::S_CDPlay, 0x1000C496, replace);
	ProcessInject(0x46BF70, (unsigned int)tomb4::ACMSetupNotifications, replace);
	ProcessInject(0x46CA20, (unsigned int)tomb4::ACMHandleNotifications, false);
	ProcessInject(0x46C860, (unsigned int)tomb4::ACMEmulateCDPlay, false);
}
