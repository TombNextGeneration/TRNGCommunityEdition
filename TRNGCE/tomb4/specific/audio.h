#pragma once
#include <windows.h>
#include <mmreg.h>
#include <msacm.h>
#include "../../trng/structures.h"
#include "../types.h"

namespace tomb4
{
	extern long &XATrack;
	extern long &audio_play_mode;
	extern trng::StrListaWav (&TrackFileNames)[256];
	extern HANDLE &NotificationThreadHandle;
	extern bool &acm_ready;
	extern uchar* &wav_file_buffer;
	extern uchar* &ADPCMBuffer;
	extern HACMDRIVER &hACMDriver;

	void S_CDStop();
	void ACMSetVolume();
	void S_CDPlay(long track, long mode);
	long ACMSetupNotifications();
	ulong __stdcall ACMHandleNotifications(void* ptr);
	void ACMEmulateCDPlay(long track, long mode);
	void ACMClose();
}

void Inject_Audio(bool replace);
