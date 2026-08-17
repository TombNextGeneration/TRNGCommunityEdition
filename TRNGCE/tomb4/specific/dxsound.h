#pragma once
#include "../types.h"

namespace tomb4
{
	extern char* &samples_buffer;
	extern ulong &samples_buffer_size;
	extern float &sfx_overall_frequency;
	extern ulong &sfx_sample_rate;

	bool DXChangeOutputFormat(long nSamplesPerSec, bool force);
	void S_SoundStopAllSamples();
	void DXStopSample(long num);
	bool DXSetOutputFormat();
	bool DXDSCreate();
	bool InitSampleDecompress();
	bool FreeSampleDecompress();
	bool DXCreateSampleADPCM(char* data, long comp_size, long uncomp_size, long num);
	long DXStartSample(long num, long volume, long pitch, long pan, ulong flags);
	long DSGetFreeChannel();
	bool DSIsChannelPlaying(long num);
	void DSAdjustPitch(long num, long pitch);
	void DSAdjustPan(long num, long pan);
	void DSChangeVolume(long num, long volume);
	long CalcVolume(long volume);
	void S_SoundStopSample(long num);
	long S_SoundPlaySample(long num, ushort volume, long pitch, short pan);
	long S_SoundPlaySampleLooped(long num, ushort volume, long pitch, short pan);
	void DXFreeSounds();
	long S_SoundSampleIsPlaying(long num);
	void S_SoundSetPanAndVolume(long num, short pan, ushort volume);
	void S_SoundSetPitch(long num, long pitch);
}

void Inject_Dxsound(bool replace);
