#include "LuaScript.h"
#include  <stdexcept>

#include <Profiler.h>

#ifdef _DEBUG
#pragma comment(lib, "ProfilerD.lib")
#else
#pragma comment(lib, "Profiler.lib")
#endif
namespace MPE
{
	using namespace luabridge;
	LuaScript::LuaScript(const char* filename) : _filename(filename) , _data(nullptr), _state(nullptr)
	{
		StartProfile;
		LuaHelpers::LoadScript(_state, filename);
		/*
		auto ref = getGlobal(L, "player");
		for (int i = 0; i < ref.length(); i++)
		{

		}*/
		StopProfile;
	}





	

	LuaScript::~LuaScript()
	{
		StartProfile;
		delete _data;
		lua_close(_state);
		StopProfile;
	}
	LuaTable * LuaScript::GetTable(const char * tableName)
	{
		StartProfile;
		if (!_data) _data = new LuaScript(_state, tableName);
		ProfileReturn(_data);
	}
	const void LuaScript::LoadScript(const char * filename)
	{
		StartProfile;
		LuaHelpers::LoadScript(_state, filename);
		StopProfile;
	}
}