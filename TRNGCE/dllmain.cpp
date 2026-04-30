#include "inject.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winternl.h>
#include <intrin.h>
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
#include "flep/patches/vehicles.h"
#include "flep/patches/minecart.h"
#include "flep/patches/quadbike.h"
#include "trng/zRoomEditor.h"
#include "trng/plugin.h"
#include "trng/ListTr4Patch.h"
#include "trng/trng_weather.h"
#include "tomb4/game/gameflow.h"
#include "tomb4/specific/output.h"
#include "tomb4/specific/dxshell.h"
#include "tomb4/specific/polyinsert.h"
#include "tomb4/game/control.h"
#include "tomb4/game/pickup.h"
#include "tomb4/specific/input.h"
#include "tomb4/game/newinv.h"
#include "tomb4/game/effect2.h"
#include "tomb4/game/items.h"
#include "tomb4/game/box.h"
#include "tomb4/game/laramisc.h"
#include "tomb4/game/hair.h"
#include "tomb4/game/spotcam.h"
#include "tomb4/game/debris.h"
#include "tomb4/game/scarab.h"
#include "tomb4/game/text.h"
#include "tomb4/game/effects.h"
#include "trng/trng_flipeffects.h"
#include "tomb4/specific/audio.h"
#include "tomb4/specific/specificfx.h"
#include "tomb4/specific/time.h"
#include "tomb4/game/traps.h"
#include "tomb4/game/sphere.h"
#include "tomb4/game/delstuff.h"
#include "tomb4/game/bike.h"
#include "tomb4/game/lara1gun.h"
#include "trng/trng_keypad.h"
#include "tomb4/specific/gamemain.h"
#include "tomb4/game/camera.h"
#include "tomb4/specific/LoadSave.h"
#include "flep/PlugIn_trng.h"
#include "flep/structures_mine.h"
#include "flep/patches/sub.h"
#include "plugin/flycheat/PlugIn_trng.h"
#include "plugin/flycheat/trng.h"
#include "plugin/particlesystem/trng/trng.h"
#include "plugin/particlesystem/Plugin_ParticleSystem.h"
#include "tomb4/specific/winmain.h"
#include "tomb4/specific/registry.h"
#include "tomb4/specific/function_table.h"
#include "tomb4/game/health.h"
#include "tomb4/game/init.h"
#include "tomb4/game/laraflar.h"
#include "tomb4/game/jeep.h"
#include "tomb4/game/laraswim.h"
#include "tomb4/game/lara.h"

