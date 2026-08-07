#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteAddressHFile

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking

#include <map>

namespace IHHook {
	std::map<std::string, int64_t> mgsvtpp_adresses_1_0_15_4_jp{
		//{"BlockHeapAlloc", NO_USE},
		//{"BlockHeapFree", NO_USE},
		{"FoxBlockProcess", 0x14006e550},//double fox::Block::Process(BlockMemory *blockMemory,undefined8 param_2,longlong *param_3)
		//{"FoxBlockUnload", NO_USE},
		//{"FoxBlockReload", NO_USE},
		//{"FoxBlockActivate", NO_USE},
		//{"FoxBlockDeactivate", NO_USE},
		//{"FoxGenerateUniqueName", NO_USE},
		//{"FoxBlock", NO_USE},
		{"FoxBlockLoad", 0x14006e0b0},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)
		//{"BlockMemoryAllocTail", NO_USE},
		//{"BlockMemoryAllocHeap", NO_USE},
		//{"GetCurrentBlockMemory", NO_USE},
		
		{"ff_stringid_hash_n", 0x141a09a00},//ff_stringid_hash_n
		{"FoxStrHash32", 0x1400234e0},//fox::FoxStrHash32
		//tex TODO need to verify naming and purpose. 
		//technically this is PathFileNameExt64, but given that PathCode - 
		//without ext is likely less used than PathCode 
		//would have been a better name for PathFileNameExt64
		{"path_hash_code", 0x141a09820},//path_hash_code	
		{"FNVHash32", 0x14033bfb0},//TODO find in prerelease map
		
		{"GetFreeMissionNameKey", 0x1409120a0},//tpp::ui::utility::GetFreeMissionNameKey
		
		//tex: TODO: verify the return AL>RAX
		{"UpdateCamera", 0x141115f50},//tpp::gamecore::camera::Player2CameraController::UpdateCamera
		
		//tex: Some info printing function that has been stubbed out
		{"foxprintf", 0x14002abc0},//fox::printf
		
		//tex: another retail stubb out to wrangle
		{"l_StubbedOut", 0x14017a190},//char * __cdecl tpp::ef::OutOfMissionRangeEffectLua::SetupInterp(uint param_1,uint param_2)
		//tex: another retail stubb out to wrangle
		{"voidreturn", 0x14024d1d0},//re::voidreturn
		
		{"foxPathPath", 0x140085760},//Path * fox::Path::Path(Path *path,PathCode64 hash)
		{"UpdateLocalPathString", 0x140040cc0},//fox::fs::Path::UpdateLocalPathString
		{"foxPathPathB", 0x140085640},//Path * __thiscall fox::Path::Path(Path *this,Path *rhs)
		{"foxPathEmpty", 0x1400859f0},//Path * fox::Path::Empty(void)
		
