#pragma once
#include "lua.h"

namespace IHHook
{
    namespace Hooks_Character
    {

        enum PlayerType : uint
        {
            PlayerType_SNAKE = 0,     // Snake
            PlayerType_DD_MALE = 1,   // Diamond Dogs Soldier (Male)
            PlayerType_DD_FEMALE = 2, // Diamond Dogs Soldier (Female)
            PlayerType_AVATAR = 3,    // Avatar
            PlayerType_LIQUID = 4,    // Eli
            PlayerType_OCELOT = 5,    // Ocelot
            PlayerType_QUIET = 6,     // Quiet

            PlayerType_MAX = 255,
        };

        enum PlayerPartsType : uint
        {
            PlayerPartsType_NORMAL = 0,            // STANDARD
            PlayerPartsType_NORMAL_SCARF = 1,      // SCARF
            PlayerPartsType_SNEAKING_SUIT = 2,     // SV-SNEAKING SUIT
            PlayerPartsType_HOSPITAL = 3,          // HOSPTIAL
            PlayerPartsType_MGS1 = 4,              // SOLID SNAKE
            PlayerPartsType_NINJA = 5,             // CYBORG NINJA
            PlayerPartsType_RAIDEN = 6,            // RAIDEN
            PlayerPartsType_NAKED = 7,             // NAKED
            PlayerPartsType_SNEAKING_SUIT_TPP = 8, // SNEAKING SUIT
            PlayerPartsType_BATTLEDRESS = 9,       // BATTLE DRESS
            PlayerPartsType_PARASITE = 10,         // PARASITE SUIT
            PlayerPartsType_LEATHER = 11,          // LEATHER JACKET
            PlayerPartsType_GOLD = 12,             // NAKED (GOLD)
            PlayerPartsType_SILVER = 13,           // NAKED (SILVER)
            PlayerPartsType_AVATAR_EDIT_MAN = 14,  // AVATAR
            PlayerPartsType_MGS3 = 15,             // FATIGUES (NS) STANDARD
            PlayerPartsType_MGS3_NAKED = 16,       // FATIGUES (NS) NAKED
            PlayerPartsType_MGS3_SNEAKING = 17,    // SNEAKING SUIT (NS)
            PlayerPartsType_MGS3_TUXEDO = 18,      // TUXEDO
            PlayerPartsType_EVA_CLOSE = 19,        // JUMPSUIT (EVA) STANDARD
            PlayerPartsType_EVA_OPEN = 20,         // JUMPSUIT (EVA) NAKED
            PlayerPartsType_BOSS_CLOSE = 21,       // SNEAKING SUIT (TB)
            PlayerPartsType_BOSS_OPEN = 22,        // SNEAKING SUIT (TB) NAKED
            PlayerPartsType_SWIMWEAR = 23,         // SWIMSUIT
            PlayerPartsType_SWIMWEAR_G = 24,       // GOB SUIT
            PlayerPartsType_SWIMWEAR_H = 25,       // MEG SUIT

            PlayerPartsType_MAX = 255,
        };

        enum PlayerCamoType : uint
        {
            PlayerCamoType_OLIVEDRAB = 0,
            PlayerCamoType_SPLITTER = 1,
            PlayerCamoType_SQUARE = 2,
            PlayerCamoType_TIGERSTRIPE = 3,
            PlayerCamoType_GOLDTIGER = 4,
            PlayerCamoType_FOXTROT = 5,
            PlayerCamoType_WOODLAND = 6,
            PlayerCamoType_WETWORK = 7,
            PlayerCamoType_ARBANGRAY = 8,
            PlayerCamoType_ARBANBLUE = 9,
            PlayerCamoType_SANDSTORM = 10,
            PlayerCamoType_REALTREE = 11,
            PlayerCamoType_INVISIBLE = 12,
            PlayerCamoType_BLACK = 13,

            PlayerCamoType_SNEAKING_SUIT_GZ = 14,
            PlayerCamoType_SNEAKING_SUIT_TPP = 15,
            PlayerCamoType_BATTLEDRESS = 16,
            PlayerCamoType_PARASITE = 17,
            PlayerCamoType_NAKED = 18,
            PlayerCamoType_LEATHER = 19,
            PlayerCamoType_SOLIDSNAKE = 20,
            PlayerCamoType_NINJA = 21,
            PlayerCamoType_RAIDEN = 22,
            PlayerCamoType_HOSPITAL = 23,
            PlayerCamoType_GOLD = 24,
            PlayerCamoType_SILVER = 25,
            PlayerCamoType_PANTHER = 26,
            PlayerCamoType_AVATAR_EDIT_MAN = 27,

