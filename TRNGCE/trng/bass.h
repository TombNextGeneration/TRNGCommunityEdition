#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace trng {
	// Channel attributes
	inline constexpr int BASS_ATTRIB_FREQ = 1;
	inline constexpr int BASS_ATTRIB_VOL = 2;
	inline constexpr int BASS_ATTRIB_PAN = 3;
	inline constexpr int BASS_ATTRIB_EAXMIX = 4;
	inline constexpr int BASS_ATTRIB_MUSIC_AMPLIFY = 0x100;
	inline constexpr int BASS_ATTRIB_MUSIC_PANSEP = 0x101;
	inline constexpr int BASS_ATTRIB_MUSIC_PSCALER = 0x102;
	inline constexpr int BASS_ATTRIB_MUSIC_BPM = 0x103;
	inline constexpr int BASS_ATTRIB_MUSIC_SPEED = 0x104;
	inline constexpr int BASS_ATTRIB_MUSIC_VOL_GLOBAL = 0x105;
	inline constexpr int BASS_ATTRIB_MUSIC_VOL_CHAN = 0x200; // + channel #
	inline constexpr int BASS_ATTRIB_MUSIC_VOL_INST = 0x300; // + instrument #

	inline constexpr int BASS_SAMPLE_8BITS = 1;	// 8 bit
	inline constexpr int BASS_SAMPLE_FLOAT = 256;	// 32-bit floating-point
	inline constexpr int BASS_SAMPLE_MONO = 2;	// mono
	inline constexpr int BASS_SAMPLE_LOOP = 4;	// looped
	inline constexpr int BASS_SAMPLE_3D = 8;	// 3D functionality
	inline constexpr int BASS_SAMPLE_SOFTWARE = 16;	// not using hardware mixing
	inline constexpr int BASS_SAMPLE_MUTEMAX = 32;	// mute at max distance (3D only)
	inline constexpr int BASS_SAMPLE_VAM = 64;	// DX7 voice allocation & management
	inline constexpr int BASS_SAMPLE_FX = 128;	// old implementation of DX8 effects
	inline constexpr int BASS_SAMPLE_OVER_VOL = 0x10000;	// override lowest volume
	inline constexpr int BASS_SAMPLE_OVER_POS = 0x20000;	// override longest playing
	inline constexpr int BASS_SAMPLE_OVER_DIST = 0x30000; // override furthest from listener (3D only)

	inline constexpr int BASS_STREAM_PRESCAN = 0x20000; // enable pin-point seeking/length (MP3/MP2/MP1)
	inline constexpr int BASS_STREAM_AUTOFREE = 0x40000;	// automatically free the stream when it stop/ends
	inline constexpr int BASS_STREAM_RESTRATE = 0x80000;	// restrict the download rate of internet file streams
	inline constexpr int BASS_STREAM_BLOCK = 0x100000; // download/play internet file stream in small blocks
	inline constexpr int BASS_STREAM_DECODE = 0x200000; // don't play the stream, only decode (BASS_ChannelGetData)
	inline constexpr int BASS_STREAM_STATUS = 0x800000; // give server status info (HTTP/ICY tags) in DOWNLOADPROC

	// BASS_ChannelGetLength/GetPosition/SetPosition modes
	inline constexpr int BASS_POS_BYTE = 0;		// byte position
	inline constexpr int BASS_POS_MUSIC_ORDER = 1;		// order.row position, MAKELONG(order,row)

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
