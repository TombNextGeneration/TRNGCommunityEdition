#include "../inject.h"
#include "structures.h"
#include "../tomb4/types.h"

namespace trng {
	// usa sottoprocedura SubBridgeTilt(pBridge, CordX, CordZ)
	void ProcMyBridgeFloor(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY)
	{
		__try { throw __func__; } __finally {}
	}

	void ProcMyBridgeCeiling(StrItemTr4 *pItem, DWORD CordX, int CordY, DWORD CordZ, int *pNewCordY)
	{
		__try { throw __func__; } __finally {}
	}

	void TightRopeCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseTightRope(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void InitialiseGuardian(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void GuardianControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	// ------- codici barra parallela ---------------------------------------
	// procedura collisione di tomb5 originale per gestire giravolte
	// di lara intorno alla parallelbar
	void ParallelBarCollision(short item_num, tomb4::ITEM_INFO *l, tomb4::COLL_INFO *coll)
	{
		__try { throw __func__; } __finally {}
	}

	// procedura redirezionata per bubble per poter lanciare singolo
	// oggetto come arpione
	void ControlBubble(short fx_number)
	{
		__try { throw __func__; } __finally {}
	}

	// ****************** FUNZIONI PER FISH ************************************
	// riposiziona l'emitter in modo che sia in una posizione centrale
	void InitializeFishGenerator(short IndiceGeneratore)
	{
		__try { throw __func__; } __finally {}
	}

	void TriggerFish(short ItemIndex)
	{
		__try { throw __func__; } __finally {}
	}

	void TorpedoControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}

	void DiverControl(short item_number)
	{
		__try { throw __func__; } __finally {}
	}
}

void Inject_Oggetti(bool replace)
{
	ProcessInject(0x1001194A, (unsigned int)trng::ProcMyBridgeFloor, false);
	ProcessInject(0x10011C6A, (unsigned int)trng::ProcMyBridgeCeiling, false);
	ProcessInject(0x1001C94C, (unsigned int)trng::TightRopeCollision, false);
	ProcessInject(0x1001C8EC, (unsigned int)trng::InitialiseTightRope, false);
	ProcessInject(0x1001D5E8, (unsigned int)trng::InitialiseGuardian, false);
	ProcessInject(0x1001D822, (unsigned int)trng::GuardianControl, false);
	ProcessInject(0x1001BF31, (unsigned int)trng::ParallelBarCollision, false);
	ProcessInject(0x10014BE3, (unsigned int)trng::ControlBubble, false);
	ProcessInject(0x10012116, (unsigned int)trng::InitializeFishGenerator, false);
	ProcessInject(0x100122A7, (unsigned int)trng::TriggerFish, false);
	ProcessInject(0x1001FE63, (unsigned int)trng::TorpedoControl, false);
	ProcessInject(0x1001548E, (unsigned int)trng::DiverControl, false);
}
