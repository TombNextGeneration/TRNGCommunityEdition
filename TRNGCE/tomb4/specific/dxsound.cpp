#include "dxsound.h"
#include "../../inject.h"
#include "dxshell.h"
#include "function_stubs.h"
#include "winmain.h"
#include "LoadSave.h"
#include "../game/sound.h"
#include "audio.h"
#include "../../flep/PlugIn_trng.h"
#include "../../flep/structures_mine.h"

namespace tomb4
{
	static LPDIRECTSOUNDBUFFER &DSPrimary = *reinterpret_cast<decltype(&DSPrimary)>(0x52B590);
	static DS_SAMPLE (&DS_Samples)[32] = *reinterpret_cast<decltype(&DS_Samples)>(0x52B598);
	static WAVEFORMATEX &pcm_format = *reinterpret_cast<decltype(&pcm_format)>(0x52A968);
	static char (&source_pcm_format)[50] = *reinterpret_cast<decltype(&source_pcm_format)>(0x4B050C);
	static HACMSTREAM &hACMStream = *reinterpret_cast<decltype(&hACMStream)>(0x52A98C);
	static MMRESULT &mmresult = *reinterpret_cast<decltype(&mmresult)>(0x52A964);
	static char* &decompressed_samples_buffer = *reinterpret_cast<decltype(&decompressed_samples_buffer)>(0x52B718);
	static ACMSTREAMHEADER &ACMStreamHeader = *reinterpret_cast<decltype(&ACMStreamHeader)>(0x52A910);
	static LPDIRECTSOUNDBUFFER (&DS_Buffers)[768] = *reinterpret_cast<decltype(&DS_Buffers)>(0x52A990);

	char* &samples_buffer = *reinterpret_cast<decltype(&samples_buffer)>(0x52A97C);
	ulong &samples_buffer_size = *reinterpret_cast<decltype(&samples_buffer_size)>(0x471A18);
	float &sfx_overall_frequency = *reinterpret_cast<decltype(&sfx_overall_frequency)>(0x4A7308);
	ulong &sfx_sample_rate = *reinterpret_cast<decltype(&sfx_sample_rate)>(0x4719D8);

	bool DXChangeOutputFormat(long nSamplesPerSec, bool force)
	{
		static long lastSPC;

		WAVEFORMATEX pcfxFormat;

		if (!force && lastSPC == nSamplesPerSec)
			return 1;

		lastSPC = nSamplesPerSec;
		pcfxFormat.wFormatTag = WAVE_FORMAT_PCM;
		pcfxFormat.nChannels = 2;
		pcfxFormat.nSamplesPerSec = nSamplesPerSec;
		pcfxFormat.nAvgBytesPerSec = 4 * nSamplesPerSec;
		pcfxFormat.nBlockAlign = 4;
		pcfxFormat.wBitsPerSample = 16;
		pcfxFormat.cbSize = 0;
		S_SoundStopAllSamples();

		if (DSPrimary && DXAttempt(DSPrimary->SetFormat(&pcfxFormat)) != DS_OK)
		{
			Log(1, "Can't set sound output format to %d", pcfxFormat.nSamplesPerSec);
			return 0;
		}

		return 1;
	}

	void S_SoundStopAllSamples()
	{
		for (int i = 0; i < 32; i++)
			DXStopSample(i);
	}

	void DXStopSample(long num)
	{
		if (num >= 0 && DS_Samples[num].buffer)
		{
			DXAttempt(DS_Samples[num].buffer->Stop());
			DXAttempt(DS_Samples[num].buffer->Release());
			DS_Samples[num].playing = 0;
			DS_Samples[num].buffer = 0;
		}
	}

	bool DXSetOutputFormat()
	{
		DSBUFFERDESC desc;

		Log(2, "DXSetOutputFormat");
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		desc.dwFlags = DSBCAPS_PRIMARYBUFFER;

		if (DXAttempt(App.dx.lpDS->CreateSoundBuffer(&desc, &DSPrimary, 0)) == DS_OK)
		{
			DXChangeOutputFormat(sfx_frequencies[SoundQuality], 0);
			DSPrimary->Play(0, 0, DSBPLAY_LOOPING);
			return 1;
		}

		Log(1, "Can't Get Primary Sound Buffer");
		return 0;
	}

	bool DXDSCreate()
	{
		Log(2, "DXDSCreate");
		DXAttempt(DirectSoundCreate(G_dxinfo->DSInfo[G_dxinfo->nDS].lpGuid, &App.dx.lpDS, 0));
		DXAttempt(App.dx.lpDS->SetCooperativeLevel(App.hWnd, DSSCL_EXCLUSIVE));
		DXSetOutputFormat();
		sound_active = 1;
		return 1;
	}

