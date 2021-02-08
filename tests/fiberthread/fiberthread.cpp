//
// Created by alex on 08/02/2021.
//

#include "fiberthread.hpp"

FiberThread::FiberThread()
{
	// Give your own name here!
	SetName(std::string("FiberThread").c_str());
}

// Some helper functions

Scripting::Player FiberThread::GetPlayer()
{
	Scripting::Player playerIndex = Scripting::ConvertIntToPlayerIndex(Scripting::GetPlayerId());
	return playerIndex;
}

Scripting::Ped FiberThread::GetPlayerPed()
{
	Scripting::Ped ped;
	Scripting::GetPlayerChar(GetPlayer(), &ped);
	return ped;
}


void FiberThread::SpawnCar(Scripting::eModel model)
{
	Scripting::RequestModel(model);

	while(!Scripting::HasModelLoaded(model))
	{
		Scripting::Wait(0);
	}

	LogInfo("Car model %d available... spawning it!", model);

	Scripting::Ped ped = GetPlayerPed();

	Scripting::Vehicle vehicle;
	f32 x,y,z;

	Scripting::GetCharCoordinates(ped, &x, &y, &z);
	Scripting::CreateCar(model, x, y, z, &vehicle, true);

	Scripting::MarkModelAsNoLongerNeeded(model);
}

void FiberThread::ChangePlayerSkin(Scripting::eModel model)
{
	Scripting::RequestModel(model);

	while(!Scripting::HasModelLoaded(model))
	{
		Scripting::Wait(0);
	}

	LogInfo("Skin model available... spawning it!");

	Scripting::eInteriorRoomKey roomKey;

	Scripting::GetKeyForCharInRoom(GetPlayerPed(), &roomKey);
	Scripting::ChangePlayerModel(GetPlayer(), model);

	Scripting::SetRoomForCharByKey(GetPlayerPed(), roomKey);
	Scripting::MarkModelAsNoLongerNeeded(model);
}

void FiberThread::TeleportToWaypoint(Scripting::Ped ped)
{
	Scripting::Blip b = GetFirstBlipInfoId(Scripting::BLIP_WAYPOINT);
	if(b.IsValid())
	{
		Scripting::Vector3 v;
		GetBlipCoords(b, &v);

		LogInfo("Teleporting to %f, %f", v.X, v.Y);

		// Thanks to Prince-Link for this magical Z coord detection code...
		Scripting::SetCharCoordinates(ped, v.X, v.Y, v.Z);
		while(v.Z == 0.0f) // The chance that ground Z is 0.0 _exactly_ is really small
		{
			Scripting::GetGroundZFor3DCoord(v.X, v.Y, 1000, &v.Z);
			Scripting::Wait(0);
		}

		Scripting::SetCharCoordinates(ped, v.X, v.Y, v.Z);
	}
	else
	{
		LogError("No way point found to teleport to.");
	}
}


// The real script

void FiberThread::RunScript()
{
	// This is a fiber thread, so we use an loop to run the contents of this script.
	// The thread will terminate when we return from this function.

	while(IsThreadAlive())
	{

		if ((GetAsyncKeyState(VK_F4) & 1) != 0)
		{
			LogInfo("Teleporting player to way point");

			TeleportToWaypoint( GetPlayerPed() );
		}
		else if ((GetAsyncKeyState(VK_F5) & 1) != 0)
		{
			LogInfo("Spawning a random car");

			Scripting::Vehicle vehicle;
			u32 modelHash;
			Scripting::ScriptAny unknown;

			f32 x,y,z;
			GetCharCoordinates(GetPlayerPed(), &x, &y, &z);

			Scripting::GetRandomCarModelInMemory(true, &modelHash, &unknown);
			CreateCar(modelHash, x, y, z, &vehicle, true);
		}
		else if ((GetAsyncKeyState(VK_F6) & 1) != 0)
		{
			LogInfo("Granting player $1000");

			Scripting::AddScore(GetPlayer(), 1000);
		}
		else if ((GetAsyncKeyState(VK_F7) & 1) != 0)
		{
			LogInfo("Requested a MODEL_BANSHEE spawn");

			SpawnCar(Scripting::MODEL_BANSHEE);
		}
		else if ((GetAsyncKeyState(VK_F8) & 1) != 0)
		{
			LogInfo("Changing the player skin");

			ChangePlayerSkin(Scripting::MODEL_IG_JOHNNYBIKER);
		}
		else if ((GetAsyncKeyState(VK_F9) & 1) != 0)
		{
			LogInfo("Changing the player skin back to Niko's");

			ChangePlayerSkin(Scripting::MODEL_PLAYER);
		}

		// Call Wait() so we can process other scripts/game code
		// You must call Wait(...) in your loop code for a fiber thread!
		Wait(100);
	}
}