#pragma once
#include "LuaTable.h"
#include <LuaHelpers.h>
#include <vector>

namespace MPE
{
	class LuaTable_Back :
		public LuaTable
	{
		luabridge::lua_State* _state;

		std::vector<std::string> _keys;
		luabridge::LuaRef* _ref;
	public:
		LuaTable_Back(luabridge::lua_State* L, const char* key, const char* filename);
		~LuaTable_Back();
	};
}
