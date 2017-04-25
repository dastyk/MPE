#ifndef _LUA_HELPERS_H_
#define _LUA_HELPERS_H_
#pragma once
#include <LuaBridge.h>

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

#include <vector>

namespace MPE
{
	//! Loads the initial state of the script
	const void LoadScript(luabridge::lua_State*& L, const char* filename);
	//! Takes the variableName and puts it on the top of the stack
	/*!
	\param L The lua state
	\param variableName Can be for example "data.pos.x"; in which case the value in x would be put on the stack.
	*/
	const void GetToStack(luabridge::lua_State* L, const std::string& variableName, const char * filename);

	//! Inserts a lua function for extracting the table keys from the lua state.
	const void LoadGetKeysFunction(luabridge::lua_State* L);

	std::vector<std::string> GetTableKeys(luabridge::lua_State * L, const char * tableName, const char * filename);
}
#endif