inline constexpr bool REPLACE = true;

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
static const int RequiredPatches[3] = {
	flep::PATCH_SAVE_ROPES,
	flep::PATCH_CLASSIC_VEHICLES,
	flep::PATCH_FIX_BABOON_BUG
};
static const char *PatchTitles[342] = {
	"Font Customizer",
	"GFX1 Customizer",
	"GFX2 Customizer",
	"Light Customizer",
	"Light Customizer - Turn Off Motorbike Headlights",
	"Light Customizer - Blinking Light as Alarm Light",
	"Audio Customizer",
	"Damage Customizer",
	"Inventory Customizer",
	"Inventory Customizer - Fix Compass Bug",
	"Inventory Customizer - 24 Savegame Slots",
	"Inventory Customizer -  Shotgun 6x Divider OFF",
	"Weapon Customizer",
	"Weapon Customizer - Enable Shotgun Gunflash",
	"Physics Customizer",
	"Objects Customizer",
	"Objects Customizer - Inverse 2-Block Plat.",
	"Objects Customizer - Inverse 2-Block Plat. (OCB 0)",
	"Objects Customizer - Squishy Block 2 Inc. Timer",
	"Objects Customizer - Squishy Block 2 No Tremble",
	"New blending modes",
	"Enable new blending modes for particles",
	"Smooth shadows",
	"Stylish static bars",
	"Disable sentry gun flame attack",
	"Enable GAME OVER",
	"Add [Hits] to statistics",
	"Disable add-on gun sound",
	"Enable ricochet sound effect",
	"Old-skool teeth spikes",
	"Disable ledge climb delay",
	"Disable dive delay",
	"Quick crawlspace climb",
	"Enable crawlspace jump",
	"Enable crawlspace pickup",
	"Monkeyswing: 180° turn (stop)",
	"Monkeyswing: 180° turn (move)",
	"Roll key setting",
	"Add Lara's Home entry to title menu",
	"Save Folder",
	"Lara's Ponytail Position Changer",
	"Wall climbing mid-point adjuster",
	"Grab frame set for standing jump",
	"Change shiny sprite",
	"Completely disable load and save items",
	"Fog colour table editor",
	"Enable DOT3 bump mapping",
	"Clear menu backgrounds",
	"Remove green flare tint",
	"Fix Lara visibility bug in binocular view",
	"Single gun with PULSE (left)",
	"Turn on underwater waves",
	"Extended steam / smoke emitter OCBs",
	"Enable extra smoke emitter flags",
	"Smoke emitter white OCB 00 settings",
	"Smoke emitter white OCB 01 settings",
	"Smoke emitter white OCB 02 settings",
	"Smoke emitter white OCB 03 settings",
	"Smoke emitter white OCB 04 settings",
	"Smoke emitter white OCB 05 settings",
	"Smoke emitter white OCB 06 settings",
	"Smoke emitter white OCB 07 settings",
	"Smoke emitter white OCB 08 settings",
	"Smoke emitter white OCB 09 settings",
	"Smoke emitter white OCB 10 settings",
	"Smoke emitter white OCB 11 settings",
	"Smoke emitter white OCB 12 settings",
	"Smoke emitter white OCB 13 settings",
	"Smoke emitter white OCB 14 settings",
	"Smoke emitter white OCB 15 settings",
	"Smoke emitter black OCB 00 settings",
	"Smoke emitter black OCB 01 settings",
	"Smoke emitter black OCB 02 settings",
	"Smoke emitter black OCB 03 settings",
	"Smoke emitter black OCB 04 settings",
	"Smoke emitter black OCB 05 settings",
	"Smoke emitter black OCB 06 settings",
	"Smoke emitter black OCB 07 settings",
	"Smoke emitter black OCB 08 settings",
	"Smoke emitter black OCB 09 settings",
	"Smoke emitter black OCB 10 settings",
	"Smoke emitter black OCB 11 settings",
	"Smoke emitter black OCB 12 settings",
	"Smoke emitter black OCB 13 settings",
	"Smoke emitter black OCB 14 settings",
	"Smoke emitter black OCB 15 settings",
	"Change healing system",
	"Fix Medipack Hotkeys bug",
	"Disable Medipack Hotkeys",
	"Vertex shader base",
	"Vertex shader rule 1",
	"Vertex shader rule 2",
	"Vertex shader rule 3",
	"Vertex shader rule 4",
	"Vertex shader rule 5",
	"Vertex shader rule 6",
	"Vertex shader rule 7",
	"Vertex shader rule 8",
	"Vertex shader rule 9",
	"Vertex shader rule 10",
	"Vertex shader rule 11",
	"Vertex shader rule 12",
	"Vertex shader rule 13",
	"Vertex shader rule 14",
	"Vertex shader rule 15",
	"Vertex shader rule 16",
	"Vertex shader rule 17",
	"Vertex shader rule 18",
	"Vertex shader rule 19",
	"Vertex shader rule 20",
	"Vertex shader rule 21",
	"Vertex shader rule 22",
	"Vertex shader rule 23",
	"Vertex shader rule 24",
	"Vertex shader rule 25",
	"Vertex shader rule 26",
	"Vertex shader rule 27",
	"Vertex shader rule 28",
	"Vertex shader rule 29",
	"Vertex shader rule 30",
	"Vertex shader rule 31",
	"Vertex shader rule 32",
	"Vertex shader rule 33",
	"Vertex shader rule 34",
	"Vertex shader rule 35",
	"Vertex shader rule 36",
	"Vertex shader rule 37",
	"Vertex shader rule 38",
	"Vertex shader rule 39",
	"Vertex shader rule 40",
	"Vertex shader rule 41",
	"Vertex shader rule 42",
	"Vertex shader rule 43",
	"Vertex shader rule 44",
	"Vertex shader rule 45",
	"Vertex shader rule 46",
	"Vertex shader rule 47",
	"Vertex shader rule 48",
	"Vertex shader rule 49",
	"Vertex shader rule 50",
	"Vertex shader rule 51",
	"Vertex shader rule 52",
	"Vertex shader rule 53",
	"Vertex shader rule 54",
	"Vertex shader rule 55",
	"Vertex shader rule 56",
	"Vertex shader rule 57",
	"Vertex shader rule 58",
	"Vertex shader rule 59",
	"Vertex shader rule 60",
	"Vertex shader rule 61",
	"Vertex shader rule 62",
	"Vertex shader rule 63",
	"Vertex shader rule 64",
	"Remap bubble array",
	"Single gun with PULSE (bugfixed)",
	"Pigtail: gravity",
	"Flat shading mode",
	"Disable all dynamic lights",
	"Remove hardcoded sound when Lara surfaces",
	"Fix hysteresis in one click deep water",
	"Add [Kills] to statistics",
	"Global [Kills] Statistics entry",
	"Fast alignment",
	"Violent bats",
	"Ladder to crawlspace",
	"Motorbike and Jeep explosion in water",
	"Remove hardcoded Jeep audio",
	"Shotgun ammo parameters",
	"Disable manual aiming",
	"Enhance torch flame",
	"Fix cogwheel animation skip",
	"Allow crouching while holding any weapon",
	"Fix sprite bug",
	"Footstep Sound Customizer",
	"Enable all footstep sound effects",
	"Change shockwave damage",
	"Wireframe mode",
	"Free camera: Lock",
	"Sample file size",
	"Sample rate",
	"Sample buffer array",
	"Reverb base",
	"Reverb classic mode",
	"Reverb advanced mode",
	"Custom 1",
	"Custom 2",
	"Custom 3",
	"Custom 4",
	"Custom 5",
	"Custom 6",
	"Custom 7",
	"Custom 8",
	"Custom 9",
	"Custom 10",
	"Custom 11",
	"Custom 12",
	"Custom 13",
	"Custom 14",
	"Custom 15",
	"Custom 16",
	"24 Savegame Slots (bugfixed)",
	"Title menu adjustment",
	"Remove Ahmet flame death",
	"Remove Small Scorpion poison hack",
	"Remove poison screen effect",
	"Show HP bar in inventory",
	"Ammo Counter / Flare Timer",
	"Ammo Counter -  Shotgun 6x Divider OFF",
	"Fix sound radius bug",
	"Upward standing jump ledge grab animation",
	"Ledge release animation",
	"Pickup flare frames",
	"Pickup item frames",
	"Jump delay",
	"Dive delay",
	"Crawlspace pickup",
	"Prevent camera position freeze",
	"Customize sas gun",
	"Fix bottom right corner bug",
	"TR2Main widescreen",
	"Fix jumping through objects",
	"Static collision",
	"Fix inconsistent camera angle when hanging",
	"Enable gliding camera",
	"Jeep without Ignition Key",
	"Fix collision when swimming on water surface",
	"Fix hair while wading",
	"Multi-pickup",
	"Fix pedestal pickup bug",
	"Change puzzle insert frame",
	"Remove jump to ladder",
	"Stop Ahmet from activating heavy triggers",
	"Fix body parts persistence",
	"Jeep explosion after falling",
	"Fix Lara's crowbar door positioning",
	"Customize Hotkeys",
	"Font Colour Customization",
	"Ammo type options - Menu Button Show/Hide",
	"Ammo type options - Shotgun",
	"Ammo type options - Grenade Gun",
	"Ammo type options - Crossbow",
	"Disable LoadScreens",
	"Remove KNIGHTS_TEMPLAR health regeneration",
	"Fix multi-mesh inventory item drawing",
	"Disable shotgun smoke sprite",
	"Remove Knights Templar sparks",
	"Fix bridge bug",
	"Corner shimmy without pressing Action",
	"Fix flashes",
	"Fix flipmap lighting",
	"Fix hardcoded lighting",
	"Remove LARA_NO sound for crowbar",
	"Hair collision with floor",
	"Force bilinear filtering",
	"Safe flare throw",
	"Plugin integrity check",
	"Keep dead enemies",
	"Change health and air bar low levels",
	"Rope drop",
	"Save ropes",
	"Fix rope glitch",
	"Change blood sprite",
	"FLEP number",
	"Disable harmless Sentry Gun behaviour",
	"Burning torch customizer",
	"Level secrets counter",
	"Disable mummy follow block",
	"Fix Lara's elbows",
	"Add dynamic lighting to statics",
	"Disable \"Hang game thread\" on lost focus",
	"Save Turn Switch direction",
	"Remove MUMMY stun animations",
	"HK Gun",
	"Enable bike nitro without Puzzle_Item1",
	"Change bike nitro item",
	"Skedaddler baddies",
	"Fix hurt Von Croy bug",
	"Fix rainbow bug",
	"Fix dying flare colours",
	"Rotate debris",
	"Pushable Object alignment",
	"Wibble rooms",
	"tomb4 circle shadow",
	"Wibble objects",
	"Pushable Object TestPosition",
	"Disable Hair Skinning",
	"Hardware Acceleration preselection",
	"Fix sector boundaries",
	"Accurate hair mesh collision",
	"Fix wade snap",
	"Quake camera",
	"Remove baddies pickup hack",
	"Baddies and small medipacks",
	"Decouple baddies animations",
	"Remap regenerating pickups array",
	"Change pickup camera angles",
	"Change object interaction camera angles",
	"Change jump camera angles",
	"Fix Lara's backstep down animation",
	"Fix null static collision bounds",
	"Fix vertical rotation toward AI objects",
	"Fix Sarcophagus pickups",
	"Angkor Wat Von Croy",
	"Fix load.bmp stretching",
	"Fix ceiling trapdoor bug",
	"Change floor trapdoor fixed camera",
	"Disable floor trapdoor fixed camera",
	"Change ceiling trapdoor fixed camera",
	"Disable ceiling trapdoor fixed camera",
	"Add copyright notice under main menu",
	"Grenadegun ammo and animations",
	"Title logo fade in",
	"Fix PuzzleCombiner",
	"Classic vehicles",
	"Hit wall frames of run animation",
	"Waterfallmist status",
	"Vault height adjuster",
	"Horizon rotation",
	"Fix unresponsive flare throw",
	"Loose flare hold while running",
	"Enable duckcrawl anim states",
	"Decouple baboons animations",
	"Fix bad baboon attack check",
	"Remove baboon magic death",
	"Fix baboon bug",
	"Fix camera cutoff",
	"Fix loading level bug",
	"Wibble rooms TREP-style",
	"Wibble objects TREP-style",
	"Remove fire smoke",
	"Black fire smoke",
	"Crawl tilting",
	"Fix Spot Light",
	"Float matrices",
	"Fix Crossbow firing from LaserSight",
	"Synchronize LaserSight with animations",
	"Fix OldFlip 14 and 15",
	"Fix shatter bug",
	"No for Puzzle Holes and Key Holes",
	"Electric Lara",
	"Headlight"
};

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

