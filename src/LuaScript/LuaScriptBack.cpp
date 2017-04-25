#include "LuaScriptBack.h"
#include  <stdexcept>

namespace MPE
{
	using namespace luabridge;
	LuaScriptBack::LuaScriptBack(const char* filename) : _filename(filename)
	{
		_LoadScript(_state, filename);
		/*
		auto ref = getGlobal(L, "player");
		for (int i = 0; i < ref.length(); i++)
		{

		}*/
	}

	const void LuaScriptBack::_LoadScript(lua_State *& L, const char * filename)
	{
		L = luaL_newstate();
		if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
		{
			L = 0;
			throw std::runtime_error(std::string("Failed to load srcipt: ") + filename);
		}
		luaL_openlibs(L);
	}

	const void LuaScriptBack::_GetToStack(lua_State * L, const std::string& variableName)
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
				throw std::runtime_error(std::string("ScriptError: Could not find variable ") + variableName + std::string(". In file: ") + _filename);
			}

			level++;
			

			prev_pos = ++pos;
		}

		
		if (level == 0) {
			lua_getglobal(L, variableName.substr(prev_pos, pos - prev_pos).c_str());
			if (lua_isnil(L, -1)) {
				throw std::runtime_error(std::string("ScriptError: Could not find variable ") + variableName + std::string(". In file: ") + _filename);
			}
		}
		else {
			lua_getfield(L, -1, variableName.substr(prev_pos, pos - prev_pos).c_str());
			if (lua_isnil(L, -1)) {
				throw std::runtime_error(std::string("ScriptError: Could not find variable ") + variableName + std::string(". In file: ") + _filename);
			}

			// Switch last loaded variable on stack(the actual thing we wanted) with the table name level s down in the stack.
			int tableIndex = lua_gettop(L) - level;
			lua_replace(L, tableIndex);
			lua_settop(L, tableIndex);

		}

		
	}

	const void LuaScriptBack::_LoadGetKeysFunction(lua_State * L)
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

	std::vector<std::string> LuaScriptBack::GetTableKeys(const char * tableName)
	{
		lua_getglobal(_state, "getKeys"); // get function
		if (lua_isnil(_state, -1)) {
			printf("Get keys function is not loaded. Loading...\n");
			_LoadGetKeysFunction(_state);
			lua_getglobal(_state, "getKeys");
		}

		_GetToStack(_state, tableName);

		lua_pcall(_state, 1, 1, 0); // execute getKeys function.
							   // One parameter, one return
		lua_pushnil(_state);
		std::vector<std::string> keys;
		while (lua_next(_state, -2)) { // get values one by one
			if (lua_type(_state, -1) == LUA_TSTRING) { // check if key is a string
				keys.push_back(lua_tostring(_state, -1));
			}
			lua_pop(_state, 1);
		}

		lua_settop(_state, 0); // remove s table from stack 
		return keys;
	}


	

	LuaScriptBack::~LuaScriptBack()
	{

	}
}