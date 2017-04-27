#pragma once

#include "LuaHelpers.h"
#include "LuaTable.h"

namespace MPE
{
	//! A wrapper for some lua functionallity
	/*!
	*/
	class LuaScript
	{
		std::string _filename;
		luabridge::lua_State* _state;


		LuaTable* _data;
	public:
		LuaScript(const char* filename);
		~LuaScript();

		//! Get the specified table
		/*!
		\param name The table name, default is data. (Can be ex. data.item)
		*/		
		LuaTable& GetTable(const char* name = "data");

		//! Load another script into the lua state.
		const void LoadScript(const char* filename);

		luabridge::lua_State*& GetState();
	};

}