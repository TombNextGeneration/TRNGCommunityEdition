#include "trng_flipeffects.h"
#include "../inject.h"
#include "Tomb_NextGeneration.h"
#include "zPatchesTomb4.h"

namespace trng {
	// qui c'e' tutto (e solo) il codice relativo all'esecuzione di flipeffect standards
	// ossia senza callback e diverse engine
	// questo e' un codice da esport
	int PerformTRNGFlipEffect(int FlipNumber, WORD Timer, WORD Flags)
	{
		__try { throw __func__; } __finally {}
	}

	void SetVolumeBass(int IndiceCanale)
	{
		float Volume;
		StrBassHandles *pBass;
		StrCanaleBass *pCanale;
		int Inizio, Fine;
		int i;

		pBass = &GlobTomb4.BaseBassHandles;
		AggiornaVolumeBass();
		Volume = pBass->VolumeMusica;

		switch (IndiceCanale) {
		case 0:
			Inizio = 0;
			Fine = 1;
			break;
		case 1:
			Inizio = 1;
			Fine = 2;
			break;
		default:
			Inizio = 0;
			Fine = 5;
			break;
		}

		for (i = Inizio; i < Fine; i++) {
			pCanale = &pBass->VetCanali[i];
			if (pCanale->Canale) {

				pBass->Proc.BASS_ChannelSetAttribute(pCanale->Canale, BASS_ATTRIB_VOL, Volume);
			}
		}
	}
}

void LoadTombNextGenerationInject_TrngFlipeffects(bool replace)
{
	ProcessInject(0x1009D2C7, (unsigned int)trng::PerformTRNGFlipEffect, false);
	ProcessInject(0x10099BF9, (unsigned int)trng::SetVolumeBass, replace);
}
