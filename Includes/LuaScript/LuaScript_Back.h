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

		//! Get the base data table
		/*!
		\param name The base table name, default is data
		*/		
		LuaTable* GetData(const char* name = "data");
	};

}