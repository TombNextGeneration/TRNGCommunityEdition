#include "texture.h"
#include "../../inject.h"

namespace tomb4
{
	TEXTURE* &Textures = *reinterpret_cast<decltype(&Textures)>(0x7537C8);
	long &nTextures = *reinterpret_cast<decltype(&nTextures)>(0x7537C4);

	LPDIRECTDRAWSURFACE4 CreateTexturePage(long w, long h, long MipMapCount, long* pSrc, rgbfunc RGBM, long format)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Texture(bool replace)
{
	ProcessInject(0x48C060, (unsigned int)tomb4::CreateTexturePage, false);
}