static void ReferenceInject(void *reference, void *value) {
	memcpy(reference, value, sizeof(void *));
}

static void *malloc_inject(size_t size) {
	return malloc(size);
}

static void *realloc_inject(void *memblock, size_t size) {
	return realloc(memblock, size);
}

static void free_inject(void *memblock) {
	free(memblock);
}

static void *calloc_inject(size_t number, size_t size) {
	return calloc(number, size);
}

static void Inject_stdlib(bool replace) {
	ProcessInject(0x49DCD6, (unsigned int)malloc_inject, replace);
	ProcessInject(0x49ED23, (unsigned int)realloc_inject, replace);
	ProcessInject(0x49E22D, (unsigned int)free_inject, replace);
	ProcessInject(0x49F2DC, (unsigned int)calloc_inject, replace);
}

static void LoadTombNextGenerationInject_stdlib(bool replace) {
	ProcessInject(0x10135531, (unsigned int)malloc_inject, replace);
	ProcessInject(0x101353F9, (unsigned int)realloc_inject, replace);
	ProcessInject(0x101355BD, (unsigned int)free_inject, replace);
	ProcessInject(0x1013E496, (unsigned int)calloc_inject, replace);
}

static void LoadTombNextGenerationInject(bool replace) {
	Inject_stdlib(replace);
	LoadTombNextGenerationInject_stdlib(replace);
	LoadTombNextGenerationInject_TombNextGeneration(replace);
	LoadTombNextGenerationInject_ZRoomEditor(replace);
	LoadTombNextGenerationInject_Plugin(replace);
	LoadTombNextGenerationInject_ListTr4Patch(replace);
	LoadTombNextGenerationInject_TrngWeather(replace);
	LoadTombNextGenerationInject_ZPatchesTomb4(replace);
	LoadTombNextGenerationInject_Oggetti(replace);
	LoadTombNextGenerationInject_TrngElevator(replace);
	LoadTombNextGenerationInject_TrngFlipeffects(replace);
	LoadTombNextGenerationInject_TrngKeypad(replace);
}

