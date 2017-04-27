#pragma once

#include <LuaHelpers.h>
#include <vector>
#include <unordered_map>

namespace MPE
{
	//! Wrappes the luabridge table functionallity and stores the keys of the table
	class LuaTable
	{
		luabridge::lua_State* _state;

		std::string _key;
		std::string _parentKey;
		std::unordered_map<std::string, LuaTable*> _tables;
		std::vector<std::string> _keys;
		luabridge::LuaRef* _ref = nullptr;
	public:
		//! Constructor for when LuaScript creates the table
		/*!
		\param key The name of the table
		\param parentKey The parent table name, if there is one.
		*/
		LuaTable(luabridge::lua_State* L, const char* key, const char* parentKey = "");

		//! Constructor for when a LuaTable creates the table
		LuaTable(luabridge::lua_State* L, luabridge::LuaRef* ref, const char* key, const char* parentKey);
		~LuaTable();

		//! Returns all the keys of the table.
		const std::vector<std::string>& GetKeys()const;


		//! Returns the specified table returned by GetKeys
		LuaTable& GetTable(const char* tableName);
	};
}
