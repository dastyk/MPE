#ifndef _LUA_SCRIPT_H_
#define  _LUA_SCRIPT_H_
#pragma once

#include "LuaTable.h"

namespace MPE
{
	//! A pure virtual class, so we can avoid including the base lua and luabridge src into the whole thing.
	/*!
	This class hides the actual lua and luabridge implementation found in LuaScript_Back
	\sa LuaScript_Back
	*/
	class LuaScript
	{
	protected:
		//! Protected Constructor
		LuaScript();

	public:
		//! Creates the actual LuaScript_Back object.
		static LuaScript* Create(const char* filename);
		virtual ~LuaScript();

		virtual LuaTable* GetData(const char* tableName) = 0;
	};
}
#endif