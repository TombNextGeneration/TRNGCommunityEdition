#include "pch.h"

#pragma comment(linker, "/EXPORT:_DummyFunction,@1,NONAME")
extern "C" int DummyFunction() {
    return 0;
}

void Inject() {

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