	bool InitSampleDecompress()
	{
		pcm_format.wFormatTag = WAVE_FORMAT_PCM;
		pcm_format.cbSize = 0;
		pcm_format.nChannels = 1;

		if (flep::pPatchMap[flep::PATCH_SAMPLE_RATE])
		{
			pcm_format.nSamplesPerSec = sfx_sample_rate;
			pcm_format.nAvgBytesPerSec = 2 * pcm_format.nSamplesPerSec;
		}
		else
		{
			pcm_format.nSamplesPerSec = 22050;
			pcm_format.nAvgBytesPerSec = 44100;
		}

		pcm_format.nBlockAlign = 2;
		pcm_format.wBitsPerSample = 16;
		mmresult = acmStreamOpen(&hACMStream, hACMDriver, (LPWAVEFORMATEX)source_pcm_format, &pcm_format, 0, 0, 0, 0);

		if (mmresult != DS_OK)
			Log(1, "Stream Open %d", mmresult);

		decompressed_samples_buffer = (char*)malloc(0x40000);
		samples_buffer = (char*)malloc(samples_buffer_size);
		memset(&ACMStreamHeader, 0, sizeof(ACMStreamHeader));
		ACMStreamHeader.pbSrc = (uchar*)(samples_buffer + 90);
		ACMStreamHeader.cbStruct = 84;
		ACMStreamHeader.cbSrcLength = 0x40000;
		ACMStreamHeader.cbDstLength = 0x40000;
		ACMStreamHeader.pbDst = (uchar*)decompressed_samples_buffer;
		mmresult = acmStreamPrepareHeader(hACMStream, &ACMStreamHeader, 0);

		if (mmresult != DS_OK)
			Log(1, "Prepare Stream %d", mmresult);

		return 1;
	}

	bool FreeSampleDecompress()
	{
		ACMStreamHeader.cbSrcLength = 0x40000;
		mmresult = acmStreamUnprepareHeader(hACMStream, &ACMStreamHeader, 0);

		if (mmresult != DS_OK)
			Log(1, "UnPrepare Stream %d", mmresult);

		mmresult = acmStreamClose(hACMStream, 0);

		if (mmresult != DS_OK)
			Log(1, "Stream Close %d", mmresult);

		free(decompressed_samples_buffer);
		free(samples_buffer);
		return 1;
	}

	bool DXCreateSampleADPCM(char* data, long comp_size, long uncomp_size, long num)
	{
		LPDIRECTSOUNDBUFFER buffer;
		LPVOID dest;
		DSBUFFERDESC desc;
		ulong bytes, size;

		if (!App.dx.lpDS)
			return 0;

		size = *(ulong*)&data[40];

		if (data[36] != 'd' && data[37] != 'a' && data[38] != 't' && data[39] != 'a')
			return 0;

		memset(&desc, 0, sizeof(desc));
		desc.dwSize = 20;
		desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
		desc.dwReserved = 0;
		desc.dwBufferBytes = size;
		desc.lpwfxFormat = &pcm_format;

		if (DXAttempt(App.dx.lpDS->CreateSoundBuffer(&desc, &buffer, 0)) != DS_OK)
		{
			Log(1, "Unable To Create Sound Buffer");
			return 0;
		}

		if (DXAttempt(buffer->Lock(0, size, &dest, &bytes, 0, 0, 0)) != DS_OK)
		{
			Log(1, "Unable To Lock Sound Buffer");
			return 0;
		}

		memcpy(dest, data + 44, size);
		DXAttempt(buffer->Unlock(dest, bytes, 0, 0));
		DS_Buffers[num] = buffer;
		return 1;
	}

	long DXStartSample(long num, long volume, long pitch, long pan, ulong flags)
	{
		LPDIRECTSOUNDBUFFER buffer;
		long channel;

		channel = DSGetFreeChannel();

		if (channel < 0 || DXAttempt(App.dx.lpDS->DuplicateSoundBuffer(DS_Buffers[num], &buffer)) != DS_OK)
			return -1;

		if (DXAttempt(buffer->SetVolume(volume)) != DS_OK || DXAttempt(buffer->SetCurrentPosition(0)) != DS_OK)
			return -1;

		DS_Samples[channel].buffer = buffer;
		DS_Samples[channel].playing = num;
		DSAdjustPitch(channel, pitch);
		DSAdjustPan(channel, pan);
		buffer->Stop();
		DXAttempt(buffer->Play(0, 0, flags));
		return channel;
	}

	long DSGetFreeChannel()
	{
		for (int i = 0; i < 32; i++)
		{
			if (!DSIsChannelPlaying(i))
				return i;
		}

		return -1;
	}

	bool DSIsChannelPlaying(long num)
	{
		ulong status;

		if (DS_Samples[num].buffer)
		{
			if (DXAttempt(DS_Samples[num].buffer->GetStatus(&status)) == DS_OK)
			{
				if (status & DSBSTATUS_PLAYING)
					return 1;

				DXStopSample(num);
			}
		}

		return 0;
	}

