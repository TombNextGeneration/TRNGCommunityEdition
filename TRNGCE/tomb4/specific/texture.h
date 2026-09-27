#pragma once
#include "../types.h"

namespace tomb4
{
	extern TEXTURE* &Textures;
	extern long &nTextures;

	LPDIRECTDRAWSURFACE4 CreateTexturePage(long w, long h, long MipMapCount, long* pSrc, rgbfunc RGBM, long format);
}

void Inject_Texture(bool replace);
