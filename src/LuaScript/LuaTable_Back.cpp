#include "LuaTable_Back.h"


namespace MPE
{
	LuaTable_Back::LuaTable_Back(luabridge::lua_State* L, const char* key, const char* filename) : _state(L)
	{
		GetTableKeys(L, key, filename);
	}


	LuaTable_Back::~LuaTable_Back()
	{
	}
}