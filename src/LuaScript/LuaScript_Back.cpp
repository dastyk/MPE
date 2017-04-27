#include "LuaScript_Back.h"
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
	LuaScript_Back::LuaScript_Back(const char* filename) : _filename(filename) , _data(nullptr), _state(nullptr)
	{
		StartProfile;
		LuaHelpers::LoadScript(_state, filename);
		/*
		auto ref = getGlobal(L, "player");
		for (int i = 0; i < ref.length(); i++)
		{

		}*/

		LuaHelpers::RegisterClass<LuaScript_Back>(_state, &LuaScript_Back::Create);


		StopProfile;
	}





	

	LuaScript_Back::~LuaScript_Back()
	{
		StartProfile;
		delete _data;
		lua_close(_state);
		StopProfile;
	}
	LuaTable * LuaScript_Back::GetTable(const char * tableName)
	{
		StartProfile;
		if (!_data) _data = new LuaTable_Back(_state, tableName);
		ProfileReturn(_data);
	}
	const void LuaScript_Back::LoadScript(const char * filename)
	{
		StartProfile;
		LuaHelpers::LoadScript(_state, filename);
		StopProfile;
	}
}