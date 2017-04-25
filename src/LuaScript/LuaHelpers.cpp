#include "LuaHelpers.h"

namespace MPE
{
	using namespace luabridge;
	const void LoadScript(lua_State *& L, const char * filename)
	{
		L = luaL_newstate();
		if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
		{
			L = 0;
			throw std::runtime_error(std::string("Failed to load srcipt: ") + filename);
		}
		luaL_openlibs(L);
	}

	const void GetToStack(luabridge::lua_State * L, const std::string & variableName, const char * filename)
	{
		int level = 0;
		std::string var = "";

		std::string::size_type prev_pos = 0, pos = 0;

		while ((pos = variableName.find('.', pos)) != std::string::npos)
		{
			std::string substring(variableName.substr(prev_pos, pos - prev_pos));

			if (level == 0) {
				lua_getglobal(L, substring.c_str());
			}
			else {
				lua_getfield(L, -1, substring.c_str());
			}

			if (lua_isnil(L, -1)) {
				throw std::runtime_error(std::string("ScriptError: Could not find variable ") + variableName + std::string(". In file: ") + filename);
			}

			level++;


			prev_pos = ++pos;
		}


		if (level == 0) {
			lua_getglobal(L, variableName.substr(prev_pos, pos - prev_pos).c_str());
			if (lua_isnil(L, -1)) {
				throw std::runtime_error(std::string("ScriptError: Could not find variable ") + variableName + std::string(". In file: ") + filename);
			}
		}
		else {
			lua_getfield(L, -1, variableName.substr(prev_pos, pos - prev_pos).c_str());
			if (lua_isnil(L, -1)) {
				throw std::runtime_error(std::string("ScriptError: Could not find variable ") + variableName + std::string(". In file: ") + filename);
			}

			// Switch last loaded variable on stack(the actual thing we wanted) with the table name level s down in the stack.
			int tableIndex = lua_gettop(L) - level;
			lua_replace(L, tableIndex);
			lua_settop(L, tableIndex);

		}
	}
	const void LoadGetKeysFunction(luabridge::lua_State * L)
	{
		std::string code =
			R"(function getKeys(t)
        s = {}
        for k, v in pairs(t) do
            table.insert(s, k)
            end 
        return s 
        end)";
		luaL_dostring(L, code.c_str());
	}

	std::vector<std::string> GetTableKeys(luabridge::lua_State * L, const char * tableName, const char * filename)
	{
		lua_getglobal(L, "getKeys"); // get function
		if (lua_isnil(L, -1)) {
			printf("Get keys function is not loaded. Loading...\n");
			LoadGetKeysFunction(L);
			lua_getglobal(L, "getKeys");
		}

		GetToStack(L, tableName, filename);

		lua_pcall(L, 1, 1, 0); // execute getKeys function.
							   // One parameter, one return
		lua_pushnil(L);
		std::vector<std::string> keys;
		while (lua_next(L, -2)) { // get values one by one
			if (lua_type(L, -1) == LUA_TSTRING) { // check if key is a string
				keys.push_back(lua_tostring(L, -1));
			}
			lua_pop(L, 1);
		}

		lua_settop(L, 0); // remove s table from stack 
		return keys;
	}
}