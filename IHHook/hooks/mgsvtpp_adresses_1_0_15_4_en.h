#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteAddressHFile

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking

#include <map>

namespace IHHook {
	std::map<std::string, int64_t> mgsvtpp_adresses_1_0_15_4_en{
		//{"BlockHeapAlloc", 0x1400dcb50},
		//{"BlockHeapFree", 0x1400dcbc0},
		{"FoxBlockProcess", 0x14006e4e0},//double fox::Block::Process(BlockMemory *blockMemory,undefined8 param_2,longlong *param_3)
		//{"FoxBlockUnload", 0x14006f990},
		//{"FoxBlockReload", 0x14006f320},
		//{"FoxBlockActivate", 0x14006cb20},
		//{"FoxBlockDeactivate", 0x14314a000},
		//{"FoxGenerateUniqueName", 0x1400e0210},
		//{"FoxBlock", 0x143145960},
		{"FoxBlockLoad", 0x14006e040},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)
		//{"BlockMemoryAllocTail", 0x1400dbb30},
		//{"BlockMemoryAllocHeap", 0x143261bf0},
		//{"GetCurrentBlockMemory", 0x14328e410},

		{"ff_stringid_hash_n", 0x141a09ac0},//ff_stringid_hash_n
		{"FoxStrHash32", 0x1400234c0},//fox::FoxStrHash32
		//tex TODO need to verify naming and purpose. 
		//technically this is PathFileNameExt64, but given that PathCode - 
		//without ext is likely less used than PathCode 
		//would have been a better name for PathFileNameExt64
		{"path_hash_code", 0x141a098e0},//path_hash_code
		{"FNVHash32", 0x14033b9d0},//TODO find in prerelease map

		{"GetFreeMissionNameKey", 0x1409121c0},//tpp::ui::utility::GetFreeMissionNameKey
		
		//tex: TODO: verify the return AL>RAX
		{"UpdateCamera", 0x141115ed0},//tpp::gamecore::camera::Player2CameraController::UpdateCamera
		
		//tex: Some info printing function that has been stubbed out
		{"foxprintf", 0x14002ab70},//fox::printf
		
		//tex: another retail stubb out to wrangle
		{"l_StubbedOut", 0x141c658e0},//char * __cdecl tpp::ef::OutOfMissionRangeEffectLua::SetupInterp(uint param_1,uint param_2)
		//tex: another retail stubb out to wrangle
		{"voidreturn", 0x140645940},//re::voidreturn	

		{"foxPathPath", 0x140085700},//Path * fox::Path::Path(Path *path,PathCode64 hash)
		{"UpdateLocalPathString", 0x140040c60},//fox::fs::Path::UpdateLocalPathString
		{"foxPathPathB", 0x1400855e0},//Path * __thiscall fox::Path::Path(Path *this,Path *rhs)
		{"foxPathEmpty", 0x140085990},//Path * fox::Path::Empty(void)

		{"GetPartsFpkPath", 0x140ae9a20},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetPartsFilePath", 0x140ae9980},//tpp::gm::player::ResourceTable::GetPartsFilePath
		{"GetCamoFpkPath", 0x140ae9080},//tpp::gm::player::ResourceTable::GetCamoFpkPath
		{"GetCamoFilePath", 0x140ae8fb0},//tpp::gm::player::ResourceTable::GetCamoFilePath
		{"GetFacialMtarFpkPath", 0x140ae9780},//tpp::gm::player::ResourceTable::GetFacialMtarFpkPath
		{"GetFacialMtarFilePath", 0x140ae96e0},//tpp::gm::player::ResourceTable::GetFacialMtarFilePath
		{"GetHandFpkPath", 0x140ae98d0},//tpp::gm::player::ResourceTable::GetHandFpkPath
		{"GetHandFilePath", 0x140ae9820},//tpp::gm::player::ResourceTable::GetHandFilePath
		{"_DoesNeedBodyFovaForDD", 0x140ae9be0},//tpp::gm::player::`anonymous_namespace'::_DoesNeedBodyFovaForDD
		{"GetBodyFovaPath", 0x140ae8d40},//tpp::gm::player::ResourceTable::GetBodyFovaPath
		{"DoesNeedFaceFova", 0x140ae8c90},//tpp::gm::player::ResourceTable::DoesNeedFaceFova
		{"DoesNeedFaceFovaForAvatar", 0x140ae8ce0},//tpp::gm::player::ResourceTable::DoesNeedFaceFovaForAvatar
		{"GetFaceFpkPath", 0x140ae95d0},//tpp::gm::player::ResourceTable::GetFaceFpkPath
		{"GetFaceFilePath", 0x140ae94c0},//tpp::gm::player::ResourceTable::GetFaceFilePath

		{"GetAvatarHoneFpkPath", 0x140ae7440},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFpkPath
		{"GetAvatarHoneFilePath", 0x140ae73d0},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFilePath

