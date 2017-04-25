#pragma once
#include "LuaScript.h"
#include <vector>
#include <LuaBridge.h>

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}



namespace MPE
{
	//! The actual lua implementation is found in this class
	/*!
	This header should not be included/used. Use LuaScript instead.
	\sa LuaScript
	*/
	class LuaScriptBack :
		public LuaScript
	{
		friend LuaScript;
		//! Private Constructor
		LuaScriptBack(const char* filename);


		const void _LoadScript(luabridge::lua_State*& L, const char* filename);
		const void _GetToStack(luabridge::lua_State* L, const std::string& variableName);
		const void _LoadGetKeysFunction(luabridge::lua_State* L);
	

		std::string _filename;
		luabridge::lua_State* _state;
	public:
		~LuaScriptBack();


		std::vector<std::string> GetTableKeys(const char* tableName);
	};

}