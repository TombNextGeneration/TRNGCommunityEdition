#pragma once
#include "../types.h"

namespace tomb4
{
	void CreateFlare(short object, long thrown);
	void undraw_flare_meshes();
	void DrawFlareInAir(ITEM_INFO* item);
}

void Inject_Laraflar(bool replace);
