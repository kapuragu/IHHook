#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteAddressHFile

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking

#include <map>

namespace IHHook {
	std::map<std::string, int64_t> mgsvtpp_adresses_1_0_15_3_jp{
		//{"BlockHeapAlloc", NO_USE},
		//{"BlockHeapFree", NO_USE},
		{"FoxBlockProcess", 0x14006e0a0},//double fox::Block::Process(BlockMemory *blockMemory,undefined8 param_2,longlong *param_3)
		//{"FoxBlockUnload", NO_USE},
		//{"FoxBlockReload", NO_USE},
		//{"FoxBlockActivate", NO_USE},
		//{"FoxBlockDeactivate", NO_USE},
		//{"FoxGenerateUniqueName", NO_USE},
		//{"FoxBlock", NO_USE},
		{"FoxBlockLoad", 0x1431d96b0},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)
		//{"BlockMemoryAllocTail", NO_USE},
		//{"BlockMemoryAllocHeap", NO_USE},
		//{"GetCurrentBlockMemory", NO_USE},
		
		{"ff_stringid_hash_n", 0x14c96c490},//ff_stringid_hash_n
		{"FoxStrHash32", 0x142eb6c10},//fox::FoxStrHash32
		//tex TODO need to verify naming and purpose. 
		//technically this is PathFileNameExt64, but given that PathCode - 
		//without ext is likely less used than PathCode 
		//would have been a better name for PathFileNameExt64
		{"path_hash_code", 0x14c96c160},//path_hash_code	
		{"FNVHash32", 0x143f6ee50},//TODO find in prerelease map
		
		{"GetFreeMissionNameKey", 0x147a6b040},//tpp::ui::utility::GetFreeMissionNameKey
		
		//tex: TODO: verify the return AL>RAX
		{"UpdateCamera", 0x141116890},//tpp::gamecore::camera::Player2CameraController::UpdateCamera
		
		//tex: Some info printing function that has been stubbed out
		{"foxprintf", 0x142ee2a90},//fox::printf
		
		//tex: another retail stubb out to wrangle
		{"l_StubbedOut", 0x141a92a30},//char * __cdecl tpp::ef::OutOfMissionRangeEffectLua::SetupInterp(uint param_1,uint param_2)
		//tex: another retail stubb out to wrangle
		{"voidreturn", 0x141934f30},//re::voidreturn
		
		{"foxPathPath", 0x143227d20},//Path * fox::Path::Path(Path *path,PathCode64 hash)
		{"UpdateLocalPathString", 0x142f665f0},//fox::fs::Path::UpdateLocalPathString
		{"foxPathPathB", 0x143227580},//Path * __thiscall fox::Path::Path(Path *this,Path *rhs)
		{"foxPathEmpty", 0x143229640},//Path * fox::Path::Empty(void)
		
		{"GetPartsFpkPath", 0x14844de90},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetPartsFilePath", 0x14844db10},//tpp::gm::player::ResourceTable::GetPartsFpkPath
		{"GetCamoFpkPath", 0x14844b070},//tpp::gm::player::ResourceTable::GetCamoFpkPath
		{"GetCamoFilePath", 0x14844aea0},//tpp::gm::player::ResourceTable::GetCamoFilePath
		{"GetFacialMtarFpkPath", 0x14844d540},//tpp::gm::player::ResourceTable::GetFacialMtarFpkPath
		{"GetFacialMtarFilePath", 0x14844d040},//tpp::gm::player::ResourceTable::GetFacialMtarFilePath
		{"GetHandFpkPath", 0x140ae8c30},//tpp::gm::player::ResourceTable::GetHandFpkPath
		{"GetHandFilePath", 0x140ae8b80},//tpp::gm::player::ResourceTable::GetHandFilePath
		{"_DoesNeedBodyFovaForDD", 0x140ae8f40},//tpp::gm::player::`anonymous_namespace'::_DoesNeedBodyFovaForDD
		{"GetBodyFovaPath", 0x140ae80a0},//tpp::gm::player::ResourceTable::GetBodyFovaPath
		{"DoesNeedFaceFova", 0x140ae7ff0},//tpp::gm::player::ResourceTable::DoesNeedFaceFova
		{"DoesNeedFaceFovaForAvatar", 0x140ae8040},//tpp::gm::player::ResourceTable::DoesNeedFaceFovaForAvatar
		{"GetFaceFpkPath", 0x140ae8930},//tpp::gm::player::ResourceTable::GetFaceFpkPath
		{"GetFaceFilePath", 0x140ae8820},//tpp::gm::player::ResourceTable::GetFaceFilePath
		
		{"GetAvatarHoneFpkPath", 0x148442ef0},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFpkPath
		{"GetAvatarHoneFilePath", 0x148442af0},//tpp::gm::player::AvatarTppResourceTable::GetAvatarHoneFilePath
		
