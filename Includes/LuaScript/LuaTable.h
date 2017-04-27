#pragma once

#include <LuaHelpers.h>
#include <vector>
#include <unordered_map>

namespace MPE
{
	class LuaTable
	{
		luabridge::lua_State* _state;

		std::string _key;
		std::string _parentKey;
		std::unordered_map<std::string, LuaTable*> _tables;
		std::vector<std::string> _keys;
		luabridge::LuaRef* _ref;
	public:
		LuaTable(luabridge::lua_State* L, const char* key, const char* parentKey = "");
		LuaTable(luabridge::lua_State* L, luabridge::LuaRef* ref, const char* key, const char* parentKey);
		~LuaTable();

		const std::vector<std::string>& GetKeys()const;
		LuaTable& GetTable(const char* tableName);
	};
}
