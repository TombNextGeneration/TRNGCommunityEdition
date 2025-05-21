#include "framework.h"
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

#pragma pack(push, 1)
struct Jump {
    unsigned char opcode;
    unsigned int offset;
};
#pragma pack(pop)

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
    Inject_ZPatchesTomb4(replace);
    Inject_TrngElevator(replace);
    Inject_Oggetti(replace);
    Inject_TombNextGeneration(replace);
    Inject_Objects(replace);
    Inject_Collide(replace);
}

static LPSTR __stdcall CallInject() {
    Inject(true);
    GetCommandLineBinding = GetCommandLineA;
    return GetCommandLineA();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        GetCommandLineBinding = CallInject;
        break;
    }
    return TRUE;
}