            PlayerCamoType_MGS3 = 28,
            PlayerCamoType_MGS3_NAKED = 29,
            PlayerCamoType_MGS3_SNEAKING = 30,
            PlayerCamoType_MGS3_TUXEDO = 31,
            PlayerCamoType_EVA_CLOSE = 32,
            PlayerCamoType_EVA_OPEN = 33,
            PlayerCamoType_BOSS_CLOSE = 34,
            PlayerCamoType_BOSS_OPEN = 35,

            PlayerCamoType_WOODLAND_FLECK = 36,
            PlayerCamoType_AMBUSH = 37,
            PlayerCamoType_SOLUM = 38,
            PlayerCamoType_DEAD_LEAF = 39,
            PlayerCamoType_LICHEN = 40,
            PlayerCamoType_STONE = 41,
            PlayerCamoType_PARASITE_MIST = 42,
            PlayerCamoType_OLD_ROSE = 43,
            PlayerCamoType_BRICK_RED = 44,
            PlayerCamoType_IRON_BLUE = 45,
            PlayerCamoType_STEEL_GREY = 46,
            PlayerCamoType_TSELINOYARSK = 47,
            PlayerCamoType_NIGHT_SPLITTER = 48,
            PlayerCamoType_RAIN = 49,
            PlayerCamoType_GREEN_TIGER_STRIPE = 50,
            PlayerCamoType_BIRCH_LEAF = 51,
            PlayerCamoType_DESERT_AMBUSH = 52,
            PlayerCamoType_DARK_LEAF_FLECK = 53,
            PlayerCamoType_NIGHT_BUSH = 54,
            PlayerCamoType_GRASS = 55,
            PlayerCamoType_RIPPLE = 56,
            PlayerCamoType_CITRULLUS = 57,
            PlayerCamoType_DIGITAL_BUSH = 58,
            PlayerCamoType_ZEBRA = 59,
            PlayerCamoType_DESERT_SAND = 60,
            PlayerCamoType_STEEL_KHAKI = 61,
            PlayerCamoType_DARK_RUBBER = 62,
            PlayerCamoType_GRAY = 63,
            PlayerCamoType_CAMOFLAGE_YELLOW = 64,
            PlayerCamoType_CAMOFLAGE_GREEN = 65,
            PlayerCamoType_IRON_GREEN = 66,
            PlayerCamoType_LIGHT_RUBBER = 67,
            PlayerCamoType_RED_RUST = 68,
            PlayerCamoType_STEEL_GREEN = 69,
            PlayerCamoType_STEEL_ORANGE = 70,
            PlayerCamoType_MUD = 71,
            PlayerCamoType_STEEL_BLUE = 72,
            PlayerCamoType_DARK_RUST = 73,
            PlayerCamoType_CITRULLUS_TWOTONE = 74,
            PlayerCamoType_GOLD_TIGER_STRIPE_TWOTONE = 75,
            PlayerCamoType_BIRCH_LEAF_TWOTONE = 76,
            PlayerCamoType_STONE_TWOTONE = 77,
            PlayerCamoType_KHAKI_URBAN_TWOTONE = 78,

            PlayerCamoType_SWIMWEAR_OLIVEDRAB = 79,
            PlayerCamoType_SWIMWEAR_TIGERSTRIPE = 80,
            PlayerCamoType_SWIMWEAR_GOLDTIGER = 81,
            PlayerCamoType_SWIMWEAR_FOXTROT = 82,
            PlayerCamoType_SWIMWEAR_WETWORK = 83,
            PlayerCamoType_SWIMWEAR_SPLITTER = 84,
            PlayerCamoType_SWIMWEAR_PARASITE_MIST = 85,
            PlayerCamoType_SWIMWEAR_OLD_ROSE = 86,
            PlayerCamoType_SWIMWEAR_CAMOFLAGE_GREEN = 87,
            PlayerCamoType_SWIMWEAR_IRON_BLUE = 88,
            PlayerCamoType_SWIMWEAR_RED_RUST = 89,
            PlayerCamoType_SWIMWEAR_MUD = 90,