		{"GetPartsFpkPath", 0x140ae9990},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetPartsFilePath", 0x140ae98f0},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetCamoFpkPath", 0x140ae8ff0},//tpp::gm::player::ResourceTable::GetCamoFpkPath
		{"GetCamoFilePath", 0x140ae8f20},//tpp::gm::player::ResourceTable::GetCamoFilePath
		{"GetFacialMtarFpkPath", 0x140ae96f0},//tpp::gm::player::ResourceTable::GetFacialMtarFpkPath
		{"GetFacialMtarFilePath", 0x140ae9650},//tpp::gm::player::ResourceTable::GetFacialMtarFilePath
		{"GetHandFpkPath", 0x140ae9840},//tpp::gm::player::ResourceTable::GetHandFpkPath
		{"GetHandFilePath", 0x140ae9790},//tpp::gm::player::ResourceTable::GetHandFilePath
		{"_DoesNeedBodyFovaForDD", 0x140ae9b50},//tpp::gm::player::`anonymous_namespace'::_DoesNeedBodyFovaForDD
		{"GetBodyFovaPath", 0x140ae8cb0},//tpp::gm::player::ResourceTable::GetBodyFovaPath
		{"DoesNeedFaceFova", 0x140ae8c00},//tpp::gm::player::ResourceTable::DoesNeedFaceFova
		{"DoesNeedFaceFovaForAvatar", 0x140ae8c50},//tpp::gm::player::ResourceTable::DoesNeedFaceFovaForAvatar
		{"GetFaceFpkPath", 0x140ae9540},//tpp::gm::player::ResourceTable::GetFaceFpkPath
		{"GetFaceFilePath", 0x140ae9430},//tpp::gm::player::ResourceTable::GetFaceFilePath
		
		{"GetAvatarHoneFpkPath", 0x140ae73c0},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFpkPath
		{"GetAvatarHoneFilePath", 0x140ae7350},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFilePath
		
		{"GetPathAtBuddyType", 0x140a466b0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtBuddyType
		{"GetBuddyQuietWeaponFileFromBuddyBlock", 0x140a46400},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyQuietWeaponFileFromBuddyBlock
		{"GetPathAtSub_BuddyDog", 0x140a46840},//part of 140a46360 tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtSub
		{"GetPathAtSub_BuddyHorse", 0x140a46b93},//ditto
		{"GetBuddyGearArmFile", 0x140a45fb0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearArmFile
		{"GetBuddyGearHeadFile", 0x140a46120},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearHeadFile
		{"GetBuddyGearMainWeaponFile", 0x140a461d0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearMainWeaponFile
		//{"foxBlockLoad", 0x1431d96b0},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)
		
		{"ReliefVehicleLoadToExhibit", 0x140b3aba0},//tpp::gm::vehicle::ReliefBlockController::LoadToExhibit
		{"ReliefVehicleLoad", 0x140b3ab00},//tpp::gm::vehicle::ReliefBlockController::Load
		
		{"GetBlockAtIndex", 0x14006d7f0},// fox::BlockGroup::GetBlockAtIndex
		
		{"gkGetColoringSystem", 0x1405cf200},//tpp::gk::GetColoringSystem
		{"stdstringstring", 0x1400164a0},//string * __thiscall std::string::string(string *this,char *cStr)

		{"GetBuddyCommandName", 0x14110d3a0},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandName
		{"GetBuddyCommandHelpName", 0x14110d150},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandHelpName
		
		{"GetChangeLocationMenuParameterByLocationId",0x140926640},//tpp::ui::menu::MotherBaseMissionCommonData::GetChangeLocationMenuParameterByLocationId
		{"GetMbFreeChangeLocationMenuParameter",0x140926770},//tpp::ui::menu::MotherBaseMissionCommonData::GetMbFreeChangeLocationMenuParameter
		{"GetPhotoAdditionalTextLangId",0x140926840},//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId

		{"lua_newstate", 0x141a16460},
		{"lua_close", 0x141a163d0},
		{"lua_newthread", 0x141a11490},
		{"lua_atpanic", 0x141a10be0},
		//{"lua_gettop", USING_CODE},
		{"lua_settop", 0x141a11eb0},
		{"lua_pushvalue", 0x141a11910},
		{"lua_remove", 0x141a11b60},
		{"lua_insert", 0x141a112d0},
		{"lua_replace", 0x141a11bb0},
		{"lua_checkstack", 0x141a10c50},
		{"lua_xmove", 0x141a122a0},
		{"lua_isnumber", 0x141a11350},
		{"lua_isstring", 0x141a11380},
		{"lua_iscfunction", 0x141a11320},
		//{"lua_isuserdata", USING_CODE},
		{"lua_type", 0x141a12250},
		//{"lua_typename", USING_CODE},
		//{"lua_equal", NOT_FOUND},
		{"lua_rawequal", 0x141a11990},
		{"lua_lessthan", 0x141a113f0},
		{"lua_tonumber", 0x141a12140},
		{"lua_tointeger", 0x141a12070},
		{"lua_toboolean", 0x141a12010},
		{"lua_tolstring", 0x141a120a0},
		{"lua_objlen", 0x141a11580},
		{"lua_tocfunction", 0x141a12040},
		{"lua_touserdata", 0x141a12210},
		{"lua_tothread", 0x141a121f0},
		{"lua_topointer", 0x141a12180},
		{"lua_pushnil", 0x141a11870},
		{"lua_pushnumber", 0x141a11890},
		{"lua_pushinteger", 0x141a117c0},
		{"lua_pushlstring", 0x141a11800},
		{"lua_pushstring", 0x141a118b0},
		{"lua_pushvfstring", 0x141a11940},
		{"lua_pushfstring", 0x141a11770},
		{"lua_pushcclosure", 0x141a116b0},
		{"lua_pushboolean", 0x141a11690},
		{"lua_pushlightuserdata", 0x141a117e0},
		{"lua_pushthread", 0x141a118e0},
		{"lua_gettable", 0x141a111f0},
		{"lua_getfield", 0x141a11120},
		{"lua_rawget", 0x141a119e0},
		{"lua_rawgeti", 0x141a11a20},
		{"lua_createtable", 0x141a10dc0},
		{"lua_newuserdata", 0x141a114d0},
		{"lua_getmetatable", 0x141a11190},
		{"lua_getfenv", 0x141a110a0},
		{"lua_settable", 0x141a11e80},
		{"lua_setfield", 0x141a11d40},
		{"lua_rawset", 0x141a11a60},
		{"lua_rawseti", 0x141a11ae0},
		{"lua_setmetatable", 0x141a11dc0},
		{"lua_setfenv", 0x141a11ca0},
		{"lua_call", 0x141a10c00},
		{"lua_pcall", 0x141a11600},
		{"lua_cpcall", 0x140bf2e40},
		{"lua_load", 0x141a11440},
		{"lua_dump", 0x141a24d40},
		//{"lua_yield", USING_CODE},
		{"lua_resume", 0x141a13270},
		//{"lua_status", USING_CODE},
		{"lua_gc", 0x141a10ef0},
		{"lua_error", 0x141a10ee0},
		{"lua_next", 0x141a11540},
		{"lua_concat", 0x141a10cf0},
		//{"lua_getallocf", NO_USE},
		//{"lua_setallocf", NO_USE},
		//{"lua_setlevel", NO_USE},
		{"lua_getstack", 0x141a20c90},
		{"lua_getinfo", 0x141a20b30},
		{"lua_getlocal", 0x141a20c20},
		{"lua_setlocal", 0x141a20d40},
		{"lua_getupvalue", 0x141a11230},
		{"lua_setupvalue", 0x141a11f10},
		{"lua_sethook", 0x141a20d10},
		//{"lua_gethook", USING_CODE},
		//{"lua_gethookmask", USING_CODE},
		//{"lua_gethookcount", USING_CODE},
		{"luaI_openlib", 0x141a17fd0},
		//{"luaL_register", USING_CODE},
		{"luaL_getmetafield", 0x141a17360},
		{"luaL_callmeta", 0x141a16dd0},
		{"luaL_typerror", 0x141a18190},
		{"luaL_argerror", 0x141a16cc0},
		{"luaL_checklstring", 0x141a16ee0},
		{"luaL_optlstring", 0x141a17d70},
		{"luaL_checknumber", 0x141a16f70},
		//{"luaL_optnumber", USING_CODE},
		{"luaL_checkinteger", 0x141a16e90},
		{"luaL_optinteger", 0x141a17d00},
		{"luaL_checkstack", 0x141a17090},
		{"luaL_checktype", 0x141a170d0},
		{"luaL_checkany", 0x141a16e50},
		{"luaL_newmetatable", 0x141a17ac0},
		{"luaL_checkudata", 0x141a17110},
		{"luaL_where", 0x141a180c0},
		{"luaL_error", 0x141a171d0},
		{"luaL_checkoption", 0x141a16fd0},
		//{"luaL_ref", USING_CODE},
		//{"luaL_unref", USING_CODE},
		{"luaL_loadfile", 0x141a17860},
		{"luaL_loadbuffer", 0x141a17830},
		//{"luaL_loadstring", USING_CODE},
		{"luaL_newstate", 0x141a17b40},
		{"luaL_gsub", 0x141a173e0},
		{"luaL_findtable", 0x141a17230},
		//{"luaL_buffinit", USING_CODE},
		{"luaL_prepbuffer", 0x141a17e60},
		{"luaL_addlstring", 0x141a16b40},
		//{"luaL_addstring", USING_CODE},
		{"luaL_addvalue", 0x141a16c00},
		{"luaL_pushresult", 0x141a17ec0},
		{"luaopen_base", 0x141a2f140},
		{"luaopen_table", 0x141a2fd70},
		{"luaopen_io", 0x141a31020},
		{"luaopen_os", 0x141a31e00},
		{"luaopen_string", 0x141a33280},
		{"luaopen_math", 0x141a34a30},
		{"luaopen_debug", 0x141a35960},
		{"luaopen_package", 0x141a36440},
		{"luaL_openlibs", 0x141a168d0},

		//{"IsUseAreaIcon",0x140f23e00},//tpp::ui::menu::impl::MbDvcMapCallbackIconImpl::IsUseAreaIcon
		//{"ConvertRadioTypeToSpeechLabel",NO_USE},//tpp::gm::CpRadioService::ConvertRadioTypeToSpeechLabel
		//{"ConvertSpeechLabelToRadioType",NO_USE},//tpp::gm::CpRadioService::ConvertSpeechLabelToRadioType
		//{"CallWithRadioType",NO_USE},//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallWithRadioType
		//{"StateRadio",NO_USE},//tpp::gm::impl::cp::ActionControllerImpl::StateRadio
		//{"IsRaining",NO_USE},//tpp::gm::soldier::impl::`anonymous_namespace'::IsRaining
		//{"ConvertToVoiceType",NO_USE},
				
		//{"LoadFile_02", 0x143227e40},//void __thiscall fox::Path::~Path(Path *this)
		//{"LoadFile_05", 0x143228120},//Path * __thiscall fox::Path::operator=(Path *this,Path *pathrhs)
		
		//compat with tpp-mod
		/*{"os_execute", NO_USE},
		{"os_exit", NO_USE},
		{"os_getenv", NO_USE},
		{"os_remove", NO_USE},
		{"os_rename", NO_USE},
		{"os_setlocale", NO_USE},
		{"os_tmpname", NO_USE},
		{"ll_loadlib", NO_USE},
		
		{"system", NO_USE},*/
				
		/*{"io_open", NO_USE},
		{"io_popen", NO_USE},
		{"io_close", NO_USE},
		{"f_read", NO_USE},
		{"f_write", NO_USE},*/
	};//map mgsvtpp_adresses_1_0_15_4_jp
}//namespace IHHook
