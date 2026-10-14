#pragma once
// GENERATED: by ghidra script ExportHooksToHeader.py

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't
// in the current exported address list NO_USE - something we dont really want to use for whatever reason USING_CODE -
// using the default lapi code implementation instead of hooking
namespace IHHook
{
    struct PatternEntry
    {
        std::string_view pattern;
        ptrdiff_t offset = 0; // relative to the start of the match
        std::function<void*(void*)> adjust = {}; // e.g. resolve RIP, add another offset, etc.
    };

    ankerl::unordered_dense::map<std::string, PatternEntry> mgsvtpp_patterns
    {

        { "FoxBlockProcess", { "74 34 41 8B D6", -0x90 } },

        { "FoxBlockLoad", { "E8 ? ? ? ? 48 8B 47 58 0F 28 00", 1,[](void* p) -> void*{return hook::get_address<void*>(p); } } },

        { "ff_stringid_hash_n", { "75 1D 4C 0F BE 01", -0x14 } },

        { "FoxStrHash32", { "E8 ? ? ? ? 89 06 8B 46 24", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }
                
                return addr; 
        } } },

        { "path_hash_code", { "75 13 8D 50 5C", -0x25 } },

        { "FNVHash32",{ "E8 ? ? ? ? C7 03 00 00 00 00 89 07", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "GetFreeMissionNameKey", { "83 F8 0A 74 59", -0x3 } },

        { "UpdateCamera", { "E8 ? ? ? ? 8B 87 0C 04 00 00", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },

        { "foxprintf",{ "E8 ? ? ? ? 49 8B 85 E0 00 00 00", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "l_StubbedOut", { "E8 ? ? ? ? 8B CF 8B E8", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "voidreturn", { "E8 ? ? ? ? 8B 4D 2C 8B C3", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "foxPathPath", { "E8 ? ? ? ? C7 45 D0 01 00 00 00 48 8B C7", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "UpdateLocalPathString", { "48 85 D2 74 13 E8", -0x1E } },

        { "foxPathPathB",{ "E8 ? ? ? ? 90 FF 03 41 0F B6 C4", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "foxPathEmpty", { "EB 12 E8 ? ? ? ? 48 8B D0 48 8D 4C 24 68", 3,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "GetPartsFpkPath", { "75 11 48 BA 95 03 6E 5B F2 E6 2A 52", -0x1F } },
        { "GetPartsFilePath", { "75 11 48 BA F6 46 0D 90 2A B8 A9 E0", -0x1F } },
        { "GetCamoFpkPath", { "48 8D 4D C8 E8 ? ? ? ? 90 48 8D 4B 18", 5, [](void* p) -> void* { return hook::get_address<void*>(p); } } },

        { "GetCamoFilePath",{ "E8 ? ? ? ? 90 44 8B CB 45 8B C6", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "GetFacialMtarFpkPath", { "48 BA 37 51 FD AD A4 1D 2A 52", -0x2F } },
        { "GetFacialMtarFilePath", { "48 BA F4 3D A0 26 35 8B 02 67", -0x2F } },

        { "GetHandFpkPath", { "48 8D 4D C8 E8 ? ? ? ? 90 48 8D 4B 08", 5, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "GetHandFilePath", { "48 8D 4D CF E8 ? ? ? ? 90 33 D2 48 8D 4D 8F", 5, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "_DoesNeedBodyFovaForDD", { "E8 ? ? ? ? 84 C0 0F 84 34 FF FF FF", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },

        { "GetBodyFovaPath", { "0F 84 71 01 00 00 FF CA", -0x28 } },
        { "DoesNeedFaceFova", { "E8 ? ? ? ? 84 C0 0F 84 A6 00 00 00 45 85 ED", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "DoesNeedFaceFovaForAvatar", { "8B CE E8 ? ? ? ? 84 C0 74 30", 3, [](void* p) -> void* { return hook::get_address<void*>(p); } } },

        { "GetFaceFpkPath", { "48 BA 64 7D A0 DF 0C 70 2B 52", -0x6C } },
        { "GetFaceFilePath", { "48 BA 7A E8 CA 78 25 5B 88 60", -0x6C } },

        { "GetAvatarHoneFpkPath", { "48 BA AF A4 61 4C 6C AF 28 52", -0x26 } },
        { "GetAvatarHoneFilePath", { "48 BA E9 40 E8 37 CB BE 8B 60", -0x26 } },

        { "GetPathAtBuddyType", { "E8 ? ? ? ? 90 48 83 7C 24 20 00 75 12", 1, [](void* p) -> void* { return hook::get_address<void*>(p); } } },
        { "GetBuddyQuietWeaponFileFromBuddyBlock", { "73 04 48 8B 14 CF", -0x5B } },
        { "GetPathAtSub_BuddyDog", { "48 BA 66 09 4D 2E 54 90 2A 52", 0xC } },
        { "GetPathAtSub_BuddyHorse", { "48 BA 66 09 4D 2E 54 90 2A 52", 0x15 } },
        { "GetBuddyGearArmFile", { "80 F9 03 73 0E", -0x2D } },
        { "GetBuddyGearHeadFile", { "80 F9 04 73 0E", -0x35 } },
        { "GetBuddyGearMainWeaponFile", { "80 F9 06 73 0E", -0x2D } },


        { "ReliefVehicleLoadToExhibit", { "74 17 0F B6 D0 48 8B 05", -0x2F } },
        { "ReliefVehicleLoad", { "48 83 C4 30 5B C3 48 8B 49 50", -0x14 } },

        { "GetBlockAtIndex",{ "E8 ? ? ? ? 48 8B 4B 58 0F B6 59 2C",1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

         { "gkGetColoringSystem",{ "E8 ? ? ? ? 41 B9 5F 00 00 00",1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },


        { "stdstringstring", { "75 F6 E8 ? ? ? ? 90", -0x39 } },

        { "GetBuddyCommandName", { "48 B8 16 1B 4E EC 11 E4 00 00", -0x29 } },
        { "BuddyCommandGetDescriptionLangId", { "48 B8 C1 91 D9 AE 7C 96 00 00", -0x29 } },


        { "GetChangeLocationMenuParameterByLocationId", { "74 3F 83 F8 14", -0x9 } },
        { "GetMbFreeChangeLocationMenuParameter", { "B9 62 75 00 00 66 90", -0x19 } },
        { "GetPhotoAdditionalTextLangId", { "40 88 7C 24 20 E8 ? ? ? ? 48 8B 18", 6, [](void* p) -> void* { return hook::get_address<void*>(p); } } },

        { "lua_newstate", { "41 B9 78 02 00 00 45 ? C0", -0x1D } },
        { "lua_close", { "48 8B 08 89 7B 60", -0x52 } },
        { "lua_newthread", { "48 39 82 80 00 00 00 72 05", -0x11 } },
        { "lua_atpanic", { "49 89 90 A8 00 00 00", -0xB } },
        { "lua_settop", { "78 42 4C 63 C2", -0x2 } },
        { "lua_pushvalue", { "4D 8B 42 10 48 8B 10", -0xC } },
        { "lua_remove",{ "E8 ? ? ? ? EB 05 BB 01 00 00 00", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_insert", { "E8 ? ? ? ? 49 83 3E 00 74 47", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_replace", { "75 16 48 8B 41 50", -0x15 } },
        { "lua_checkstack", { "7F 75 4C 8B 41 10", -0x13 } },
        { "lua_xmove", { "48 C1 E0 04 48 01 41 10", -0x14 } },
        { "lua_isnumber", { "75 05 48 83 C4 38 C3 B8 01 00 00 00", -0x1F } },
        { "lua_isstring", { "74 15 8B 40 08", -0x13 } },
        { "lua_iscfunction", { "83 78 08 06 75 13", -0x9 } },

        { "lua_type", { "E8 ? ? ? ? 83 F8 05 0F 85 8B 00 00 00", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_rawequal",{ "E8 ? ? ? ? 85 C0 74 4D 48 83 3F 00",1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_lessthan",{ "E8 ? ? ? ? 8B F8 48 8B CB 85 FF", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_tonumber", { "C3 F2 0F 10 00", -0x28 } },
        { "lua_tointeger", { "F2 48 0F 2C 00", -0x26 } },
        { "lua_toboolean", { "74 14 83 F9 01", -0xE } },
        { "lua_tolstring", { "75 1E 48 85 DB", -0x32 } },
        { "lua_objlen",{ "E8 ? ? ? ? 48 8B E8 BE 01 00 00 00",1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_tocfunction", { "75 12 48 8B 00", -0xD } },

        { "lua_touserdata",{ "E8 ? ? ? ? 48 8B F8 48 85 C0 0F 84 97 01 00 00", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_tothread", { "83 78 08 08 74 07", -0x9 } },

        { "lua_topointer",{ "74 49 48 89 5C 24 30 E8 ? ? ? ? BA 01 00 00 00", 8,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },


        { "lua_pushnil", { "48 8B 41 ? C7 40 ? 00 00 00 00 48 83 41" } },
        { "lua_pushnumber", { "48 8B 41 ? F2 0F 11 08" } },
        { "lua_pushinteger", { "48 8B 41 ? 0F 57 C0 F2 48 0F 2A C2"} },
        { "lua_pushlstring",{ "E8 ? ? ? ? 8B 44 24 48 4C 8D 44 24 58",1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_pushstring", { "75 0D 48 8B 41 10", -0x3 } },
        { "lua_pushvfstring", { "72 05 E8 ? ? ? ? ? ? ? 48", -0x27 } },
        { "lua_pushfstring", { "72 0A E8 ? ? ? ? 48 8B 54 24 38", -0x26 } },

        { "lua_pushcclosure", { "74 ? 48 8D 50 28",-0x67 } },
        { "lua_pushboolean",{ "0F B6 D0 E8 ? ? ? ? 48 8B 7C 24 60", 4,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_pushlightuserdata", { "48 8B 41 ? 48 89 10 C7" } },
        { "lua_pushthread", { "48 8B 41 ? 48 89 08 C7" } },
        { "lua_gettable", { "48 83 EC 28 ? ? ? E8 ? ? ? ? 4D 8B 42 10 49" } },
        { "lua_getfield", { "48 83 43 10 10 48 8B 5C 24 40", -0x56 } },
        { "lua_rawget",{ "E8 ? ? ? ? 48 8B D3 48 8B CB E8",1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_rawgeti",{ "E8 ? ? ? ? 41 83 C8 FF 48 8B D3 48 8D 4D E8", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_createtable",{ "E8 ? ? ? ? BA 53 00 00 00 48 8B CE", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_newuserdata",{ "E8 ? ? ? ? 0F 28 C6 0F 28 CE F3 0F 11 00", 1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_getmetatable", { "74 13 83 F9 07", -0x13 } },
        { "lua_getfenv", { "83 E9 06 74 3E", -0xF } },

        { "lua_settable", { "4C 8B 43 10 4D 8D ? F0", -0xE } },
        { "lua_setfield",{ "8B 5C 24 48 8B D3 48 8B CE", 0xA,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_rawset", { "48 8B 5F 10 48 8B 10", -0x17 } },
        { "lua_rawseti", { "48 8B 10 48 8B 5F 10", -0x1A } },

        { "lua_setmetatable", { "E8 ? ? ? ? 4F 8B 44 F5 00",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "lua_setfenv",{ "8D 50 FE 48 8B CB E8 ? ? ? ? 85 C0", 0x7,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_call",{ "75 12 48 8B 47 28",-0x29 } },

        { "lua_pcall", { "75 12 48 8B 4B 28", -0x63 } },
        { "lua_cpcall", { "48 83 EC 48 4C 8B 49 10" } }, // could be wrong ?

        { "lua_load", { "4D 85 C9 48 8D 1D", -0xA } },
        { "lua_dump",{ "48 8B D9 44 8D 42 05", 0x36,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_resume", { "3C 01 0F 84 86 00 00 00", -0x11 } },
        { "lua_gc", { "33 FF 48 8B F1 83 FA 07", -0x13 } },
        { "lua_error",{ "74 08 48 8B CF E8 ? ? ? ? 41 83 C8 FF", 0x6,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_next", { "4C 8B 43 10 48 8B 10 49 83 E8 10", -0xE } },
        { "lua_concat", { "83 FA 02 7C ? 4C 8B 41 20 49", -0xF } },
        { "lua_getstack", { "4C 8B 51 50 90", -0xB } },
        { "lua_getinfo", { "80 3A 3E 48 ? ? 75 ? 48", -0x1B } },

        { "lua_getlocal", { "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 63 42 ?" } },
        { "lua_setlocal", { "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 63 42 ?" } },


        { "lua_getupvalue",{ "E8 ? ? ? ? 48 85 C0 74 DE 48 8B D0 48 8B CB E8 ? ? ? ? BA FE FF FF FF",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "lua_setupvalue", { "33 C0 48 83 C4 28 C3 48 8B 10", -0x18 } },

        { "lua_sethook",{ "E8 ? ? ? ? 48 8B 5C 24 58 48 8B 6C 24 60 33 C0",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },


        { "luaI_openlib", { "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 20 41 83 CC FF" } },

        { "luaL_getmetafield", { "E8 ? ? ? ? 85 C0 75 10 48 8B 5C 24 30",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaL_callmeta",{ "E8 ? ? ? ? 85 C0 0F 85 E1 00 00 00",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaL_typerror",{ "E8 ? ? ? ? 48 8B 5C 24 40 0F 28 C6", 0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "luaL_argerror",{ "BA 01 00 00 00 E8 ? ? ? ? E9 DD 01 00 00", 0x6,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaL_checklstring", { "75 51 8D 50 04", -0x1F } },
        { "luaL_optlstring", { "7F 29 48 85 FF", -0x26 } },
        { "luaL_checknumber", { "0F 28 F0 75 1F", -0x20 } },
        { "luaL_checkinteger", { "75 0E 44 8D 43 03",-0x2D } },
        { "luaL_optinteger",{ "E8 ? ? ? ? 41 88 44 DE 12",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaL_checkstack",{ "E8 ? ? ? ? BE 01 00 00 00 41 8B ED", 0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "luaL_checktype",{ "E8 ? ? ? ? BA 02 00 00 00 48 8B CB 44 8D 42 04", 0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "luaL_checkany", { "83 F8 FF 75 11 4C 8D 05", -0x14 } },
        { "luaL_newmetatable", { "48 ? ? ? ? ? BA F0 D8 FF FF", -0xA } },
        { "luaL_checkudata",{ "E8 ? ? ? ? 48 8B D8 48 8B 08 48 85 C9", 0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaL_where", { "74 34 4C 8D 44 24 20", -0x2A } },
        { "luaL_error", { "48 8D 7C 24 50 E8", -0x1D } },
        { "luaL_checkoption", { "4A 8B 44 CF 08", -0x77 } },
        { "luaL_loadfile", { "83 F8 23 75 2C", -0x83 } },
        { "luaL_loadbuffer", { "4C 89 44 24 28 4C 8D 44 24 20", -0x9 } },
        { "luaL_newstate", { "48 ? ? 48 85 C0 74 12 48 8D 15", -0x14 } },
        { "luaL_gsub", { "49 FF C7 88 01", -0x177 } },

        { "luaL_findtable",{ "E8 ? ? ? ? 48 8B CB 48 85 C0 74 1E", 0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaL_prepbuffer", { "49 83 E8 18 74 32", -0xF } },
        { "luaL_addlstring", { "4C 3B C5 72 27",-0x39 } },

        { "luaL_addvalue",{ "E8 ? ? ? ? EB 44 48 8D 95 50 01 00 00",0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "luaL_pushresult",{ "E8 ? ? ? ? 48 85 FF 74 10 83 CA FF", 0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = hook::get_address<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },
        { "luaopen_base", { "E8 ? ? ? ? 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 ? ? E8 ? ? ? ? B8 02 00 00 00", -0x9 } },
        { "luaopen_table",{ "48 8B 7C 24 50 48 83 C4 30 5E 5D", 0x12,
            [](void* p) -> void*
            {
                uint8_t* addr = reinterpret_cast<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

        { "luaopen_io", { "48 8D 78 60 E8", -0x208 } },

        { "luaopen_os",{ "48 83 EC 20 49 8B E8 8B DA 48 8B F9", -0x40,
            [](void* p) -> void*
            {
                uint8_t* addr = reinterpret_cast<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },


         { "luaopen_string",{ "53 48 83 EC 20 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 ? ? E8 ? ? ? ? 4C 8D 05 ? ? ? ? 83 CA FF 48 ? ? E8 ? ? ? ? 4C 8D 05 ? ? ? ? BA FE FF FF FF 48 ? ? E8 ? ? ? ? 48 ? ? E8 ? ? ? ? B8 01 00 00 00 48 83 C4 20 5B C3", -0x1,
            [](void* p) -> void*
            {
                uint8_t* addr = reinterpret_cast<uint8_t*>(p);

                if (addr[0] != 0x40)
                {
                    return addr + 1;
                }

                return addr;
            } } },


        { "luaopen_math",{ "F2 0F 10 08 E8", -0x4A,
            [](void* p) -> void*
            {
                uint8_t* addr = reinterpret_cast<uint8_t*>(p);

                if (addr[0] != 0x40)
                {
                    return addr + 1;
                }

                return addr;
            } } },

         { "luaopen_debug",{ "48 8B CF E8 ? ? ? ? BA FE FF FF FF 48 8B CF E8 ? ? ? ? 48 8D 05",-0x7D,
            [](void* p) -> void*
            {
                uint8_t* addr = reinterpret_cast<uint8_t*>(p);

                if (addr[0] == 0xE9)
                {
                    return hook::get_address<void*>(addr + 1);
                }

                return addr;
            } } },

            
        { "luaopen_package",{ "FF C7 48 85 C0", -0xC7,
            [](void* p) -> void*
            {
                uint8_t* addr = reinterpret_cast<uint8_t*>(p);

                if (addr[0] != 0x40)
                {
                    return addr + 1;
                }

                return addr;
            } } },

        { "luaL_openlibs", { "75 CB 48 8B 5C 24 30 48 83 C4 20", -0x53 } },
    }; // map mgsvtpp_patterns
} // namespace IHHook
