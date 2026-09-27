#pragma once

namespace tomb4
{
	void InitialiseObjects();
	void SetupGame();
	void ClearFootPrints();
	void InitTarget();
	void InitialiseGameFlags();
	void InitialiseLara();
	void GetCarriedItems();
	void GetAIPickups();
	void reset_cutseq_vars();
}

void Inject_Setup(bool replace);