	void DSAdjustPitch(long num, long pitch)
	{
		float source_frequency;
		ulong frequency;

		if (DS_Samples[num].buffer)
		{
			source_frequency = sfx_overall_frequency;

			if (flep::pPatchMap[flep::PATCH_SAMPLE_RATE])
				source_frequency = (float)pcm_format.nSamplesPerSec;

			frequency = ulong((float)pitch / 65536.0F * source_frequency);

			if (frequency < 100)
				frequency = 100;
			else if (frequency > 100000)
				frequency = 100000;

			DS_Samples[num].buffer->SetFrequency(frequency);
		}
	}

	void DSAdjustPan(long num, long pan)
	{
		if (DS_Samples[num].buffer)
		{
			if (pan < 0)
			{
				if (pan < -0x4000)
					pan = -0x8000 - pan;
			}
			else if (pan > 0 && pan > 0x4000)
				pan = 0x8000 - pan;

			pan >>= 4;
			DS_Samples[num].buffer->SetPan(pan);
		}
	}

	void DSChangeVolume(long num, long volume)
	{
		if (DS_Samples[num].buffer)
			DS_Samples[num].buffer->SetVolume(volume);
	}

	long CalcVolume(long volume)
	{
		long result;

		result = 8000 - long(float(0x7FFF - volume) * 0.30518511F);

		if (result > 0)
			result = 0;
		else if (result < -10000)
			result = -10000;

		result -= (100 - SFXVolume) * 50;

		if (result > 0)
			result = 0;
		else if (result < -10000)
			result = -10000;

		return result;
	}

	void S_SoundStopSample(long num)
	{
		DXStopSample(num);
	}

	long S_SoundPlaySample(long num, ushort volume, long pitch, short pan)
	{
		return DXStartSample(num, CalcVolume(volume), pitch, pan, 0);
	}

	long S_SoundPlaySampleLooped(long num, ushort volume, long pitch, short pan)
	{
		return DXStartSample(num, CalcVolume(volume), pitch, pan, DSBPLAY_LOOPING);
	}

	void DXFreeSounds()
	{
		S_SoundStopAllSamples();

		for (int i = 0; i < 768; i++)
		{
			if (DS_Buffers[i])
			{
				Log(4, "Released %s @ %x - RefCnt = %d", "SoundBuffer", DS_Buffers[i], DS_Buffers[i]->Release());
				DS_Buffers[i] = 0;
			}
		}
	}

	long S_SoundSampleIsPlaying(long num)
	{
		if (!sound_active)
			return 0;

		return DSIsChannelPlaying(num);
	}

	void S_SoundSetPanAndVolume(long num, short pan, ushort volume)
	{
		if (sound_active)
		{
			DSChangeVolume(num, CalcVolume(volume));
			DSAdjustPan(num, pan);
		}
	}

	void S_SoundSetPitch(long num, long pitch)
	{
		if (sound_active)
			DSAdjustPitch(num, pitch);
	}
}

void Inject_Dxsound(bool replace)
{
	ProcessInject(0x471700, (unsigned int)tomb4::DXChangeOutputFormat, replace);
	ProcessInject(0x471E80, (unsigned int)tomb4::S_SoundStopAllSamples, replace);
	ProcessInject(0x471C80, (unsigned int)tomb4::DXStopSample, replace);
	ProcessInject(0x471880, (unsigned int)tomb4::DXSetOutputFormat, replace);
	ProcessInject(0x471920, (unsigned int)tomb4::DXDSCreate, replace);
	ProcessInject(0x471990, (unsigned int)tomb4::InitSampleDecompress, replace);
	ProcessInject(0x471AB0, (unsigned int)tomb4::FreeSampleDecompress, replace);
	ProcessInject(0x471B30, (unsigned int)tomb4::DXCreateSampleADPCM, replace);
	ProcessInject(0x471D40, (unsigned int)tomb4::DXStartSample, replace);
	ProcessInject(0x471D20, (unsigned int)tomb4::DSGetFreeChannel, replace);
	ProcessInject(0x471CD0, (unsigned int)tomb4::DSIsChannelPlaying, replace);
	ProcessInject(0x4717D0, (unsigned int)tomb4::DSAdjustPitch, replace);
	ProcessInject(0x471820, (unsigned int)tomb4::DSAdjustPan, replace);
	ProcessInject(0x4717B0, (unsigned int)tomb4::DSChangeVolume, replace);
	ProcessInject(0x471E20, (unsigned int)tomb4::CalcVolume, replace);
	ProcessInject(0x471EA0, (unsigned int)tomb4::S_SoundStopSample, replace);
	ProcessInject(0x471EB0, (unsigned int)tomb4::S_SoundPlaySample, replace);
	ProcessInject(0x471EE0, (unsigned int)tomb4::S_SoundPlaySampleLooped, replace);
	ProcessInject(0x471F10, (unsigned int)tomb4::DXFreeSounds, replace);
	ProcessInject(0x471F60, (unsigned int)tomb4::S_SoundSampleIsPlaying, replace);
	ProcessInject(0x471F80, (unsigned int)tomb4::S_SoundSetPanAndVolume, replace);
	ProcessInject(0x471FC0, (unsigned int)tomb4::S_SoundSetPitch, replace);
}