static void __stdcall LoadInject(ULONG NotificationReason, LDR_DLL_NOTIFICATION_DATA *NotificationData, PVOID Context) {
	if (NotificationReason == 1 && !_wcsicmp(NotificationData->Loaded.BaseDllName->Buffer, L"Tomb_NextGeneration.dll"))
		LoadTombNextGenerationInject(REPLACE);
}

static void Terminate(const char *message) {
	MessageBox(NULL, message, "TRNG-CE Engine", MB_OK);
	TerminateProcess(GetCurrentProcess(), 0);
}

[[noreturn]] static void PluginErrorTerminate(const char *name) {
	char message[1024];

	strcpy_s(message, "The game can't start because ");
	strcat_s(message, name);
	strcat_s(message, " is incompatible with TRNG-CE. Try installing the latest version of the plugin to fix this problem.");
	Terminate(message);
	__assume(0);
}

static void CheckPluginVersion(const char *name, WORD major, WORD minor, WORD build, WORD revision) {
	DWORD size;
	LPVOID block;
	VS_FIXEDFILEINFO *version;
	UINT length;
	WORD required[4], actual[4];
	int index;

	if (!name || !GetModuleHandle(name))
		return;
	size = GetFileVersionInfoSize(name, NULL);
	if (!size)
		PluginErrorTerminate(name);
	block = HeapAlloc(GetProcessHeap(), 0, size);
	if (!block)
		PluginErrorTerminate(name);
	if (!GetFileVersionInfo(name, 0, size, block) || !VerQueryValue(block, "\\", (LPVOID*)&version, &length) || !length)
		PluginErrorTerminate(name);
	required[0] = major;
	required[1] = minor;
	required[2] = build;
	required[3] = revision;
	actual[0] = version->dwFileVersionMS >> 16;
	actual[1] = version->dwFileVersionMS & 0xFFFF;
	actual[2] = version->dwFileVersionLS >> 16;
	actual[3] = version->dwFileVersionLS & 0xFFFF;
	for (index = 0; index < 4; ++index) {
		if (actual[index] > required[index])
			break;
		if (actual[index] < required[index])
			PluginErrorTerminate(name);
	}
	HeapFree(GetProcessHeap(), 0, block);
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
	Inject_Vehicles(replace);
	Inject_Minecart(replace);
	Inject_Quadbike(replace);
	Inject_Gameflow(replace);
	Inject_Output(replace);
	Inject_Dxshell(replace);
	Inject_Polyinsert(replace);
	Inject_Control(replace);
	Inject_Pickup(replace);
	Inject_Input(replace);
	Inject_Newinv(replace);
	Inject_Effect2(replace);
	Inject_Items(replace);
	Inject_Box(replace);
	Inject_Laramisc(replace);
	Inject_Hair(replace);
	Inject_Spotcam(replace);
	Inject_Debris(replace);
	Inject_Scarab(replace);
	Inject_Text(replace);
	Inject_Effects(replace);
	Inject_Audio(replace);
	Inject_Specificfx(replace);
	Inject_Time(replace);
	Inject_Traps(replace);
	Inject_Sphere(replace);
	Inject_Delstuff(replace);
	Inject_Bike(replace);
	Inject_Lara1Gun(replace);
	Inject_Gamemain(replace);
	Inject_Camera(replace);
	Inject_Loadsave(replace);
	Inject_Sub(replace);
	Inject_Plugin_FlyCheat(GetModuleHandle("Plugin_FlyCheat.dll"), replace);
	Inject_Plugin_FlyCheat_trng(GetModuleHandle("Plugin_FlyCheat.dll"), replace);
	Inject_Plugin_Particlesystem_trng(GetModuleHandle("Plugin_ParticleSystem.dll"), replace);
	Inject_Plugin_Particlesystem(GetModuleHandle("Plugin_ParticleSystem.dll"), replace);
	Inject_Winmain(replace);
	Inject_Registry(replace);
	Inject_FunctionTable(replace);
	Inject_Health(replace);
	Inject_Init(replace);
	Inject_Laraflar(replace);
	Inject_Jeep(replace);
	Inject_Laraswim(replace);
	Inject_Lara(replace);
}

