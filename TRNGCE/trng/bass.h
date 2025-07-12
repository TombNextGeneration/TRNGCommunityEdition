#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace trng {
	typedef unsigned __int64 QWORD;

	typedef DWORD HMUSIC;		// MOD music handle
	typedef DWORD HSAMPLE;		// sample handle
	typedef DWORD HCHANNEL;		// playing sample's channel handle
	typedef DWORD HSTREAM;		// sample stream handle
	typedef DWORD HRECORD;		// recording handle
	typedef DWORD HSYNC;		// synchronizer handle
	typedef DWORD HDSP;			// DSP handle
	typedef DWORD HFX;			// DX8 effect handle
	typedef DWORD HPLUGIN;		// Plugin handle

	// ------------------ DEFINIZIONI PUNTATORI DI FUNZIONI --------------

	typedef BOOL (WINAPI *TYPE_BASS_Init)(int device, DWORD freq, DWORD flags, HWND win, const GUID *dsguid);

	typedef BOOL (WINAPI *TYPE_BASS_Free)(void);

	typedef BOOL (WINAPI *TYPE_BASS_ChannelSlideAttribute)(DWORD handle, DWORD attrib, float value, DWORD time);

	typedef BOOL (WINAPI *TYPE_BASS_ChannelSetAttribute)(DWORD handle, DWORD attrib, float value);

	typedef HSTREAM (WINAPI *TYPE_BASS_StreamCreateFile)(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags);

	typedef BOOL (WINAPI *TYPE_BASS_ChannelPlay)(DWORD handle, BOOL restart);

	typedef int (WINAPI *TYPE_BASS_ErrorGetCode)();

	typedef BOOL (WINAPI* TYPE_BASS_Pause)();

	typedef BOOL (WINAPI* TYPE_BASS_Start)();

	typedef DWORD (WINAPI* TYPE_BASS_ChannelFlags)(DWORD handle, DWORD flags, DWORD mask);

	typedef BOOL (WINAPI * TYPE_BASS_ChannelStop)(DWORD handle);

	typedef BOOL (WINAPI * TYPE_BASS_Stop)();

	typedef BOOL (WINAPI * TYPE_BASS_ChannelSetPosition) (DWORD handle,	QWORD pos, DWORD mode);

	typedef QWORD (WINAPI * TYPE_BASS_ChannelGetPosition) (DWORD handle, DWORD mode);

	typedef DWORD (WINAPI * TYPE_BASS_ChannelIsActive) (DWORD handle);

	typedef QWORD (WINAPI * TYPE_BASS_StreamGetFilePosition)(HSTREAM handle, DWORD mode);
}
