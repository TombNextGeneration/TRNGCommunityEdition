#include "pch.h"

#pragma comment(linker, "/EXPORT:_DummyFunction,@1,NONAME")
extern "C" int DummyFunction() {
    return 0;
}

#pragma pack(push, 1)
struct Jump {
    BYTE opcode;
    DWORD offset;
};
#pragma pack(pop)

static void WriteProcessJump(DWORD from, DWORD to) {
    DWORD protection;
    Jump buffer;

    VirtualProtect((LPVOID) from, sizeof(Jump), PAGE_EXECUTE_READWRITE, &protection);
    buffer.opcode = 0xE9;
    buffer.offset = to - from + sizeof(Jump);
    memcpy((void *) from, &buffer, sizeof(Jump));
    VirtualProtect((LPVOID) from, sizeof(Jump), protection, &protection);
}

void WriteProcess(DWORD from, DWORD to, bool replace) {
    if (replace)
        WriteProcessJump(from, to);
    else
        WriteProcessJump(to, from);
}

static void Inject() {

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Inject();
        break;
    }
    return TRUE;
}