static LPSTR __stdcall CallInject() {
	int index;
	char message[1024];
	bool error;

	error = false;
	for (index = 0; index < 3; ++index) {
		if (!flep::pPatchMap[RequiredPatches[index]]) {
			if (!error) {
				strcpy_s(message, "The game can't start because the following required patches aren't enabled:\n\n");
				error = true;
			}
			strcat_s(message, PatchTitles[RequiredPatches[index]]);
			strcat_s(message, "\n");
		}
	}
	if (error) {
		strcat_s(message, "\nTry enabling the patches to fix this problem.");
		Terminate(message);
	}
	CheckPluginVersion("Plugin_FlyCheat.dll", 4, 0, 0, 2);
	CheckPluginVersion("Plugin_ParticleSystem.dll", 1, 0, 0, 1);
	Inject(REPLACE);
	GetCommandLineBinding = GetCommandLineA;
	return GetCommandLineA();
}

static void Break() {
	__debugbreak();
}

void ProcessInject(unsigned int from, unsigned int to, bool replace) {
	if (replace)
		ProcessInjectJump(from, to);
	else
		ProcessInjectJump(to, from);
}

void ModuleProcessInject(void *module, const char *name, unsigned int to, bool replace) {
	if (!module)
		ProcessInject((unsigned int) Break, to, false);
	else
		ProcessInject((unsigned int) GetProcAddress((HMODULE) module, name), to, replace);
}

void IndirectReferenceInject(void **reference) {
	ReferenceInject(reference, *reference);
}

void ModuleReferenceInject(void **reference, void *module) {
	void *address;

	address = module ? (void *) GetProcAddress((HMODULE) module, (LPCSTR) *reference) : (void *) 0xCCCCCCCC;
	ReferenceInject(reference, &address);
}

void CopyInject(void *module, const char *name, void *target, unsigned int size) {
	if (!module)
		return;
	memcpy(target, (void *) GetProcAddress((HMODULE) module, name), size);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
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
		Inject_stdlib(REPLACE);
		LdrRegisterDllNotification(0, LoadInject, NULL, &cookie);
		GetCommandLineBinding = CallInject;
	}
	return TRUE;
}
