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
		double FoxBlockProcessHook(void* Block, void* TaskContext, void* BlockProcessState);
		int* FoxBlockLoadHook(void* thisPtr, int* errorCode, uint64_t* pathID, uint32_t count);
		extern bool open_io_override;
		void CreateHooksForTppMod();
		int luaopen_ioHook(lua_State* L);
		longlong io_openHook(lua_State* L);
		longlong io_popenHook(lua_State* L);
		void io_closeHook(lua_State* L);
		void f_readHook(lua_State* L);
		void f_writeHook(lua_State* L);
	}//namespace Hooks_Lua
}//namespace IHHook