#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteAddressHFile

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking

#include <map>

namespace IHHook {
	std::map<std::string, int64_t> mgsvtpp_adresses_1_0_15_3_en{
		//{"BlockHeapAlloc", 0x143264660},
		//{"BlockHeapFree", 0x1432651b0},
		{"FoxBlockProcess", 0x14006df80},//double fox::Block::Process(BlockMemory *blockMemory,undefined8 param_2,longlong *param_3)
		//{"FoxBlockUnload", 0x143154a00},
		//{"FoxBlockReload", 0x1431533b0},
		//{"FoxBlockActivate", 0x14006cb20},
		//{"FoxBlockDeactivate", 0x14314a000},
		//{"FoxGenerateUniqueName", 0x1400e0210},
		//{"FoxBlock", 0x143145960},
		{"FoxBlockLoad", 0x143151e80},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)
		//{"BlockMemoryAllocTail", 0x1400dbb30},
		//{"BlockMemoryAllocHeap", 0x143261bf0},
		//{"GetCurrentBlockMemory", 0x14328e410},

		{"ff_stringid_hash_n", 0x14c1bd730},//ff_stringid_hash_n
		{"FoxStrHash32", 0x142ece7f0},//fox::FoxStrHash32
		//tex TODO need to verify naming and purpose. 
		//technically this is PathFileNameExt64, but given that PathCode - 
		//without ext is likely less used than PathCode 
		//would have been a better name for PathFileNameExt64
		{"path_hash_code", 0x14c1bd5d0},//path_hash_code
		{"FNVHash32", 0x143f33a20},//TODO find in prerelease map

		{"GetFreeMissionNameKey", 0x145e60f40},//tpp::ui::utility::GetFreeMissionNameKey
		
		//tex: TODO: verify the return AL>RAX
		{"UpdateCamera", 0x141116800},//tpp::gamecore::camera::Player2CameraController::UpdateCamera
		
		//tex: Some info printing function that has been stubbed out
		{"foxprintf", 0x142ef2bf0},//fox::printf
		
		//tex: another retail stubb out to wrangle
		{"l_StubbedOut", 0x14024a8e0},//char * __cdecl tpp::ef::OutOfMissionRangeEffectLua::SetupInterp(uint param_1,uint param_2)
		//tex: another retail stubb out to wrangle
		{"voidreturn", 0x1409c8f90},//re::voidreturn	

		{"foxPathPath", 0x14319ea20},//Path * fox::Path::Path(Path *path,PathCode64 hash)
		{"UpdateLocalPathString", 0x142f784a0},//fox::fs::Path::UpdateLocalPathString
		{"foxPathPathB", 0x14319d620},//Path * __thiscall fox::Path::Path(Path *this,Path *rhs)
		{"foxPathEmpty", 0x1431a0130},//Path * fox::Path::Empty(void)

