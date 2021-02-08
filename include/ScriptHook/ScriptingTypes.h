/*****************************************************************************\

  Copyright (C) 2009, Aru <oneforaru at gmail dot com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Please see ScriptHook-License.txt for information on how this source/header
  file is licensed as part of the ScriptHook SDK.

\*****************************************************************************/

#pragma once

#include "Types.h"

#define DefineScriptHandle(name) typedef struct name : ScriptHandle {} name
#define DefineInheritedScriptHandle(name, baseName) typedef struct name : baseName {} name

namespace Scripting
{

    typedef u32 ScriptVoid;     // We shall use ScriptVoid instead of explicit void because some 
                                // of our template code return values.

    typedef u32 ScriptAny;      // ScriptAny for any types that we don't know yet :)

    typedef struct ScriptHandle
    {
    private:
        u32 Handle;             // Handles are usually just uint32s

    public:
        ScriptHandle() : Handle(0) {}
        explicit ScriptHandle(u32 handle) : Handle(handle) {}
        inline b8 IsNull() const { return Handle == 0; }
        inline b8 IsValid() const { return Handle != 0; }
        inline u32 Get() const { return Handle; }

        // The comparison operation is only valid for handles of the same type!
        inline b8 operator == (const ScriptHandle &other) const { return Handle == other.Handle; }
        inline b8 operator != (const ScriptHandle &other) const { return Handle != other.Handle; }

        inline b8 operator == (const u32 handle) const { return Handle == handle; }
        inline b8 operator != (const u32 handle) const { return Handle != handle; }
    } ScriptHandle;

    // Explicitly defined handles
    // Use structs instead of just typedefing as ScriptHandle to enforce a bit of type-safety

    typedef u32 Player;     // Left as u32 for legacy support
    typedef u32 FireId;

	DefineScriptHandle(Ped);
	DefineScriptHandle(Vehicle);
	DefineScriptHandle(Cam);
	DefineScriptHandle(CarGenerator);
	DefineScriptHandle(Group);
	DefineInheritedScriptHandle(Train, Vehicle);
	DefineScriptHandle(Pickup);
	DefineScriptHandle(Object);
	DefineScriptHandle(Interior);
	DefineScriptHandle(Blip);
	DefineScriptHandle(Texture);
	DefineScriptHandle(TextureDict);
	DefineScriptHandle(CoverPoint);
	DefineScriptHandle(DecisionMaker);
	DefineScriptHandle(Camera);
	DefineScriptHandle(TaskSequence);

    // For legacy script support...
    typedef Ped Char;
    typedef Vehicle Car;

    // See http://www.gtamodding.com/index.php?title=Carcols.dat#GTA4 for more info
    typedef u32 ColourIndex;    // 0 thru 133 inclusive
    
    // Some real structures... these are never passed in directly, but only
    // by reference.

    typedef struct { f32 X, Y, Z; } Vector3;

}
