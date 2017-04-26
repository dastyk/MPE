#include "LuaTable_Back.h"

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif
namespace MPE
{
	using namespace luabridge;
	LuaTable_Back::LuaTable_Back(lua_State* L, const char* key, const char* parentKey) : _state(L), _ref(nullptr), _parentKey(parentKey), _key(key)
	{
		StartProfile;
		_keys = LuaHelpers::GetTableKeys(L, (_parentKey + _key).c_str());
		_ref = new LuaRef( getGlobal(L, key));
		StopProfile;

	}

	LuaTable_Back::LuaTable_Back(luabridge::lua_State * L, luabridge::LuaRef * ref, const char * key, const char * parentKey) : _state(L), _ref(nullptr), _parentKey(parentKey), _key(key)
	{
		StartProfile;
		_keys = LuaHelpers::GetTableKeys(L, (_parentKey + _key).c_str());
		_ref = new LuaRef((*ref)[key]);
		StopProfile;
	}


	LuaTable_Back::~LuaTable_Back()
	{
		StartProfile;
		for (auto t : _tables)
			delete t.second;
		delete _ref;
		StopProfile
	}

	const std::vector<std::string>& LuaTable_Back::GetKeys() const
	{
		return _keys;
	}

	LuaTable * LuaTable_Back::GetTable(const char * tableName)
	{
		StartProfile;
		auto find = _tables.find(tableName);
		auto& table = _tables[tableName];
		if (find == _tables.end())
		{
			table = new LuaTable_Back(_state, _ref, tableName, (_parentKey + _key + ".").c_str());
		}
		ProfileReturn( table);
	}
}