#pragma once
#include "LuaScript.h"

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

		lua_State* L;
	public:
		~LuaScriptBack();

	};

}