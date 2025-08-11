#pragma once

namespace tomb4
{
	extern char (&HairSkinVertNums)[6][12];

	void CreateSkinningData();
}

void Inject_Laraskin(bool replace);