		{"GetPathAtBuddyType", 0x140a45ca0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtBuddyType
		{"GetBuddyQuietWeaponFileFromBuddyBlock", 0x14811f640},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyQuietWeaponFileFromBuddyBlock
		{"GetPathAtSub_BuddyDog", 0x140a4617a},//part of 140a46360 tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetPathAtSub
		{"GetPathAtSub_BuddyHorse", 0x140a46183},//ditto
		{"GetBuddyGearArmFile", 0x14811dea0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearArmFile
		{"GetBuddyGearHeadFile", 0x14811e600},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearHeadFile
		{"GetBuddyGearMainWeaponFile", 0x14811e9a0},//tpp::gm::buddy::impl::Buddy2BlockControllerImpl::GetBuddyGearMainWeaponFile
		//{"foxBlockLoad", 0x1431d96b0},//int * fox::Block::Load(void *thisPtr,int *errorCode,ulonglong *pathID,uint param_4)
		
		{"ReliefVehicleLoadToExhibit", 0x1485731b0},//tpp::gm::vehicle::ReliefBlockController::LoadToExhibit
		{"PreparePlayerVehicleInGame", 0x148572fb0},//tpp::gm::vehicle::ReliefBlockController::Load
		
		{"GetBlockAtIndex", 0x1431d5520},// fox::BlockGroup::GetBlockAtIndex
		
		{"gkGetColoringSystem", 0x144e8da60},//tpp::gk::GetColoringSystem
		{"stdstringstring", 0x142e77d10},//string * __thiscall std::string::string(string *this,char *cStr)

		{"GetBuddyCommandName", 0x14110dcc0},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandName
		{"GetBuddyCommandHelpName", 0x14110da70},//tpp::gm::player::impl::`anonymous_namespace'::GetBuddyCommandHelpName
		
		{"GetChangeLocationMenuParameterByLocationId",0x147b88d00},//tpp::ui::menu::MotherBaseMissionCommonData::GetChangeLocationMenuParameterByLocationId
		{"GetMbFreeChangeLocationMenuParameter",0x147b897d0},//tpp::ui::menu::MotherBaseMissionCommonData::GetMbFreeChangeLocationMenuParameter
		{"GetPhotoAdditionalTextLangId",0x140925910},//tpp::ui::menu::MotherBaseMissionCommonData::GetPhotoAdditionalTextLangId

		{"lua_newstate", 0x14c9a52c0},
		{"lua_close", 0x14c9a5100},
		{"lua_newthread", 0x14c989a70},
		{"lua_atpanic", 0x14c9855b0},
		//{"lua_gettop", USING_CODE},
		{"lua_settop", 0x14c990ed0},
		{"lua_pushvalue", 0x14c98e1d0},
		{"lua_remove", 0x14c98f0f0},
		{"lua_insert", 0x14c9888d0},
		{"lua_replace", 0x14c98f490},
		{"lua_checkstack", 0x14c985da0},
		{"lua_xmove", 0x14c993c00},
		{"lua_isnumber", 0x14c988960},
		{"lua_isstring", 0x14c988ca0},
		{"lua_iscfunction", 0x141a11770},
		//{"lua_isuserdata", USING_CODE},
		{"lua_type", 0x14c9935f0},
		//{"lua_typename", USING_CODE},
		//{"lua_equal", NOT_FOUND},
		{"lua_rawequal", 0x14c98e690},
		{"lua_lessthan", 0x14c989590},
		{"lua_tonumber", 0x14c9924d0},
		{"lua_tointeger", 0x14c991b80},
		{"lua_toboolean", 0x14c991120},
		{"lua_tolstring", 0x14c992060},
		{"lua_objlen", 0x14c98a230},
		{"lua_tocfunction", 0x14c991460},
		{"lua_touserdata", 0x14c992e00},
		{"lua_tothread", 0x14c992bc0},
		{"lua_topointer", 0x14c992610},
		{"lua_pushnil", 0x14c98d570},
		{"lua_pushnumber", 0x14c98d800},
		{"lua_pushinteger", 0x14c98c7c0},
		{"lua_pushlstring", 0x14c98ccc0},
		{"lua_pushstring", 0x14c98dcb0},
		{"lua_pushvfstring", 0x14c98e4a0},
		{"lua_pushfstring", 0x14c98c4b0},
		{"lua_pushcclosure", 0x14c98c080},
		{"lua_pushboolean", 0x14c98b310},
		{"lua_pushlightuserdata", 0x14c98c9e0},
		{"lua_pushthread", 0x14c98df80},
		{"lua_gettable", 0x14c987b90},
		{"lua_getfield", 0x14c987300},
		{"lua_rawget", 0x14c98e930},
		{"lua_rawgeti", 0x14c98ebc0},
		{"lua_createtable", 0x14c986520},
		{"lua_newuserdata", 0x14c989bf0},
		{"lua_getmetatable", 0x14c9878c0},
		{"lua_getfenv", 0x14c987110},
		{"lua_settable", 0x14c990bd0},
		{"lua_setfield", 0x14c990870},
		{"lua_rawset", 0x14c98ed50},
		{"lua_rawseti", 0x14c98efe0},
		{"lua_setmetatable", 0x14c990a80},
		{"lua_setfenv", 0x14c98f9f0},
		{"lua_call", 0x14c9859f0},
		{"lua_pcall", 0x14c98acb0},
		{"lua_cpcall", 0x1489e59c0},
		{"lua_load", 0x14c9898e0},
		{"lua_dump", 0x14caa27a0},
		//{"lua_yield", USING_CODE},
		{"lua_resume", 0x14c996a10},
		//{"lua_status", USING_CODE},
		{"lua_gc", 0x141a11340},
		{"lua_error", 0x14c986ea0},
		{"lua_next", 0x14c98a010},
		{"lua_concat", 0x14c986010},
		//{"lua_getallocf", NO_USE},
		//{"lua_setallocf", NO_USE},
		//{"lua_setlevel", NO_USE},
		{"lua_getstack", 0x14ca99b40},
		{"lua_getinfo", 0x14ca993e0},
		{"lua_getlocal", 0x14ca99980},
		{"lua_setlocal", 0x14ca9a230},
		{"lua_getupvalue", 0x14c9884b0},
		{"lua_setupvalue", 0x141a12360},
		{"lua_sethook", 0x14ca99f50},
		//{"lua_gethook", USING_CODE},
		//{"lua_gethookmask", USING_CODE},
		//{"lua_gethookcount", USING_CODE},
		{"luaI_openlib", 0x141a18410},
		//{"luaL_register", USING_CODE},
		{"luaL_getmetafield", 0x14c9a9020},
		{"luaL_callmeta", 0x14c9a6740},
		{"luaL_typerror", 0x141a185d0},
		{"luaL_argerror", 0x14c9a5ff0},
		{"luaL_checklstring", 0x14c9a72e0},
		{"luaL_optlstring", 0x14c9aac90},
		{"luaL_checknumber", 0x14c9a7490},
		//{"luaL_optnumber", USING_CODE},
		{"luaL_checkinteger", 0x14c9a6db0},
		{"luaL_optinteger", 0x14c9aa940},
		{"luaL_checkstack", 0x14c9a7ab0},
		{"luaL_checktype", 0x14c9a8030},
		{"luaL_checkany", 0x14c9a6b30},
		{"luaL_newmetatable", 0x14c9a9f50},
		{"luaL_checkudata", 0x14c9a8430},
		{"luaL_where", 0x14c9ac500},
		{"luaL_error", 0x14c9a8870},
		{"luaL_checkoption", 0x14c9a7600},
		//{"luaL_ref", USING_CODE},
		//{"luaL_unref", USING_CODE},
		{"luaL_loadfile", 0x141a17ca0},
		{"luaL_loadbuffer", 0x14c9a98c0},
		//{"luaL_loadstring", USING_CODE},
		{"luaL_newstate", 0x1476e65e6},
		{"luaL_gsub", 0x141a17820},
		{"luaL_findtable", 0x14c9a8a20},
		//{"luaL_buffinit", USING_CODE},
		{"luaL_prepbuffer", 0x14c9ab0c0},
		{"luaL_addlstring", 0x141a16f80},
		//{"luaL_addstring", USING_CODE},
		{"luaL_addvalue", 0x14c9a5d20},
		{"luaL_pushresult", 0x14c9ab8b0},
		{"luaopen_base", 0x14caa9570},
		{"luaopen_table", 0x14caa9640},
		{"luaopen_io", 0x14caa9bb0},
		{"luaopen_os", 0x141a32280},
		{"luaopen_string", 0x14caaa490},
		{"luaopen_math", 0x14caaa7d0},
		{"luaopen_debug", 0x14caaab70},
		{"luaopen_package", 0x141a368c0},
		{"luaL_openlibs", 0x14c9a5860},

		//{"IsUseAreaIcon",0x140f23e00},//tpp::ui::menu::impl::MbDvcMapCallbackIconImpl::IsUseAreaIcon
		//{"ConvertRadioTypeToSpeechLabel",NO_USE},//tpp::gm::CpRadioService::ConvertRadioTypeToSpeechLabel
		//{"ConvertSpeechLabelToRadioType",NO_USE},//tpp::gm::CpRadioService::ConvertSpeechLabelToRadioType
		//{"CallWithRadioType",NO_USE},//tpp::gm::impl::cp::`anonymous_namespace'::RadioSpeechHandlerImpl::CallWithRadioType
		//{"StateRadio",NO_USE},//tpp::gm::impl::cp::ActionControllerImpl::StateRadio
		//{"IsRaining",NO_USE},//tpp::gm::soldier::impl::`anonymous_namespace'::IsRaining
		//{"ConvertToVoiceType",NO_USE},
				
		//{"LoadFile_02", 0x143227e40},//void __thiscall fox::Path::~Path(Path *this)
		//{"LoadFile_05", 0x143228120},//Path * __thiscall fox::Path::operator=(Path *this,Path *pathrhs)
	};//map mgsvtpp_adresses_1_0_15_3_jp
}//namespace IHHook
