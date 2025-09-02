#include "inject.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winternl.h>
#include "tomb4/game/croc.h"
#include "tomb4/game/sound.h"
#include "tomb4/game/draw.h"
#include "tomb4/game/tomb4fx.h"
#include "tomb4/specific/function_stubs.h"
#include "tomb4/specific/3dmath.h"
#include "tomb4/specific/file.h"
#include "tomb4/game/laraskin.h"
#include "tomb4/game/setup.h"
#include "tomb4/specific/drawroom.h"
#include "trng/zPatchesTomb4.h"
#include "trng/trng_elevator.h"
#include "trng/Oggetti.h"
#include "trng/Tomb_NextGeneration.h"
#include "tomb4/game/objects.h"
#include "tomb4/game/collide.h"
#include "tomb4/game/savegame.h"
#include "flep/patches/vehicles/main.h"
#include "flep/patches/vehicles/minecart.h"
#include "flep/patches/vehicles/quadbike.h"
#include "trng/zRoomEditor.h"
#include "trng/plugin.h"
#include "trng/ListTr4Patch.h"
#include "trng/trng_weather.h"
#include "tomb4/game/gameflow.h"
#include "tomb4/specific/output.h"
#include "tomb4/specific/dxshell.h"
#include "tomb4/specific/polyinsert.h"

#pragma pack(push, 1)
struct Jump {
	unsigned char opcode;
	unsigned int offset;
};
#pragma pack(pop)

struct LDR_DLL_LOADED_NOTIFICATION_DATA {
	ULONG Flags;                    //Reserved.
	PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
	PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
	PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
	ULONG SizeOfImage;              //The size of the DLL image, in bytes.
};

struct LDR_DLL_UNLOADED_NOTIFICATION_DATA {
	ULONG Flags;                    //Reserved.
	PCUNICODE_STRING FullDllName;   //The full path name of the DLL module.
	PCUNICODE_STRING BaseDllName;   //The base file name of the DLL module.
	PVOID DllBase;                  //A pointer to the base address for the DLL in memory.
	ULONG SizeOfImage;              //The size of the DLL image, in bytes.
};

union LDR_DLL_NOTIFICATION_DATA {
	LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
	LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
};

static LPSTR (__stdcall *&GetCommandLineBinding)() = *reinterpret_cast<decltype(&GetCommandLineBinding)>(0x4A7128);

#pragma comment(linker, "/EXPORT:_DummyFunction,@1,NONAME")
extern "C" int DummyFunction() {
	return 0;
}

static void ProcessInjectJump(unsigned int from, unsigned int to) {
	DWORD protection;
	Jump buffer;

	VirtualProtect((LPVOID) from, sizeof(Jump), PAGE_EXECUTE_READWRITE, &protection);
	buffer.opcode = 0xE9;
	buffer.offset = to - from - sizeof(Jump);
	memcpy((void *) from, &buffer, sizeof(Jump));
	VirtualProtect((LPVOID) from, sizeof(Jump), protection, &protection);
}

void ProcessInject(unsigned int from, unsigned int to, bool replace) {
	if (replace)
		ProcessInjectJump(from, to);
	else
		ProcessInjectJump(to, from);
}

static void LoadTombNextGenerationInject(bool replace) {
	LoadTombNextGenerationInject_TombNextGeneration(replace);
	LoadTombNextGenerationInject_ZRoomEditor(replace);
	LoadTombNextGenerationInject_Plugin(replace);
	LoadTombNextGenerationInject_ListTr4Patch(replace);
	LoadTombNextGenerationInject_TrngWeather(replace);
	LoadTombNextGenerationInject_ZPatchesTomb4(replace);
	LoadTombNextGenerationInject_Oggetti(replace);
	LoadTombNextGenerationInject_TrngElevator(replace);
}

static void __stdcall LoadInject(ULONG NotificationReason, LDR_DLL_NOTIFICATION_DATA *NotificationData, PVOID Context) {
	if (NotificationReason == 1 && !_wcsicmp(NotificationData->Loaded.BaseDllName->Buffer, L"Tomb_NextGeneration.dll"))
		LoadTombNextGenerationInject(true);
}

static void Inject(bool replace) {
	Inject_Croc(replace);
	Inject_Sound(replace);
	Inject_Draw(replace);
	Inject_Tomb4fx(replace);
	Inject_FunctionStubs(replace);
	Inject_3dmath(replace);
	Inject_File(replace);
	Inject_Laraskin(replace);
	Inject_Setup(replace);
	Inject_Drawroom(replace);
	Inject_Objects(replace);
	Inject_Collide(replace);
	Inject_Savegame(replace);
	Inject_VehiclesMain(replace);
	Inject_VehiclesMinecart(replace);
	Inject_VehiclesQuadbike(replace);
	Inject_Gameflow(replace);
	Inject_Output(replace);
	Inject_Dxshell(replace);
	Inject_Polyinsert(replace);
}

static LPSTR __stdcall CallInject() {
	Inject(true);
	GetCommandLineBinding = GetCommandLineA;
	return GetCommandLineA();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	NTSTATUS (__stdcall *LdrRegisterDllNotification)(ULONG, void (__stdcall *)(ULONG, LDR_DLL_NOTIFICATION_DATA *, PVOID), PVOID, PVOID *);
	HMODULE module;
	PVOID cookie;

	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		module = GetModuleHandle("ntdll.dll");
		if (!module)
			return FALSE;
		LdrRegisterDllNotification = (NTSTATUS (__stdcall *)(ULONG, void (__stdcall *)(ULONG, LDR_DLL_NOTIFICATION_DATA *, PVOID), PVOID, PVOID *)) GetProcAddress(module, "LdrRegisterDllNotification");
		if (!LdrRegisterDllNotification)
			return FALSE;
		LdrRegisterDllNotification(0, LoadInject, NULL, &cookie);
		GetCommandLineBinding = CallInject;
	}
	return TRUE;
}