		{"GetPathAtBuddyType", 0x140a46870},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtBuddyType
		{"GetBuddyQuietWeaponFileFromBuddyBlock", 0x140a465c0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyQuietWeaponFileFromBuddyBlock
		{"GetPathAtSub_BuddyDog", 0x140a46d4a},//part of 140a46360 tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtSub
		{"GetPathAtSub_BuddyHorse", 0x140a46d53},//ditto
		{"GetBuddyGearArmFile", 0x140a46170},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearArmFile
		{"GetBuddyGearHeadFile", 0x140a462e0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearHeadFile
		{"GetBuddyGearMainWeaponFile", 0x140a46390},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearMainWeaponFile
		//{"foxBlockLoad", 0x143151e80},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)

		{"ReliefVehicleLoadToExhibit", 0x140b3abf0},//tpp::gm::vehicle::ReliefBlockController::LoadToExhibit
		{"ReliefVehicleLoad", 0x140b3ab50},//tpp::gm::vehicle::ReliefBlockController::Load

		{"GetBlockAtIndex", 0x14006d790},// fox::BlockGroup::GetBlockAtIndex

		{"gkGetColoringSystem", 0x1405cef50},//tpp::gk::GetColoringSystem
		{"stdstringstring", 0x140016490},//string * __thiscall std::string::string(string *this,char *cStr)

		{"GetBuddyCommandName", 0x14110d320},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandName
		{"BuddyCommandGetDescriptionLangId", 0x14110d0d0},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandHelpName

		{"GetChangeLocationMenuParameterByLocationId",0x140926730},//tpp::ui::menu::MotherBaseMissionCommonData::GetChangeLocationMenuParameterByLocationId
		{"GetMbFreeChangeLocationMenuParameter",0x140926860},//tpp::ui::menu::MotherBaseMissionCommonData::GetMbFreeChangeLocationMenuParameter
		{"GetPhotoAdditionalTextLangId",0x140926940},//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId

		{"lua_newstate", 0x141a16510},//tex could use default implementation, but may want to hook if we want to see what the engine is up to
		{"lua_close", 0x141a16480},
		{"lua_newthread", 0x141a11550},
		{"lua_atpanic", 0x141a10ca0},
		//{"lua_gettop", USING_CODE},
		{"lua_settop", 0x141a11f70},
		{"lua_pushvalue", 0x141a119d0},
		{"lua_remove", 0x141a11c20},
		{"lua_insert", 0x141a11390},
		{"lua_replace", 0x141a11c70},
		{"lua_checkstack", 0x141a10d10},
		{"lua_xmove", 0x141a12350},
		{"lua_isnumber", 0x141a11410},
		{"lua_isstring", 0x141a11440},
		{"lua_iscfunction", 0x141a113e0},
		//{"lua_isuserdata", USING_CODE},//tex: No calls in lua distro, so may be hard to find, or have been culled by compilation
		{"lua_type", 0x141a12300},
		//{"lua_typename", USING_CODE},
		//{"lua_equal", NOT_FOUND},//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
		{"lua_rawequal", 0x141a11a50},
		{"lua_lessthan", 0x141a114b0},
		{"lua_tonumber", 0x141a121f0},
		{"lua_tointeger", 0x141a12120},
		{"lua_toboolean", 0x141a120c0},
		{"lua_tolstring", 0x141a12150},
		{"lua_objlen", 0x141a11640},
		{"lua_tocfunction", 0x141a120f0},
		{"lua_touserdata", 0x141a122c0},
		{"lua_tothread", 0x141a122a0},
		{"lua_topointer", 0x141a12230},
		{"lua_pushnil", 0x141a11930},
		{"lua_pushnumber", 0x141a11950},
		{"lua_pushinteger", 0x141a11880},
		{"lua_pushlstring", 0x141a118c0},
		{"lua_pushstring", 0x141a11970},
		{"lua_pushvfstring", 0x141a11a00},
		{"lua_pushfstring", 0x141a11830},
		{"lua_pushcclosure", 0x141a11770},
		{"lua_pushboolean", 0x141a11750},
		{"lua_pushlightuserdata", 0x141a118a0},
		{"lua_pushthread", 0x141a119a0},
		{"lua_gettable", 0x141a112b0},
		{"lua_getfield", 0x141a111e0},
		{"lua_rawget", 0x141a11aa0},
		{"lua_rawgeti", 0x141a11ae0},//via MACRO lua_getref
		{"lua_createtable", 0x141a10e80},
		{"lua_newuserdata", 0x141a11590},
		{"lua_getmetatable", 0x141a11250},
		{"lua_getfenv", 0x141a11160},
		{"lua_settable", 0x141a11f40},
		{"lua_setfield", 0x141a11e00},
		{"lua_rawset", 0x141a11b20},
		{"lua_rawseti", 0x141a11ba0},
		{"lua_setmetatable", 0x141a11e80},
		{"lua_setfenv", 0x141a11d60},
		{"lua_call", 0x141a10cc0},
		{"lua_pcall", 0x141a116c0},
		{"lua_cpcall", 0x140bf2e90},
		{"lua_load", 0x141a11500},
		{"lua_dump", 0x141a10ef0},
		//{"lua_yield", USING_CODE},//tex: DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)
		{"lua_resume", 0x141a13320},
		//{"lua_status", USING_CODE},//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
		{"lua_gc", 0x141a10fb0},
		{"lua_error", 0x141a10fa0},
		{"lua_next", 0x141a11600},
		{"lua_concat", 0x141a10db0},
		//{"lua_getallocf", NO_USE},//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
		//{"lua_setallocf", NO_USE},//tex don't really want to mess with allocator function anyway
		//{"lua_setlevel", NO_USE},//tex: labeled by lua as a hack to be removed in lua 5.2
		{"lua_getstack", 0x141a20d40},
		{"lua_getinfo", 0x141a20be0},
		{"lua_getlocal", 0x141a20cd0},
		{"lua_setlocal", 0x141a20df0},
		{"lua_getupvalue", 0x141a112f0},
		{"lua_setupvalue", 0x141a11fd0},
		{"lua_sethook", 0x141a20dc0},
		//{"lua_gethook", USING_CODE},
		//{"lua_gethookmask", USING_CODE},
		//{"lua_gethookcount", USING_CODE},
		{"luaI_openlib", 0x141a17c30},
		//{"luaL_register", USING_CODE},
		{"luaL_getmetafield", 0x141a17410},
		{"luaL_callmeta", 0x141a16e80},
		{"luaL_typerror", 0x141a18240},
		{"luaL_argerror", 0x141a16d70},
		{"luaL_checklstring", 0x141a16f90},
		{"luaL_optlstring", 0x141a17e20},
		{"luaL_checknumber", 0x141a17020},
		//{"luaL_optnumber", USING_CODE},//tex: Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes
		{"luaL_checkinteger", 0x141a16f40},
		{"luaL_optinteger", 0x141a17db0},
		{"luaL_checkstack", 0x141a17140},
		{"luaL_checktype", 0x141a17180},
		{"luaL_checkany", 0x141a16f00},
		{"luaL_newmetatable", 0x141a17b70},
		{"luaL_checkudata", 0x141a171c0},
		{"luaL_where", 0x141a18170},
		{"luaL_error", 0x141a17280},
		{"luaL_checkoption", 0x141a17080},
		//{"luaL_ref", USING_CODE},//tex: Unsure on this address. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param
		//{"luaL_unref", USING_CODE},
		{"luaL_loadfile", 0x141a17910},
		{"luaL_loadbuffer", 0x141a178e0},
		//{"luaL_loadstring", USING_CODE},
		{"luaL_newstate", 0x141a17bf0},
		{"luaL_gsub", 0x141a17490},
		{"luaL_findtable", 0x141a172e0},
		//{"luaL_buffinit", USING_CODE},
		{"luaL_prepbuffer", 0x141a17f10},
		{"luaL_addlstring", 0x141a16bf0},
		//{"luaL_addstring", USING_CODE},//tex: Only call is in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
		{"luaL_addvalue", 0x141a16cb0},
		{"luaL_pushresult", 0x141a17f70},
		{"luaopen_base", 0x141a2f1f0},
		{"luaopen_table", 0x141a2fe20},
		{"luaopen_io", 0x141a310d0},//48 89 5c 24 08 48 89 74 24 10
		{"luaopen_os", 0x141a31eb0},
		{"luaopen_string", 0x141a33330},
		{"luaopen_math", 0x141a34ae0},
		{"luaopen_debug", 0x141a35a10},//48 83 ec 28 4c 8d 05 b5 23 a8 00
		{"luaopen_package", 0x141a364f0},
		{"luaL_openlibs", 0x141a16980},
		
		//{"IsUseAreaIcon",0x140f23e00},//tpp::ui::menu::impl::MbDvcMapCallbackIconImpl::IsUseAreaIcon
		//{"ConvertRadioTypeToSpeechLabel",0x140d685c0},//tpp::gm::CpRadioService::ConvertRadioTypeToSpeechLabel
		//{"ConvertSpeechLabelToRadioType",0x140d58d20},//tpp::gm::CpRadioService::ConvertSpeechLabelToRadioType
		//{"CallWithRadioType",0x1473cff10},//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallWithRadioType
		//{"StateRadio",0x140d69140},//tpp::gm::impl::cp::ActionControllerImpl::StateRadio
		//{"IsRaining",0x1413605f0},//tpp::gm::soldier::impl::`anonymous_namespace'::IsRaining
		//{"ConvertToVoiceType",0x140d83ab0},
		
		//{"LoadFile_02", 0x14319eb70},//void __thiscall fox::Path::~Path(Path *this)
		//{"LoadFile_05", 0x14319ee10},//Path * __thiscall fox::Path::operator=(Path *this,Path *pathrhs)
	};//map mgsvtpp_adresses_1_0_15_4_en
}//namespace IHHook
