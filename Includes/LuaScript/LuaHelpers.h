#ifndef _LUA_HELPERS_H_
#define _LUA_HELPERS_H_
#pragma once
#include <LuaBridge\LuaBridge.h>

extern "C" {
# include <Lua\lua.h>
# include <Lua\lauxlib.h>
# include <Lua\lualib.h>
}

#include <vector>

namespace MPE
{
	namespace LuaHelpers
	{
		//! Loads the initial state of the script
		const void LoadScript(luabridge::lua_State*& L, const char* filename);
		//! Takes the variableName and puts it on the top of the stack
		/*!
		\param L The lua state
		\param variableName Can be for example "data.pos.x"; in which case the value in x would be put on the stack.
		*/
		const void GetToStack(luabridge::lua_State* L, const std::string& variableName);

		//! Inserts a lua function for extracting the table keys from the lua state.
		const void LoadGetKeysFunction(luabridge::lua_State* L);
		
		//! Inserts a lua function for extending the data table
		const void LoadDataExtendFunction(luabridge::lua_State* L);

		//! Get the keys of the specified table
		std::vector<std::string> GetTableKeys(luabridge::lua_State * L, const char * tableName);
	}
}
#endif