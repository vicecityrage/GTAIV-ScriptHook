//
// Created by alex on 08/02/2021.
//

#include "main.hpp"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD fdwReason, LPVOID lpReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			ScriptHookManager::RegisterThread(&_fiberThread);
			break;

		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}