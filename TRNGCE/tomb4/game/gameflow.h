#pragma once
#include "../types.h"

namespace tomb4
{
	extern uchar &gfCurrentLevel;
	extern ushort &gfLevelFlags;
	extern uchar &gfGameMode;
	extern CVECTOR &gfLayer1Col;
	extern CVECTOR &gfLayer2Col;
	extern char &gfLayer1Vel;
	extern char &gfLayer2Vel;
	extern uchar &gfLevelComplete;
	extern ushort* &gfStringOffset;
	extern char* &gfStringWad;
	extern GAMEFLOW* &Gameflow;
	extern long &gfStatus;
	extern char &gfUVRotate;
	extern uchar &gfNumMips;
	extern uchar &gfMirrorRoom;
	extern CVECTOR &gfFog;
	extern char &skipped_level;
	extern PHD_VECTOR &gfLensFlare;
	extern CVECTOR &gfLensFlareColour;
	extern long &gfMirrorZPlane;
	extern uchar (&gfMips)[8];
	extern PHD_VECTOR &gfLoadCam;
	extern PHD_VECTOR &gfLoadTarget;
	extern uchar &gfLoadRoom;
	extern uchar &gfInitialLegendTime;
	extern ulong &GameTimer;

	void DoGameflow();
	void DoLevel(uchar Name, uchar Audio);
	void DoTitle(uchar Name, uchar Audio);
}

void Inject_Gameflow(bool replace);
