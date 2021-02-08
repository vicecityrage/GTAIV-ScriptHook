//
// Created by alex on 08/02/2021.
//

#ifndef SCRIPTHOOK_MAIN_HPP
#define SCRIPTHOOK_MAIN_HPP

#include <windows.h>
#include <ScriptHook/ScriptHookManager.h>

#include "fiberthread.hpp"

static FiberThread _fiberThread;
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved);

#endif //SCRIPTHOOK_MAIN_HPP
