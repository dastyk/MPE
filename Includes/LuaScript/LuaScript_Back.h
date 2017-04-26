#pragma once
#include "LuaScript.h"

#include <LuaHelpers.h>

#include "LuaTable_Back.h"


namespace MPE
{
	//! The actual lua implementation is found in this class
	/*!
	This header should not be included/used. Use LuaScript instead.
	\sa LuaScript
	*/
	class LuaScript_Back :
		public LuaScript
	{
		std::string _filename;
		luabridge::lua_State* _state;


		LuaTable_Back* _data;
	public:
		LuaScript_Back(const char* filename);
		~LuaScript_Back();

		//! Get the specified table
		/*!
		\param name The table name, default is data. (Can be ex. data.item)
		*/		
		LuaTable* GetTable(const char* name = "data");

		const void LoadScript(const char* filename);
	};

}