            PlayerCamoType_SWIMWEAR_G_OLIVEDRAB = 91,
            PlayerCamoType_SWIMWEAR_G_TIGERSTRIPE = 92,
            PlayerCamoType_SWIMWEAR_G_GOLDTIGER = 93,
            PlayerCamoType_SWIMWEAR_G_FOXTROT = 94,
            PlayerCamoType_SWIMWEAR_G_WETWORK = 95,
            PlayerCamoType_SWIMWEAR_G_SPLITTER = 96,
            PlayerCamoType_SWIMWEAR_G_PARASITE_MIST = 97,
            PlayerCamoType_SWIMWEAR_G_OLD_ROSE = 98,
            PlayerCamoType_SWIMWEAR_G_CAMOFLAGE_GREEN = 99,
            PlayerCamoType_SWIMWEAR_G_IRON_BLUE = 100,
            PlayerCamoType_SWIMWEAR_G_RED_RUST = 101,
            PlayerCamoType_SWIMWEAR_G_MUD = 102,

            PlayerCamoType_SWIMWEAR_H_OLIVEDRAB = 103,
            PlayerCamoType_SWIMWEAR_H_TIGERSTRIPE = 104,
            PlayerCamoType_SWIMWEAR_H_GOLDTIGER = 105,
            PlayerCamoType_SWIMWEAR_H_FOXTROT = 106,
            PlayerCamoType_SWIMWEAR_H_WETWORK = 107,
            PlayerCamoType_SWIMWEAR_H_SPLITTER = 108,
            PlayerCamoType_SWIMWEAR_H_PARASITE_MIST = 109,
            PlayerCamoType_SWIMWEAR_H_OLD_ROSE = 110,
            PlayerCamoType_SWIMWEAR_H_CAMOFLAGE_GREEN = 111,
            PlayerCamoType_SWIMWEAR_H_IRON_BLUE = 112,
            PlayerCamoType_SWIMWEAR_H_RED_RUST = 113,
            PlayerCamoType_SWIMWEAR_H_MUD = 114,

            PlayerCamoType_OCELOT = 115,
            PlayerCamoType_QUIET = 116,

            PlayerCamoType_MAX = 255,
        };

        enum PlayerHandType : uint
        {
            PlayerHandType_NONE = 0,
            PlayerHandType_NORMAL = 1,
            PlayerHandType_STUN_ARM = 2,
            PlayerHandType_JEHUTY = 3,
            PlayerHandType_STUN_ROCKET = 4,
            PlayerHandType_KILL_ROCKET = 5,
            PlayerHandType_GOLD = 6,
            PlayerHandType_SILVER = 7,

            PlayerHandType_MAX = 255,
        };

        enum PlayerFaceEquip : char
        {
            PlayerFaceEquip_NONE = 0,
            PlayerFaceEquip_BANDANA = 1,
            PlayerFaceEquip_MUGEN_BANDANA = 2,
        };

        void CreateHooks();
        int CreateLibs(lua_State* L);

        int l_SetOverrideCharacterSystem(lua_State* L);
        int l_SetPlayerTypeForPartsType(lua_State* L);
        int l_SetPlayerPartsTypeForPartsType(lua_State* L);
        int l_SetUseHeadForPlayerParts(lua_State* L);
        int l_SetUseBionicHandForPlayerParts(lua_State* L);

        int l_SetPlayerPartsFpkPath(lua_State* L);
        int l_SetPlayerPartsPartsPath(lua_State* L);
        int l_SetSkinToneFv2Path(lua_State* L);
        int l_SetPlayerCamoFpkPath(lua_State* L);
        int l_SetPlayerCamoFv2Path(lua_State* L);
        int l_SetBionicHandFpkPath(lua_State* L);
        int l_SetBionicHandFv2Path(lua_State* L);
        int l_SetSnakeFaceFpkPath(lua_State* L);
        int l_SetSnakeFaceFv2Path(lua_State* L);
        int l_SetAvatarHornFpkPath(lua_State* L);
        int l_SetAvatarHornFv2Path(lua_State* L);

        // UNUSED alternative
        int l_SetPlayerPartsFpk(lua_State* L);
        int l_SetPlayerPartsPart(lua_State* L);
    } // namespace Hooks_Character
} // namespace IHHook
