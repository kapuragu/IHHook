#pragma once

#include <lua.h>

namespace IHHook {
	namespace Hooks_Lua {
		void CreateHooks();
		void SetupLog();

		int l_FoxLua_Init(lua_State* L);
		int l_FoxLua_InitMain(lua_State* L);
		int l_FoxLua_OnUpdate(lua_State* L);

		extern lua_State* luaState;
		std::map<uint64_t, std::string> readPathCodeDictionary(const std::string& filename);
		int* LoadDefaultFpksFuncHook(void* thisPtr, int* errorCode, uint64_t* pathID, uint32_t count);
		void* GetChangeLocationMenuParameterByLocationIdHook(void* MotherBaseMissionCommonData, unsigned short locationCode);
	}//namespace Hooks_Lua
}//namespace IHHook