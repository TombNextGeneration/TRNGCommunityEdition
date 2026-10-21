#include "PlugIn_trng.h"
#include "../../inject.h"
#include "trng.h"

namespace plugin::objecthelper {
	int (&PluginFunctionQueryHandle)[tomb4::NUMBER_OBJECTS] = *reinterpret_cast<decltype(&PluginFunctionQueryHandle)>(0x1000A348);
	DWORD (&PluginQuerySupport)[tomb4::NUMBER_OBJECTS] = *reinterpret_cast<decltype(&PluginQuerySupport)>(0x10009B28);
	StrResult &Result = *reinterpret_cast<decltype(&Result)>(0x10009B18);
	trng::CALL_FLIPEFFECT_MINE (&PluginPointer)[PLUGINS] = *reinterpret_cast<decltype(&PluginPointer)>(0x1000AB68);
	char *(&PluginName)[PLUGINS] = *reinterpret_cast<decltype(&PluginName)>(0x10009AE8);

	void HeadshotEnemy(trng::StrItemTr4 *item)
	{
		Trng.pGlobTomb4->pBaseVariableTRNG->Globals.CurrentValue = (int) item;
		MakeQuery(item->SlotID, QUERY_HEADSHOT);
	}

	void MakeQuery(WORD Slot, DWORD Query)
	{
		if (PluginFunctionQueryHandle[Slot] != -1) {
			if (PluginQuerySupport[Slot] & Query) {
				PerformNewFlipeffect(PluginFunctionQueryHandle[Slot], PLUGIN_FLIPEFFECT_QUERY, Query);
				Result.Value = Trng.pGlobTomb4->pBaseVariableTRNG->Globals.CurrentValue;
				Result.Support = true;
			} else {
				Result.Support = false;
			}
			Result.Available = true;
		} else {
			Result.Available = false;
		}
	}

	void PerformNewFlipeffect(int Handle, int Flipeffect, DWORD Timer)
	{
		if (Timer <= TIMER_THRESHOLD) {
			PerformGeneralFlipeffect(Handle, Flipeffect, (WORD) Timer, 0);
		} else {
			PerformGeneralFlipeffect(Handle, Flipeffect, TIMER_EXTENDED, (WORD) HighestBitSet(Timer));
		}
	}

	void PerformGeneralFlipeffect(int Handle, int Flipeffect, WORD Timer, WORD Extra)
	{
		if (PluginPointer[Handle]) {
			PluginPointer[Handle]((WORD) Flipeffect, Timer, Extra, trng::SCANF_DIRECT_CALL);
		} else {
			PerformFlipeffect(PluginName[Handle], Flipeffect, Timer, Extra);
		}
	}

	int HighestBitSet(DWORD Value)
	{
		int Bit;

		Bit = 0;
		while (Value) {
			Value >>= 1;
			++Bit;
		}
		return Bit;
	}

	void HitEnemy(trng::StrItemTr4 *item)
	{
		Trng.pGlobTomb4->pBaseVariableTRNG->Globals.CurrentValue = (int) item;
		MakeQuery(item->SlotID, QUERY_ZOMBIE);
	}
}

__declspec(naked) static void** Inject_Plugin_Objecthelper_PluginFunctionQueryHandle() { __asm lea eax, [plugin::objecthelper::PluginFunctionQueryHandle] __asm ret }
__declspec(naked) static void** Inject_Plugin_Objecthelper_PluginQuerySupport() { __asm lea eax, [plugin::objecthelper::PluginQuerySupport] __asm ret }
__declspec(naked) static void** Inject_Plugin_Objecthelper_Result() { __asm lea eax, [plugin::objecthelper::Result] __asm ret }
__declspec(naked) static void** Inject_Plugin_Objecthelper_PluginPointer() { __asm lea eax, [plugin::objecthelper::PluginPointer] __asm ret }
__declspec(naked) static void** Inject_Plugin_Objecthelper_PluginName() { __asm lea eax, [plugin::objecthelper::PluginName] __asm ret }

void Inject_Plugin_Objecthelper(void* module, bool replace)
{
	ModuleAddressReferenceInject(Inject_Plugin_Objecthelper_PluginFunctionQueryHandle(), module);
	ModuleAddressReferenceInject(Inject_Plugin_Objecthelper_PluginQuerySupport(), module);
	ModuleAddressReferenceInject(Inject_Plugin_Objecthelper_Result(), module);
	ModuleAddressReferenceInject(Inject_Plugin_Objecthelper_PluginPointer(), module);
	ModuleAddressReferenceInject(Inject_Plugin_Objecthelper_PluginName(), module);

	ModuleAddressProcessInject(module, 0x10001480, (unsigned int)plugin::objecthelper::HeadshotEnemy, replace);
	ModuleAddressProcessInject(module, 0x10001110, (unsigned int)plugin::objecthelper::MakeQuery, replace);
	ModuleAddressProcessInject(module, 0x10001000, (unsigned int)plugin::objecthelper::PerformNewFlipeffect, replace);
	ModuleAddressProcessInject(module, 0x100013F0, (unsigned int)plugin::objecthelper::HitEnemy, replace);
}
