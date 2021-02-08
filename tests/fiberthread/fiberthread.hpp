//
// Created by alex on 08/02/2021.
//

#ifndef SCRIPTHOOK_FIBERTHREAD_HPP
#define SCRIPTHOOK_FIBERTHREAD_HPP

#include <windows.h>
#include <ScriptHook/Scripting.h>

#include <ScriptHook/Log.h>
#include <ScriptHook/ScriptThread.h>

#include <ScriptHook/ScriptingEnums.h>
#include <ScriptHook/ScriptingTypes.h>

#include <string>

class FiberThread :
		public ScriptThread
{
private:
	static Scripting::Player GetPlayer();
	static Scripting::Ped GetPlayerPed();

	static void SpawnCar(Scripting::eModel model);
	static void ChangePlayerSkin(Scripting::eModel model);
	static void TeleportToWaypoint(Scripting::Ped ped);

protected:
	// We don't want a Tick based script, so we override RunScript.
	void RunScript() override;

public:
	FiberThread();
};

#endif //SCRIPTHOOK_FIBERTHREAD_HPP