		{"GetPartsFpkPath", 0x146866c80},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetPartsFilePath", 0x146865f80},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetCamoFpkPath", 0x146864180},//tpp::gm::player::ResourceTable::GetCamoFpkPath
		{"GetCamoFilePath", 0x146863f80},//tpp::gm::player::ResourceTable::GetCamoFilePath
		{"GetFacialMtarFpkPath", 0x1468656c0},//tpp::gm::player::ResourceTable::GetFacialMtarFpkPath
		{"GetFacialMtarFilePath", 0x146865370},//tpp::gm::player::ResourceTable::GetFacialMtarFilePath
		{"GetHandFpkPath", 0x140ae90f0},//tpp::gm::player::ResourceTable::GetHandFpkPath
		{"GetHandFilePath", 0x140ae9040},//tpp::gm::player::ResourceTable::GetHandFilePath
		{"_DoesNeedBodyFovaForDD", 0x140ae9400},//tpp::gm::player::`anonymous_namespace'::_DoesNeedBodyFovaForDD
		{"GetBodyFovaPath", 0x140ae8560},//tpp::gm::player::ResourceTable::GetBodyFovaPath
		{"DoesNeedFaceFova", 0x140ae84b0},//tpp::gm::player::ResourceTable::DoesNeedFaceFova
		{"DoesNeedFaceFovaForAvatar", 0x140ae8500},//tpp::gm::player::ResourceTable::DoesNeedFaceFovaForAvatar
		{"GetFaceFpkPath", 0x140ae8df0},//tpp::gm::player::ResourceTable::GetFaceFpkPath
		{"GetFaceFilePath", 0x140ae8ce0},//tpp::gm::player::ResourceTable::GetFaceFilePath

		{"GetAvatarHoneFpkPath", 0x14685dd50},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFpkPath
		{"GetAvatarHoneFilePath", 0x14685da20},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFilePath

		{"GetPathAtBuddyType", 0x140a461d0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtBuddyType
		{"GetBuddyQuietWeaponFileFromBuddyBlock", 0x1464d5dc0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyQuietWeaponFileFromBuddyBlock
		{"GetPathAtSub_BuddyDog", 0x140a466aa},//part of 140a46360 tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtSub
		{"GetPathAtSub_BuddyHorse", 0x140a466b3},//ditto
		{"GetBuddyGearArmFile", 0x1464d3fc0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearArmFile
		{"GetBuddyGearHeadFile", 0x1464d44a0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearHeadFile
		{"GetBuddyGearMainWeaponFile", 0x1464d47f0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearMainWeaponFile
		//{"foxBlockLoad", 0x143151e80},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)

		{"ReliefVehicleLoadToExhibit", 0x146a95640},//tpp::gm::vehicle::ReliefBlockController::LoadToExhibit
		{"ReliefVehicleLoad", 0x146a95380},//tpp::gm::vehicle::ReliefBlockController::Load

		{"GetBlockAtIndex", 0x14314bda0},// fox::BlockGroup::GetBlockAtIndex

		{"gkGetColoringSystem", 0x145006860},//tpp::gk::GetColoringSystem
		{"stdstringstring", 0x142e8a5d0},//string * __thiscall std::string::string(string *this,char *cStr)

		{"GetBuddyCommandName", 0x14110dc60},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandName
		{"GetBuddyCommandHelpName", 0x14110da10},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandHelpName

		{"GetChangeLocationMenuParameterByLocationId",0x145f785d0},//tpp::ui::menu::MotherBaseMissionCommonData::GetChangeLocationMenuParameterByLocationId
		{"GetMbFreeChangeLocationMenuParameter",0x145f78b90},//tpp::ui::menu::MotherBaseMissionCommonData::GetMbFreeChangeLocationMenuParameter
		{"GetPhotoAdditionalTextLangId",0x140925ef0},//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId

		{"lua_newstate", 0x14c1fc960},//tex could use default implementation, but may want to hook if we want to see what the engine is up to
		{"lua_close", 0x14c1fc380},
		{"lua_newthread", 0x14c1d9d90},
		{"lua_atpanic", 0x14c1d5120},
		//{"lua_gettop", USING_CODE},
		{"lua_settop", 0x14c1ebbe0},
		{"lua_pushvalue", 0x14c1e87e0},
		{"lua_remove", 0x14c1ea0c0},
		{"lua_insert", 0x14c1d8150},
		{"lua_replace", 0x14c1ea370},
		{"lua_checkstack", 0x14c1d5900},
		{"lua_xmove", 0x14c1edcd0},
		{"lua_isnumber", 0x14c1d8c90},
		{"lua_isstring", 0x14c1d9250},
		{"lua_iscfunction", 0x141a11650},
		//{"lua_isuserdata", USING_CODE},//tex: No calls in lua distro, so may be hard to find, or have been culled by compilation
		{"lua_type", 0x14c1ed760},
		//{"lua_typename", USING_CODE},
		//{"lua_equal", NOT_FOUND},//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
		{"lua_rawequal", 0x14c1e8d70},
		{"lua_lessthan", 0x14c1d9890},
		{"lua_tonumber", 0x14c1ecdd0},
		{"lua_tointeger", 0x14c1ec760},
		{"lua_toboolean", 0x14c1ebe40},
		{"lua_tolstring", 0x14c1eca70},
		{"lua_objlen", 0x14c1da960},
		{"lua_tocfunction", 0x14c1ec560},
		{"lua_touserdata", 0x14c1ed4b0},
		{"lua_tothread", 0x14c1ed3c0},
		{"lua_topointer", 0x14c1ed230},
		{"lua_pushnil", 0x14c1e7cc0},
		{"lua_pushnumber", 0x14c1e7dd0},
		{"lua_pushinteger", 0x14c1e6ef0},
		{"lua_pushlstring", 0x14c1e7310},
		{"lua_pushstring", 0x14c1e7ee0},
		{"lua_pushvfstring", 0x14c1e8b10},
		{"lua_pushfstring", 0x14c1e6a70},
		{"lua_pushcclosure", 0x14c1e67b0},
		{"lua_pushboolean", 0x14c1db230},
		{"lua_pushlightuserdata", 0x14c1e71b0},
		{"lua_pushthread", 0x14c1e86a0},
		{"lua_gettable", 0x14c1d7c10},
		{"lua_getfield", 0x14c1d7320},
		{"lua_rawget", 0x14c1e9190},
		{"lua_rawgeti", 0x14c1e9320},//via MACRO lua_getref
		{"lua_createtable", 0x14c1d6320},
		{"lua_newuserdata", 0x14c1d9f80},
		{"lua_getmetatable", 0x14c1d79b0},
		{"lua_getfenv", 0x14c1d7160},
		{"lua_settable", 0x14c1eb2b0},
		{"lua_setfield", 0x14c1eabb0},
		{"lua_rawset", 0x14c1e9cf0},
		{"lua_rawseti", 0x14c1e9ff0},
		{"lua_setmetatable", 0x14c1eb040},
		{"lua_setfenv", 0x14c1eaa00},
		{"lua_call", 0x14c1d5690},
		{"lua_pcall", 0x14c1daff0},
		{"lua_cpcall", 0x146c7dd00},
		{"lua_load", 0x14c1d99c0},
		{"lua_dump", 0x14c1d6690},
		//{"lua_yield", USING_CODE},//tex: DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)
		{"lua_resume", 0x14c1f0d80},
		//{"lua_status", USING_CODE},//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
		{"lua_gc", 0x141a11220},
		{"lua_error", 0x14c1d6c90},
		{"lua_next", 0x14c1da770},
		{"lua_concat", 0x14c1d5d50},
		//{"lua_getallocf", NO_USE},//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
		//{"lua_setallocf", NO_USE},//tex don't really want to mess with allocator function anyway
		//{"lua_setlevel", NO_USE},//tex: labeled by lua as a hack to be removed in lua 5.2
		{"lua_getstack", 0x14c20fbd0},
		{"lua_getinfo", 0x14c20f650},
		{"lua_getlocal", 0x14c20f880},
		{"lua_setlocal", 0x14c20fff0},
		{"lua_getupvalue", 0x14c1d7ea0},
		{"lua_setupvalue", 0x141a12240},
		{"lua_sethook", 0x14c20fde0},
		//{"lua_gethook", USING_CODE},
		//{"lua_gethookmask", USING_CODE},
		//{"lua_gethookcount", USING_CODE},
		{"luaI_openlib", 0x14c201610},
		//{"luaL_register", USING_CODE},
		{"luaL_getmetafield", 0x14c200d50},
		{"luaL_callmeta", 0x14c1fec20},
		{"luaL_typerror", 0x141a184c0},
		{"luaL_argerror", 0x14c1fe5f0},
		{"luaL_checklstring", 0x14c1ff790},
		{"luaL_optlstring", 0x14c201de0},
		{"luaL_checknumber", 0x14c1ffb30},
		//{"luaL_optnumber", USING_CODE},//tex: Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes
		{"luaL_checkinteger", 0x14c1ff430},
		{"luaL_optinteger", 0x14c201a70},
		{"luaL_checkstack", 0x14c200010},
		{"luaL_checktype", 0x14c2004c0},
		{"luaL_checkany", 0x14c1ff2f0},
		{"luaL_newmetatable", 0x14c2013c0},
		{"luaL_checkudata", 0x14c200630},
		{"luaL_where", 0x14c203350},
		{"luaL_error", 0x14c2008f0},
		{"luaL_checkoption", 0x14c1ffd60},
		//{"luaL_ref", USING_CODE},//tex: Unsure on this address. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param
		//{"luaL_unref", USING_CODE},
		{"luaL_loadfile", 0x141a17b90},
		{"luaL_loadbuffer", 0x14c200f90},
		//{"luaL_loadstring", USING_CODE},
		{"luaL_newstate", 0x14c201490},
		{"luaL_gsub", 0x141a17710},
		{"luaL_findtable", 0x14c200aa0},
		//{"luaL_buffinit", USING_CODE},
		{"luaL_prepbuffer", 0x14c202140},
		{"luaL_addlstring", 0x141a16e70},
		//{"luaL_addstring", USING_CODE},//tex: Only call is in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
		{"luaL_addvalue", 0x14c1fd9b0},
		{"luaL_pushresult", 0x14c202280},
		{"luaopen_base", 0x14c21d5c0},
		{"luaopen_table", 0x14c21d8d0},
		{"luaopen_io", 0x14c21da00},
		{"luaopen_os", 0x14c21e020},
		{"luaopen_string", 0x14c21e720},
		{"luaopen_math", 0x14c21e800},
		{"luaopen_debug", 0x14c21ea00},
		{"luaopen_package", 0x14c21ee20},
		{"luaL_openlibs", 0x14c1fd0c0},
		
		//{"IsUseAreaIcon",0x140f23e00},//tpp::ui::menu::impl::MbDvcMapCallbackIconImpl::IsUseAreaIcon
		//{"ConvertRadioTypeToSpeechLabel",0x140d685c0},//tpp::gm::CpRadioService::ConvertRadioTypeToSpeechLabel
		//{"ConvertSpeechLabelToRadioType",0x140d58d20},//tpp::gm::CpRadioService::ConvertSpeechLabelToRadioType
		//{"CallWithRadioType",0x1473cff10},//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallWithRadioType
		//{"StateRadio",0x140d69140},//tpp::gm::impl::cp::ActionControllerImpl::StateRadio
		//{"IsRaining",0x1413605f0},//tpp::gm::soldier::impl::`anonymous_namespace'::IsRaining
		//{"ConvertToVoiceType",0x140d83ab0},
		
		//{"LoadFile_02", 0x14319eb70},//void __thiscall fox::Path::~Path(Path *this)
		//{"LoadFile_05", 0x14319ee10},//Path * __thiscall fox::Path::operator=(Path *this,Path *pathrhs)
	};//map mgsvtpp_adresses_1_0_15_3_en
}//namespace IHHook
